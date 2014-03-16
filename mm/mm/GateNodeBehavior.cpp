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
//  GateNodeBehavior.cpp
//  mm
//
//  Created by Riemer van Rozen on 10/16/13.
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
#include "String.h"
#include "Location.h"
#include "Name.h"
#include "Element.h"
#include "Exp.h"
#include "Edge.h"
#include "NodeWorkItem.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "GateNodeBehavior.h"
#include "Declaration.h"
#include "Definition.h"
#include "Instance.h"

const MM::CHAR * MM::GateNodeBehavior::GATE_STR = "gate";
const MM::UINT32 MM::GateNodeBehavior::GATE_LEN =
  strlen(MM::GateNodeBehavior::GATE_STR);

MM::GateNodeBehavior::GateNodeBehavior(MM::NodeBehavior::IO   io,
                                       MM::NodeBehavior::When when,
                                       MM::NodeBehavior::Act  act,
                                       MM::NodeBehavior::How  how):
  NodeBehavior(io, when, act, how)
{
}

MM::GateNodeBehavior::~GateNodeBehavior()
{
}

MM::VOID MM::GateNodeBehavior::recycle(MM::Recycler *r)
{
  this->MM::NodeBehavior::recycle(r);
}

MM::TID MM::GateNodeBehavior::getTypeId()
{
  return MM::T_GateNodeBehavior;
}

MM::BOOLEAN MM::GateNodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_GateNodeBehavior)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::NodeBehavior::instanceof(tid);
  }
}

MM::UINT32 MM::GateNodeBehavior::getCreateMessage()
{
  return MM::MSG_NEW_GATE;
}

MM::UINT32 MM::GateNodeBehavior::getUpdateMessage()
{
  return MM::MSG_UPD_GATE;
}

MM::UINT32 MM::GateNodeBehavior::getDeleteMessage()
{
  return MM::MSG_DEL_GATE;
}

MM::VOID MM::GateNodeBehavior::stepPullAll(MM::Node * node,
                                           MM::Instance * i,
                                           MM::Vector<MM::NodeWorkItem *> * work,
                                           MM::Machine * m,
                                           MM::Transition * tr)
{
  //TODO
}

MM::VOID MM::GateNodeBehavior::stepPushAll(MM::Node * node,
                                           MM::Instance * i,
                                           MM::Vector<MM::NodeWorkItem *> * work,
                                           MM::Machine * m,
                                           MM::Transition * tr)
{
  //gates don't push
}

MM::VOID MM::GateNodeBehavior::begin(MM::Instance * i,
                                     MM::Machine * m,
                                     MM::Node * n)
{
  //TODO
}

MM::VOID MM::GateNodeBehavior::end(MM::Instance * i,
                                   MM::Machine * m,
                                   MM::Node * n)
{
  //TODO
}

MM::VOID MM::GateNodeBehavior::change(MM::Instance * i,
                                      MM::Machine * m,
                                      MM::Node * n)
{
  //TODO
}

MM::VOID MM::GateNodeBehavior::add(MM::Instance * i,
                                   MM::Machine * m,
                                   MM::Node * n,
                                   MM::UINT32 amount)
{
  //gate value is zero if not stored before
  MM::UINT32 tempValue = i->getGateValue(n);
  tempValue = tempValue + amount;
  i->setGateValue(n, tempValue);
}

MM::VOID MM::GateNodeBehavior::sub(MM::Instance * i,
                                   MM::Machine * m,                                   
                                   MM::Node * n,
                                   MM::UINT32 amount)
{
  //if the gate value is not available this should fail!
  MM::UINT32 tempValue = i->getGateValue(n);
 
  if(amount <= tempValue)
  {
    tempValue = tempValue - amount;
    i->setGateValue(n, tempValue);
  }
  else
  {
    //error
  }
}

MM::UINT32 MM::GateNodeBehavior::getCapacity(MM::Instance * i,
                                            MM::Node * n)
{
  //NOTE: we assume gates can propagate resources later
  return MM_MAX_RESOURCES;
}

MM::UINT32 MM::GateNodeBehavior::getResources(MM::Instance * i,
                                              MM::Node * n)
{
  //NOTE: when queried for pulling gates always reply no resources are available
  return 0;
}

MM::BOOLEAN MM::GateNodeBehavior::hasCapacity(MM::Instance * i,
                                              MM::Node * n,
                                              MM::UINT32 amount)
{
  return MM_TRUE;
}

MM::BOOLEAN MM::GateNodeBehavior::hasResources(MM::Instance * i,
                                               MM::Node * n,
                                               MM::UINT32 amount)
{
  return MM_FALSE;
}

MM::VOID MM::GateNodeBehavior::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::GateNodeBehavior::GATE_STR,
               MM::GateNodeBehavior::GATE_LEN);
}

MM::VOID MM::GateNodeBehavior::toString(MM::String * buf, MM::Name * name)
{
  MM::NodeBehavior::toString(buf, name);
  toString(buf);
  buf->space();
  name->toString(buf);
}