//
//  SourceNode.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/11/13.
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
#include "Observer.h"
#include "Observable.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Transformation.h"
#include "Program.h"
#include "Modification.h"
#include "Transition.h"
#include "FlowEvent.h"
#include "Operator.h"
#include "Exp.h"
#include "Assertion.h"
#include "Deletion.h"
#include "Activation.h"
#include "Signal.h"
#include "Edge.h"
#include "StateEdge.h"
#include "FlowEdge.h"
#include "NodeWorkItem.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "PoolNodeBehavior.h"
#include "SourceNodeBehavior.h"
#include "DrainNodeBehavior.h"
#include "GateNodeBehavior.h"
#include "RefNodeBehavior.h"
#include "ConverterNodeBehavior.h"
#include "Declaration.h"
#include "InterfaceNode.h"
#include "Definition.h"
#include "Instance.h"
#include "Operator.h"
#include "ValExp.h"
#include "UnExp.h"
#include "BinExp.h"
#include "DieExp.h"
#include "RangeValExp.h"
#include "BooleanValExp.h"
#include "NumberValExp.h"
#include "OverrideExp.h"
#include "ActiveExp.h"
#include "AllExp.h"
#include "AliasExp.h"
#include "OneExp.h"
#include "VarExp.h"
#include "Reflector.h"
#include "Evaluator.h"
#include "Machine.h"

const MM::CHAR * MM::SourceNodeBehavior::SOURCE_STR  = "source";
const MM::UINT32  MM::SourceNodeBehavior::SOURCE_LEN =
  strlen(MM::SourceNodeBehavior::SOURCE_STR);

MM::SourceNodeBehavior::SourceNodeBehavior(MM::NodeBehavior::IO io,
                                           MM::NodeBehavior::When when):
  MM::NodeBehavior(io,
                   when,
                   MM::NodeBehavior::ACT_PUSH,
                   MM::NodeBehavior::HOW_ALL)
{
}

MM::SourceNodeBehavior::~SourceNodeBehavior()
{
}

MM::VOID MM::SourceNodeBehavior::recycle(MM::Recycler *r)
{
  this->MM::NodeBehavior::recycle(r);
}

MM::TID MM::SourceNodeBehavior::getTypeId()
{
  return MM::T_SourceNodeBehavior;
}

MM::BOOLEAN MM::SourceNodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_SourceNodeBehavior)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::NodeBehavior::instanceof(tid);
  }
}

MM::UINT32 MM::SourceNodeBehavior::getCreateMessage()
{
  return MM::MSG_NEW_SOURCE;
}

MM::UINT32 MM::SourceNodeBehavior::getUpdateMessage()
{
  return MM::MSG_UPD_SOURCE;
}

MM::UINT32 MM::SourceNodeBehavior::getDeleteMessage()
{
  return MM::MSG_DEL_SOURCE;
}

MM::VOID MM::SourceNodeBehavior::stepPullAny(MM::Node * tgtNode,
                                             MM::Instance * tgtInstance,
                                             MM::Vector<MM::NodeWorkItem *> * work,
                                             MM::Machine * m,
                                             MM::Transition * tr)
{
  //sources don't pull
}


MM::VOID MM::SourceNodeBehavior::stepPullAll(MM::Node * tgtNode,
                                             MM::Instance * tgtInstance,
                                             MM::Vector<MM::NodeWorkItem *> * work,
                                             MM::Machine * m,
                                             MM::Transition * tr)
{
  //sources don't pull
}

