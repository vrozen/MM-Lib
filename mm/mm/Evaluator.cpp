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
#include "Declaration.h"
#include "Definition.h"
#include "Instance.h"
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
#include "Evaluator.h"
#include "Machine.h"

MM::Evaluator::Evaluator(MM::Machine * m) : MM::Recyclable()
{
  this->m = m;
  pullAllWork = new MM::Vector<MM::Evaluator::NodeInstance *>();
  pullAnyWork = new MM::Vector<MM::Evaluator::NodeInstance *>();
  pushAllWork = new MM::Vector<MM::Evaluator::NodeInstance *>();
  pushAnyWork = new MM::Vector<MM::Evaluator::NodeInstance *>();
}

MM::Evaluator::~Evaluator()
{
  delete pullAllWork;
  delete pullAnyWork;
  delete pushAllWork;
  delete pushAnyWork;
}

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


MM::Evaluator::NodeInstance::NodeInstance(MM::Instance * instance,
                                          MM::Node * node)
{
  this->instance = instance;
  this->node = node;
}

MM::Evaluator::NodeInstance::~NodeInstance()
{
}

MM::Instance * MM::Evaluator::NodeInstance::getInstance()
{
  return instance;
}

MM::Node * MM::Evaluator::NodeInstance::getNode()
{
  return node;
}

MM::Transition * MM::Evaluator::step()
{
  MM::Reflector * r = m->getReflector();
  MM::Instance * i = r->getInstance();
  MM::Transition * t = m->createTransition();
  prepare(i);
  stepLevel(t, pullAllWork);
  stepLevel(t, pullAnyWork);
  stepLevel(t, pushAllWork);
  stepLevel(t, pushAnyWork);
  finalize(i);
  return t;
}

MM::VOID MM::Evaluator::prepare(MM::Instance * instance)
{
  MM::Definition * def = instance->getDefinition();
  MM::Vector<Node *> * pullAllNodes = def->getPullAllNodes();
  MM::Vector<Node *> * pullAnyNodes = def->getPullAnyNodes();
  MM::Vector<Node *> * pushAllNodes = def->getPushAllNodes();
  MM::Vector<Node *> * pushAnyNodes = def->getPushAnyNodes();
    
  instance->begin();

  MM::Vector<Node *>::Iterator pullAllIter = pullAllNodes->getIterator();
  while(pullAllIter.hasNext() == MM_TRUE)
  {
    MM::Node * node = pullAllIter.getNext();
    if(instance->isActive(node) == MM_TRUE)
    {
      MM::Evaluator::NodeInstance * ni = new NodeInstance(instance, node);
      pullAllWork->add(ni);
    }
  }

  MM::Vector<Node *>::Iterator pullAnyIter = pullAnyNodes->getIterator();
  while(pullAnyIter.hasNext() == MM_TRUE)
  {
    MM::Node * node = pullAnyIter.getNext();
    if(instance->isActive(node) == MM_TRUE)
    {
      MM::Evaluator::NodeInstance * ni = new NodeInstance(instance, node);
      pullAnyWork->add(ni);
    }
  }
  
  MM::Vector<Node *>::Iterator pushAllIter = pushAllNodes->getIterator();
  while(pushAllIter.hasNext() == MM_TRUE)
  {
    MM::Node * node = pushAllIter.getNext();
    if(instance->isActive(node) == MM_TRUE)
    {
      MM::Evaluator::NodeInstance * ni = new NodeInstance(instance, node);
      pushAllWork->add(ni);
    }
  }
  
  MM::Vector<Node *>::Iterator pushAnyIter = pushAnyNodes->getIterator();
  while(pushAnyIter.hasNext() == MM_TRUE)
  {
    MM::Node * node = pushAnyIter.getNext();
    if(instance->isActive(node) == MM_TRUE)
    {
      MM::Evaluator::NodeInstance * ni = new NodeInstance(instance, node);
      pushAnyWork->add(ni);
    }
  }
  
  MM::Map<MM::Declaration *, MM::Instance *> * instances =
    instance->getInstances();
  MM::Map<MM::Declaration *, MM::Instance *>::Iterator instanceIter =
    instances->getIterator();

  while(instanceIter.hasNext() == MM_TRUE)
  {
    MM::Instance * iChild = instanceIter.getNext();
    prepare(iChild);
  }
}

MM::VOID MM::Evaluator::finalize(MM::Instance * instance)
{
  MM::Map<MM::Declaration *, MM::Instance *> * instances =
  instance->getInstances();
  MM::Map<MM::Declaration *, MM::Instance *>::Iterator instanceIter =
  instances->getIterator();

  instance->commit();
  
  while(instanceIter.hasNext() == MM_TRUE)
  {
    MM::Instance * iChild = instanceIter.getNext();
    finalize(iChild);
  }
}

