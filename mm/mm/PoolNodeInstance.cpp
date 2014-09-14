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
//  PoolNodeInstance.cpp
//  mm
//
//  Created by Riemer van Rozen on September 14th 2014
//
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
#include "PoolNodeInstance.h"

MM::PoolNodeInstance::PoolNodeInstance(MM::Node * poolNode,
                                       MM::Instance * instance,
                                       MM::INT32 initVal):
                      MM::Observer(),
                      MM::Observable()
{
  this->poolNode = poolNode;
  this->instance = instance;
  this->val = initVal;
  this->oldVal = initVal;
  this->newVal = initVal;
  this->dirty = MM_TRUE;
}

MM::PoolNodeInstance::~PoolNodeInstance()
{
  this->poolNode = MM_NULL;
  this->instance = MM_NULL;
  this->val = 0;
  this->oldVal = 0;
  this->newVal = 0;
  this->dirty = MM_FALSE;
}

MM::Node * MM::PoolNodeInstance::getNode()
{
  return this->poolNode;
}

MM::Instance * MM::PoolNodeInstance::getInstance()
{
  return this->instance;
}

//MM::VOID recycle(MM::Recycler * r);
//MM::TID getTypeId();
//MM::BOOLEAN instanceof(MM::TID tid);
//add the end of a step
MM::VOID MM::PoolNodeInstance::setValue(MM::INT32 val)
{
  this->val = val;
}

//during a step
MM::VOID MM::PoolNodeInstance::setOldValue(MM::INT32 oldVal)
{
  this->oldVal = oldVal;
}

//during a step
MM::VOID MM::PoolNodeInstance::setNewValue(MM::INT32 newVal)
{
  this->newVal = newVal;
}

//in between steps
MM::INT32 MM::PoolNodeInstance::getValue()
{
  return this->val;
}

//during a step
MM::INT32 MM::PoolNodeInstance::getOldValue()
{
  return this->oldVal;
}

//during a step
MM::INT32 MM::PoolNodeInstance::getNewValue()
{
  return this->newVal;
}

//during a step
MM::VOID MM::PoolNodeInstance::setDirty(MM::BOOLEAN dirty)
{
  this->dirty = dirty;
}

//in between steps
MM::BOOLEAN MM::PoolNodeInstance::isDirty()
{
  return this->dirty;
}

//begin step
MM::VOID MM::PoolNodeInstance::begin()
{
  //copy values to old and new
  oldVal = val;
  newVal = val;
  this->setDirty(MM_FALSE);
}

//finalize step
MM::VOID MM::PoolNodeInstance::finalize()
{
  if(val != newVal)
  {
    //printf("PNI %lu %s value is %ld was %ld becomes %ld\n", this, poolNode->getName()->getBuffer(), val, oldVal, newVal);
    //fflush(stdout);
    this->setDirty(MM_TRUE);
    val = newVal;
  }
}

MM::VOID MM::PoolNodeInstance::update(MM::Observable * observable,
                                      MM::VOID * aux,
                                      MM::UINT32 message,
                                      MM::VOID * object)
{
  switch(message)
  {
    case MM::MSG_UPD_VALUE:
      MM_printf("PoolNodeInstance: Sees poolNodeInstance %s change\n",
             ((MM::Node*)observable)->getName()->getBuffer());
      //a pool node instance we're observing changed (part of the add-expression)
      //this means our observable value changed
      //and that we should inform anyone observing this pool node instance
      this->setDirty(MM_TRUE);
      break;
    case MM::MSG_END_VALUE:
      MM_printf("PoolNodeInstance: Sees poolNodeInstance %s end\n",
             ((MM::Node*)observable)->getName()->getBuffer());
      //any pool node instance listening to a value end should trigger a run-time exception
      break;
    default:
      break;
  }
}