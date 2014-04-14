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
//  ReferenceNode.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/28/13.
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
#include "Exp.h"
#include "Edge.h"
#include "NodeWorkItem.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "PoolNodeBehavior.h"
#include "RefNodeBehavior.h"
#include "Declaration.h"
#include "Definition.h"
#include "Instance.h"
#include "InterfaceNode.h"

const MM::CHAR * MM::RefNodeBehavior::REF_STR = "ref";
const MM::UINT32 MM::RefNodeBehavior::REF_LEN =
  strlen(MM::RefNodeBehavior::REF_STR);

MM::RefNodeBehavior::RefNodeBehavior(MM::NodeBehavior::IO io):
  NodeBehavior(io, WHEN_ERROR, ACT_ERROR, HOW_ERROR)
{
  alias = MM_NULL;
}

MM::RefNodeBehavior::~RefNodeBehavior()
{
  alias = MM_NULL;
}

MM::VOID MM::RefNodeBehavior::recycle(MM::Recycler *r)
{
  this->MM::NodeBehavior::recycle(r);
}

MM::TID MM::RefNodeBehavior::getTypeId()
{
  return MM::T_RefNodeBehavior;
}

MM::BOOLEAN MM::RefNodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_RefNodeBehavior)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::NodeBehavior::instanceof(tid);
  }
}

MM::Edge * MM::RefNodeBehavior::getAlias()
{
  return alias;
}

MM::VOID MM::RefNodeBehavior::setAlias(MM::Edge * edge)
{
  if(alias != MM_NULL)
  {
    MM_printf("Warning: reset alias");
  }
  this->alias = edge;
}

MM::Node * MM::RefNodeBehavior::getReference()
{
  if(alias != MM_NULL)
  {
    MM::Node * src = alias->getSource();
    MM::NodeBehavior * behavior = src->getBehavior();
    if(behavior->getTypeId() == MM::T_RefNodeBehavior)
    {
      MM::RefNodeBehavior * ref = (MM::RefNodeBehavior *) behavior;
      return ref->getReference();
    }
    else
    {
      return src;
    }
  }
  else
  {
    //TODO: error
    MM_printf("Error: unresolved alias");
    return MM_NULL;
  }
}

MM::UINT32 MM::RefNodeBehavior::getCreateMessage()
{
  return MM::MSG_NEW_REF;
}

MM::UINT32 MM::RefNodeBehavior::getUpdateMessage()
{
  return MM::MSG_UPD_REF;
}

MM::UINT32 MM::RefNodeBehavior::getDeleteMessage()
{
  return MM::MSG_DEL_REF;
}

//resolve reference via alias edge and i to the correct i and node
/*
MM::Instance * MM::RefNodeBehavior::resolveInstance(MM::Instance * i,
                                                    MM::Node * aliasSrc,
                                                    MM::Node * aliasTgt)
{
  MM::Instance * aliasInstance = i;
  if(aliasTgt->instanceof(MM::T_InterfaceNode) == MM_TRUE)
  {
    aliasInstance = i->getParent();
  }

  if(aliasSrc->instanceof(MM::T_InterfaceNode) == MM_TRUE)
  {
    MM::InterfaceNode * iNode = (MM::InterfaceNode *) aliasSrc;
    MM::Declaration * decl = iNode->getDeclaration();
    aliasInstance = aliasInstance->getInstance(decl);
  }
  
  return aliasInstance;
}*/



MM::VOID MM::RefNodeBehavior::step(MM::Node * n,
              MM::Instance * i,
              MM::Machine * m,
              MM::Transition * t)
{
  //refnodes don't act
}

MM::VOID MM::RefNodeBehavior::stepPullAny(MM::Node * tgtNode,
                                          MM::Instance * tgtInstance,
                                          MM::Vector<MM::NodeWorkItem *> * work,
                                          MM::Machine * m,
                                          MM::Transition * tr)
{
  //refnodes don't act
}

MM::VOID MM::RefNodeBehavior::stepPushAny(MM::Node * srcNode,
                                          MM::Instance * srcInstance,
                                          MM::Vector<MM::NodeWorkItem *> * work,
                                          MM::Machine * m,
                                          MM::Transition * tr)
{
  //refnodes don't act
}

MM::VOID MM::RefNodeBehavior::stepPullAll(MM::Node * tgtNode,
                                          MM::Instance * tgtInstance,
                                          MM::Vector<MM::NodeWorkItem *> * work,
                                          MM::Machine * m,
                                          MM::Transition * tr)
{
  //refnodes don't act
}

MM::VOID MM::RefNodeBehavior::stepPushAll(MM::Node * srcNode,
                                          MM::Instance * srcInstance,
                                          MM::Vector<MM::NodeWorkItem *> * work,
                                          MM::Machine * m,
                                          MM::Transition * tr)
{
  //refnodes don't act
}

