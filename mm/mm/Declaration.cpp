//
//  Instance.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/23/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
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
#include "Observer.h"
#include "Observable.h"
#include "Exp.h"
#include "Edge.h"
#include "StateEdge.h"
#include "FlowEdge.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "PoolNodeBehavior.h"
#include "DrainNodeBehavior.h"
#include "SourceNodeBehavior.h"
#include "RefNodeBehavior.h"
#include "Assertion.h"
#include "Deletion.h"
#include "Signal.h"
#include "Declaration.h"
#include "Definition.h"
#include "InterfaceNode.h"

MM::Declaration::Declaration(MM::Name * type,
                             MM::Name * name,
  MM::Map<MM::Name *, Node *, MM::Name::Compare> * interfaces):
  MM::Observer(), MM::Element(name)
{
  this->type = type;
  this->interfaces = interfaces;
  this->def = MM_NULL;
}

MM::Declaration::~Declaration()
{
  type = MM_NULL;
  interfaces = MM_NULL;
  def  = MM_NULL;
}

MM::VOID MM::Declaration::recycle(MM::Recycler * r)
{
  MM::Map<MM::Name *, MM::Node *, MM::Name::Compare>::Iterator i =
    interfaces->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Node * n = i.getNext();
    n->recycle(r);
  }
  type->recycle(r);
  this->Element::recycle(r);
}

MM::TID MM::Declaration::getTypeId()
{
  return MM::T_Declaration;
}

MM::BOOLEAN MM::Declaration::instanceof(MM::TID tid)
{
  if(tid == MM::T_Declaration)
  {
    return MM_TRUE;
  }
  else if(MM::Element::instanceof(tid) == MM_TRUE ||
          MM::Observer::instanceof(tid) == MM_TRUE)
  {
    return MM_TRUE;
  }
  {
    return MM_FALSE;
  }
}

MM::VOID MM::Declaration::update(MM::Observable * observable,
                                 MM::VOID * aux,
                                 MM::UINT32 message,
                                 MM::VOID * object)
{
  switch(message)
  {
    case MM::MSG_NEW_DRAIN:
    case MM::MSG_NEW_POOL:
    case MM::MSG_NEW_SOURCE:
    case MM::MSG_NEW_REF:
      addInterface((MM::Machine*) aux,(MM::Node *) object);
      break;
    case MM::MSG_DEL_DRAIN:
    case MM::MSG_DEL_POOL:
    case MM::MSG_DEL_SOURCE:
    case MM::MSG_DEL_REF:
      removeInterface((MM::Machine*) aux, (MM::Node *) object);
      break;
    default:
      //message not understood
      break;
  }
}

MM::Name * MM::Declaration::getTypeName()
{
  return type;
}

MM::VOID MM::Declaration::setDefinition(MM::Definition * def)
{
  this->def = def;
}

MM::Definition * MM::Declaration::getDefinition()
{
  return def;
}

MM::Node * MM::Declaration::getInterface(MM::Name * name)
{
  return interfaces->get(name);
}

MM::VOID MM::Declaration::addInterface(MM::Machine * m, MM::Node * node)
{
  if(node->getBehavior()->getIO() != MM::NodeBehavior::IO_PRIVATE)
  {
    //MM::InterfaceNode * i = m->createInterfaceNode(MM_NULL, this, node);
    //MM::Name * name = node->getName();
    //interfaces->put(name, i);
  }
}

MM::VOID MM::Declaration::removeInterface(MM::Machine * m, MM::Node * node)
{
  MM::Name * name = node->getName();  
  if(interfaces->contains(name) == MM_TRUE)
  {
    //FIXME: recylce an interface
    MM::InterfaceNode * i = (MM::InterfaceNode *) interfaces->get(name);
    delete i;
    interfaces->remove(name);
  }
}

MM::VOID MM::Declaration::toString(MM::String * buf)
{
  toString(buf,0);
}

MM::VOID MM::Declaration::toString(MM::String * buf, MM::UINT32 indent)
{
  buf->space(indent);
  type->toString(buf);
  buf->space();
  name->toString(buf);
}