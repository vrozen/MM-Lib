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
//  InterfaceNode.cpp
//  mm
//
//  Created by Riemer van Rozen on 10/8/13.
//
#include <stdio.h>
#include <stdlib.h>
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
#include "Edge.h"
#include "NodeWorkItem.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "Transformation.h"
#include "Modification.h"
#include "Transition.h"
#include "Declaration.h"
#include "Definition.h"
#include "Node.h"
#include "InterfaceNode.h"
//#include "Instance.h"

MM::InterfaceNode::InterfaceNode(MM::Name    * name,
                                 MM::Element * decl,
                                 MM::Node    * ref):
  MM::Node(name, MM_NULL)
{
  this->decl = decl;
  this->ref = ref;
}

MM::InterfaceNode::~InterfaceNode()
{
  this->decl = MM_NULL;
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

MM::Element * MM::InterfaceNode::getDeclaration()
{
  return decl;
}

MM::Node * MM::InterfaceNode::getNode()
{
  return ref;
}

MM::VOID MM::InterfaceNode::add(MM::Instance * i,
                                MM::UINT32 amount)
{
  MM_printf("should not happen anaymore MM::InterfaceNode::add\n");
}

MM::VOID MM::InterfaceNode::sub(MM::Instance * i, MM::UINT32 amount)
{  
  MM_printf("should not happen anaymore MM::InterfaceNode::sub\n");
  //MM::Instance * iChild = i->getInstance(decl);
  //ref->sub(iChild, amount);
}

MM::INT32 MM::InterfaceNode::getCapacity(MM::Instance * i, MM::Machine * m)
{
  MM_printf("should not happen anaymore MM::InterfaceNode::getCapacity\n");
  //MM::Instance * iChild = i->getInstance(decl);
  //return ref->getCapacity(iChild);
  return 0;
}

MM::INT32 MM::InterfaceNode::getResources(MM::Instance * i, MM::Machine * m)
{
  MM_printf("should not happen anaymore MM::InterfaceNode::getResources\n");
  //MM::Instance * iChild = i->getInstance(decl);
  //return ref->getResources(iChild);
  return 0;
}

MM::BOOLEAN MM::InterfaceNode::hasCapacity(MM::Instance * i,
                                           MM::UINT32 amount, MM::Machine * m)
{
  MM_printf("should not happen anaymore MM::InterfaceNode::hasCapacity");
  //MM::Instance * iChild = i->getInstance(decl);
  //return ref->hasCapacity(iChild, amount);
  return MM_FALSE;
}

MM::BOOLEAN MM::InterfaceNode::hasResources(MM::Instance * i,
                                            MM::UINT32 amount, MM::Machine * m)
{
  MM_printf("should not happen anaymore MM::InterfaceNode::hasResources");
  //MM::Instance * iChild = i->getInstance(decl);
  //return ref->hasResources(iChild, amount);
  return MM_FALSE;
}

MM::VOID MM::InterfaceNode::activateTriggerTargets(MM::Instance * i,
                                                   MM::Machine * m)
{
  MM_printf("should not happen anaymore MM::InterfaceNode::activateTriggerTargets\n");
  //MM::NodeBehavior * behavior = ref->getBehavior(); //HACK
  //behavior->activateTriggerTargets(this, i, m);
}


MM::VOID MM::InterfaceNode::toString(MM::String * buf)
{
  //not explicitly represented, output is a comment
  buf->append((MM::CHAR*)"// interface ", 13);
  name->toString(buf);
  buf->linebreak();
}