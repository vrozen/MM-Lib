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
//  Evaluator.cpp
//  mm
//
//  Created by Riemer van Rozen on 9/26/13.
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
#include "VarExp.h"
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
#include "Activation.h"
#include "Enablement.h"
#include "Disablement.h"
#include "Prevention.h"
#include "Violation.h"
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

MM::VOID MM::Evaluator::recycle(MM::Recycler * r)
{
  
}

MM::VOID MM::Evaluator::toString(MM::String * buf)
{
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

MM::VOID MM::Evaluator::step(MM::Transition * tr)
{
  MM::Reflector * r = m->getReflector();
  MM::Instance * i = r->getInstance();
  prepareAll(i);
  MM_printf("STEP LEVEL (%ld nodes): pull all\n", pullAllWork->size());
  stepLevel(tr, pullAllWork);
  MM_printf("STEP LEVEL (%ld nodes): pull any\n", pullAnyWork->size());
  stepLevel(tr, pullAnyWork);
  MM_printf("STEP LEVEL (%ld nodes): push all\n", pushAllWork->size());
  stepLevel(tr, pushAllWork);
  MM_printf("STEP LEVEL (%ld nodes): push any\n", pushAnyWork->size());
  stepLevel(tr, pushAnyWork);
  MM_printf("\n");

  //FIXME: we need the currently active nodes to calculate 'satisfied'
  //clearActiveNodes(i);
  
  finalizeAll(i, tr);

  //create temporary string
  MM::String * str = m->createString(10000);
  
  //stringify transition
  str->clear();
  tr->toString(str);
  str->print();
  
  //stringify state
  i->toString(str);
  str->print();
  str->clear();

  //notify flow
  notifyFlow(tr);

  //notify dirty pool instance values
  i->notifyValues(m);
  //notifyValues(i);

  //clean up instances
  //notify deletions
  i->sweep(m);
  
  //recycle string
  str->recycle(m);
}

MM::VOID MM::Evaluator::prepareAll(MM::Instance * instance)
{
  prepare(instance);
  instance->begin(); //does not clear active and disabled
  
  //MM::Map<MM::Declaration *, MM::Instance *> * instances =
  //instance->getInstances();
  //MM::Map<MM::Declaration *, MM::Instance *>::Iterator instanceIter =
  //instances->getIterator();
  
  MM::Map<MM::Element *, MM::Vector<MM::Instance *> *> * instanceMap =
    instance->getInstances();
  
  MM::Map<MM::Element *, MM::Vector<MM::Instance *> *>::Iterator instanceMapIter =
    instanceMap->getIterator();
  
  while(instanceMapIter.hasNext() == MM_TRUE)
  {
    MM::Vector<MM::Instance *> * instanceVect = instanceMapIter.getNext();
    
    MM::Vector<MM::Instance *>::Iterator instanceVectIter = instanceVect->getIterator();
    while(instanceVectIter.hasNext() == MM_TRUE)
    {
      MM::Instance * instance = instanceVectIter.getNext();
      prepareAll(instance);
    }
  }
}

MM::VOID MM::Evaluator::prepare(MM::Instance * instance)
{
  MM::Definition * def = instance->getDefinition();
  
  //NOTE: these nodes are statically defined
  MM::Vector<Node *> * pullAllNodes = def->getPullAllNodes();
  MM::Vector<Node *> * pullAnyNodes = def->getPullAnyNodes();
  MM::Vector<Node *> * pushAllNodes = def->getPushAllNodes();
  MM::Vector<Node *> * pushAnyNodes = def->getPushAnyNodes();

  //printf("pull all %ld\n", pullAllNodes->size());
  //printf("pull any %ld\n", pullAnyNodes->size());
  //printf("push all %ld\n", pushAllNodes->size());
  //printf("push any %ld\n", pushAnyNodes->size());
  
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
      //printf("YAY!\n");
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
}

//process a set of instance nodes
MM::VOID MM::Evaluator::stepLevel(MM::Transition * tr,
                                  MM::Vector<MM::Evaluator::NodeInstance*> * work)
{
  MM::UINT32 size = work->size();
  while(size != 0)
  {
    MM::UINT32 randomPos = rand() % size;
    MM::Evaluator::NodeInstance * ni = work->elementAt(randomPos);
    work->remove(ni);
    MM::Instance * instance = ni->getInstance();
    MM::Node * node = ni->getNode();
    //stepNode(tr, instance, node);
    node->step(instance, m, tr);    
    size = work->size();
  }
}

MM::VOID MM::Evaluator::finalizeAll(MM::Instance * i, MM::Transition * tr)
{
  finalize(i, tr);
  
  MM::Map<MM::Element *, MM::Vector<MM::Instance *> *> * instanceMap =
    i->getInstances();
  MM::Map<MM::Element *, MM::Vector<MM::Instance *> *>::Iterator instanceMapIter =
    instanceMap->getIterator();
  while(instanceMapIter.hasNext() == MM_TRUE)
  {
    MM::Vector<MM::Instance *> * instanceVect = instanceMapIter.getNext();
    
    MM::Vector<MM::Instance *>::Iterator instanceVectIter = instanceVect->getIterator();
    
    while(instanceVectIter.hasNext() == MM_TRUE)
    {
      MM::Instance * iChild = instanceVectIter.getNext();
      finalizeAll(iChild, tr);
    }
  }
}


MM::VOID MM::Evaluator::finalize(MM::Instance * i, MM::Transition * tr)
{
  //set active nodes based on automatic nodes, satisfied nodes and triggers
  setActiveNodes(i, tr);

 //new values become current values
  i->finalize();

  //check which nodes are enabled based on condition edges
  //set active nodes disabled if necessary
  setEnabledNodes(i, tr);
}

//check in the old state and a transition that has happened
//if nodes can be made active in the next state
//since the state is not yet complete it uses setNextActive
MM::VOID MM::Evaluator::setActiveNodes(MM::Instance * i,
                                       MM::Transition * tr)
{
  MM::Definition * def = i->getDefinition();
  MM::Vector<MM::Element *> * elements = def->getElements();
  
  MM::Vector<MM::Element *>::Iterator eIter = elements->getIterator();
  while(eIter.hasNext() == MM_TRUE)
  {
    MM::Element * element = eIter.getNext();
    if(element->instanceof(MM::T_Node) == MM_TRUE)
    {
      MM::Node * node = (MM::Node *) element;
      MM::NodeBehavior * behavior = node->getBehavior();      
      if(behavior->Recyclable::instanceof(MM::T_RefNodeBehavior) == MM_FALSE)
      {
        if(node->isSatisfied(i, tr) == MM_TRUE)
        {
          node->activateTriggerTargets(i, m);
        }
      }
    }
  }
}


//set active nodes for a new instance (at the end of the last step)
//since the state is 'complete' / 'committed' it uses setActive and setDisabled
//for some reason this is slow... profile and improve
MM::VOID MM::Evaluator::setEnabledNodes(MM::Instance * i, MM::Transition * tr)
{
  MM::Definition * def = i->getDefinition();
  MM::Vector<MM::Element *> * elements = def->getElements();
  
  MM::Vector<MM::Element *>::Iterator eIter = elements->getIterator();
  while(eIter.hasNext() == MM_TRUE)
  {
    MM::Element * element = eIter.getNext();
    if(element->instanceof(MM::T_Node) == MM_TRUE)
    {
      MM::Node * node = (MM::Node *) element;
      MM::NodeBehavior * behavior = node->getBehavior();
      
      if(behavior->Recyclable::instanceof(MM::T_RefNodeBehavior) == MM_FALSE)
      {
        if(i->isActive(node) == MM_TRUE)
        {
          if(node->isDisabled(i, this, m) == MM_TRUE)
          {
            MM::Disablement * event = m->createDisablement(i, node);
            tr->addElement(event);
            i->setDisabled(node);
          }
          else
          {
            MM::Enablement * event = m->createEnablement(i, node);
            tr->addElement(event);
          }
		    }
      }
    }
  }
}

MM::VOID MM::Evaluator::notifyFlow(MM::Transition * tr)
{
  MM::Vector<MM::Element *> * elements = tr->getElements();
  MM::Vector<MM::Element *>::Iterator eIter = elements->getIterator();
  MM::Element * element;
  
  while(eIter.hasNext() == MM_TRUE)
  {
    element = eIter.getNext();
    /*TODO: improve this --> */
    if(element->instanceof(MM::T_FlowEvent) == MM_TRUE)
    {
      MM::FlowEvent * event = (MM::FlowEvent *) element;
      
	    MM::Instance * instance = event->getInstance();
      MM::Instance * srcInstance = event->getSourceInstance();
      MM::Instance * tgtInstance = event->getTargetInstance();
      MM::Node * srcNode = event->getSourceNode();
      MM::Node * tgtNode = event->getTargetNode();
      MM::UINT32 amount = event->getAmount();
      
	    srcInstance->notifyObservers(srcInstance, (MM::VOID*)amount, MM::MSG_SUB_VALUE, srcNode);
      tgtInstance->notifyObservers(tgtInstance, (MM::VOID*)amount, MM::MSG_ADD_VALUE, tgtNode);

      //hack to notify the instance in which the flow occurred
	    if(srcInstance != tgtInstance)
	    {
		    srcInstance->notifyObservers(srcInstance, (MM::VOID*)amount, MM::MSG_ADD_VALUE, tgtNode);
	      tgtInstance->notifyObservers(tgtInstance, (MM::VOID*)amount, MM::MSG_SUB_VALUE, srcNode);
		  }

	    //let observers of instances know the current value of a pool.
      /*
      if(srcNode->getBehavior()->instanceof(MM::T_PoolNodeBehavior) == MM_TRUE)
      {
        MM::INT32 srcAmount = srcNode->getAmount(srcInstance, m);
        srcInstance->notifyObservers(srcInstance, (MM::VOID*)srcAmount, MM::MSG_HAS_VALUE, srcNode);
      }
      if(tgtNode->getBehavior()->instanceof(MM::T_PoolNodeBehavior) == MM_TRUE)
      {
        MM::INT32 tgtAmount = tgtNode->getAmount(tgtInstance, m);
        tgtInstance->notifyObservers(tgtInstance, (MM::VOID*)tgtAmount, MM::MSG_HAS_VALUE, tgtNode);
      }
      */
    }
	  else if(element->instanceof(MM::T_Event) == MM_TRUE)
	  {
      MM::Event * event = (MM::Event *) element;
      MM::Element * e = event->getElement();
      MM::Instance * i = event->getInstance();
      MM::MESSAGE msg = event->getMessage();
      i->notifyObservers(i, (MM::VOID*)0, msg, e); 
	  }
  }
}

/*
//notifies all values of an instance
//this brute force notification was devised to avoid having to check dependencies
//its main drawback is that all values are notified every step
MM::VOID MM::Evaluator::notifyValues(MM::Instance * instance)
{
  MM::Definition * definition = instance->getDefinition();
  MM::Vector<MM::Element *> * elements = definition->getElements();
  if(elements != MM_NULL)
  {
    MM::Vector<MM::Element *>::Iterator elementIter = elements->getIterator();
    while(elementIter.hasNext() == MM_TRUE)
    {
      MM::Element * element = elementIter.getNext();

      if(element->instanceof(MM::T_Node) == MM_TRUE)
      {
        MM::Node * node = (MM::Node *) element;
        MM::NodeBehavior * behavior = node->getBehavior();
        if(behavior->instanceof(MM::T_PoolNodeBehavior) == MM_TRUE)
        {
          MM::INT32 amount = node->getAmount(instance, m);
          instance->notifyObservers(instance, (MM::VOID*)amount, MM::MSG_HAS_VALUE, node);
        }
      }
    }
  }

  MM::Map<MM::Element *, MM::Vector<MM::Instance *> *> * instances = instance->getInstances();
  MM::Map<MM::Element *, MM::Vector<MM::Instance *> *>::Iterator vectIter = instances->getIterator();

  while(vectIter.hasNext() == MM_TRUE)
  {
    MM::Element * element = MM_NULL;
    MM::Vector<MM::Instance *> * is = vectIter.getNext(&element);
    MM::Vector<MM::Instance *>::Iterator instanceIter = is->getIterator();
 
    while(instanceIter.hasNext() == MM_TRUE)
    {
      MM::Instance * childInstance = instanceIter.getNext();
      this->notifyValues(childInstance);
    }
  }
}
*/

/*
//recursively propagate all gates until no gate contains temp values
//NOTE: run-time errors can emerge... hard to analyze statically
MM::VOID MM::Evaluator::propagateGates(MM::Instance * i,
                                       MM::Transition * tr)
{
  //for each gate g in instance i that has temporary values
  //while(value(g) != 0) { getnext output(g); }
  //eval (output)
  //propagate
  //remove g from temp map
  
  
  MM::Map<MM::Node *, MM::UINT32> * gateValues = i->getGateValues();
  MM::Map<MM::Node *, MM::UINT32>::Iterator gateIter = gateValues->getIterator();
  
  while(gateValues->isEmpty() == MM_FALSE)
  {
    MM::Node * gate = MM_NULL;
    MM::UINT32 value = gateIter.getNext(&gate);
   
  
    while(value != 0)
    {
      MM::FlowEdge * edge = i->getNextOutput(gate);
      MM::ValExp * valExp = eval(i, edge);
    
      //call push any behavior
      
      

    }
      
  }
  
  MM::Map<MM::Declaration *, MM::Instance *> * instances = i->getInstances();
  MM::Map<MM::Declaration *, MM::Instance *>::Iterator iter =
    instances->getIterator();
  
  //recurse over child instances
  while(iter.hasNext() == MM_TRUE)
  {
    MM::Instance * iChild = iter.getNext();
    propagateGates(iChild, tr);
  }
}
*/


//------------------------------------------------------------------------------
//eval
//------------------------------------------------------------------------------
MM::ValExp * MM::Evaluator::eval(MM::Instance * i, MM::Edge * e)
{
  return eval(e->getExp(), i, e);
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
      MM_printf("missing case in eval\n");
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


/*
MM::ValExp * MM::Evaluator::eval(MM::VarExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  MM::UINT32 val = 0;
  
  MM::Definition * def = i->getDefinition();
  
  MM::Name * name = exp->getName();
  
  MM::Element * element = def->getElement(name);
  
  if(element->instanceof(MM::T_Node) == MM_TRUE)
  {
    MM::Node * curNode = (MM::Node *) element;
    MM::NodeBehavior * curNodeBehavior = curNode->getBehavior();
    MM::Instance * curInstance = i;
    
    while(curNodeBehavior->instanceof(MM::T_RefNodeBehavior) == MM_TRUE)
    {
      MM::Edge * aliasEdge = ((MM::RefNodeBehavior *)curNodeBehavior)->getAlias();
      if(aliasEdge != MM_NULL)
      {
        curNode = aliasEdge->getSource();
        curNodeBehavior = curNode->getBehavior();

        //internally bound: alias source node is in the same type
        MM::Definition * def = curInstance->getDefinition();
        if(def->containsElement(curNode) == MM_TRUE)
        {
          break;
        }
        else
        {
          //externally bound: alias source node is in the parent type
          //ASSUME: parent definition contains curNode
          //WRONG!

          curInstance = curInstance->getParent();
          break;
        }
      }
      else
      {
        MM_printf("NodeBehavior Error: %s has unresolved alias!\n",
                  curNode->getName()->getBuffer());
        break;
      }
    }
    

    //DECISION: expressions are fixed during a step to the
    //          current values of the previous step
    //          changes to observable values are only taken
    //          into account at the next step
    //          when calculating resources or capacity
    //NOTE:     it may be possible to use the new value instead...
    //          and set expressions dirty... :(
    //          for not getting old incorrect values
    val = curNode->getAmount(curInstance, m);

    //val = curInstance->getValue(curNode);
  }
  
  return m->createNumberValExp(val);
}
*/

MM::ValExp * MM::Evaluator::eval(MM::VarExp * exp,
                                 MM::Instance * i,
                                 MM::Edge * e)
{
  MM::UINT32 val = 0;
  MM::Node * node = MM_NULL;
  MM::Instance * instance = MM_NULL;
  MM::ValExp * rExp = MM_NULL;

  i->findNodeInstance(exp, &node, &instance);

  if(node != MM_NULL && instance != MM_NULL)
  {
    val = node->getAmount(instance, m);
    rExp = m->createNumberValExp(val);
  }

  //DECISION: expressions are fixed during a step to the
  //          current values of the previous step
  //          changes to observable values are only taken
  //          into account at the next step
  //          when calculating resources or capacity
  //NOTE:     it may be possible to use the new value instead...
  //          and set expressions dirty... :(
  //          for not getting old incorrect values
 
  return rExp;
}


MM::ValExp * MM::Evaluator::eval(MM::AllExp * exp,
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
          MM_printf("missing case in eval\n");
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
          MM_printf("missing case in eval\n");
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
          MM_printf("missing case in eval\n");
          return MM_NULL;
        }
      }
    }
    default:
    {
      //TODO: throw EvaluatorException
      MM_printf("missing case in eval\n");
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
      MM_printf("unknown operator on boolean");
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
      MM_printf("unknown operator on boolean");
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
      MM_printf("unknown operator on boolean");
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
      MM_printf("unknown operator on boolean");
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
  MM::INT32 rrmin = 0;
  MM::INT32 rrmax = 0;
  MM::INT32 min = e2->getMin();
  MM::INT32 max = e2->getMax();
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
      MM_printf("unknown operator on boolean");
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
  MM::INT32 rrmin = 0;
  MM::INT32 rrmax = 0;
  MM::BOOLEAN rbval = MM_FALSE;
  MM::INT32 min = e1->getMin();
  MM::INT32 max = e1->getMax();
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
      MM_printf("unknown operator on boolean");
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
      MM_printf("missing case in eval\n");
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
      MM_printf("missing operator case in eval");
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
  MM::INT32 val = exp->getValue();
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
      //TODO: throw EvaluatorException
      MM_printf("missing operator case in eval");
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