//process a set of instance nodes
MM::VOID MM::Evaluator::stepLevel(MM::Transition * t,
                                  MM::Vector<MM::Evaluator::NodeInstance*> * work)
{
  printf("STEP LEVEL (%ld nodes)\n", work->size());

  MM::UINT32 size = work->size();
  while(size != 0)
  {
    MM::UINT32 randomPos = rand() % size;
    MM::Evaluator::NodeInstance * ni = work->elementAt(randomPos);
    work->remove(ni);
    MM::Instance * instance = ni->getInstance();
    MM::Node * node = ni->getNode();
    stepNode(t, instance, node);
    size = work->size();
  }
}

//process an instance node
MM::VOID MM::Evaluator::stepNode(MM::Transition * t,
                                 MM::Instance * i,
                                 MM::Node * node)
{
  MM::Vector<MM::Edge *> * work = MM_NULL;
  MM::NodeBehavior * behavior = node->getBehavior();
  printf("STEP NODE %ld %s\n", (MM::UINT32)i, node->getName()->getBuffer());
  
  if(behavior->getAct() == MM::NodeBehavior::ACT_PULL)
  {
    work = node->getInput();
  }
  else
  {
    work = node->getOutput();
  }
  
  if(behavior->getHow() == MM::NodeBehavior::HOW_ANY)
  {
    stepNodeAny(t, i, node, work);
  }
  else
  {
    stepNodeAll(t, i, node, work);
  }
}

//process an all instance node
MM::VOID MM::Evaluator::stepNodeAll(MM::Transition * tr,
                                    MM::Instance * i,
                                    MM::Node * node,
                                    MM::Vector<Edge *> * work)
{
  MM::Vector<Edge *>::Iterator edgeIter = work->getIterator();
  bool success = true;
  printf("STEP ALL NODE %s (%ld edges)\n",
         node->getName()->getBuffer(),
         work->size());
  
  
  while(edgeIter.hasNext() == MM_TRUE)
  {
    Edge * edge = edgeIter.getNext();
    MM::Exp * exp = edge->getExp();
    MM::ValExp * valExp = eval(exp, i, edge);
    MM::INT32 flow = 0;
    if(valExp->getTypeId() == MM::T_NumberValExp)
    {
      flow = ((NumberValExp *) valExp)->getIntValue();
    }
    else if(valExp->getTypeId() == MM::T_RangeValExp)
    {
      flow = ((RangeValExp *) valExp)->getIntValue();
    }
    
    Node * src = edge->getSource();
    Node * tgt = edge->getTarget();
    
    //TODO: evaluate flow amount
    
    if(flow > 0 &&
       i->hasResources(src,flow) &&
       i->hasCapacity(tgt,flow))
    {
      i->sub(src, flow);
      i->add(tgt, flow);
      MM::FlowEdge * edge = synthesizeFlowEdge(i, src, flow, tgt);
      tr->addElement(edge);
      
      //tr->addElement(element);
      //tr->add(new FlowEvent(src,flow,tgt));
    }
    else
    {
      success = false;
      break;
    }
  }
  
  if(!success)
  {
    //FIXME
    //tr->back();
    //tr->clear();
  }
  
  //return tr;
}

MM::FlowEdge * MM::Evaluator::synthesizeFlowEdge(MM::Instance * i,
                                                 MM::Node * src,
                                                 MM::UINT32 flow,
                                                 MM::Node * tgt)
{
  MM::Name * srcName = src->getName();
  MM::Name * tgtName = tgt->getName();
  
  MM::Name * edgeName = MM_NULL;
  MM::Name * curName = MM_NULL;
  MM::Instance * curInstance = i;
  
  while(curInstance != MM_NULL)
  {
    if(curInstance->getParent() != MM_NULL)
    {
      curName = curInstance->getName();
      MM::Name * name = m->createName(curName);
      name->setName(edgeName);
      edgeName = name;
    }    
    curInstance = curInstance->getParent();
  }
  
  MM::Name * srcName2 = m->createName(srcName);
  MM::Name * tgtName2 = m->createName(tgtName);
  MM::Exp * exp = m->createNumberValExp(flow * 100);
  MM::FlowEdge * edge = m->createFlowEdge(edgeName, srcName2, exp, tgtName2);
  return edge;
}

