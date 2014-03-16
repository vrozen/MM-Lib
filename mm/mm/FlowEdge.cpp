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
//  FlowEdge.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/11/13.

#include <stdio.h>
#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Recycler.h"
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
#include "FlowEdge.h"

const MM::CHAR* MM::FlowEdge::MIN_STR    = "-";
const MM::CHAR* MM::FlowEdge::MINGT_STR  = "->";
const MM::UINT32 MM::FlowEdge::MIN_LEN   = strlen(MM::FlowEdge::MIN_STR);
const MM::UINT32 MM::FlowEdge::MINGT_LEN = strlen(MM::FlowEdge::MINGT_STR);

MM::FlowEdge::FlowEdge(MM::Name * name,
                       MM::Name * src,
                       MM::Exp  * exp,
                       MM::Name * tgt) : MM::Edge(name, src, exp, tgt)
{
}

MM::FlowEdge::~FlowEdge()
{
}

MM::VOID MM::FlowEdge::recycle(MM::Recycler *r)
{
  this->MM::Edge::recycle(r);
}

MM::TID MM::FlowEdge::getTypeId()
{
  return MM::T_FlowEdge;
}

MM::BOOLEAN MM::FlowEdge::instanceof(MM::TID tid)
{
  if(tid == MM::T_FlowEdge)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Edge::instanceof(tid);
  }
}

MM::VOID MM::FlowEdge::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::FlowEdge::toString(MM::String * buf, MM::UINT32 indent)
{
  MM::Edge::toString(buf, indent);
  getSourceName()->toString(buf);
  buf->space();
  buf->append((MM::CHAR*)MM::FlowEdge::MIN_STR, MM::FlowEdge::MIN_LEN);
  getExp()->toString(buf);
  buf->append((MM::CHAR*)MM::FlowEdge::MINGT_STR, MM::FlowEdge::MINGT_LEN);
  buf->space();
  getTargetName()->toString(buf);
}
