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
 * The RangeValExp abstraction defines range value expressions.
 * @package MM
 * @file    RangeValExp.cpp
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
#include "RangeValExp.h"

const MM::CHAR * MM::RangeValExp::DOTDOT_STR = "..";
const MM::UINT32 MM::RangeValExp::DOTDOT_LEN =
  strlen(MM::RangeValExp::DOTDOT_STR);

MM::RangeValExp::RangeValExp(MM::UINT32 min,
                             MM::UINT32 max) : MM::ValExp()
{
  this->min = min;
  this->max = max;
  this->minLoc = MM_NULL;
  this->rangeLoc = MM_NULL;
  this->maxLoc = MM_NULL;
}

MM::RangeValExp::RangeValExp(MM::UINT32     min,
                             MM::UINT32     max,
                             MM::Location * minLoc,
                             MM::Location * rangeLoc,
                             MM::Location * maxLoc) : MM::ValExp()
{
  this->min = min;
  this->max = max;
  this->minLoc = minLoc;
  this->rangeLoc = rangeLoc;
  this->maxLoc = maxLoc;
}

MM::RangeValExp::~RangeValExp()
{
  min = 0;
  max = 0;
  minLoc = MM_NULL;
  rangeLoc = MM_NULL;
  maxLoc = MM_NULL;
}

MM::VOID MM::RangeValExp::recycle(MM::Recycler * r)
{
  if(minLoc != MM_NULL)
  {
    maxLoc->recycle(r);
  }
  if(maxLoc != MM_NULL)
  {
    maxLoc->recycle(r);
  }
  if(rangeLoc != MM_NULL)
  {
    rangeLoc->recycle(r);
  }
  this->MM::ValExp::recycle(r);
}

MM::TID MM::RangeValExp::getTypeId()
{
  return MM::T_RangeValExp;
}

MM::BOOLEAN MM::RangeValExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_RangeValExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::ValExp::instanceof(tid);
  }
}

MM::UINT32 MM::RangeValExp::getMin()
{
  return this->min;
}

MM::UINT32 MM::RangeValExp::getMax()
{
  return this->max;
}

MM::INT32 MM::RangeValExp::getIntValue()
{
  return (rand() % (max-min+1) + min); //random number between min and max
}

//NOTE: if the flow is at least min then this value "satisfies"
MM::BOOLEAN MM::RangeValExp::greaterEquals(MM::UINT32 val)
{
  if(val > this->min)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::VOID MM::RangeValExp::toString(MM::String * buf)
{
  buf->appendInt(min);
  buf->append((MM::CHAR *) MM::RangeValExp::DOTDOT_STR,
              MM::RangeValExp::DOTDOT_LEN);
  buf->appendInt(max);
}