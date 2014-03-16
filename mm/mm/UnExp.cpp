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
 * The UnExp abstraction defines unary expressions.
 * @package MM
 * @file    UnExp.cpp
 * @author  Riemer van Rozen
 * @date    July 19th 2013
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
#include "UnExp.h"

MM::UnExp::UnExp(MM::Operator::OP op,
                 Exp * exp) : MM::Exp()
{
  this->exp = exp;
  this->op = op;
}

MM::UnExp::UnExp(MM::Operator::OP op,
                 Exp * exp,                 
                 MM::Location * loc) : MM::Exp()
{
  this->exp = exp;
  this->op = op;
  this->loc = loc;
}

MM::UnExp::~UnExp()
{
  exp = MM_NULL;
  loc = MM_NULL;
}

MM::VOID MM::UnExp::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  exp->recycle(r);
  this->MM::Exp::recycle(r);
}

MM::TID MM::UnExp::getTypeId()
{
  return MM::T_UnExp;
}

MM::BOOLEAN MM::UnExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_UnExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

MM::Exp * MM::UnExp::getExp()
{
  return this->exp;
}

MM::Operator::OP MM::UnExp::getOperator()
{
  return this->op;
}

MM::VOID MM::UnExp::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::Operator::OP_STR[op], MM::Operator::OP_LEN[op]);
  buf->space();
  exp->toString(buf);
}