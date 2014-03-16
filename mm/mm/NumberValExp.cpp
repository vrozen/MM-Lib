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
 * The NumberValExp abstraction defines number value expressions.
 * @package MM
 * @file    NumberValExp.cpp
 * @author  Riemer van Rozen
 * @date    July 19th 2013
 */
/******************************************************************************/
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
#include "Exp.h"
#include "ValExp.h"
#include "NumberValExp.h"

const MM::CHAR MM::NumberValExp::DOT_CHAR = '.';

MM::NumberValExp::NumberValExp(MM::INT32 val) : MM::ValExp()
{
  this->val = val * 100;
  this->loc = MM_NULL;
}

MM::NumberValExp::NumberValExp(MM::INT32 val,
                               MM::Location * loc) : MM::ValExp()
{
  this->val = val * 100;
  this->loc = loc;
}

MM::NumberValExp::NumberValExp(MM::INT32 val,
                               MM::UINT8 fraction) : MM::ValExp()
{
  this->val = (val * 100) + (fraction % 100);
  this->loc = MM_NULL;
}

MM::NumberValExp::NumberValExp(MM::INT32 val,
                               MM::UINT8 fraction,
                               MM::Location * loc) : MM::ValExp()
{
  this->val = val * 100 + (fraction %100);
  this->loc = loc;
}

MM::NumberValExp::~NumberValExp()
{
  this->val = 0;
  this->loc = MM_NULL;
}

MM::VOID MM::NumberValExp::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::ValExp::recycle(r);
}

MM::TID MM::NumberValExp::getTypeId()
{
  return MM::T_NumberValExp;
}

MM::BOOLEAN MM::NumberValExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_NumberValExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::ValExp::instanceof(tid);
  }
}

MM::INT32 MM::NumberValExp::getValue()
{
  return val;
}

MM::INT32 MM::NumberValExp::getIntValue()
{
  return val / 100;
}

MM::Location *  MM::NumberValExp::getLocation()
{
  return loc;
}

MM::BOOLEAN MM::NumberValExp::greaterEquals(MM::UINT32 val)
{
  if(((MM::INT32)val) >= this->val)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::VOID MM::NumberValExp::toString(MM::String * buf)
{
  buf->appendInt(val / 100);
  if(val % 100 != 0)
  {
    buf->append(MM::NumberValExp::DOT_CHAR);
    buf->appendInt(val % 100);
  }
}

