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
/*!
 * The Instance abstraction defines instances of type definitions.
 * @package MM
 * @file    Instance.cpp
 * @author  Riemer van Rozen
 * @date    September 11 2013
 */
/******************************************************************************/
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
#include "Enablement.h"
#include "Disablement.h"
#include "Violation.h"
#include "Prevention.h"
#include "Operator.h"
#include "Exp.h"
#include "Assertion.h"
#include "Deletion.h"
#include "Activation.h"
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

const MM::UINT32 MM::Instance::INDENT = 2;
const MM::CHAR * MM::Instance::ACTIVE_STR = "active";
const MM::CHAR * MM::Instance::DISABLED_STR = "disabled";

/**
 * @fn MM::Instance::Instance(MM::Definition * type) : MM::Recyclable()
 * @brief Instantiates an Instance.
 * @param type Definition that defines the instance
 * @return new Instance object
 */
MM::Instance::Instance(MM::Instance * parent,
                       MM::Definition * def,
                       MM::Element * decl): MM::Recyclable(),
                                            MM::Observer(),
                                            MM::Observable()
{
  //TODO, make Machine create this
  values = new MM::Map<MM::Node*, MM::UINT32>();
  oldValues = new MM::Map<MM::Node*, MM::UINT32>();
  newValues = new MM::Map<MM::Node*, MM::UINT32>();
  //instances = new MM::Map<MM::Declaration*, MM::Instance *>();
  instances = new MM::Map<MM::Element *, MM::Vector<MM::Instance *> *>();
  disabledNodes = new MM::Vector<MM::Node *>();
  activeNodes = new MM::Vector<MM::Node *>();
  newActiveNodes = new MM::Vector<MM::Node *>();
  gates = new MM::Map<MM::Node *, MM::Vector<Edge*>::Iterator *>();
  curGateValues = new MM::Map<MM::Node *, MM::UINT32>();
  gateValues = new MM::Map<MM::Node*, MM::UINT32>();
  evaluatedExps = new MM::Map<MM::Exp *, MM::INT32>();  
  this->parent = parent;
  this->def = def;
  this->decl = decl;
  this->marked = MM_FALSE;
}

/**
 * @fn MM::Instance::~Instance()
 * @brief Destructs an Instance object
 */
MM::Instance::~Instance()
{
  //clean up values
  delete values;
  
  //clean up instances
  delete instances;
  
  //clean up gates
  delete gates;
  delete curGateValues;

  //clean up temporary data
  delete oldValues;
  delete newValues;
  delete gateValues;
  
  delete evaluatedExps;
  delete activeNodes;
  delete newActiveNodes;
  delete disabledNodes;
  
  values = MM_NULL;
  instances = MM_NULL;
  gates = MM_NULL;
  curGateValues = MM_NULL;
  oldValues = MM_NULL;
  newValues = MM_NULL;
  gateValues = MM_NULL;
  
  evaluatedExps = MM_NULL;
  activeNodes = MM_NULL;
  newActiveNodes = MM_NULL;
  disabledNodes = MM_NULL;
  
  this->parent = MM_NULL;
  this->def = MM_NULL;
  this->decl = MM_NULL;
  
  this->marked = MM_TRUE;
}

/**
 * @fn MM::VOID MM::Instance::recycle(MM::Recycler * r)
 * @brief Recycles an Instance object in a Recycler.
 * @param r Recycler object
 */
MM::VOID MM::Instance::recycle(MM::Recycler * r)
{
  //NOTE: type is not owned, leave intact

  MM::Map<MM::Element *, MM::Vector<MM::Instance *> *>::Iterator i =
    instances->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Vector<MM::Instance *> * is = i.getNext();
    
    MM::Vector<MM::Instance *>::Iterator j = is->getIterator();
    while(j.hasNext() == MM_TRUE)
    {
      MM::Instance * instance = j.getNext();
      instance->recycle(r);
    }
  }
  MM::Recyclable::recycle(r);
}

