/******************************************************************************
 * Copyright (c) 2013-2014, Amsterdam University of Applied Sciences (HvA) and
 *                          Centrum Wiskunde & Informatica (CWI)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contributors:
 *   * Riemer van Rozen - rozen@cwi.nl - HvA / CWI
 ******************************************************************************/
//
//  SourceNode.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/11/13.
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
#include "Event.h"
#include "FlowEvent.h"
#include "TriggerEvent.h"
#include "Failure.h"
#include "Activation.h"
#include "Enablement.h"
#include "Disablement.h"
#include "Violation.h"
#include "Prevention.h"
#include "Operator.h"
#include "Exp.h"
#include "Assertion.h"
#include "Deletion.h"
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
  
 // MM::INT32 tempSrcAmount = srcInstance->getValue(srcNode);
  
  MM_printf("STEP PUSH ALL NODE %s (%ld edges)\n",
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
  
    val = evaluateExpression(srcInstance, exp, edge, m);

    val = (val / 100) * 100;
    
    if(val >= 100 &&
       tgtInstance->hasCapacity(tgtNode, val, m) == MM_TRUE)
    {
      //tempSrcAmount -= val;
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
      MM_printf("Full flow %ld\n", flow);
      
      srcInstance->sub(srcNode, m, flow);
      tgtInstance->add(tgtNode, m, flow);
    }
  }
  else
  {
    //fail
	  MM::Failure * event = m->createFailure(srcInstance, srcNode);
    tr->addElement(event);
	  
	  //clean up
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


MM::INT32 MM::SourceNodeBehavior::getCapacity(MM::Instance * i,
                                              MM::Node * n,
                                              MM::Machine * m)
{
  return 0;
}

MM::INT32 MM::SourceNodeBehavior::getResources(MM::Instance * i,
                                               MM::Node * n,
                                               MM::Machine * m)
{
  return MM_MAX_RESOURCES;
}

MM::BOOLEAN MM::SourceNodeBehavior::hasCapacity(MM::Instance * i,
                                                MM::Node * n,
                                                MM::UINT32 amount,
                                                MM::Machine * m)
{
  return MM_FALSE;
}

MM::BOOLEAN MM::SourceNodeBehavior::hasResources(MM::Instance * i,
                                                 MM::Node * n,
                                                 MM::UINT32 amount,
                                                 MM::Machine * m)
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