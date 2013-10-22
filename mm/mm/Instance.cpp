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
/*
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
#include "Name.h"
#include "Observer.h"
#include "Observable.h"
#include "Element.h"
#include "Exp.h"
#include "Edge.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "Definition.h"
#include "Declaration.h"
#include "Instance.h"
*/


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

/**
 * @fn MM::Instance::Instance(MM::Definition * type) : MM::Recyclable()
 * @brief Instantiates an Instance.
 * @param type Definition that defines the instance
 * @return new Instance object
 */
MM::Instance::Instance(MM::Instance * parent,
                       MM::Definition * def,
                       MM::Name * name) : MM::Recyclable()
{
  //TODO, make Machine create this
  values = new MM::Map<MM::Node*, MM::UINT32>();
  oldValues = MM_NULL;
  newValues = MM_NULL;
  instances = new MM::Map<MM::Declaration*, MM::Instance *>();
  activeNodes = new MM::Vector<MM::Node *>();
  this->type = def;
  this->name = name;
}

/**
 * @fn MM::Instance::~Instance()
 * @brief Destructs an Instance object
 */
MM::Instance::~Instance()
{  
  delete values;
  delete instances;
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
MM::VOID MM::Instance::store(MM::Node * node, MM::UINT32 val)
{
  values->put(node, val);
}

/**
 * @fn MM::INT32 MM::Instance::retrieve(MM::UINT32 node)
 * @brief Retrieves the value of a pool.
 * @param node pool node id
 * @return value
 */
MM::INT32 MM::Instance::retrieve(MM::Node * node)
{
  return values->get(node);
}

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

/**
 * @fn MM::BOOLEAN MM::Instance::isActive(MM::UINT32 id)
 * @brief Retrieves an Instance object for a declaration id
 * @param decl declaration id
 * @return Instance object
 */
MM::BOOLEAN MM::Instance::isActive(MM::Node * node)
{
  MM::BOOLEAN r = MM_FALSE;
  
  if(node->getBehavior()->getWhen() == MM::NodeBehavior::WHEN_AUTO ||
     activeNodes->contains(node) == MM_TRUE)
  {
      r = MM_TRUE;
  }
  
  return r;
}

/**
 * @fn MM::VOID MM::Instance::setActive(MM::UINT32 node, MM::BOOLEAN active)
 * @brief Activates and deactivates a node in an instance.
 * @param node node id
 * @param active activity status
 */
MM::VOID MM::Instance::setActive(MM::Node * node,
                                 MM::BOOLEAN active)
{
  MM::BOOLEAN contains = activeNodes->contains(node);  
  if(active == MM_TRUE)
  {
    if(contains == MM_FALSE)
    {
      activeNodes->add(node);
    }
  }
  else
  {
    if(contains == MM_TRUE)
    {
      activeNodes->remove(node);
    }
  }
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
    case MM::MSG_NEW_DECL:
      printf("Instance: Sees declaration %s begin\n",
             ((MM::Declaration*)object)->getName()->getBuffer());
      createInstance((Declaration *) object, (MM::Machine *) aux );
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
}

MM::VOID MM::Instance::removeInstance(MM::Declaration * decl,
                                      MM::Recycler * r)
{
  MM::Instance * instance = instances->get(decl);
  instances->remove(decl);
  instance->recycle(r);
}

MM::VOID MM::Instance::removePool(MM::Node * pool)
{
  values->remove(pool);
}


MM::VOID MM::Instance::begin()
{
  //copy values to old and new
  oldValues = new MM::Map<MM::Node*, MM::UINT32>(values);
  newValues = new MM::Map<MM::Node*, MM::UINT32>(values);
}


MM::UINT32 MM::Instance::getResources(MM::Node * node)
{
  MM::UINT32 resources = oldValues->get(node);
  return resources; //FIXME: drain, source, gate
}

MM::BOOLEAN MM::Instance::hasResources(MM::Node * node,
                                       MM::UINT32 amount)
{
  //old has resources
  if(oldValues->get(node) > amount)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::UINT32 MM::Instance::getCapacity(MM::Node * node)
{
  MM::UINT32 capacity = 0;  
  MM::NodeBehavior * behavior = node->getBehavior();
  MM::UINT32 max = 0;
  if(behavior->getTypeId() == MM::T_PoolNodeBehavior)
  {
    max = ((MM::PoolNodeBehavior*) behavior)->getMax();
    capacity = max - newValues->get(node);
  }
  return capacity; //FIXME: drain, source, gate
}

MM::BOOLEAN MM::Instance::hasCapacity(MM::Node * node,
                                      MM::UINT32 amount)
{
  MM::NodeBehavior * behavior = node->getBehavior();
  MM::UINT32 max = 0;
  if(behavior->getTypeId() == MM::T_PoolNodeBehavior)
  {
    max = ((MM::PoolNodeBehavior*) behavior)->getMax();
    if(max - newValues->get(node) >= amount  || max == 0)
    {
      return MM_TRUE;
    }
  }
  return MM_FALSE; //FIXME: drain, source, gate
}

MM::VOID MM::Instance::sub(MM::Node * node,
                           MM::UINT32 amount)
{
  //subtract from old value
  MM::UINT32 oldValue = oldValues->get(node);
  oldValue = oldValue - amount;
  oldValues->put(node, oldValue);
  
  //subtract from new value
  MM::UINT32 newValue = newValues->get(node);
  newValue = newValue - amount;
  newValues->put(node, newValue);
}

MM::VOID MM::Instance::add(MM::Node * node,
                           MM::UINT32 amount)
{
  //add to new value
  MM::UINT32 newValue = newValues->get(node);
  newValue = newValue + amount;
  newValues->put(node, newValue);
}

/**
 * @fn MM::VOID MM::Instance::commit()
 * @brief Commits the new values and purges the old values.
 */
MM::VOID MM::Instance::commit()
{
  delete values;        //delete old values
  delete oldValues;     //delete old values
  values = newValues;   //commit new values
  oldValues = MM_NULL;  //reset pointers
  newValues = MM_NULL;  //reset pointers
}

MM::VOID MM::Instance::toString(MM::String * buf)
{
  toString(buf, 0);
}

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
  
  buf->space(indent);
  buf->append('}');
  buf->linebreak();
}