/**
 * @fn MM::TID MM::Instance::getTypeId()
 * @brief Retrieves the type id of an Instance object.
 * @return type id
 */
MM::TID MM::Instance::getTypeId()
{
  return MM::T_Instance;
}

/**
 * @fn MM::BOOLEAN MM::Instance::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::Instance::instanceof(MM::TID tid)
{
  if(tid == MM::T_Instance)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}


/**
 * @fn MM::Definition * MM::Instance::getDefinition()
 * @brief Retrieves the definition of an Instance object.
 * @return Definition object
 */
MM::Definition * MM::Instance::getDefinition()
{
  return def;
}

MM::Instance * MM::Instance::getParent()
{
  return parent;
}

MM::Element * MM::Instance::getDeclaration()
{
  return decl;
}

/**
 * @fn MM::VOID MM::Instance::store(MM::UINT32 node, MM::UINT32 val)
 * @brief Stores the value of a pool.
 * @param node pool node id
 * @param val pool value
 */
/*
MM::VOID MM::Instance::store(MM::Node * node,
                             MM::UINT32 val)
{
  values->put(node, val);
}
*/

/**
 * @fn MM::INT32 MM::Instance::retrieve(MM::UINT32 node)
 * @brief Retrieves the value of a pool.
 * @param node pool node id
 * @return value
 */
/*
MM::INT32 MM::Instance::retrieve(MM::Node * node)
{
  return values->get(node);
}
*/

MM::VOID MM::Instance::mark()
{
  marked = MM_TRUE;
}

MM::BOOLEAN MM::Instance::isMarked()
{
  return marked;
}

//sweep is stack heavy, i'm not happy with it
MM::VOID MM::Instance::sweep(MM::Machine * m)
{
  MM::Map<MM::Element *, MM::Vector<MM::Instance *> *>::Iterator mapIter = instances->getIterator();
  while(mapIter.hasNext() == MM_TRUE)
  {
    MM::Vector<MM::Instance *> * vector = mapIter.getNext();
    MM::Vector<MM::Instance *>::Iterator vectIter = vector->getIterator();
 
    MM::Vector<MM::Instance *> del;
    
    while(vectIter.hasNext() == MM_TRUE)
    {
      MM::Instance * instance = vectIter.getNext();
      
      if(instance->isMarked() == MM_TRUE)
      {
        del.add(instance);
        
      }
      else
      {
        instance->sweep(m);
      }
    }
    while(del.isEmpty() == MM_FALSE)
    {
      MM::Instance * instance = del.pop();
	  MM::Definition * unitDef = instance->getDefinition();
      vector->remove(instance);

      //notify observers an instance has been deleted
      notifyObservers(this, /*FIX: unitDef was m*/ unitDef, MM::MSG_DEL_INST, instance);
      instance->recycle(m);
    }
  }
}



MM::Map<MM::Element *, MM::Vector<MM::Instance *> *> * MM::Instance::getInstances()
{
  return instances;
}

MM::Vector<MM::Instance *> * MM::Instance::getInstances(MM::Element * element)
{
  return instances->get(element);
}

/**
 * @fn MM::Instance * MM::Instance::getInstance(MM::Node * node)
 * @brief Retrieves an Instance object for a node
 * @param decl declaration id
 * @return Instance object
 */
MM::Instance * MM::Instance::getInstance(MM::Declaration * decl)
{
  MM::Instance * r = MM_NULL;
  MM::Vector<MM::Instance *> * is = instances->get(decl);
  if(is->size() == 1)
  {
    r = is->elementAt(0);
  }
  return r;
}

MM::INT32 MM::Instance::getIndex(MM::Element * element, MM::Instance * i)
{
  MM::Vector<MM::Instance *> * is = instances->get(element);
  return is->getPosition(i);
}

