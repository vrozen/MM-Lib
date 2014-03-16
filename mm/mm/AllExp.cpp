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
 * The AllExp abstraction expresses a that the full available amount will
 * flow along a FlowEdge from a source node to target node.
 * @note A - all -> B equals A - A -> B
 * @package MM
 * @file    AllExp.cpp
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
#include "AllExp.h"

const MM::CHAR * MM::AllExp::ALL_STR = "all";
const MM::UINT32 MM::AllExp::ALL_LEN = strlen(MM::AllExp::ALL_STR);

/**
 * @fn MM::AllExp::AllExp() : MM::Exp()
 * Constructs an AllExp object.
 * @return new AllExp object
 */
MM::AllExp::AllExp() : MM::Exp()
{
  this->loc = MM_NULL;
}

/**
 * @fn MM::AllExp::AllExp() : MM::Exp()
 * Constructs an AllExp object.
 * @param source location
 * @return new AllExp object
 */

MM::AllExp::AllExp(MM::Location * loc) : MM::Exp()
{
  this->loc = loc;
}

/**
 * @fn MM::AllExp::~AllExp()
 * Deconstructs a VarExp object.
 */
MM::AllExp::~AllExp()
{
  loc = MM_NULL;
}

/**
 * @fn MM::VOID MM::AllExp::recycle(MM::Recycler * r)
 * Recycles an AllExp object in a Recycler.
 * @param r Recycler
 */
MM::VOID MM::AllExp::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::Exp::recycle(r);
}

/**
 * @fn MM::TID MM::AllExp::getTypeId()
 * @brief Retrieves the type id of a AllExp object.
 * @return type id
 */
MM::TID MM::AllExp::getTypeId()
{
  return MM::T_AllExp;
}

/**
 * @fn MM::BOOLEAN MM::AllExp::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::AllExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_AllExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

/**
 * @fn MM::VOID MM::AllExp::toString(MM::String * buf)
 * @brief Serializes an AllExp object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::AllExp::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::AllExp::ALL_STR, MM::AllExp::ALL_LEN);
}

