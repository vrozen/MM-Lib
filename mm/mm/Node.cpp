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
//  Node.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
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
#include "Transformation.h"
#include "Modification.h"
#include "Transition.h"
#include "Event.h"
#include "FlowEvent.h"
#include "TriggerEvent.h"
#include "Failure.h"
#include "Enablement.h"
#include "Disablement.h"
#include "Violation.h"
#include "Prevention.h"
#include "Activation.h"
#include "Program.h"
#include "PoolNodeBehavior.h"
#include "SourceNodeBehavior.h"
#include "DrainNodeBehavior.h"
#include "RefNodeBehavior.h"
#include "GateNodeBehavior.h"
#include "ConverterNodeBehavior.h"
#include "Declaration.h"
#include "InterfaceNode.h"
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

MM::Node::Node(MM::Name * name,
               MM::NodeBehavior * behavior): MM::Element(name)
{
  this->behavior = behavior;
  input = MM_NULL;
  output = MM_NULL;
  conditions = MM_NULL;
  triggers = MM_NULL;
  aliases = MM_NULL;
  isOwner = MM_TRUE;
}

MM::Node::~Node()
{
  behavior = MM_NULL;
  input = MM_NULL;
  output = MM_NULL;
  conditions = MM_NULL;
  triggers = MM_NULL;
  aliases = MM_NULL;
  isOwner = MM_FALSE;
}

MM::VOID MM::Node::recycle(MM::Recycler * r)
{
  if(isOwner == MM_TRUE)
  {
    if(input != MM_NULL)
    {
      delete input;  //FIXME
    }
    if(output != MM_NULL)
    {
      delete output; //FIXME
    }
    if(conditions != MM_NULL)
    {
      delete conditions;   //FIXME
    }
    if(triggers != MM_NULL)
    {
      delete triggers; //FIXME
    }
    if(aliases != MM_NULL)
    {
      delete aliases;
    }
  }
  
  if(behavior != MM_NULL)
  {
    behavior->recycle(r);
  }
  
  MM::Element::recycle(r);
}

MM::TID MM::Node::getTypeId()
{
  return MM::T_Node;
}

MM::BOOLEAN MM::Node::instanceof(MM::TID tid)
{
  if(tid == MM::T_Node)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}

MM::VOID MM::Node::setEdgeOwnership(MM::BOOLEAN isOwner)
{
  this->isOwner = isOwner;
}

MM::BOOLEAN MM::Node::hasEdgeOwnership()
{
  return isOwner;
}

MM::NodeBehavior * MM::Node::getBehavior()
{
  return behavior;
}

MM::VOID MM::Node::setBehavior(MM::NodeBehavior * behavior)
{
  this->behavior = behavior;
}

MM::VOID MM::Node::addInput(MM::Edge * edge)
{
  input->add(edge);
}

MM::VOID MM::Node::addOutput(MM::Edge * edge)
{
  output->add(edge);
}

MM::VOID MM::Node::addCondition(MM::Edge * edge)
{
  conditions->add(edge);
}

MM::VOID MM::Node::addTrigger(MM::Edge * edge)
{
  triggers->add(edge);
}

MM::VOID MM::Node::addAlias(MM::Edge * edge)
{
  aliases->add(edge);
}

MM::VOID MM::Node::removeInput(MM::Edge * edge)
{
  input->remove(edge);
}

MM::VOID MM::Node::removeOutput(MM::Edge * edge)
{
  output->remove(edge);
}

MM::VOID MM::Node::removeCondition(MM::Edge * edge)
{
  conditions->remove(edge);
}

MM::VOID MM::Node::removeTrigger(MM::Edge * edge)
{
  triggers->remove(edge);
}

MM::VOID MM::Node::removeAlias(MM::Edge * edge)
{
  aliases->remove(edge);
}

MM::Vector<MM::Edge *> * MM::Node::getInput()
{
  return input;
}