MM::BOOLEAN MM::Instance::isEvaluatedExp(MM::Exp * exp)
{
  return evaluatedExps->contains(exp);
}

MM::VOID MM::Instance::setEvaluatedExp(MM::Exp * exp, MM::INT32 val)
{
  evaluatedExps->put(exp, val);
}

MM::INT32 MM::Instance::getEvaluatedExp(MM::Exp * exp)
{
  return evaluatedExps->get(exp);
}

MM::BOOLEAN MM::Instance::isActive(MM::Node * node)
{
  return activeNodes->contains(node);
}

//used externally, in between steps
MM::VOID MM::Instance::setActive(MM::Node * node)
{
  activeNodes->add(node);

  //notify observers a node was activated

  //moved to notify part based on transition
  //notifyObservers(this, MM_NULL, MM::MSG_ACTIVATE, node);
}

//used internally, during steps
MM::VOID MM::Instance::setNextActive(MM::Node * node)
{
  newActiveNodes->add(node);
  
  //notify observers a node was activated
  //moved to notify part based on transition
  //notifyObservers(this, MM_NULL, MM::MSG_ACTIVATED, node);
}

MM::VOID MM::Instance::setDisabled(MM::Node * node)
{
  disabledNodes->add(node);
  
  //notify observers a node was disabled
  //moved to notify part based on transition
  //notifyObservers(this, MM_NULL, MM::MSG_DISABLED, node);
}

MM::BOOLEAN MM::Instance::isDisabled(MM::Node * node)
{
  return disabledNodes->contains(node);
}

MM::UINT32 MM::Instance::getValue(MM::Node * node)
{
  return values->get(node);
}

MM::UINT32 MM::Instance::getNewValue(MM::Node * node)
{
  return newValues->get(node);
}

MM::UINT32 MM::Instance::getOldValue(MM::Node * node)
{
  return oldValues->get(node);
}

MM::UINT32 MM::Instance::getGateValue(MM::Node * node)
{
  return gateValues->get(node);
}

MM::VOID MM::Instance::deleteValue(MM::Node * node)
{
  values->remove(node);
}

MM::VOID MM::Instance::setValue(MM::Node * node, MM::UINT32 value)
{
  values->put(node, value);
}

MM::VOID MM::Instance::setNewValue(MM::Node * node, MM::UINT32 value)
{
  newValues->put(node, value);
}

MM::VOID MM::Instance::setOldValue(MM::Node * node, MM::UINT32 value)
{
  oldValues->put(node, value);
}

MM::VOID MM::Instance::setGateValue(MM::Node * node, MM::UINT32 value)
{
  gateValues->put(node, value);
}

/**
 * @fn MM::VOID MM::Instance::update(MM::Observable * observable,
 MM::VOID * aux, MM::UINT32 message, MM::VOID * object)
 * @brief Updates an Observer
 * @param observable Observable object
 * @param aux Auxiliary argument
 * @param message Message to specify what changed
 * @param object Object that changed with respect to observable
 * @note changes to instances are made using the observer pattern,
 *       the message redistribution looks clunky because it might just as well
 *       just use NEW DEL and UPD messages which requires less code.
 */
