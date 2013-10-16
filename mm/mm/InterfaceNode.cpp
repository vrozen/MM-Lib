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

MM::InterfaceNode::InterfaceNode(MM::Name * name,
                                 MM::Declaration * decl,
                                 MM::Node * ref):
  MM::Node(name, MM_NULL)
{
}

MM::InterfaceNode::~InterfaceNode()
{
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

MM::Declaration * MM::InterfaceNode::getDeclaration()
{
  return this->decl;
}

MM::Node * MM::InterfaceNode::getReference()
{
  return this->ref;
}

MM::VOID MM::InterfaceNode::toString(MM::String * buf)
{
}