MM::Vector<MM::Edge *> * MM::Node::getOutput()
{
  return output;
}

MM::Vector<MM::Edge *> * MM::Node::getConditions()
{
  return conditions;
}

MM::Vector<MM::Edge *> * MM::Node::getTriggers()
{
  return triggers;
}

MM::Vector<MM::Edge *> * MM::Node::getAliases()
{
  return aliases;
}

MM::VOID MM::Node::setInput(MM::Vector<MM::Edge *> * input)
{
  this->input = input;
}

MM::VOID MM::Node::setOutput(MM::Vector<MM::Edge *> * output)
{
  this->output = output;
}

MM::VOID MM::Node::setConditions(MM::Vector<MM::Edge *> * conditions)
{
  this->conditions = conditions;
}

MM::VOID MM::Node::setTriggers(MM::Vector<MM::Edge *> * triggers)
{
  this->triggers = triggers;
}

MM::VOID MM::Node::setAliases(MM::Vector<MM::Edge *> * aliases)
{
  this->aliases = aliases;
}


//NOTE: we need all conditions that affect nodes in this instance
//      in order to re-evaluate if a node is active in this state ... :'(

MM::VOID MM::Node::begin(MM::Instance * i, MM::Machine * m)
{
  if(behavior->getWhen() == MM::NodeBehavior::WHEN_AUTO)
  {
    i->setActive(this);
  }
  
  behavior->begin(i, m, this);
}

MM::VOID MM::Node::end(MM::Instance * i, MM::Machine * m)
{
  behavior->end(i, m, this);
}

MM::VOID MM::Node::change(MM::Instance * i, MM::Machine * m)
{
  behavior->change(i, m, this);
}

MM::INT32 MM::Node::getAmount(MM::Instance * i, MM::Machine * m)
{
  return behavior->getAmount(i, m, this);
}

MM::VOID MM::Node::add(MM::Instance * i,
                       MM::Machine * m,
                       MM::UINT32 amount)
{
  behavior->add(i, m, this, amount);
}

MM::VOID MM::Node::sub(MM::Instance * i,
                       MM::Machine * m,
                       MM::UINT32 amount)
{
  behavior->sub(i, m, this, amount);
}

MM::UINT32 MM::Node::getCapacity(MM::Instance * i)
{
  return behavior->getCapacity(i, this);
}

MM::UINT32 MM::Node::getResources(MM::Instance * i)
{
  return behavior->getResources(i, this);
}

MM::BOOLEAN MM::Node::hasCapacity(MM::Instance * i,
                                  MM::UINT32 amount)
{
  return behavior->hasCapacity(i, this, amount);
}

MM::BOOLEAN MM::Node::hasResources(MM::Instance * i,
                                   MM::UINT32 amount)
{
  return behavior->hasResources(i, this, amount);
}


MM::VOID MM::Node::step(MM::Instance * i,
                        MM::Machine * m,
                        MM::Transition * tr) //output

{
  behavior->step(this, i, m, tr);
}

MM::BOOLEAN MM::Node::isDisabled(MM::Instance  * i,
                                 MM::Evaluator * e,
                                 MM::Recycler  * r)
{
  MM::BOOLEAN result = MM_FALSE;
  
  MM::Vector<MM::Edge *>::Iterator cIter = conditions->getIterator();
  while(cIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = cIter.getNext();
    MM::ValExp * resultExp = e->eval(i, edge);
    
    if(resultExp->instanceof(MM::T_BooleanValExp) == MM_TRUE)
    {
      MM::BOOLEAN value = ((MM::BooleanValExp *) resultExp)->getValue();
      resultExp->recycle(r);
      if(value == MM_FALSE)
      {
        result = MM_TRUE;
        break;
      }
    }
    else
    {
      resultExp->recycle(r);
      //FIXME: run-time type error!
      r = MM_FALSE;
      break;
    }
  }
  
  MM::Vector<MM::Edge *>::Iterator aIter = aliases->getIterator();
  while(aIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = aIter.getNext();
    MM::Node * tgtNode = edge->getTarget();
    //target must be a Node with RefNodeBehavior
    //or InterfaceNode that results from a Node with RefNodeBehavior
    
    MM::BOOLEAN disabled = tgtNode->isDisabled(i, e, r);
    if(disabled == MM_TRUE)
    {
      result = MM_TRUE;
      break;
    }    
  }
  
  return result;
}