MM::VOID MM::Instance::update(MM::Observable * observable,
                              MM::VOID * aux,
                              MM::UINT32 message,
                              MM::VOID * object)
{
  switch(message)
  {
    //------------------------------------------------------------------
    //creation
    //------------------------------------------------------------------
    case MM::MSG_NEW_POOL:
      MM_printf("Instance: Sees pool %s begin\n",
             ((MM::Node*)object)->getName()->getBuffer());
      ((MM::Node *) object)->begin(this, (MM::Machine *) aux);
      break;
    case MM::MSG_NEW_GATE:
      MM_printf("Instance: Sees gate %s begin\n",
             ((MM::Node*)object)->getName()->getBuffer());
      ((MM::Node *) object)->begin(this, (MM::Machine *) aux);
      break;
    case MM::MSG_NEW_DECL:
      MM_printf("Instance: Sees declaration %s begin\n",
             ((MM::Declaration*)object)->getName()->getBuffer());
      ((MM::Declaration *) object)->begin(this, (MM::Machine *) aux);
      break;
      
    //------------------------------------------------------------------
    //deletion
    //------------------------------------------------------------------
    case MM::MSG_DEL_POOL:
      MM_printf("Instance: Sees pool %s end\n",
             ((MM::Node*)object)->getName()->getBuffer());
      ((MM::Node *) object)->end(this, (MM::Machine *) aux);
      break;
    case MM::MSG_DEL_GATE:
      MM_printf("Instance: Sees gate %s end\n",
             ((MM::Node*)object)->getName()->getBuffer());
      ((MM::Node *) object)->end(this, (MM::Machine *) aux);
      break;
    case MM::MSG_DEL_DECL:
      MM_printf("Instance: Sees declaration %s end\n",
             ((MM::Declaration*)object)->getName()->getBuffer());
      ((MM::Declaration *) object)->end(this, (MM::Machine *) aux);
      break;

    //------------------------------------------------------------------
    //mutation
    //------------------------------------------------------------------
    case MM::MSG_UPD_POOL:
      MM_printf("Instance: Sees pool %s change\n",
             ((MM::Node*)object)->getName()->getBuffer());
      ((MM::Node *) object)->change(this, (MM::Machine *) aux);
      break;
    case MM::MSG_UPD_GATE:
      MM_printf("Instance: Sees gate %s change\n",
             ((MM::Node*)object)->getName()->getBuffer());
      ((MM::Node *) object)->change(this, (MM::Machine *) aux);
      break;
    case MM::MSG_UPD_DECL:
      MM_printf("Instance: Sees declaration %s change\n",
             ((MM::Node*)object)->getName()->getBuffer());
      ((MM::Node *) object)->change(this, (MM::Machine *) aux);
      break;
    default:
      //message not understood
      break;
  }
}

