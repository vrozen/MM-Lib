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
//  StateEdge.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/11/13.
//

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
#include "BinExp.h"
#include "Edge.h"
#include "NodeWorkItem.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "StateEdge.h"

const MM::CHAR * MM::StateEdge::DOT_STR   = ".";
const MM::CHAR * MM::StateEdge::DOTGT_STR = ".>";
const MM::UINT32 MM::StateEdge::DOT_LEN   = strlen(MM::StateEdge::DOT_STR);
const MM::UINT32 MM::StateEdge::DOTGT_LEN = strlen(MM::StateEdge::DOTGT_STR);

MM::StateEdge::StateEdge(MM::Name * name,
                         MM::Name * src,
                         MM::Exp  * exp,
                         MM::Name * tgt) : MM::Edge(name, src, exp, tgt)
{
}

MM::StateEdge::~StateEdge()
{
}

MM::VOID MM::StateEdge::recycle(MM::Recycler *r)
{
  this->MM::Edge::recycle(r);
}

MM::TID MM::StateEdge::getTypeId()
{
  return MM::T_StateEdge;
}

MM::BOOLEAN MM::StateEdge::instanceof(MM::TID tid)
{
  if(tid == MM::T_StateEdge)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Edge::instanceof(tid);
  }
}

MM::BOOLEAN MM::StateEdge::isTrigger()
{
  MM::BOOLEAN r = MM_FALSE;
  MM::Exp * exp = this->getExp();
  if(exp != MM_NULL)
  {
    if(exp->getTypeId() == MM::T_BinExp)
    {
      MM::BinExp * binExp = (MM::BinExp *) exp;
      r = binExp->isTriggerExp();
    }
  }
  return r;
}

MM::BOOLEAN MM::StateEdge::isAlias()
{
  MM::BOOLEAN r = MM_FALSE;
  MM::Exp * exp = this->getExp();
  if(exp != MM_NULL)
  {
    if(exp->getTypeId() == MM::T_AliasExp)
    {
      r = MM_TRUE;
    }
  }
  return r;
}

MM::BOOLEAN MM::StateEdge::isCondition()
{
  MM::BOOLEAN r = MM_FALSE;
  if(isTrigger() == MM_FALSE && isAlias() == MM_FALSE)
  {
    r = MM_TRUE;
  }
  return r;
}

MM::VOID MM::StateEdge::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::StateEdge::toString(MM::String * buf, MM::UINT32 indent)
{
  //prevent output of anonymous state edges
  if(getSourceName() != MM_NULL && getTargetName() != MM_NULL)
  {
    MM::Edge::toString(buf, indent);
    getSourceName()->toString(buf);
    buf->space();
    buf->append((MM::CHAR*)MM::StateEdge::DOT_STR, MM::StateEdge::DOT_LEN);
    getExp()->toString(buf);
    buf->append((MM::CHAR*)MM::StateEdge::DOTGT_STR, MM::StateEdge::DOTGT_LEN);
    buf->space();
    getTargetName()->toString(buf);
  }
}