//checks if a node is "satisfied" such that its triggers activate other nodes
//NOTE: call after a flow happens -> transition occurs!
//NOTE: call after disabled nodes are calculated and stored in the instance!
//FIXME: include aliases
MM::BOOLEAN MM::Node::isSatisfied(MM::Instance * i, MM::Transition * tr)
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
  
  if(i->isDisabled(this) == MM_TRUE)
  {
    return MM_FALSE; //diabled nodes are never satisfied
  }
  
  MM::BOOLEAN satisfied = MM_TRUE;
  MM::NodeBehavior::Act act = behavior->getAct();
  
  MM::Vector<MM::Edge *> * nodeEdges = MM_NULL;
  
  if(act == MM::NodeBehavior::ACT_PULL)
  {
    nodeEdges = input;
  }
  else //act == ACT_PUSH
  {
    nodeEdges = output;
  }


  if(nodeEdges->isEmpty() == MM_TRUE)
  {
    if(behavior->getWhen() == MM::NodeBehavior::WHEN_AUTO ||
       i->isActive(this) == MM_TRUE)
    {
      satisfied = MM_TRUE; 
    }
    else
    {
      satisfied = MM_FALSE;
    }
  }
  else
  {
    MM::Vector<Edge *>::Iterator iIter = nodeEdges->getIterator();
    
    while(iIter.hasNext() == MM_TRUE)
    {
      MM::Edge * iEdge = iIter.getNext();
      MM::Exp * iExp = iEdge->getExp();
      MM::BOOLEAN found = MM_FALSE;
      
      MM::Vector<Element *> * tElements = tr->getElements();
      MM::Vector<Element *>::Iterator tIter = tElements->getIterator();
      while(tIter.hasNext() == MM_TRUE)
      {
        MM::Element * tElement = tIter.getNext();
        if(tElement->instanceof(MM::T_FlowEvent) == MM_TRUE)
        {
          MM::FlowEvent * event = (MM::FlowEvent *) tElement;
          MM::Instance * actInstance = event->getActInstance();
          MM::Node * actNode = event->getActNode();
          MM::Edge * actEdge = event->getActEdge();
          if(actInstance == i && actNode == this && actEdge == iEdge)
          {
            found = MM_TRUE;
            MM::UINT32 flowValue = event->getAmount();
            //note flowValue may not be the full flow value
            //because two nodes can operate on the same edge
            MM::UINT32 evaluatedEdgeExp = i->getEvaluatedExp(iExp);
            
            if(flowValue < evaluatedEdgeExp)
            {
              satisfied = MM_FALSE;
              break;
            }
          }
        }
      }
      if(found == MM_FALSE)
      {
        satisfied = MM_FALSE;
        break;
      }
    }
  }

  if(satisfied == MM_TRUE)
  {
    MM::CHAR * buf = MM_NULL;
    
    if(name != MM_NULL)
    {
      buf = name->getBuffer();
    }
    
    MM_printf("SATISFIED %s\n", buf);
  }
  
  return satisfied;
}

MM::VOID MM::Node::activateTriggerTargets(MM::Instance * i, MM::Machine * m)
{
  behavior->activateTriggerTargets(this, i, m);
}

MM::VOID MM::Node::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::Node::toString(MM::String * buf, MM::UINT32 indent)
{
  buf->space(indent);
  behavior->toString(buf, name);
}
