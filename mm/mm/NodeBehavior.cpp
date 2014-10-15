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
//  NodeBehavior.cpp
//  mm
//
//  Created by Riemer van Rozen on 10/9/13.
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

const MM::CHAR * MM::NodeBehavior::IO_STR[] =
{
  "error",
  "", //epsilon = private
  "in",
  "out",
  "inout",
  "extern"
};

const MM::CHAR * MM::NodeBehavior::WHEN_STR[] =
{
  "error",
  "", //epsilon = passive
  "auto",
  "user",
  "start"
};

const MM::CHAR * MM::NodeBehavior::ACT_STR[] =
{
  "error",
  "", //epsilon = pull
  "push"
};

const MM::CHAR * MM::NodeBehavior::HOW_STR[] =
{
  "error",
  "", //epsilon = any
  "all"
};

const MM::UINT32 MM::NodeBehavior::IO_LEN[] =
{
  strlen(MM::NodeBehavior::IO_STR[0]), //error
  strlen(MM::NodeBehavior::IO_STR[1]), //epsilon (private)
  strlen(MM::NodeBehavior::IO_STR[2]), //in
  strlen(MM::NodeBehavior::IO_STR[3]), //out
  strlen(MM::NodeBehavior::IO_STR[4]), //inout
  strlen(MM::NodeBehavior::IO_STR[5])  //extern
};

const MM::UINT32 MM::NodeBehavior::WHEN_LEN[] =
{
  strlen(MM::NodeBehavior::WHEN_STR[0]), //error
  strlen(MM::NodeBehavior::WHEN_STR[1]), //epsilon (passive)
  strlen(MM::NodeBehavior::WHEN_STR[2]), //auto
  strlen(MM::NodeBehavior::WHEN_STR[3]), //user
  strlen(MM::NodeBehavior::WHEN_STR[4])  //start
};

const MM::UINT32 MM::NodeBehavior::ACT_LEN[] =
{
  strlen(MM::NodeBehavior::ACT_STR[0]), //error
  strlen(MM::NodeBehavior::ACT_STR[1]), //epsilon (pull)
  strlen(MM::NodeBehavior::ACT_STR[2])  //push
};

const MM::UINT32 MM::NodeBehavior::HOW_LEN[] =
{
  strlen(MM::NodeBehavior::HOW_STR[0]), //error
  strlen(MM::NodeBehavior::HOW_STR[1]), //any
  strlen(MM::NodeBehavior::HOW_STR[2])  //all
};

MM::NodeBehavior::NodeBehavior(MM::NodeBehavior::IO io,
                               MM::NodeBehavior::When when,
                               MM::NodeBehavior::Act act,
                               MM::NodeBehavior::How how) : MM::Recyclable()
{
  this->io = io;
  this->when = when;
  this->act = act;
  this->how = how;
}

MM::NodeBehavior::~NodeBehavior()
{
  this->io = MM::NodeBehavior::IO_ERROR;
  this->when = MM::NodeBehavior::WHEN_ERROR;
  this->act = MM::NodeBehavior::ACT_ERROR;
  this->how = MM::NodeBehavior::HOW_ERROR;
}

MM::VOID MM::NodeBehavior::recycle(MM::Recycler * r)
{
  MM::Recyclable::recycle(r);
}

MM::TID MM::NodeBehavior::getTypeId()
{
  return MM::T_NodeBehavior;
}

MM::BOOLEAN MM::NodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_NodeBehavior)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

MM::NodeBehavior::IO MM::NodeBehavior::getIO()
{
  return io;
}

MM::NodeBehavior::When MM::NodeBehavior::getWhen()
{
  return when;
}

MM::NodeBehavior::Act MM::NodeBehavior::getAct()
{
  return act;
}

MM::NodeBehavior::How MM::NodeBehavior::getHow()
{
  return how;
}

MM::VOID  MM::NodeBehavior::setIO(MM::NodeBehavior::IO io)
{
  this->io = io;
}