//process an any instance node
MM::VOID MM::Evaluator::stepNodeAny(MM::Transition * tr,
                                    MM::Instance * i,
                                    MM::Node * node,
                                    MM::Vector<Edge *> * work)
{
  MM::Vector<Edge *>::Iterator edgeIter = work->getIterator();
  //FIXME random
  printf("STEP ANY NODE %s (%ld edges)\n",
         node->getName()->getBuffer(),
         work->size());

  while(edgeIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = edgeIter.getNext();
    MM::Exp * exp = edge->getExp();
    MM::ValExp * valExp = eval(exp, i, edge);
    
    MM::INT32 flow = 0;
    
    if(valExp->getTypeId() == MM::T_NumberValExp)
    {
      flow = ((NumberValExp *) valExp)->getIntValue();
    }
    else if(valExp->getTypeId() == MM::T_RangeValExp)
    {
      flow = ((RangeValExp *) valExp)->getIntValue();
    }
    
    valExp->recycle(m);
    
    Node * src = edge->getSource();
    Node * tgt = edge->getTarget();
    
    //TODO: evaluate flow amount
    
    if(flow > 0 &&
       i->hasResources(src,1) == MM_TRUE &&
       i->hasCapacity(tgt,1) == MM_TRUE)
    {
      if(i->hasResources(src, flow) == MM_TRUE)
      {
        if(i->hasCapacity(tgt, flow) == MM_TRUE)
        {
          printf("Full flow %ld\n", flow);
          i->sub(src,flow);
          i->add(tgt,flow);
          MM::FlowEdge * edge = synthesizeFlowEdge(i, src, flow, tgt);
          tr->addElement(edge);
        }
        else
        {
          flow = i->getCapacity(tgt);
          printf("Flow up to capacity %ld\n", flow);
          i->sub(src, flow);
          i->add(tgt, flow);
          MM::FlowEdge * edge = synthesizeFlowEdge(i, src, flow, tgt);
          tr->addElement(edge);
        }
      }
      else
      {
        flow = i->getResources(src);
        if(i->hasCapacity(tgt,flow) == MM_TRUE)
        {
          printf("Flow up to availability %ld\n", flow);
          i->sub(src, flow);
          i->add(tgt, flow);
          MM::FlowEdge * edge = synthesizeFlowEdge(i, src, flow, tgt);
          tr->addElement(edge);

        }
        else
        {
          flow = i->getCapacity(tgt);
          printf("Flow up to capacity %ld\n", flow);
          i->sub(src,flow);
          i->add(tgt,flow);
          MM::FlowEdge * edge = synthesizeFlowEdge(i, src, flow, tgt);
          tr->addElement(edge);
        }
      }
    }
  }
}




MM::BOOLEAN MM::Evaluator::isSatisfied(MM::Instance * i,
                                       MM::Node *,
                                       MM::Transition * t)
{
  //calculate which node's inputs are 'satisfied'
  //this set is the set of node labels for which all flow edges they operate on are satisfied at the same time
  //this semantics is a bit strange since we also have the 'all' and 'any' modifiers
  //therefore we might expect any nodes to trigger when any flow is satisfied, but this is not true!
  
  //satisfied nodes are
  //1. pulling nodes
  //either each inflow is satisfied and it has inflow
  //or the node has no inflow and it is active (auto or activated)
  //2. pushing nodes
  //either each outflow is satisfied and it has outflow
  //or the node has no outflow and it is active (auto or activated)

    MM::BOOLEAN satisfied = MM_TRUE;
  /*
  
  if(act == MM::Node::ACT_PULL)
  {
    if(input->isEmpty() == MM_TRUE)
    {
      satisfied = this->isActive(i);
    }
    else
    {
      MM::Vector<Edge *>::Iterator fIter = input->getIterator();
      while(fIter.hasNext())
      {
        Edge * edge = fIter.getNext();
        Node * src = edge->getSource();
        Node * tgt = edge->getTarget();
        ValExp * val = 0; //FIXME: edge->getExp()->eval(m, i, edge);
        //FlowEvent * flow = t->getFlow(i, src, tgt);
        //UINT32 amount = flow->getAmount();
        
        //if(flow != MM_NULL)
        //{
        //satisfied = val->greaterEquals(amount);
        //}
        //else
        //{
        // satisfied = MM_FALSE;
        // }
      }
    }
  }
  else if(act == ACT_PUSH)
  {
    MM::Vector<Edge *>::Iterator iter = input->getIterator();
    
    while(iter.hasNext())
    {
      Edge * edge = iter.getNext();
      
      //if(!edge->isSatisfied(instance, transition))
      //{
      // satisified = MM_FALSE;
      //}
    }
  }
  else
  {
    //error
  }
  */
  return satisfied;
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
  return m->createNumberValExp(100);
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
  return m->createRangeValExp(1, exp->getMax());
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
  return m->createBooleanValExp(exp->getValue());
}

MM::ValExp * MM::Evaluator::eval(MM::NumberValExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  return m->createNumberValExp(exp->getValue());
}

MM::ValExp * MM::Evaluator::eval(MM::RangeValExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  return m->createRangeValExp(exp->getMin(), exp->getMax());
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
  
  return m->createBooleanValExp(valr);
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
  
  return m->createBooleanValExp(valr);
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
  
  return m->createBooleanValExp(valr);
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
  
  return m->createBooleanValExp(valr);
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
      r = m->createBooleanValExp(rbval);
      break;
    case MM::T_NumberValExp:
      r = m->createNumberValExp(rnval);
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
      r = m->createBooleanValExp(rbval);
      break;
    }
    case MM::T_RangeValExp:
    {
      r = m->createRangeValExp(rrmin, rrmax);
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
  
  return m->createBooleanValExp(valr);
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
      r = m->createBooleanValExp(rbval);
      break;
    }
    case MM::T_RangeValExp:
    {
      r = m->createRangeValExp(rrmin, rrmax);
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
  
  return m->createBooleanValExp(valr);
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
  
  return m->createBooleanValExp(valr);
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
  
  return m->createNumberValExp(nvalr);
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

