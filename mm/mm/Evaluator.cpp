//
//  Evaluator.cpp
//  mm
//
//  Created by Riemer van Rozen on 9/26/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Map.h"
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Pair.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "Assertion.h"
#include "Deletion.h"
#include "Signal.h"
#include "Edge.h"
#include "StateEdge.h"
#include "FlowEdge.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "Transformation.h"
#include "Modification.h"
#include "Transition.h"
#include "Program.h"
#include "PoolNodeBehavior.h"
#include "SourceNodeBehavior.h"
#include "DrainNodeBehavior.h"
#include "RefNodeBehavior.h"
#include "Observer.h"
#include "Observable.h"
#include "Instance.h"
#include "Declaration.h"
#include "Definition.h"
#include "Operator.h"
#include "ValExp.h"
#include "UnExp.h"
#include "BinExp.h"
#include "RangeValExp.h"
#include "BooleanValExp.h"
#include "NumberValExp.h"
#include "OverrideExp.h"
#include "ActiveExp.h"
#include "AllExp.h"
#include "DieExp.h"
#include "AliasExp.h"
#include "OneExp.h"
#include "VarExp.h"
#include "Reflector.h"
#include "Machine.h"
#include "Evaluator.h"


MM::TID MM::Evaluator::getTypeId()
{
  return MM::T_Evaluator;
}