MM::VOID MM::NodeBehavior::setWhen(MM::NodeBehavior::When when)
{
  this->when = when;
}

MM::VOID MM::NodeBehavior::setAct(MM::NodeBehavior::Act act)
{
  this->act = act;
}

MM::VOID MM::NodeBehavior::setHow(MM::NodeBehavior::How how)
{
  this->how = how;
}

MM::BOOLEAN MM::NodeBehavior::conformsTo(MM::NodeBehavior::IO direction)
{
  MM::BOOLEAN r = MM_FALSE;
  if(direction == MM::NodeBehavior::IO_IN)
  {
    if(io == MM::NodeBehavior::IO_INOUT || io == MM::NodeBehavior::IO_IN)
    {
      r = MM_TRUE;
    }
  }
  else if(direction == MM::NodeBehavior::IO_OUT)
  {
    if(io == MM::NodeBehavior::IO_INOUT || io == MM::NodeBehavior::IO_OUT)
    {
      r = MM_TRUE;
    }
  }  
  return r;
}

MM::VOID MM::NodeBehavior::getWork(MM::Node * node, /*edge source node*/
                                   MM::Instance * instance,
                                   MM::Edge * edge,
                                   MM::Vector<MM::NodeWorkItem *> * work)
{
  if(node->instanceof(MM::T_InterfaceNode) == MM_TRUE)
  {
    //we are dealing with an interface node, for which work must be resolved
    MM::InterfaceNode * interfaceNode = (MM::InterfaceNode *) node;
    MM::Name * interfaceNodeName = interfaceNode->getName();

    //retrieve the parent declaration the interface node is part of
    MM::Element * decl = interfaceNode->getDeclaration();
    
    //retrieve type definition of that declaration
    MM::Definition * def = MM_NULL;
    if(decl->instanceof(MM::T_Declaration) == MM_TRUE)
    {
      def = ((MM::Declaration *) decl)->getDefinition();
    }
    else if(decl->instanceof(MM::T_Node) == MM_TRUE)
    {
      MM::Node * declNode = (MM::Node *) decl;
      MM::NodeBehavior * behavior = declNode->getBehavior();
      if(behavior->instanceof(MM::T_PoolNodeBehavior) == MM_TRUE)
      {
        def = ((MM::PoolNodeBehavior *) behavior)->getDefinition();
      }
    }
    //FIXME: if there is no definition something is wrong
    if(def != MM_NULL)
    {
      MM::Element * declNode = def->getElement(interfaceNodeName);
      MM::Vector<MM::Instance *> * instances = instance->getInstances(decl);
      MM::Vector<MM::Instance *>::Iterator iIter = instances->getIterator();
      while(iIter.hasNext() == MM_TRUE)
      {
        MM::Instance * declInstance = iIter.getNext();
        getWork((MM::Node*)declNode, declInstance, edge, work);
      }
    }
  }
  else if(node->getBehavior()->instanceof(MM::T_RefNodeBehavior) == MM_TRUE)
  {
    //resolve the reference to an actual node instance
    MM::Node * curNode = node;
    MM::NodeBehavior * curNodeBehavior = curNode->getBehavior();
    MM::Instance * curInstance = instance;
    
    while(curNodeBehavior->instanceof(MM::T_RefNodeBehavior) == MM_TRUE)
    {
      MM::Edge * aliasEdge = ((MM::RefNodeBehavior *)curNodeBehavior)->getAlias();
      if(aliasEdge != MM_NULL)
      {
        curNode = aliasEdge->getSource();

        //internally bound: alias source node is in the same type
        MM::Definition * def = curInstance->getDefinition();
        if(def->containsElement(curNode) == MM_TRUE)
        {
          curNodeBehavior = curNode->getBehavior();
        }
        else
        {
          //externally bound: alias source node is in the parent type
          //ASSUME: parent definition contains curNode
          curInstance = instance->getParent();
          break;
        }
      }
      else
      {
        MM_printf("NodeBehavior Error: %s has unresolved alias!\n",
                  node->getName()->getBuffer());
        return;
      }
    }
    //NOTE: assumed correct, references can be resolved using alias edges
    //curNode and curInstance are resolved to a node instance edge works on
    getWork(curNode, curInstance, edge, work);
  }
  else
  {
    //this is an actual node on which the edge can perform work
    MM::NodeWorkItem * workItem =
      new MM::NodeWorkItem(instance, node, edge);
    work->add(workItem);
  }
}