MM::VOID MM::RefNodeBehavior::begin(MM::Instance * i,
                                    MM::Machine * m,
                                    MM::Node * n)
{
  //do nothing
}

MM::VOID MM::RefNodeBehavior::end(MM::Instance * i,
                                  MM::Machine * m,
                                  MM::Node * n)
{
  //do nothing
}

MM::VOID MM::RefNodeBehavior::change(MM::Instance * i,
                                     MM::Machine * m,
                                     MM::Node * n)
{
  //do nothing
}

MM::VOID MM::RefNodeBehavior::add(MM::Instance * i,
                                  MM::Machine * m,
                                  MM::Node * n,
                                  MM::UINT32 amount)
{
  MM_printf("SHOULD NOT HAPPEN ANYMORE MM::RefNodeBehavior::add");
  
  //MM::Node * aliasSrc = alias->getSource();
  //MM::Node * aliasTgt = alias->getTarget();
  //MM::Instance * aliasInstance = resolveInstance(i, aliasSrc, aliasTgt);
  //aliasSrc->add(aliasInstance, amount);
}

MM::VOID MM::RefNodeBehavior::sub(MM::Instance * i,
                                  MM::Machine * m,
                                  MM::Node * n,
                                  MM::UINT32 amount)
{
  MM_printf("SHOULD NOT HAPPEN ANYMORE MM::RefNodeBehavior::sub");

  //MM::Node * aliasSrc = alias->getSource();
  //MM::Node * aliasTgt = alias->getTarget();
  //MM::Instance * aliasInstance = resolveInstance(i, aliasSrc, aliasTgt);
  //aliasSrc->sub(aliasInstance, amount);
}

MM::UINT32 MM::RefNodeBehavior::getCapacity(MM::Instance * i,
                                            MM::Node * n)
{
  MM_printf("SHOULD NOT HAPPEN ANYMORE MM::RefNodeBehavior::getCapacity\n");
  //MM::Node * aliasSrc = alias->getSource();
  //MM::Node * aliasTgt = alias->getTarget();
  //MM::Instance * aliasInstance = resolveInstance(i, aliasSrc, aliasTgt);
  //return aliasSrc->getCapacity(aliasInstance);
  return 0;
}

MM::UINT32 MM::RefNodeBehavior::getResources(MM::Instance * i,
                                             MM::Node * n)
{
  MM_printf("SHOULD NOT HAPPEN ANYMORE MM::RefNodeBehavior::getResources\n");
  //MM::Node * aliasSrc = alias->getSource();
  //MM::Node * aliasTgt = alias->getTarget();
  //MM::Instance * aliasInstance = resolveInstance(i, aliasSrc, aliasTgt);
  //return aliasSrc->getResources(aliasInstance);
  return 0;
}

MM::BOOLEAN MM::RefNodeBehavior::hasCapacity(MM::Instance * i,
                                             MM::Node * n,
                                             MM::UINT32 amount)
{
  MM_printf("SHOULD NOT HAPPEN ANYMORE MM::RefNodeBehavior::hasCapacity\n");
  //MM::Node * aliasSrc = alias->getSource();
  //MM::Node * aliasTgt = alias->getTarget();
  //MM::Instance * aliasInstance = resolveInstance(i, aliasSrc, aliasTgt);
  //return aliasSrc->hasCapacity(aliasInstance, amount);
  return MM_FALSE;
}

MM::BOOLEAN MM::RefNodeBehavior::hasResources(MM::Instance * i,
                                              MM::Node * n,
                                              MM::UINT32 amount)
{
  MM_printf("SHOULD NOT HAPPEN ANYMORE MM::RefNodeBehavior::hasResources\n");
  //MM::Node * aliasSrc = alias->getSource();
  //MM::Node * aliasTgt = alias->getTarget();
  //MM::Instance * aliasInstance = resolveInstance(i, aliasSrc, aliasTgt);
  //return aliasSrc->hasResources(aliasInstance, amount);
  return MM_FALSE;
}

MM::VOID MM::RefNodeBehavior::doTriggers(MM::Instance * i,
                                         MM::Node * n)
{
  MM_printf("SHOULD NOT HAPPEN ANYMORE MM::RefNodeBehavior::doTriggers\n");
}


MM::VOID MM::RefNodeBehavior::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::RefNodeBehavior::REF_STR,
              MM::RefNodeBehavior::REF_LEN);
}

MM::VOID MM::RefNodeBehavior::toString(MM::String * buf, MM::Name * name)
{
  MM::NodeBehavior::toString(buf,name);
  toString(buf);
  buf->space();
  name->toString(buf);
}