/*
//all nodes do this on creation
MM::VOID MM::Instance::createNode(MM::Node * node)
{
  //TODO: for all new nodes add it to the active nodes when auto
  //FIXME: remove when an edge is added that disables it again? YES
  MM::NodeBehavior * behavior = node->getBehavior();
  if(behavior->getWhen() == MM::NodeBehavior::WHEN_AUTO)
  {
    setActive(node);
  }
}

MM::VOID MM::Instance::createInstance(MM::Declaration * decl,
                                      MM::Machine * m)
{
  MM::Definition * def = decl->getDefinition();
  
  MM::Instance * instance = m->createInstance(this, def, decl);
  MM::NodeBehavior * behavior = MM_NULL;
  MM::Vector<Element *> * elements = def->getElements();
  MM::Vector<Element *>::Iterator i = elements->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Element * element = i.getNext();
    switch(element->getTypeId())
    {
      case MM::T_Node:
        behavior = ((MM::Node*)element)->getBehavior();
        instance->update(def, m, behavior->getCreateMessage(), element);
        break;
      case MM::T_Declaration:
        instance->update(def, m, MM::MSG_NEW_DECL, element);
        break;
      default:
        //do nothing
        break;
    }
  }
  def->addObserver(instance);
  
  if(instances->get(decl) == MM_NULL)
  {
    instances->put(decl, new Vector<Instance *>());
  }
  
  MM::Vector<Instance *> * is = instances->get(decl);
  is->add(instance);
  
  //notify observers a new instance has been created
  notifyObservers(this, MM_NULL, MM::MSG_NEW_INST, instance);
}

MM::VOID MM::Instance::createPool(MM::Node * node,
                                  MM::Machine * m)
{
  MM::NodeBehavior * behavior = node->getBehavior();
  if(behavior->getTypeId() == MM::T_PoolNodeBehavior)
  {
    createNode(node);
    MM::PoolNodeBehavior * poolNodeBehavior = (MM::PoolNodeBehavior*) behavior;
    MM::Name * ofUnit = poolNodeBehavior->getOf();
    MM::UINT32 at = poolNodeBehavior->getAt();
    if(ofUnit != MM_NULL)
    {
      MM::Element * unitDef = def->findDeclaredDefinition(ofUnit);
      if(unitDef != MM_NULL &&
         unitDef->instanceof(MM::T_Definition) == MM_TRUE)
      {
        createInstancePool(node, at, m, (MM::Definition *) unitDef);
      }
    }
    values->put(node, at);
  }
}

MM::VOID MM::Instance::createInstancePool(MM::Node         * node,
                                          MM::UINT32         at,
                                          MM::Machine      * m,
                                          MM::Definition   * unitDef)
{
  if(instances->get(node) == MM_NULL)
  {
    instances->put(node, new Vector<Instance *>());
  }
  else
  {
    //they exist already... now what?!
    //TODO: reset kill instances?
  }
  MM::Vector<Instance *> * is = instances->get(node);

  
  for(int nrOfInstances = 0; nrOfInstances < at; nrOfInstances++)
  {
    MM::Instance * instance = m->createInstance(this, unitDef, node);

    MM::NodeBehavior * behavior = MM_NULL;
    MM::Vector<Element *> * elements = unitDef->getElements();
    MM::Vector<Element *>::Iterator i = elements->getIterator();
    while(i.hasNext() == MM_TRUE)
    {
      MM::Element * element = i.getNext();
      switch(element->getTypeId())
      {
         case MM::T_Node:
           behavior = ((MM::Node*)element)->getBehavior();
           instance->update(unitDef, m, behavior->getCreateMessage(), element);
           break;
         case MM::T_Declaration:
           instance->update(unitDef, m, MM::MSG_NEW_DECL, element);
           break;
         default:
         //do nothing
           break;
      }
    }
    unitDef->addObserver(instance);
                    
    is->add(instance);
          
    //notify observers a new instance has been created
    notifyObservers(this, MM_NULL, MM::MSG_NEW_INST, instance);
  }
}

MM::VOID MM::Instance::createGate(MM::Node * gate)
{
  MM::NodeBehavior * behavior = gate->getBehavior();  
  if(behavior->getTypeId() == MM::T_GateNodeBehavior)
  {
    MM::Vector<MM::Edge *> * output = gate->getOutput();
    MM::Vector<Edge *>::Iterator * i = MM_NULL;
    
    if(gates->contains(gate) == MM_TRUE)
    {
      i = gates->get(gate);
      delete i;
    }

    i = output->getNewIterator();
    gates->put(gate, i);
    curGateValues->put(gate, 0);
  }
  
  createNode(gate);
}

MM::VOID MM::Instance::createSource(MM::Node * source)
{
  createNode(source);
}

MM::VOID MM::Instance::createDrain(MM::Node * drain)
{
  createNode(drain);
}

MM::VOID MM::Instance::createReference(MM::Node * ref)
{
  createNode(ref);
}

MM::VOID MM::Instance::createConverter(MM::Node * converter)
{
  createNode(converter);
}

MM::VOID MM::Instance::removeInstance(MM::Declaration * decl,
                                      MM::Recycler * r)
{
  MM::Vector<Instance *> * is = instances->get(decl);
  if(is != MM_NULL)
  {
    MM::Vector<Instance *>::Iterator iIter = is->getIterator();
    while(iIter.hasNext() == MM_TRUE)
    {
      MM::Instance * instance = iIter.getNext();
      //notify observers an instance has been deleted
      notifyObservers(this, MM_NULL, MM::MSG_DEL_INST, instance);
      instance->recycle(r);
    }
  }
  instances->remove(decl);
}

MM::VOID MM::Instance::removePool(MM::Node * pool)
{
  //PRE: not during transition / no temp values
  values->remove(pool);
}

MM::VOID MM::Instance::removeGate(MM::Node * gate)
{
  //PRE: not during transition / no temp values
  if(gates->contains(gate) == MM_TRUE)
  {
    gates->remove(gate);
  }
  if(curGateValues->contains(gate) == MM_TRUE)
  {
    curGateValues->remove(gate);
  }
}
*/