MM::INT32 MM::NodeBehavior::evaluateExpression(MM::Instance * instance,
                                               MM::Exp * exp,
                                               MM::Edge * edge,
                                               MM::Machine * m)
{
  MM::INT32 val = 0;
  if(instance->isEvaluatedExp(exp) == MM_TRUE) //check if expression is pre-evaluated
  {
    val = instance->getEvaluatedExp(exp);
  }
  else
  {
    MM::Evaluator * evaluator = m->getEvaluator();

    //NOTE: whatever is evaluated here will hold during this step
    //      since it is stored in evaluated expressions
    //      and chance plays into this!
    MM::ValExp * valExp = evaluator->eval(exp, instance, edge);
      
    if(valExp->getTypeId() == MM::T_NumberValExp)
    {
      val = ((NumberValExp *) valExp)->getValue();
      instance->setEvaluatedExp(exp, val);
    }
    else if(valExp->getTypeId() == MM::T_RangeValExp)
    {
      val = ((RangeValExp *) valExp)->getIntValue() * 100;
      instance->setEvaluatedExp(exp, val);
    }
    else
    {
      //TODO runtime exception
    }      
    valExp->recycle(m);
  }
  return val;
}

MM::VOID MM::NodeBehavior::step(MM::Node * node,
                                MM::Instance * i,
                                MM::Machine * m,
                                MM::Transition * tr)
{
  MM::Name * name = node->getName();
  MM::CHAR * buf = name->getBuffer();
  MM_printf("STEP NODE %s\n", buf);
  
  //NOTE: the work should be processed including
  //  1. the edge the node operates on
  //  2. the "connecting" instance (source or target depending on push, pull)
  //  3. the actual node the resolved edge connects to (may be aliased)
  //that way
  //  1. late lookups / forwarding are not necessary
  //  2. the same edge can connect multiple nodes (as with instance pools)
  //     a. for declarations there is one
  //are nodeinstances cleaned up properly?
  //are edgeinstances cleaned up properly?
  
  MM::Vector<MM::NodeWorkItem *> * work = new MM::Vector<MM::NodeWorkItem *>();
  
  if(act == MM::NodeBehavior::ACT_PULL)
  {
    //1. direct input  
    MM::Vector<MM::Edge *> * edges = edges = node->getInput();
    MM::Vector<MM::Edge *>::Iterator eIter = edges->getIterator();
    while(eIter.hasNext() == MM_TRUE)
    {
      MM::Edge * edge = eIter.getNext();
      MM::Node * srcNode = edge->getSource();      
      getWork(srcNode, i, edge, work);
    }
    
    //2. interface input
    //   FIXME: note to self, make this much less ugly please
    if(conformsTo(MM::NodeBehavior::IO_IN) == MM_TRUE)
    {
      MM::Element * decl = i->getDeclaration();
      MM::Name * nodeName = node->getName();
      edges = MM_NULL;
      if(decl->instanceof(MM::T_Declaration) == MM_TRUE)
      {
        MM::Declaration * declaration = (MM::Declaration *) decl;
        MM::Node * interfaceNode = declaration->getInterface(nodeName);
        edges = interfaceNode->getInput();
      }
      else if(decl->instanceof(MM::T_Node) == MM_TRUE)
      {
        MM::Node * declNode = (MM::Node *) decl;
        MM::NodeBehavior * declNodeBehavior = declNode->getBehavior();
        if(declNodeBehavior->instanceof(MM::T_PoolNodeBehavior) == MM_TRUE)
        {
          MM::PoolNodeBehavior * declPoolNodeBehavior = (MM::PoolNodeBehavior *) declNodeBehavior;
          MM::Node * interfaceNode = declPoolNodeBehavior->getInterface(nodeName);
          edges = interfaceNode->getInput();
        }
      }
      if(edges != MM_NULL)
      {
        MM::Vector<MM::Edge *>::Iterator eIter = edges->getIterator();
        while(eIter.hasNext() == MM_TRUE)
        {
          MM::Edge * edge = eIter.getNext();
          MM::Node * srcNode = edge->getSource();
          getWork(srcNode, i->getParent(), edge, work);
        }
      }
    }
  }
  else
  {    
    //1. direct output
    MM::Vector<MM::Edge *> * edges = node->getOutput();
    MM::Vector<MM::Edge *>::Iterator eIter = edges->getIterator();
    while(eIter.hasNext() == MM_TRUE)
    {
      MM::Edge * edge = eIter.getNext();
      MM::Node * tgtNode = edge->getTarget();
      getWork(tgtNode, i, edge, work);
    }

    //2. interface output
    //   FIXME: note to self, make this much less ugly please
    if(conformsTo(MM::NodeBehavior::IO_OUT) == MM_TRUE)
    {
      MM::Element * decl = i->getDeclaration();
      MM::Name * nodeName = node->getName();
      edges = MM_NULL;
      if(decl->instanceof(MM::T_Declaration) == MM_TRUE)
      {
        MM::Declaration * declaration = (MM::Declaration *) decl;
        MM::Node * interfaceNode = declaration->getInterface(nodeName);
        edges = interfaceNode->getOutput();
      }
      else if(decl->instanceof(MM::T_Node) == MM_TRUE)
      {
        MM::Node * declNode = (MM::Node *) decl;
        MM::NodeBehavior * declNodeBehavior = declNode->getBehavior();
        if(declNodeBehavior->instanceof(MM::T_PoolNodeBehavior) == MM_TRUE)
        {
          MM::PoolNodeBehavior * declPoolNodeBehavior = (MM::PoolNodeBehavior *) declNodeBehavior;
          MM::Node * interfaceNode = declPoolNodeBehavior->getInterface(nodeName);
          edges = interfaceNode->getOutput();
        }
      }
      if(edges != MM_NULL)
      {
        MM::Vector<MM::Edge *>::Iterator eIter = edges->getIterator();
        while(eIter.hasNext() == MM_TRUE)
        {
          MM::Edge * edge = eIter.getNext();
          MM::Node * tgtNode = edge->getTarget();
          getWork(tgtNode, i->getParent(), edge, work);
        }
      }
    }
  }
  
  if(how == MM::NodeBehavior::HOW_ANY)
  {
    if(act == MM::NodeBehavior::ACT_PULL)
    {
      stepPullAny(node, i, work, m, tr);
    }
    else
    {
      stepPushAny(node, i, work, m, tr);
    }
  }
  else
  {
    if(act == MM::NodeBehavior::ACT_PULL)
    {
      stepPullAll(node, i, work, m, tr);
    }
    else
    {
      stepPushAll(node, i, work, m, tr);
    }
  }
}


