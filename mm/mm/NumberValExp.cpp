//
//  NumberValExp.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/19/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "Location.h"
#include "String.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "ValExp.h"
#include "BooleanValExp.h"
#include "RangeValExp.h"
#include "NumberValExp.h"

const MM::CHAR * MM::NumberValExp::DOT_STR = ".";
const MM::UINT32 MM::NumberValExp::DOT_LEN = 1;

MM::NumberValExp::NumberValExp(MM::INT32 val) : MM::ValExp()
{
  this->val = val * 100;
  this->loc = MM_NULL;
}

MM::NumberValExp::NumberValExp(MM::INT32 val,
                               MM::Location * loc) : MM::ValExp()
{
  this->val = val * 100;
  this->loc = loc;
}

MM::NumberValExp::NumberValExp(MM::INT32 val,
                               MM::UINT8 fraction) : MM::ValExp()
{
  this->val = (val * 100) + (fraction % 100);
  this->loc = MM_NULL;
}

MM::NumberValExp::NumberValExp(MM::INT32 val,
                               MM::UINT8 fraction,
                               MM::Location * loc) : MM::ValExp()
{
  this->val = val * 100 + (fraction %100);
  this->loc = loc;
}

MM::NumberValExp::~NumberValExp()
{
  if(loc != MM_NULL)
  {
    delete loc;
  }
}

MM::ValExp::TYPE MM::NumberValExp::getType()
{
  return MM::ValExp::T_NUMBER;
}

MM::INT32 MM::NumberValExp::getValue()
{
  return val;
}

MM::INT32 MM::NumberValExp::getIntValue()
{
  return val / 100;
}

MM::ValExp * MM::NumberValExp::eval()
{
  return new MM::NumberValExp(val/100, val%100);
}

MM::ValExp * MM::NumberValExp::eval(MM::Operator::OP op)
{
  MM::INT32 nvalr = 0;
  switch(op)
  {
    case MM::Operator::OP_UNM:
    {
      nvalr = -val;
      break;
    }
    default:
    {
      //todo: operand error
      break;
    }
  }
  return new MM::NumberValExp(nvalr);
}

MM::ValExp * MM::NumberValExp::eval(MM::Operator::OP op, MM::ValExp * v)
{
  switch(v->getType())
  {
    case MM::ValExp::T_NUMBER:
      return evalNumber(op, (MM::NumberValExp *) v);
      break;
    case MM::ValExp::T_RANGE:
      return evalRange(op, (MM::RangeValExp *)v);
      break;
    default:
      //todo: type error
      break;
  }
  return 0;
}

MM::ValExp * MM::NumberValExp::evalNumber(MM::Operator::OP op, MM::NumberValExp * v)
{
  MM::ValExp * r = 0;
  MM::INT32   val2  = v->getValue();
  MM::ValExp::TYPE rtype = MM::ValExp::T_ERROR;
  MM::INT32   rnval = 0;
  MM::BOOLEAN rbval = MM_FALSE;
  
  switch(op)
  {
    case MM::Operator::OP_ADD:
    {
      rnval = val + val2;
      rtype = MM::ValExp::T_NUMBER;
      break;
    }
    case MM::Operator::OP_SUB:
    {
      rnval = val - val2;
      rtype = MM::ValExp::T_NUMBER;
      break;
    }
    case MM::Operator::OP_MUL:
    {
      rnval = (val * val2) / 100;
      rtype = MM::ValExp::T_NUMBER;
      break;
    }
    case MM::Operator::OP_DIV:
    {
      rnval = (val * 100) / val2;
      rtype = MM::ValExp::T_NUMBER;
      break;
    }
    case MM::Operator::OP_EQ:
    {
      if(val == val2)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::ValExp::T_BOOLEAN;
      break;
    }
    case MM::Operator::OP_NEQ:
    {
      if(val != val2)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::ValExp::T_BOOLEAN;
      break;
    }
    case MM::Operator::OP_GT:
    {
      if(val > val2)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::ValExp::T_BOOLEAN;
      break;
    }
    case MM::Operator::OP_LT:
    {
      if(val < val2)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::ValExp::T_BOOLEAN;
      break;
    }
    case MM::Operator::OP_LE:
    {
      if(val <= val2)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::ValExp::T_BOOLEAN;
      break;
    }
    case MM::Operator::OP_GE:
    {
      if(val >= val2)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::ValExp::T_BOOLEAN;
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
    case MM::ValExp::T_BOOLEAN:
      r = new MM::BooleanValExp(rbval);
      break;
    case MM::ValExp::T_NUMBER:
      r = new MM::NumberValExp(rnval/100, rnval%100);
      break;
    default:
      break;
  }
  
  return r;
}

MM::ValExp * MM::NumberValExp::evalRange(MM::Operator::OP op, MM::RangeValExp * v)
{
  MM::ValExp * r = 0;
  MM::ValExp::TYPE rtype = T_ERROR;
  MM::UINT32 rrmin = 0;
  MM::UINT32 rrmax = 0;
  MM::UINT32 min = 0;
  MM::UINT32 max = 0;
  MM::INT32 val = getIntValue();
  MM::BOOLEAN rbval = MM_FALSE;
  
  if(v->getType() == MM::ValExp::T_NUMBER)
  {
    min = v->getMin();
    max = v->getMax();
  }
  else
  {
    //todo: type error
  }
  
  switch(op)
  {
    case MM::Operator::OP_ADD:
    {
      rrmin = val + min;
      rrmax = val + max;
      rtype = MM::ValExp::T_RANGE;
      break;
    }
    case MM::Operator::OP_SUB:
    {
      rrmin = val - min;
      rrmax = val - max;
      rtype = MM::ValExp::T_RANGE;
      break;
    }
    case MM::Operator::OP_MUL:
    {
      rrmin = val * min;
      rrmax = val * max;
      rtype = MM::ValExp::T_RANGE;
      break;
    }
    case MM::Operator::OP_DIV:
    {
      rrmin = val / min;
      rrmax = val / max;
      rtype = MM::ValExp::T_RANGE;
      break;
    }
    case MM::Operator::OP_EQ:
    {
      rbval = MM_FALSE;
      rtype = MM::ValExp::T_BOOLEAN;
      break;
    }
    case MM::Operator::OP_NEQ:
    {
      rbval = MM_TRUE;
      rtype = MM::ValExp::T_BOOLEAN;
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
      rtype = MM::ValExp::T_BOOLEAN;
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
      rtype = MM::ValExp::T_BOOLEAN;
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
      rtype = MM::ValExp::T_BOOLEAN;
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
      rtype = MM::ValExp::T_BOOLEAN;
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
    case MM::ValExp::T_BOOLEAN:
      r = new MM::BooleanValExp(rbval);
      break;
    case MM::ValExp::T_RANGE:
      r = new MM::RangeValExp(rrmin, rrmax);
      break;
    default:
      //todo: return type error
      break;
  }
  
  return r;
}

MM::Location *  MM::NumberValExp::getLocation()
{
  return loc;
}

MM::VOID MM::NumberValExp::toString(MM::String * buf)
{
  buf->append(val / 100);
  buf->append((MM::CHAR*)MM::NumberValExp::DOT_STR, MM::NumberValExp::DOT_LEN);
  buf->append(val % 100);
}

