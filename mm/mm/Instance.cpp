/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
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
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Transformation.h"
#include "Program.h"
#include "Modification.h"
#include "Transition.h"
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
#include "PoolNodeBehavior.h"
#include "SourceNodeBehavior.h"
#include "DrainNodeBehavior.h"
#include "GateNodeBehavior.h"
#include "RefNodeBehavior.h"
#include "Observer.h"
#include "Observable.h"
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
                       MM::Name * name): MM::Recyclable(),
                                         MM::Observer(),
                                         MM::Observable()
{
  //TODO, make Machine create this
  values = new MM::Map<MM::Node*, MM::UINT32>();
  oldValues = new MM::Map<MM::Node*, MM::UINT32>();
  newValues = new MM::Map<MM::Node*, MM::UINT32>();
  instances = new MM::Map<MM::Declaration*, MM::Instance *>();
  disabledNodes = new MM::Vector<MM::Node *>();
  activeNodes = new MM::Vector<MM::Node *>();  
  gates = new MM::Map<MM::Node *, MM::Vector<Edge*>::Iterator *>();
  curGateValues = new MM::Map<MM::Node *, MM::UINT32>();
  gateValues = new MM::Map<MM::Node*, MM::UINT32>();
  
  this->parent = parent;
  this->type = def;
  this->name = name;
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
}

/**
 * @fn MM::VOID MM::Instance::recycle(MM::Recycler * r)
 * @brief Recycles an Instance object in a Recycler.
 * @param r Recycler object
 */