MM::VOID MM::SourceNodeBehavior::stepPushAll(MM::Node * srcNode,
                                             MM::Instance * srcInstance,
                                             MM::Vector<MM::NodeWorkItem *> * work,
                                             MM::Machine * m,
                                             MM::Transition * tr)
{
  MM::Evaluator * evaluator = m->getEvaluator();
  
  MM::Vector<MM::Element *> es;
  MM::Vector<MM::NodeWorkItem *>::Iterator workIter = work->getIterator();
  MM::BOOLEAN success = MM_TRUE;
  
  MM::INT32 tempSrcAmount = srcInstance->getValue(srcNode);
  
  printf("STEP PUSH ALL NODE %s (%ld edges)\n",
         srcNode->getName()->getBuffer(),
         work->size());
  
  while(workIter.hasNext() == MM_TRUE)
  {
    MM::NodeWorkItem * workItem = workIter.getNext();
    MM::Edge * edge = workItem->getEdge();
    MM::Exp * exp = edge->getExp();
    MM::Node * tgtNode = workItem->getNode();
    MM::Instance * tgtInstance = workItem->getInstance();
    MM::INT32 val = 0; //evaluated expression
    
    if(srcInstance->isEvaluatedExp(exp) == MM_TRUE) //check if expression is pre-evaluated
    {
      val = srcInstance->getEvaluatedExp(exp);
    }
    else
    {
      //NOTE: whatever is evaluated here will hold during this step
      //      since it is stored in evaluated expressions
      //      and chance plays into this!
      MM::ValExp * valExp = evaluator->eval(srcInstance, edge);
      
      if(valExp->getTypeId() == MM::T_NumberValExp)
      {
        val = ((NumberValExp *) valExp)->getIntValue();
        srcInstance->setEvaluatedExp(exp, val);
      }
      else if(valExp->getTypeId() == MM::T_RangeValExp)
      {
        val = ((RangeValExp *) valExp)->getIntValue();
        srcInstance->setEvaluatedExp(exp, val);
      }
      else
      {
        //TODO runtime exception
      }
      
      valExp->recycle(m);
    }
    
    if(val > 0 &&
       tgtInstance->hasCapacity(tgtNode,val) == MM_TRUE)
    {
      tempSrcAmount -= val;
      MM::FlowEvent * event =
        m->createFlowEvent(srcInstance, srcNode, edge,
                           srcInstance, srcNode, val, tgtInstance, tgtNode);
      es.add(event);
    }
    else
    {
      success = MM_FALSE;
      break;
    }
  }
  
  
  //if we have computed a succesfull transition, then apply it
  if(success == MM_TRUE)
  {
    MM::Vector<MM::Element *>::Iterator eIter = es.getIterator();
    while(eIter.hasNext() == MM_TRUE)
    {
      //store the transition
      MM::FlowEvent * event = (MM::FlowEvent *) eIter.getNext();
      tr->addElement((MM::Element*)event);
      
      //and apply the flow
      MM::Instance * srcInstance = event->getSourceInstance();
      MM::Instance * tgtInstance = event->getTargetInstance();
      MM::Node * srcNode = event->getSourceNode();
      MM::Node * tgtNode = event->getTargetNode();
      MM::UINT32 flow = event->getAmount();
      printf("Full flow %ld\n", flow);
      
      srcInstance->sub(srcNode, m, flow);
      tgtInstance->add(tgtNode, m, flow);
    }
  }
  else
  {
    MM::Vector<MM::Element *>::Iterator eIter = es.getIterator();
    while(eIter.hasNext() == MM_TRUE)
    {
      MM::Element * element = eIter.getNext();
      element->recycle(m);
    }
  }
}

MM::VOID MM::SourceNodeBehavior::begin(MM::Instance * i,
                                       MM::Machine * m,
                                       MM::Node * n)
{
  //do nothing
}

MM::VOID MM::SourceNodeBehavior::end(MM::Instance * i,
                                     MM::Machine * m,
                                     MM::Node * n)
{
  //do nothing
}

MM::VOID MM::SourceNodeBehavior::change(MM::Instance * i,
                                        MM::Machine * m,
                                        MM::Node * n)
{
  //do nothing
}

MM::VOID MM::SourceNodeBehavior::add(MM::Instance * i,
                                     MM::Machine * m,
                                     MM::Node * n,
                                     MM::UINT32 amount)
{
  //do nothing
}

MM::VOID MM::SourceNodeBehavior::sub(MM::Instance * i,
                                     MM::Machine * m,
                                     MM::Node * n,
                                     MM::UINT32 amount)
{
  //do nothing
}


MM::UINT32 MM::SourceNodeBehavior::getCapacity(MM::Instance * i,
                                               MM::Node * n)
{
  return 0;
}

MM::UINT32 MM::SourceNodeBehavior::getResources(MM::Instance * i,
                                                MM::Node * n)
{
  return MM_MAX_RESOURCES;
}

MM::BOOLEAN MM::SourceNodeBehavior::hasCapacity(MM::Instance * i,
                                                MM::Node * n,
                                                MM::UINT32 amount)
{
  return MM_FALSE;
}

MM::BOOLEAN MM::SourceNodeBehavior::hasResources(MM::Instance * i,
                                                 MM::Node * n,
                                                 MM::UINT32 amount)
{
  return MM_TRUE;
}

MM::VOID MM::SourceNodeBehavior::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::SourceNodeBehavior::SOURCE_STR,
              MM::SourceNodeBehavior::SOURCE_LEN);
}

MM::VOID MM::SourceNodeBehavior::toString(MM::String * buf, MM::Name * name)
{
  MM::NodeBehavior::toString(buf,name);
  toString(buf);
  buf->space();
  name->toString(buf);
}