MM::VOID MM::NodeBehavior::stepPullAny(MM::Node * node,
                                       MM::Instance * i,
                                       MM::Vector<MM::NodeWorkItem *> * work,
                                       MM::Machine * m,
                                       MM::Transition * tr)
{
  stepAny(MM::NodeBehavior::ACT_PULL, node, i, work, m, tr);
}

MM::VOID MM::NodeBehavior::stepPushAny(MM::Node * node,
                             MM::Instance * i,
                             MM::Vector<MM::NodeWorkItem *> * work,
                             MM::Machine * m,
                             MM::Transition * tr)
{
  stepAny(MM::NodeBehavior::ACT_PUSH, node, i, work, m, tr);
}

//process an any instance node
MM::VOID MM::NodeBehavior::stepAny(MM::NodeBehavior::Act act,
                                   MM::Node * node,
                                   MM::Instance * i,
                                   MM::Vector<MM::NodeWorkItem *> * work,
                                   MM::Machine * m,
                                   MM::Transition * tr)
{
  MM::Evaluator * evaluator = m->getEvaluator();
  
  MM::UINT32 size = work->size();
  
  MM_printf("STEP ");
  if(act == MM::NodeBehavior::ACT_PULL)
  {
    MM_printf("PULL ");
  }
  else
  {
    MM_printf("PUSH ");
  }
  MM_printf("ANY NODE (%ld edges)\n", size);
  
  MM::BOOLEAN success = MM_FALSE;

  //process work
  while(size != 0)
  {
    MM::UINT32 randomPos = rand() % size;
    MM::NodeWorkItem * workItem = work->elementAt(randomPos);
    
    MM::Edge * edge = workItem->getEdge();
    MM::Exp * exp = edge->getExp();
    work->remove(workItem);
    size = work->size();
    
    MM::INT32 val = 0;
    if(i->isEvaluatedExp(exp) == MM_TRUE)
    {
      val = i->getEvaluatedExp(exp);
    }
    else
    {
      //FIXME: move to val exp method
      MM::ValExp * valExp = evaluator->eval(i, edge);
      if(valExp->getTypeId() == MM::T_NumberValExp)
      {
        val = ((NumberValExp *) valExp)->getValue();
        i->setEvaluatedExp(exp, val);
      }
      else if(valExp->getTypeId() == MM::T_RangeValExp)
      {
        val = ((RangeValExp *) valExp)->getIntValue() * 100;
        i->setEvaluatedExp(exp, val);
      }
      else
      {
        //TODO runtime exception
      }
      
      valExp->recycle(m);
    }

    //remove fp remainder
    val = (val / 100) * 100;
    
    MM::Node * srcNode = MM_NULL;
    MM::Node * tgtNode = MM_NULL;
    MM::Instance * srcInstance = MM_NULL;
    MM::Instance * tgtInstance = MM_NULL;
    
    if(act == MM::NodeBehavior::ACT_PULL)
    {
      srcNode = workItem->getNode();
      tgtNode = node;
      srcInstance = workItem->getInstance();
      tgtInstance = i;
    }
    else
    {
      srcNode = node;
      tgtNode = workItem->getNode();
      srcInstance = i;
      tgtInstance = workItem->getInstance();
    }
    
    if(val >= 100 &&
       srcInstance->hasResources(srcNode, 100, m) == MM_TRUE &&
       tgtInstance->hasCapacity(tgtNode, 100, m) == MM_TRUE)
    {
      if(srcInstance->hasResources(srcNode, val, m) == MM_TRUE)
      {
        if(tgtInstance->hasCapacity(tgtNode, val, m) == MM_TRUE)
        {
          MM_printf("Full flow %ld\n", val);
          srcInstance->sub(srcNode, m, val);
          tgtInstance->add(tgtNode, m, val);
          MM::FlowEvent * event =
            m->createFlowEvent(i, node, edge,
                               srcInstance, srcNode, val, tgtInstance, tgtNode);

          tr->addElement(event);

		      success = MM_TRUE;
        }
        else
        {
          val = i->getCapacity(tgtNode, m);
          MM_printf("Flow up to capacity %ld\n", val);
          srcInstance->sub(srcNode, m, val);
          tgtInstance->add(tgtNode, m, val);
          MM::FlowEvent * event =
            m->createFlowEvent(i, node, edge,
                               srcInstance, srcNode, val, tgtInstance, tgtNode);
          
          tr->addElement(event);

          success = MM_TRUE;
		    }
      }
      else
      {
        val = srcInstance->getResources(srcNode, m);
        if(tgtInstance->hasCapacity(tgtNode, val, m) == MM_TRUE)
        {
          MM_printf("Flow up to availability %ld\n", val);
          srcInstance->sub(srcNode, m, val);
          tgtInstance->add(tgtNode, m, val);
          MM::FlowEvent * event =
            m->createFlowEvent(i, node, edge,
                               srcInstance, srcNode, val, tgtInstance, tgtNode);
          
          tr->addElement(event);

		      success = MM_TRUE;
        }
        else
        {
          val = tgtInstance->getCapacity(tgtNode, m);
          MM_printf("Flow up to capacity %ld\n", val);
          srcInstance->sub(srcNode, m, val);
          tgtInstance->add(tgtNode, m, val);
          MM::FlowEvent * event =
            m->createFlowEvent(i, node, edge,
                               srcInstance, srcNode, val, tgtInstance, tgtNode);
          
          tr->addElement(event);

          success = MM_TRUE;
        }
      }
    }
  }

  if(success == MM_FALSE)
  {
    MM::Failure * event = m->createFailure(i, node);
    tr->addElement(event);
  }

}

