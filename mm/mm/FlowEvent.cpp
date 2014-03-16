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
//  FlowEvent.cpp
//  mm
//
//  Created by Riemer van Rozen on 1/30/14.
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
#include "FlowEvent.h"
#include "Operator.h"
#include "Exp.h"
#include "Assertion.h"
#include "Deletion.h"
#include "Activation.h"
#include "Signal.h"
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

MM::FlowEvent::FlowEvent(MM::Instance * actInstance,
                         MM::Node     * actNode,
                         MM::Edge     * actEdge,
                         MM::Instance * srcInstance,
                         MM::Node     * srcNode,
                         MM::UINT32     amount,
                         MM::Instance * tgtInstance,
                         MM::Node     * tgtNode) : MM::Element(MM_NULL)
{
  this->actInstance = actInstance;
  this->actNode = actNode,
  this->actEdge = actEdge,
  this->srcInstance = srcInstance;
  this->srcNode = srcNode;
  this->amount = amount;
  this->tgtInstance = tgtInstance;
  this->tgtNode = tgtNode;
}

MM::FlowEvent::~FlowEvent()
{
  this->actInstance = MM_NULL;
  this->actNode = MM_NULL,
  this->actEdge = MM_NULL,
  this->srcInstance = MM_NULL;
  this->srcNode = MM_NULL;
  this->amount = MM_NULL;
  this->tgtInstance = MM_NULL;
  this->tgtNode = MM_NULL;
}

MM::VOID MM::FlowEvent::recycle(MM::Recycler *r)
{
  this->MM::Element::recycle(r);
}

MM::TID MM::FlowEvent::getTypeId()
{
  return MM::T_FlowEvent;
}

MM::BOOLEAN MM::FlowEvent::instanceof(MM::TID tid)
{
  if(tid == MM::T_FlowEvent)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}

MM::Node * MM::FlowEvent::getSourceNode()
{
  return srcNode;
}

MM::UINT32 MM::FlowEvent::getAmount()
{
  return amount;
}

MM::Node * MM::FlowEvent::getTargetNode()
{
  return tgtNode;
}

MM::Instance * MM::FlowEvent::getActInstance()
{
  return actInstance;
}

MM::Edge * MM::FlowEvent::getActEdge()
{
  return actEdge;
}

MM::Node * MM::FlowEvent::getActNode()
{
  return actNode;
}

MM::Instance * MM::FlowEvent::getSourceInstance()
{
  return srcInstance;
}

MM::Instance * MM::FlowEvent::getTargetInstance()
{
  return tgtInstance;
}

MM::VOID MM::FlowEvent::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::FlowEvent::toString(MM::String * buf, MM::UINT32 indent)
{
  srcInstance->nameToString(srcNode, buf);
  buf->space();
  buf->append('-');
  buf->appendInt(amount);
  buf->append('-');
  buf->append('>');
  buf->space();
  tgtInstance->nameToString(tgtNode, buf);
}