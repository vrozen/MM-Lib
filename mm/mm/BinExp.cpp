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
/*!
 * The BinExp abstraction defines binary expressions.
 * @package MM
 * @file    BinExp.h
 * @author  Riemer van Rozen
 * @date    July 18th 2013
 */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Operator.h"
#include "Exp.h"
#include "BinExp.h"

MM::BinExp::BinExp(Exp              * e1,
                   MM::Operator::OP   op,
                   Exp              * e2) : MM::Exp()
{
  this->e1  = e1;
  this->op  = op;
  this->e2  = e2;
  this->loc = MM_NULL;
}

MM::BinExp::BinExp(Exp              * e1,
                   MM::Operator::OP   op,
                   Exp              * e2,
                   MM::Location     * loc) : MM::Exp()
{
  this->e1  = e1;
  this->op  = op;
  this->e2  = e2;
  this->loc = loc;
}

MM::BinExp::~BinExp()
{
  e1 = MM_NULL;
  e2 = MM_NULL;
  loc = MM_NULL;
}

MM::VOID MM::BinExp::recycle(MM::Recycler * r)
{
  e1->recycle(r);
  e2->recycle(r);
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::Exp::recycle(r);
}

MM::TID MM::BinExp::getTypeId()
{
  return MM::T_BinExp;
}

MM::BOOLEAN MM::BinExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_BinExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

MM::BOOLEAN MM::BinExp::isTriggerExp()
{
  MM::BOOLEAN r = MM_FALSE;
  if(op == Operator::OP_MUL &&
    e1->getTypeId() == MM::T_OneExp &&
    e2->getTypeId() == MM::T_OneExp)
  {
    r = MM_TRUE;
  }
  return r;
}

MM::Exp * MM::BinExp::getLhsExp()
{
  return this->e1;
}

MM::Exp * MM::BinExp::getRhsExp()
{
  return this->e2;
}

MM::Operator::OP MM::BinExp::getOperator()
{
  return this->op;
}

MM::VOID MM::BinExp::toString(MM::String * buf)
{
  e1->toString(buf);
  buf->space();
  buf->append((MM::CHAR*) MM::Operator::OP_STR[op], MM::Operator::OP_LEN[op]);
  buf->space();
  e2->toString(buf);
}
