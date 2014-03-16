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
 * The OneExp abstraction expresses shorthand on edges
 *  -->    : OneExp has a flow of one: NumberValueExp(1)
 *  . * .> : BinExp has lhs OneExp and rhs OneExp: isTrigger() = MM_TRUE
 *  . == .>: BinExp has lhs OneExp and rhs OneExp:
 *           lhs OneExp refers to source and rhs OneExp refers to target
 * @package MM
 * @file    AliasExp.h
 * @author  Riemer van Rozen
 * @date    July 20th 2013
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
#include "Exp.h"
#include "ValExp.h"
#include "OneExp.h"

/**
 * @fn MM::OneExp::OneExp() : MM::Exp()
 * Constructs a OneExp object.
 * @return new OneExp object
 */
MM::OneExp::OneExp() : MM::ValExp()
{
  this->loc = MM_NULL;
}

/**
 * @fn MM::OneExp::OneExp(MM::Location * loc) : MM::Exp()
 * Constructs a OneExp object.
 * @param loc source location
 * @return new OneExp object
 */
MM::OneExp::OneExp(MM::Location * loc) : MM::ValExp()
{
  this->loc = loc;
}

/**
 * @fn MM::OneExp::~OneExp()
 * Destructs an OneExp object.
 */
MM::OneExp::~OneExp()
{
  loc = MM_NULL;
}

/**
 * @fn MM::VOID MM::OneExp::recycle(MM::Recycler * r)
 * Recycles an OneExp object in a Recycler.
 * @param r Recycler
 */
MM::VOID MM::OneExp::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::ValExp::recycle(r);
}

/**
 * @fnMM::TID MM::OneExp::getTypeId()
 * @brief Retrieves the type id of a OneExp object.
 * @return type id
 */
MM::TID MM::OneExp::getTypeId()
{
  return MM::T_OneExp;
}

/**
 * @fn MM::BOOLEAN MM::OneExp::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::OneExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_OneExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::ValExp::instanceof(tid);
  }
}

MM::BOOLEAN MM::OneExp::greaterEquals(MM::UINT32 val)
{
  if(val >= 1)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

/**
 * @fn MM::VOID MM::OneExp::toString(MM::String * buf)
 * @brief Serializes an OneExp object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::OneExp::toString(MM::String * buf)
{
  //write nothing
}
