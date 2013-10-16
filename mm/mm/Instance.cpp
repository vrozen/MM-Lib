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
#include "Name.h"
#include "Observer.h"
#include "Observable.h"
#include "Element.h"
#include "Exp.h"
#include "Edge.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "Instance.h"
#include "Declaration.h"
#include "Definition.h"

/**
 * @fn MM::Instance::Instance(MM::Definition * type) : MM::Recyclable()
 * @brief Instantiates an Instance.
 * @param type Definition that defines the instance
 * @return new Instance object
 */
MM::Instance::Instance(MM::Definition * type) : MM::Recyclable()
{
  //TODO, make Machine create this
  values = new MM::Map<MM::UINT32, MM::UINT32>();
  instances = new MM::Map<MM::UINT32, MM::Instance *>();
  activeNodes = new MM::Vector<MM::UINT32>();
  this->type = type;
}

/**
 * @fn MM::Instance::~Instance()
 * @brief Destructs an Instance object
 */
MM::Instance::~Instance()
{
  //TODO make Machine clean this
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
  //FIXME: destructor cleans it for now
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
  return type;
}

/**
 * @fn MM::VOID MM::Instance::store(MM::UINT32 node, MM::UINT32 val)
 * @brief Stores the value of a pool.
 * @param node pool node id
 * @param val pool value
 */
MM::VOID MM::Instance::store(MM::UINT32 node, MM::UINT32 val)
{
  values->put(node, val);
}

/**
 * @fn MM::INT32 MM::Instance::retrieve(MM::UINT32 node)
 * @brief Retrieves the value of a pool.
 * @param node pool node id
 * @return value
 */
MM::INT32 MM::Instance::retrieve(MM::UINT32 node)
{
  return values->get(node);
}

/**
 * @fn MM::VOID MM::Instance::commit()
 * @brief Commits the new values and purges the old values.
 */
MM::VOID MM::Instance::commit()
{
  //FIXME implement old and new values
  //TODO commit new values
  //TODO purge old values
}

/**
 * @fn MM::Instance * MM::Instance::retrieveInstance(MM::UINT32 decl)
 * @brief Retrieves an Instance object for a declaration id
 * @param decl declaration id
 * @return Instance object
 */
MM::Instance * MM::Instance::retrieveInstance(MM::UINT32 decl)
{
  return instances->get(decl);
}

/**
 * @fn MM::BOOLEAN MM::Instance::isActive(MM::UINT32 id)
 * @brief Retrieves an Instance object for a declaration id
 * @param decl declaration id
 * @return Instance object
 */
MM::BOOLEAN MM::Instance::isActive(MM::UINT32 id)
{
  MM::BOOLEAN r = MM_FALSE;
  MM::Element * element = MM_NULL;// FIXMEtype->getElement(id);
  
  if(element->getTypeId() == MM::T_Node)
  {
    MM::Node * node = (MM::Node *) element;
    
    if(node->getBehavior()->getWhen() == MM::NodeBehavior::WHEN_AUTO ||
       activeNodes->contains(id) == MM_TRUE)
    {
      r = MM_TRUE;
    }
  }
  
  return r;
}

/**
 * @fn MM::VOID MM::Instance::setActive(MM::UINT32 node, MM::BOOLEAN active)
 * @brief Activates and deactivates a node in an instance.
 * @param node node id
 * @param active activity status
 */
MM::VOID MM::Instance::setActive(MM::UINT32 node,
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
      //createPool((MM::PoolNode *) object);
      break;
    case MM::MSG_DEL_POOL:
      //removePool((MM::Node *) object);
      break;
    case MM::MSG_NEW_DECL:
      //createInstance((Declaration *) object, (MM::Machine *) aux );
    case MM::MSG_DEL_DECL:
      //removeInstance((Declaration *) object, (MM::Recycler *) aux);
      break;
    default:
      //message not understood
      break;
  }
  
}