MM::BOOLEAN MM::Evaluator::instanceof(MM::TID tid)
{
  if(tid == MM::T_Evaluator)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

//C++ does not support runtime type matching
//I am helping it by doing it manually...
//breaking several of the highly praised OO laws
//for now, I decline to use a double dispatch method
MM::ValExp * MM::Evaluator::eval(MM::Exp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  switch(exp->getTypeId())
  {
    case MM::T_OneExp:
    {
      return eval((MM::OneExp *) exp, i, e);
    }
    case MM::T_ActiveExp:
    {
      return eval((MM::ActiveExp *) exp, i, e);
    }
    case MM::T_DieExp:
    {
      return eval((MM::DieExp *) exp, i, e);
    }
    case MM::T_OverrideExp:
    {
      return eval((MM::OverrideExp *) exp, i, e);
    }
    case MM::T_VarExp:
    {
      return eval((MM::VarExp *) exp, i, e);
    }
    case MM::T_AllExp:
    {
      return eval((MM::AllExp *) exp, i, e);
    }
    case MM::T_BinExp:
    {
      return eval((MM::BinExp *) exp, i, e);
    }
    case MM::T_UnExp:
    {
      return eval((MM::UnExp *) exp, i, e);
    }
    case MM::T_NumberValExp:
    {
      return eval((MM::NumberValExp *) exp, i, e);
    }
    case MM::T_BooleanValExp:
    {
      return eval((MM::BooleanValExp *) exp, i, e);
    }
    case MM::T_RangeValExp:
    {
      return eval((MM::RangeValExp *) exp, i, e);
    }
    default:
    {
      //TODO: throw EvaluatorException
      printf("missing case in eval\n");
      return MM_NULL;
    }
  }
}

MM::ValExp * MM::Evaluator::eval(MM::OneExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  return m->createNumberValExp(1, MM_NULL);
}


MM::ValExp * MM::Evaluator::eval(MM::ActiveExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  //MM::Name * id = exp->getId();
  //MM::BOOLEAN val = i->isActive(id);
  //return m->createBooleanValExp(val, MM_NULL);
  return MM_NULL;
}

MM::ValExp * MM::Evaluator::eval(MM::DieExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  return m->createRangeValExp(1, MM_NULL, MM_NULL, exp->getMax(), MM_NULL);
}

MM::ValExp * MM::Evaluator::eval(MM::OverrideExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  return eval((MM::Exp*)exp->getExp(), i, e);
}

MM::ValExp * MM::Evaluator::eval(MM::VarExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  //TODO: return the NumberValExp representing the value of the pool
  //Node * node = exp->getReference();  
  //MM::INT32 val = i->getValue(node);
  //return m->createNumberValExp(rnval, MM_NULL);
  return MM_NULL;
}

MM::ValExp * MM::Evaluator::eval(MM::AllExp exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  //TODO: return the NumberValExp representing the value of the pool
  //Node * node = e->getSource();
  //MM::INT32 val = i->getValue(node);
  //return m->createNumberValExp(rnval, MM_NULL);
  return MM_NULL;
}

MM::ValExp * MM::Evaluator::eval(MM::BinExp * exp,
                                 MM::Instance *i,
                                 MM::Edge * e)
{
  MM::ValExp * r  = MM_NULL;
  MM::ValExp * v1 = eval(exp->getLhsExp(), i, e);
  MM::ValExp * v2 = eval(exp->getRhsExp(), i, e);
    
  r = eval(v1, exp->getOperator(), v2, i, e);
  
  v1->recycle(m);
  v2->recycle(m);
  return r;
}

MM::ValExp * MM::Evaluator::eval(MM::UnExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  MM::ValExp * r = MM_NULL;
  MM::ValExp * v = eval((MM::Exp*)exp->getExp(), i, e);
  
  r = eval(exp->getOperator(), v, i, e);
  
  v->recycle(m);  
  return r;
}

MM::ValExp * MM::Evaluator::eval(MM::BooleanValExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  return m->createBooleanValExp(exp->getValue(), MM_NULL);
}

MM::ValExp * MM::Evaluator::eval(MM::NumberValExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  return m->createNumberValExp(exp->getValue(), MM_NULL);
}

MM::ValExp * MM::Evaluator::eval(MM::RangeValExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  return m->createRangeValExp(exp->getMin(),
                              MM_NULL, MM_NULL, exp->getMax(), MM_NULL);
}


//------------------------------------------------------------
//BinExp Visitor
//------------------------------------------------------------
MM::ValExp * MM::Evaluator::eval(MM::ValExp * e1,
                                 MM::Operator::OP op,
                                 MM::ValExp * e2,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  switch(e1->getTypeId())
  {
    case MM::T_BooleanValExp:
    {
      switch(e2->getTypeId())
      {
        case MM::T_BooleanValExp:
        {
          return eval((MM::BooleanValExp *) e1, op, (MM::BooleanValExp *) e2, i, e);
        }
        case MM::T_NumberValExp:
        {
          return eval((MM::BooleanValExp *) e1, op, (MM::NumberValExp *) e2, i, e);
        }
        case MM::T_RangeValExp:
        {
          return eval((MM::BooleanValExp *) e1, op, (MM::RangeValExp *) e2, i, e);
        }
        default:
        {
          //TODO: throw EvaluatorException
          printf("missing case in eval\n");
          return MM_NULL;
        }
      }
    }
    case MM::T_NumberValExp:
    {
      switch(e2->getTypeId())
      {
        case MM::T_BooleanValExp:
        {
          return eval((MM::NumberValExp *) e1, op, (MM::BooleanValExp *) e2, i, e);
        }
        case MM::T_NumberValExp:
        {
          return eval((MM::NumberValExp *) e1, op, (MM::NumberValExp *) e2, i, e);
        }
        case MM::T_RangeValExp:
        {
          return eval((MM::NumberValExp *) e1, op, (MM::RangeValExp *) e2, i, e);
        }
        default:
        {
          //TODO: throw EvaluatorException
          printf("missing case in eval\n");
          return MM_NULL;
        }
      }
    }
    case MM::T_RangeValExp:
    {
      switch(e2->getTypeId())
      {
        case MM::T_BooleanValExp:
        {
          return eval((MM::RangeValExp *) e1, op, (MM::BooleanValExp *) e2, i, e);
        }
        case MM::T_NumberValExp:
        {
          return eval((MM::RangeValExp *) e1, op, (MM::NumberValExp *) e2, i, e);
        }
        case MM::T_RangeValExp:
        {
          return eval((MM::RangeValExp *) e1, op, (MM::RangeValExp *) e2, i, e);
        }
        default:
        {
          //TODO: throw EvaluatorException
          printf("missing case in eval\n");
          return MM_NULL;
        }
      }
    }
    default:
    {
      //TODO: throw EvaluatorException
      printf("missing case in eval\n");
      return MM_NULL;
    }
  }
}

MM::ValExp * MM::Evaluator::eval(MM::BooleanValExp * e1,
                                 MM::Operator::OP op,
                                 MM::BooleanValExp * e2,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  MM::BOOLEAN val1 = e1->getValue();
  MM::BOOLEAN val2 = e2->getValue();
  MM::BOOLEAN valr = MM_FALSE;
  
  switch(op)
  {
    case MM::Operator::OP_AND:
    {
      if(val1 == MM_TRUE && val2 == MM_TRUE)
      {
        valr = MM_TRUE;
      }
      else
      {
        valr = MM_FALSE;
      }
      break;
    }
    case MM::Operator::OP_OR:
    {
      if(val1 == MM_TRUE || val2 == MM_TRUE)
      {
        valr = MM_TRUE;
      }
      else
      {
        valr = MM_FALSE;
      }
      break;
    }
    case MM::Operator::OP_EQ:
    {
      if(val1 == val2)
      {
        valr = MM_TRUE;
      }
      else
      {
        valr = MM_FALSE;
      }
      break;
    }
    case MM::Operator::OP_NEQ:
    {
      if(val1 != val2)
      {
        valr = MM_TRUE;
      }
      else
      {
        valr = MM_FALSE;
      }
      break;
    }
    default:
    {
      //TODO: throw EvaluatorException
      printf("unknown operator on boolean");
      break;
    }
  }
  
  return m->createBooleanValExp(valr, MM_NULL);
}

MM::ValExp * MM::Evaluator::eval(MM::BooleanValExp * e1,
                                 MM::Operator::OP op,
                                 MM::NumberValExp * e2,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  MM::BOOLEAN valr = MM_FALSE;
  
  switch(op)
  {
    case MM::Operator::OP_EQ:
    {
      valr = MM_FALSE;
      break;
    }
    case MM::Operator::OP_NEQ:
    {
      valr = MM_TRUE;
      break;
    }
    default:
    {
      //TODO: throw EvaluatorException
      printf("unknown operator on boolean");
      break;
    }
  }
  
  return m->createBooleanValExp(valr, MM_NULL);
}

MM::ValExp * MM::Evaluator::eval(MM::BooleanValExp * e1,
                                 MM::Operator::OP op,
                                 MM::RangeValExp * e2,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  MM::BOOLEAN valr = MM_FALSE;
  
  switch(op)
  {
    case MM::Operator::OP_EQ:
    {
      valr = MM_FALSE;
      break;
    }
    case MM::Operator::OP_NEQ:
    {
      valr = MM_TRUE;
      break;
    }
    default:
    {
      //TODO: throw EvaluatorException
      printf("unknown operator on boolean");
      break;
    }
  }
  
  return m->createBooleanValExp(valr, MM_NULL);
}

MM::ValExp * MM::Evaluator::eval(MM::NumberValExp * e1,
                                 MM::Operator::OP op,
                                 MM::BooleanValExp * e2,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  MM::BOOLEAN valr = MM_FALSE;
  
  switch(op)
  {
    case MM::Operator::OP_EQ:
    {
      valr = MM_FALSE;
      break;
    }
    case MM::Operator::OP_NEQ:
    {
      valr = MM_TRUE;
      break;
    }
    default:
    {
      //TODO: throw EvaluatorException
      printf("unknown operator on boolean");
      break;
    }
  }
  
  return m->createBooleanValExp(valr, MM_NULL);
}

MM::ValExp * MM::Evaluator::eval(MM::NumberValExp * e1,
                                 MM::Operator::OP op,
                                 MM::NumberValExp * e2,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  MM::ValExp * r = 0;
  MM::INT32   val1  = e1->getValue();
  MM::INT32   val2  = e2->getValue();
  MM::TID     rtype = MM::T_NULL;
  MM::INT32   rnval = 0;
  MM::BOOLEAN rbval = MM_FALSE;
  
  switch(op)
  {
    case MM::Operator::OP_ADD:
    {
      rnval = val1 + val2;
      rtype = MM::T_NumberValExp;
      break;
    }
    case MM::Operator::OP_SUB:
    {
      rnval = val1 - val2;
      rtype = MM::T_NumberValExp;
      break;
    }
    case MM::Operator::OP_MUL:
    {
      rnval = (val1 * val2) / 100;
      rtype = MM::T_NumberValExp;
      break;
    }
    case MM::Operator::OP_DIV:
    {
      rnval = (val1 * 100) / val2;
      rtype = MM::T_NumberValExp;
      break;
    }
    case MM::Operator::OP_EQ:
    {
      if(val1 == val2)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_NEQ:
    {
      if(val1 != val2)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_GT:
    {
      if(val1 > val2)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_LT:
    {
      if(val1 < val2)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_LE:
    {
      if(val1 <= val2)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_GE:
    {
      if(val1 >= val2)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    default:
    {
      //todo: exception
      break;
    }
  }
  
  switch(rtype)
  {
    case MM::T_BooleanValExp:
      r = m->createBooleanValExp(rbval, MM_NULL);
      break;
    case MM::T_NumberValExp:
      r = m->createNumberValExp(rnval, MM_NULL);
      break;
    default:
      break;
  }
  
  return r;
}

MM::ValExp * MM::Evaluator::eval(MM::NumberValExp * e1,
                                 MM::Operator::OP op,
                                 MM::RangeValExp * e2,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  MM::ValExp * r = 0;
  MM::TID    rtype = MM::T_NULL;
  MM::UINT32 rrmin = 0;
  MM::UINT32 rrmax = 0;
  MM::UINT32 min = e2->getMin();
  MM::UINT32 max = e2->getMax();
  MM::INT32 val = e1->getIntValue();
  MM::BOOLEAN rbval = MM_FALSE;
  
  switch(op)
  {
    case MM::Operator::OP_ADD:
    {
      rrmin = val + min;
      rrmax = val + max;
      rtype = MM::T_RangeValExp;
      break;
    }
    case MM::Operator::OP_SUB:
    {
      rrmin = val - min;
      rrmax = val - max;
      rtype = MM::T_RangeValExp;
      break;
    }
    case MM::Operator::OP_MUL:
    {
      rrmin = val * min;
      rrmax = val * max;
      rtype = MM::T_RangeValExp;
      break;
    }
    case MM::Operator::OP_DIV:
    {
      rrmin = val / min;
      rrmax = val / max;
      rtype = MM::T_RangeValExp;
      break;
    }
    case MM::Operator::OP_EQ:
    {
      rbval = MM_FALSE;
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_NEQ:
    {
      rbval = MM_TRUE;
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_GT:
    {
      if(val > max)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_LT:
    {
      if(val < min)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_LE:
    {
      if(val <= min)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_GE:
    {
      if(val >= max)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    default:
    {
      //TODO: operand error
      break;
    }
  }
  
  switch(rtype)
  {
    case MM::T_BooleanValExp:
    {
      //r = new MM::BooleanValExp(rbval);
      r = m->createBooleanValExp(rbval, MM_NULL);
      break;
    }
    case MM::T_RangeValExp:
    {
      r = m->createRangeValExp(rrmin, MM_NULL, MM_NULL, rrmax, MM_NULL);
      break;
    }
    default:
    {
      //TODO: return type error
      break;
    }
  }
  
  return r;
}

MM::ValExp *  MM::Evaluator::eval(MM::RangeValExp * e1,
                                  MM::Operator::OP op,
                                  MM::BooleanValExp * e2,
                                  MM::Instance * i,
                                  MM::Edge * e)
{
  MM::BOOLEAN valr = MM_FALSE;
  
  switch(op)
  {
    case MM::Operator::OP_EQ:
    {
      valr = MM_FALSE;
      break;
    }
    case MM::Operator::OP_NEQ:
    {
      valr = MM_TRUE;
      break;
    }
    default:
    {
      //TODO: throw EvaluatorException
      printf("unknown operator on boolean");
      break;
    }
  }
  
  return m->createBooleanValExp(valr, MM_NULL);
}


MM::ValExp * MM::Evaluator::eval(MM::RangeValExp * e1,
                                 MM::Operator::OP op,
                                 MM::NumberValExp * e2,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  MM::ValExp * r = MM_NULL;
  MM::TID    rtype = MM::T_NULL;
  MM::UINT32 rrmin = 0;
  MM::UINT32 rrmax = 0;
  MM::BOOLEAN rbval = MM_FALSE;
  MM::UINT32 min = e1->getMin();
  MM::UINT32 max = e1->getMax();
  MM::INT32 val = e2->getValue();
  
  switch(op)
  {
    case MM::Operator::OP_ADD:
    {
      rrmin = min + val;
      rrmax = max + val;
      rtype = MM::T_RangeValExp;
      break;
    }
    case MM::Operator::OP_SUB:
    {
      rrmin = min - val;
      rrmax = max - val;
      rtype = MM::T_RangeValExp;
      break;
    }
    case MM::Operator::OP_MUL:
    {
      rrmin = min * val;
      rrmax = max * val;
      rtype = MM::T_RangeValExp;
      break;
    }
    case MM::Operator::OP_DIV:
    {
      rrmin = min / val;
      rrmax = max / val;
      rtype = MM::T_RangeValExp;
      break;
    }
    case MM::Operator::OP_EQ:
    {
      rbval = MM_FALSE;
      rtype = MM::T_RangeValExp;
      break;
    }
    case MM::Operator::OP_NEQ:
    {
      rbval = MM_TRUE;
      rtype = MM::T_RangeValExp;
      break;
    }
    case MM::Operator::OP_GT:
    {
      if(min > val)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_LT:
    {
      if(max < val)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_LE:
    {
      if(max <= val)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    case MM::Operator::OP_GE:
    {
      if(min >= val)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::T_BooleanValExp;
      break;
    }
    default:
    {
      //todo: operand error
      break;
    }
  }
  
  switch(rtype)
  {
    case MM::T_BooleanValExp:
    {
      r = m->createBooleanValExp(rbval, MM_NULL);
      break;
    }
    case MM::T_RangeValExp:
    {
      r = m->createRangeValExp(rrmin, MM_NULL, MM_NULL, rrmax, MM_NULL);
      break;
    }
    default:
    {
      //TODO: return type error
      break;
    }
  }
  
  return r;
}

MM::ValExp *  MM::Evaluator::eval(MM::RangeValExp * e1,
                                  MM::Operator::OP op,
                                  MM::RangeValExp * e2,
                                  MM::Instance * i,
                                  MM::Edge * e)
{
  MM::BOOLEAN valr = MM_FALSE;
  
  switch(op)
  {
    case MM::Operator::OP_EQ:
    {
      valr = MM_FALSE;
      break;
    }
    case MM::Operator::OP_NEQ:
    {
      valr = MM_TRUE;
      break;
    }
    default:
    {
      //TODO: throw EvaluatorException
      printf("unknown operator on boolean");
      break;
    }
  }
  
  return m->createBooleanValExp(valr, MM_NULL);
}

//------------------------------------------------------------
//UnExp Visitor
//------------------------------------------------------------
MM::ValExp * MM::Evaluator::eval(MM::Operator::OP op,
                                 MM::ValExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  switch(exp->getTypeId())
  {
    case MM::T_BooleanValExp:
    {
      return eval((MM::BooleanValExp *) exp, i, e);
    }
    case MM::T_NumberValExp:
    {
      return eval((MM::NumberValExp *) exp, i, e);
    }
    case MM::T_RangeValExp:
    {
      return eval((MM::RangeValExp *) exp, i, e);
    }
    default:
    {
      //TODO: throw EvaluatorException
      printf("missing case in eval\n");
      return MM_NULL;
    }
  }
}

MM::ValExp * MM::Evaluator::eval(MM::Operator::OP op,
                                 MM::BooleanValExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  MM::BOOLEAN val = exp->getValue();
  MM::BOOLEAN valr = MM_FALSE;
  switch(op)
  {
    case MM::Operator::OP_NOT:
    {
      if(val == MM_FALSE)
      {
        valr = MM_TRUE;
      }
      else
      {
        valr = MM_FALSE;
      }
      break;
    }
    default:
    {
      //TODO: throw EvaluatorException
      printf("missing operator case in eval");
      break;
    }
  }
  
  return m->createBooleanValExp(valr, MM_NULL);
}

MM::ValExp * MM::Evaluator::eval(MM::Operator::OP op,
                                 MM::NumberValExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  MM::UINT32 val = exp->getValue();
  MM::UINT32 nvalr = 0;
  
  switch(op)
  {
    case MM::Operator::OP_UNM:
    {
      nvalr = -val;
      break;
    }
    default:
    {
      //TODO: throw EvaluatorException
      printf("missing operator case in eval");
      break;
    }
  }
  
  return m->createNumberValExp(nvalr, MM_NULL);
}

MM::ValExp * MM::Evaluator::eval(MM::Operator::OP op,
                                 MM::RangeValExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  //FIXME
  //Is there a valid unary operator on ranges?
  return MM_NULL;
}

