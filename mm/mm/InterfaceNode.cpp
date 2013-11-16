//
//  InterfaceNode.cpp
//  mm
//
//  Created by Riemer van Rozen on 10/8/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Map.h"
#include "Observer.h"
#include "Observable.h"
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "Edge.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "Transformation.h"
#include "Modification.h"
#include "Transition.h"
#include "Declaration.h"
#include "Definition.h"
#include "Node.h"
#include "InterfaceNode.h"
#include "Instance.h"

MM::InterfaceNode::InterfaceNode(MM::Name * name,
                                 MM::Declaration * decl,
                                 MM::Node * ref):
  MM::Node(name, MM_NULL)
{
  this->ref = ref;
}

MM::InterfaceNode::~InterfaceNode()
{
  this->ref = MM_NULL;
}

MM::VOID MM::InterfaceNode::recycle(MM::Recycler *r)
{  
  this->MM::Node::recycle(r);
}

MM::TID MM::InterfaceNode::getTypeId()
{
  return MM::T_InterfaceNode;
}

MM::BOOLEAN MM::InterfaceNode::instanceof(MM::TID tid)
{
  if(tid == MM::T_InterfaceNode)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Node::instanceof(tid);
  }
}

MM::NodeBehavior * MM::InterfaceNode::getBehavior()
{
  return ref->getBehavior();
}


MM::Declaration * MM::InterfaceNode::getDeclaration()
{
  return this->decl;
}

MM::Node * MM::InterfaceNode::getNode()
{
  return this->ref;
}

MM::VOID MM::InterfaceNode::add(MM::Instance * i, MM::UINT32 amount)
{
  MM::Instance * iChild = i->getInstance(decl);
  ref->add(iChild, amount);
}

MM::VOID MM::InterfaceNode::sub(MM::Instance * i, MM::UINT32 amount)
{
  MM::Instance * iChild = i->getInstance(decl);
  ref->sub(iChild, amount);
}

MM::UINT32 MM::InterfaceNode::getCapacity(MM::Instance * i)
{
  MM::Instance * iChild = i->getInstance(decl);
  return ref->getCapacity(iChild);
}

MM::UINT32 MM::InterfaceNode::getResources(MM::Instance * i)
{
  MM::Instance * iChild = i->getInstance(decl);
  return ref->getResources(iChild);
}

MM::BOOLEAN MM::InterfaceNode::hasCapacity(MM::Instance * i,
                                           MM::UINT32 amount)
{
  MM::Instance * iChild = i->getInstance(decl);
  return ref->hasCapacity(iChild, amount);
}

MM::BOOLEAN MM::InterfaceNode::hasResources(MM::Instance * i,
                                            MM::UINT32 amount)
{
  MM::Instance * iChild = i->getInstance(decl);
  return ref->hasResources(iChild, amount);
}

MM::VOID MM::InterfaceNode::toString(MM::String * buf)
{
  //not explicitly represented
}