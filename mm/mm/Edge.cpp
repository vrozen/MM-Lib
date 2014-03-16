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
//  Edge.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
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
#include "Operator.h"
#include "Exp.h"
#include "Edge.h"
#include "FlowEdge.h"
#include "NodeWorkItem.h"
#include "NodeBehavior.h"
#include "Node.h"

const MM::CHAR MM::Edge::COLON_CHAR = ':';

MM::Edge::Edge(MM::Name * name,
               MM::Name * src,
               MM::Exp * exp,
               MM::Name * tgt): MM::Element(name)
{
  this->srcName = src;
  this->exp = exp;
  this->tgtName = tgt;
  this->srcNode = MM_NULL;
  this->tgtNode = MM_NULL;
}

MM::Edge::~Edge()
{
  this->srcName = MM_NULL;
  this->exp = MM_NULL;
  this->tgtName = MM_NULL;
  this->srcNode = MM_NULL;
  this->tgtNode = MM_NULL;
}

MM::VOID MM::Edge::recycle(MM::Recycler * r)
{
  if(srcName != MM_NULL)
  {
    srcName->recycle(r);
  }
  if(tgtName != MM_NULL)
  {
    tgtName->recycle(r);
  }
  exp->recycle(r);
  this->Element::recycle(r);
}

MM::TID MM::Edge::getTypeId()
{
  return MM::T_Edge;
}

MM::BOOLEAN MM::Edge::instanceof(MM::TID tid)
{
  if(tid == MM::T_Edge)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}

MM::Node * MM::Edge::getSource()
{
  return this->srcNode;
}

MM::Node * MM::Edge::getTarget()
{
  return this->tgtNode;
}

MM::Exp * MM::Edge::getExp()
{
  return this->exp;
}

MM::VOID MM::Edge::setExp(MM::Exp * exp)
{
  this->exp = exp;
}

MM::VOID MM::Edge::setSource(MM::Node * src)
{
  this->srcNode = src;
}

MM::VOID MM::Edge::setTarget(MM::Node * tgt)
{
  this->tgtNode = tgt;
}

MM::Name * MM::Edge::getSourceName()
{
  return this->srcName;
}

MM::Name * MM::Edge::getTargetName()
{
  return this->tgtName;
}

MM::VOID MM::Edge::toString(MM::String * buf, MM::UINT32 indent)
{
  buf->space(indent);
  if(name != MM_NULL)
  {
    name->toString(buf);
    buf->append(MM::Edge::COLON_CHAR);
    buf->space();
  }
}