MM::VOID MM::Instance::createInstances(MM::Element    * element,
                                       MM::Machine    * m,
                                       MM::Definition * unitDef,
                                       MM::UINT32       amount)
{  
  if(instances->get(element) == MM_NULL)
  {
    instances->put(element, new Vector<Instance *>());
  }  
  MM::Vector<Instance *> * is = instances->get(element);
  
  for(MM::UINT32 nrOfInstances = 0; nrOfInstances < amount; nrOfInstances++)
  {
    MM::Instance * instance = m->createInstance(this, unitDef, element);
    
    MM::NodeBehavior * behavior = MM_NULL;
    MM::Vector<Element *> * elements = unitDef->getElements();
    MM::Vector<Element *>::Iterator eIter = elements->getIterator();
    while(eIter.hasNext() == MM_TRUE)
    {
      MM::Element * element = eIter.getNext();
      switch(element->getTypeId())
      {
        case MM::T_Node:
          behavior = ((MM::Node*)element)->getBehavior();
          instance->update(unitDef, m, behavior->getCreateMessage(), element);
          break;
        case MM::T_Declaration:
          instance->update(unitDef, m, MM::MSG_NEW_DECL, element);
          break;
        default:
          //do nothing
          break;
      }
    }
    unitDef->addObserver(instance);
    
    is->add(instance);
    
    //notify observers a new instance has been created
	notifyObservers(this, /*FIX: unitDef was m*/ unitDef, MM::MSG_NEW_INST, instance);

    eIter.reset();
    while(eIter.hasNext() == MM_TRUE)
    {
      MM::Element * element = eIter.getNext();

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
}

MM::VOID MM::Instance::destroyInstances(MM::Element    * element,
                                        MM::Machine    * m,
                                        MM::UINT32       amount)
{
  MM::Vector<MM::Instance *> * is = instances->get(element);
  if(is != MM_NULL)
  {
    MM::UINT32 size = is->size();
    
    //randomly destroy instances
    MM::Vector<MM::Instance *>::Iterator iIter = is->getIterator();
    for(MM::UINT32 count = 0; count < amount && iIter.hasNext() == MM_TRUE; count++)
    {
      MM::UINT32 randomPos = rand() % size;
      MM::Instance * instance = is->elementAt(randomPos);
      instance->mark();
      //postpone:
      //notifyObservers(this, m, MM::MSG_DEL_INST, instance);
      //instance->recycle(m);
    }
  }
}

MM::VOID MM::Instance::destroyAllInstances(MM::Element    * element,
                                           MM::Machine    * m)
{
  MM::Vector<MM::Instance *> * is = instances->get(element);
  if(is != MM_NULL)
  {
    MM::Vector<MM::Instance *>::Iterator iIter = is->getIterator();
    while(iIter.hasNext() == MM_TRUE)
    {
      MM::Instance * instance = iIter.getNext();
      instance->mark();
      //postpone:
      //notify observers an instance has been deleted
      //notifyObservers(this, m, MM::MSG_DEL_INST, instance);
      //instance->recycle(m);
    }
  }
  //postpone:
  //delete is;
  //instances->remove(element);
}

MM::VOID MM::Instance::destroyInstance(MM::Element  * element,
                                       MM::Machine  * m,
                                       MM::Instance * instance)
{
  MM::Vector<MM::Instance *> * is = instances->get(element);
  if(is != MM_NULL)
  {
    instance->mark();
    //postpone:
    //is->remove(instance);
    //notifyObservers(this, m, MM::MSG_DEL_INST, instance);
    //instance->recycle(m);
  }
}

//begin step
MM::VOID MM::Instance::begin()
{
  //copy values to old and new
  oldValues->clear();
  newValues->clear();  
  oldValues->putAll(values);
  newValues->putAll(values);  
  gateValues->clear();
  
  evaluatedExps->clear();

  //these remain valid.
  //disabledNodes->clear();
  //activeNodes->clear();
}

/**
 * @fn MM::VOID MM::Instance::finalize()
 * @brief Commits the new values and purges the old values.
 * finalize step
 */
MM::VOID MM::Instance::finalize()
{
  //TODO: forward gate values!
  values->clear();    //clear current values
  oldValues->clear(); //clear old values
  gateValues->clear(); //clear gate values

  //clear disabled nodes
  disabledNodes->clear();

  //commit new values
  MM::Map<MM::Node *, MM::UINT32> * tempValues = values;
  values = newValues;
  newValues = tempValues;

  //commit active nodes
  activeNodes->clear(); //clear active nodes
  MM::Vector<MM::Node *> * tempActiveNodes = activeNodes;
  activeNodes = newActiveNodes;
  newActiveNodes = tempActiveNodes;
}

/*
MM::VOID MM::Instance::clearActive()
{
  activeNodes->clear();
}

MM::VOID MM::Instance::clearDisabled()
{
  disabledNodes->clear();
}
*/

MM::UINT32 MM::Instance::getResources(MM::Node * node)
{
  //checks in old values
  return node->getResources(this);
}

MM::BOOLEAN MM::Instance::hasResources(MM::Node * node,
                                       MM::UINT32 amount)
{
  //checks in old values  
  return node->hasResources(this, amount);
}

MM::UINT32 MM::Instance::getCapacity(MM::Node * node)
{
  return node->getCapacity(this);
}

MM::BOOLEAN MM::Instance::hasCapacity(MM::Node * node,
                                      MM::UINT32 amount)
{
  //checks in new values
  return node->hasCapacity(this, amount);
}

MM::VOID MM::Instance::sub(MM::Node * node,
                           MM::Machine * m,
                           MM::UINT32 amount)
{
  node->sub(this, m, amount);
  //notifyObservers(this, (void*) amount, MM::MSG_ADD_VALUE, node);
}

MM::VOID MM::Instance::add(MM::Node * node,
                           MM::Machine * m,
                           MM::UINT32 amount)
{
  node->add(this, m, amount);
  //notifyObservers(this, (void*) amount, MM::MSG_SUB_VALUE, node);
}

MM::VOID MM::Instance::nameToString(MM::Element * element, MM::String * buf)
{
  nameToString(buf);
  MM::Name * elementName = element->getName();  
  elementName->toString(buf);
}


MM::VOID MM::Instance::nameToString(MM::String * buf)
{
  MM::Vector<MM::Instance *> iStack;
  
  MM::Instance * curInstance = this;
  while(curInstance != MM_NULL)
  {
    iStack.add(curInstance);
    curInstance = curInstance->getParent();
  }
  
  while(iStack.size() != 0)
  {
    MM::Instance * curInstance = iStack.pop();
    MM::Element * curDecl = curInstance->getDeclaration();
    
    if(curDecl != MM_NULL)
    {
      MM::Name * n = curDecl->getName();
      if(n != MM_NULL)
      {
        n->toString(buf);
        if(curDecl->instanceof(MM::T_Node) == MM_TRUE)
        {
          //it's an instance pool
          MM::Instance * parent = curInstance->getParent();
          MM::UINT32 index = parent->getIndex(curDecl, curInstance);
          buf->append('[');
          buf->appendInt(index);
          buf->append(']');
        }
        buf->append('.');
      }
    }
  }
}

MM::VOID MM::Instance::toString(MM::String * buf)
{
  toString(buf, 0);
}

//serializes an instance to a JSON object
MM::VOID MM::Instance::toString(MM::String * buf, MM::UINT32 indent)
{
  MM::Map<MM::Node *, MM::UINT32>::Iterator valueIter =
    values->getIterator();
  MM::Map<MM::Element *, MM::Vector<Instance *> *>::Iterator vectIter =
    instances->getIterator();

  buf->space(indent);
  buf->append('{');
  buf->linebreak();
  while(valueIter.hasNext() == MM_TRUE)
  {
    MM::Node * node = MM_NULL;
    MM::UINT32 value = valueIter.getNext(&node);
    MM::Name * name = node->getName();
    buf->space(indent+MM::Instance::INDENT);
    name->toString(buf);
    buf->append(':');
    buf->space();
    buf->appendInt(value);
    buf->append(',');
    buf->linebreak();
  }
  
  while(vectIter.hasNext() == MM_TRUE)
  {
    MM::Element * element = MM_NULL;
    MM::Vector<Instance *> * is = vectIter.getNext(&element);
    MM::Vector<Instance *>::Iterator instanceIter = is->getIterator();
    MM::UINT32 index = 0;
    
    MM::Name * name = element->getName();
    buf->space(indent+MM::Instance::INDENT);
    name->toString(buf);
    
    buf->append(':');
    
    //hack name of index
    if(element->instanceof(MM::T_Node) == MM_TRUE)
    {
      buf->linebreak();
      buf->space(indent + MM::Instance::INDENT);
      buf->append('[');
      buf->linebreak();
      indent += MM::Instance::INDENT;
    }
    
    while(instanceIter.hasNext() == MM_TRUE)
    {
      MM::Instance * instance = instanceIter.getNext();
    
      instance->toString(buf, indent + MM::Instance::INDENT);
      if(instanceIter.hasNext() == MM_TRUE)
      {
        buf->space(indent+MM::Instance::INDENT);
        buf->append(',');
        buf->linebreak();
      }
      index += 1;
    }
    
    //hack name of index
    if(element->instanceof(MM::T_Node) == MM_TRUE)
    {
      indent -= MM::Instance::INDENT;
      buf->space(indent+MM::Instance::INDENT);
      buf->append(']');
    }
    
    buf->append(',');
    buf->linebreak();
  }
  
  buf->space(indent+MM::Instance::INDENT);
  buf->append((MM::CHAR*)MM::Instance::ACTIVE_STR,
              strlen(MM::Instance::ACTIVE_STR));
  buf->append(':');
  buf->space();
  buf->append('[');
  
  MM::Vector<MM::Node *>::Iterator activeIter =
  activeNodes->getIterator();
  while(activeIter.hasNext() == MM_TRUE)
  {
    MM::Node * node = activeIter.getNext();
    
    MM::Name * name = node->getName();
    
    if(name != MM_NULL)
    {
      name->toString(buf);
      if(activeIter.hasNext() == MM_TRUE)
      {
        buf->append(',');
      }
    }
  }
  buf->append(']');
  buf->append(',');
  buf->linebreak();
  
  
  buf->space(indent+MM::Instance::INDENT);
  buf->append((MM::CHAR*)MM::Instance::DISABLED_STR,
              strlen(MM::Instance::DISABLED_STR));
  buf->space();
  buf->append(':');
  buf->space();
  buf->append('[');

  MM::Vector<MM::Node *>::Iterator disabledIter =
  disabledNodes->getIterator();
  while(activeIter.hasNext() == MM_TRUE)
  {
    MM::Node * node = disabledIter.getNext();
    node->getName()->toString(buf);
    if(disabledIter.hasNext() == MM_TRUE)
    {
      buf->append(',');
    }
  }
  buf->append(']');
  buf->linebreak();
  
  
  buf->space(indent);
  buf->append('}');
  buf->linebreak();
}