MM::VOID MM::Instance::recycle(MM::Recycler * r)
{
  //NOTE: type is not owned, leave intact

  MM::Map<MM::Declaration*, MM::Instance*>::Iterator i =
    instances->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Instance * instance = i.getNext();
    instance->recycle(r);
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

MM::Map<MM::Declaration *, MM::Instance *> * MM::Instance::getInstances()
{
  return instances;
}

/**
 * @fn MM::Definition * MM::Instance::getDefinition()
 * @brief Retrieves the definition of an Instance object.
 * @return Definition object
 */
MM::Definition * MM::Instance::getDefinition()
{
  return type;
}

MM::Instance * MM::Instance::getParent()
{
  return parent;
}

MM::Instance * MM::Instance::getInstance(MM::Declaration * decl)
{
  return instances->get(decl);
}

MM::Name * MM::Instance::getName()
{
  return name;
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

/**
 * @fn MM::Instance * MM::Instance::retrieveInstance(MM::UINT32 decl)
 * @brief Retrieves an Instance object for a declaration id
 * @param decl declaration id
 * @return Instance object
 */
MM::Instance * MM::Instance::retrieveInstance(MM::Declaration * decl)
{
  return instances->get(decl);
}

MM::BOOLEAN MM::Instance::isActive(MM::Node * node)
{
  return activeNodes->contains(node);
}

MM::VOID MM::Instance::setActive(MM::Node * node)
{
  activeNodes->add(node);

  //notify observers a node was activated
  notifyObservers(this, MM_NULL, MM::MSG_ACTIVATED, node);
}

MM::BOOLEAN MM::Instance::isDisabled(MM::Node * node)
{
  return disabledNodes->contains(node);
}

MM::VOID MM::Instance::setDisabled(MM::Node * node)
{
  disabledNodes->add(node);
  
  //notify observers a node was disabled
  notifyObservers(this, MM_NULL, MM::MSG_DISABLED, node);
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
 */
MM::VOID MM::Instance::update(MM::Observable * observable,
                              MM::VOID * aux,
                              MM::UINT32 message,
                              MM::VOID * object)
{
  //Type updates that require dynamic fixes

  switch(message)
  {
    case MM::MSG_NEW_POOL:
      printf("Instance: Sees pool %s begin\n",
             ((MM::Node*)object)->getName()->getBuffer());
      createPool((MM::Node *) object);
      break;
    case MM::MSG_UPD_POOL:
      printf("Instance: Sees pool %s change\n",
             ((MM::Node*)object)->getName()->getBuffer());
      createPool((MM::Node*) object);
      break;
    case MM::MSG_DEL_POOL:
      printf("Instance: Sees pool %s end\n",
             ((MM::Node*)object)->getName()->getBuffer());
      removePool((MM::Node *) object);
      break;
    case MM::MSG_NEW_GATE:
      printf("Instance: Sees gate %s begin\n",
             ((MM::Node*)object)->getName()->getBuffer());
      createGate((MM::Node *) object);
      break;
    case MM::MSG_UPD_GATE:
      printf("Instance: Sees gate %s begin\n",
             ((MM::Node*)object)->getName()->getBuffer());
      createGate((MM::Node *) object);
      break;
    case MM::MSG_DEL_GATE:
      printf("Instance: Sees gate %s begin\n",
             ((MM::Node*)object)->getName()->getBuffer());
      removeGate((MM::Node *) object);
      break;
    case MM::MSG_NEW_REF:
      break;
    case MM::MSG_UPD_REF:
      break;
    case MM::MSG_DEL_REF:
      break;
    case MM::MSG_NEW_DRAIN:
      break;
    case MM::MSG_UPD_DRAIN:
      break;
    case MM::MSG_DEL_DRAIN:
      break;
    case MM::MSG_NEW_SOURCE:
      break;
    case MM::MSG_UPD_SOURCE:
      break;
    case MM::MSG_DEL_SOURCE:
      break;
    case MM::MSG_NEW_DECL:
      printf("Instance: Sees declaration %s begin\n",
             ((MM::Declaration*)object)->getName()->getBuffer());
      createInstance((Declaration *) object, (MM::Machine *) aux );
      break;
    case MM::MSG_UPD_DECL:
      break;
    case MM::MSG_DEL_DECL:
      printf("Instance: Sees declaration %s end\n",
             ((MM::Declaration*)object)->getName()->getBuffer());
      //removeInstance((Declaration *) object, (MM::Recycler *) aux);
      break;
    default:
      //message not understood
      break;
  }
}

MM::VOID MM::Instance::createInstance(MM::Declaration * decl,
                                      MM::Machine * m)
{
  MM::Definition * def = decl->getDefinition();
  MM::Name * name = decl->getName();
  
  MM::Instance * instance = m->createInstance(this, def, name);
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
        if(behavior->getTypeId() == MM::T_PoolNodeBehavior)
        {
          instance->update(def, m, MM::MSG_NEW_POOL, element);
        }
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
  instances->put(decl, instance);
  
  //notify observers a new instance has been created
  notifyObservers(this, MM_NULL, MM::MSG_NEW_INST, instance);
}

MM::VOID MM::Instance::createPool(MM::Node * pool)
{
  MM::NodeBehavior * behavior = pool->getBehavior();
  if(behavior->getTypeId() == MM::T_PoolNodeBehavior)
  {
    MM::PoolNodeBehavior * poolBehavior = (MM::PoolNodeBehavior*) behavior;
    MM::UINT32 at = poolBehavior->getAt();
    values->put(pool, at);
  }

  //TODO: for all new nodes add it to the active nodes when auto
  if(pool->getBehavior()->getWhen() == MM::NodeBehavior::WHEN_AUTO)
  {
    //FIXME: remove when an edge is added that disables it again?
    activeNodes->add(pool);
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
}


MM::VOID MM::Instance::removeInstance(MM::Declaration * decl,
                                      MM::Recycler * r)
{
  MM::Instance * instance = instances->get(decl);
  instances->remove(decl);
  instance->recycle(r);
  
  //notify observers an instance has been deleted
  notifyObservers(this, MM_NULL, MM::MSG_DEL_INST, instance);  
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

MM::VOID MM::Instance::begin()
{
  //copy values to old and new
  oldValues->clear();
  newValues->clear();  
  oldValues->putAll(values);
  newValues->putAll(values);
  
  gateValues->clear();
  disabledNodes->clear();
  activeNodes->clear();
}

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
                           MM::UINT32 amount)
{
  return node->sub(this, amount);
}

MM::VOID MM::Instance::add(MM::Node * node,
                           MM::UINT32 amount)
{
  return node->add(this, amount);
}

/**
 * @fn MM::VOID MM::Instance::commit()
 * @brief Commits the new values and purges the old values.
 */
MM::VOID MM::Instance::commit()
{
  //TODO: forward gate values!
  values->clear();    //clear current values
  oldValues->clear(); //clear old values
  gateValues->clear(); //clear gate values
  
  //commit new values
  MM::Map<MM::Node *, MM::UINT32> * temp = values;
  values = newValues;   
  newValues = temp;
}

/**
 * @fn MM::VOID MM::Instance::rollback()
 * @brief Purges old and new values and keeps the current ones.
 */
MM::VOID MM::Instance::rollback()
{
  newValues->clear();
  oldValues->clear();
  gateValues->clear();
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
  MM::Map<MM::Declaration*, MM::Instance*>::Iterator instanceIter =
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
    if(valueIter.hasNext() == MM_TRUE || instanceIter.hasNext() == MM_TRUE)
    {
      buf->append(',');
    }
    buf->linebreak();
  }
  
  while(instanceIter.hasNext() == MM_TRUE)
  {
    MM::Declaration * decl = MM_NULL;
    MM::Instance * instance = instanceIter.getNext(&decl);
    MM::Name * name = decl->getName();
    buf->space(indent+MM::Instance::INDENT);
    name->toString(buf);
    buf->append(':');
    buf->linebreak();
    instance->toString(buf, indent + MM::Instance::INDENT);
    if(instanceIter.hasNext() == MM_TRUE)
    {
      buf->space(indent+MM::Instance::INDENT);
      buf->append(',');
      buf->linebreak();
    }
  }
    
  buf->space(indent+MM::Instance::INDENT);
  buf->append((MM::CHAR*)MM::Instance::ACTIVE_STR,
              strlen(MM::Instance::ACTIVE_STR));
  buf->space();
  buf->append(':');
  buf->space();
  buf->append('[');
  
  MM::Vector<MM::Node *>::Iterator activeIter =
  activeNodes->getIterator();
  while(activeIter.hasNext() == MM_TRUE)
  {
    MM::Node * node = activeIter.getNext();
    node->getName()->toString(buf);
    if(activeIter.hasNext() == MM_TRUE)
    {
      buf->append(',');
    }
  }
  buf->append(']');
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