MM::VOID MM::NodeBehavior::activateTriggerTargets(MM::Node * node,
                                                  MM::Instance * i,
                                                  MM::Machine * m)
{
  MM::Evaluator * e = m->getEvaluator();
  MM::Vector<MM::Edge *> * triggers = node->getTriggers();
  MM::Vector<MM::Edge *>::Iterator tIter = triggers->getIterator();
  while(tIter.hasNext() == MM_TRUE)
  {    
    MM::Edge * trigger = tIter.getNext();
    MM::Node * tgtNode = trigger->getTarget();
    
    //notify observers a trigger happened
    //FIXME: if trigger has no name --> error
    //i->notifyObservers(i, MM_NULL, MM::MSG_TRIGGER, trigger); 
    
    if(tgtNode->isDisabled(i, e, m) == MM_FALSE)
    {
      i->setNextActive(tgtNode);
    }
	  //FIXME: notify when a trigger did not fire
  }
  
  //FIXME: activate trigger targets of aliases
  //NOTE: trigger targets might live in different instances :S
  MM::Vector<MM::Edge *> * aliases = node->getAliases();
  MM::Vector<MM::Edge *>::Iterator aIter = aliases->getIterator();
  while(aIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = aIter.getNext();
    MM::Node * aliasNode = edge->getTarget();
    aliasNode->activateTriggerTargets(i, m);
  }
}

//retrieve resources from a full state in between steps
//get the value of a node instance 
MM::INT32 MM::NodeBehavior::getAmount(MM::Instance * i,
                                      MM::Node * n,
                                      MM::Machine * m)
{
  //default: getResources
  return getResources(i, n, m);
}

MM::VOID MM::NodeBehavior::setAmount(MM::Instance * i,
                                     MM::Node * n,
                                     MM::Machine * m,
                                     MM::INT32 val)
{
  //default: do nothing
}

MM::VOID MM::NodeBehavior::toString(MM::String * buf, MM::Name * name)
{
  if(io != MM::NodeBehavior::IO_PRIVATE &&
     io != MM::NodeBehavior::IO_ERROR)
  {
    buf->append((MM::CHAR*)MM::NodeBehavior::IO_STR[io],
                MM::NodeBehavior::IO_LEN[io]);
    buf->space();
  }
  if(when != MM::NodeBehavior::WHEN_PASSIVE &&
     when != MM::NodeBehavior::WHEN_ERROR)
  {
    buf->append((MM::CHAR*)MM::NodeBehavior::WHEN_STR[when],
              MM::NodeBehavior::WHEN_LEN[when]);
    buf->space();
  }
  if(act != MM::NodeBehavior::ACT_PULL &&
     act != MM::NodeBehavior::ACT_ERROR)
  {
    buf->append((MM::CHAR*)MM::NodeBehavior::ACT_STR[act],
                MM::NodeBehavior::ACT_LEN[act]);
    buf->space();
  }
  if(how != MM::NodeBehavior::HOW_ANY &&
     how != MM::NodeBehavior::HOW_ERROR)
  {
    buf->append((MM::CHAR*)MM::NodeBehavior::HOW_STR[how],
              MM::NodeBehavior::HOW_LEN[how]);
    buf->space();
  }
}