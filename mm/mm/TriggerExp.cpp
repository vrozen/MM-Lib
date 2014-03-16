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
 * The TriggerExp abstraction expresses that a source of a state edge
 * activates the target of that edge if all of the edge the source operates
 * on are satisfied (meaning a flow of one or more exists for that edge).
 * @note The notion of satisfied does not respect all or any modifiers of nodes.
 * @package MM
 * @file    TriggerExp.cpp
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
#include "TriggerExp.h"

const MM::CHAR MM::TriggerExp::TRIGGER_CHAR = '*';

/**
 * @fn MM::Exp::Exp() : MM::Recyclable()
 * Constructs a TriggerExp object.
 * @return new TriggerExp object
 */
MM::TriggerExp::TriggerExp() : MM::Exp()
{
  this->loc = MM_NULL;
}

/**
 * @fn MM::TriggerExp::TriggerExp(MM::Location * loc) : MM::Exp()
 * Constructs a TriggerExp object.
 * @param loc source location
 * @return new TriggerExp object
 */
MM::TriggerExp::TriggerExp(MM::Location * loc) : MM::Exp()
{
  this->loc = loc;
}

/**
 * @fn MM::TriggerExp::~TriggerExp()
 * Descructs a TriggerExp object.
 */
MM::TriggerExp::~TriggerExp()
{
}

/**
 * @fn MM::VOID MM::TriggerExp::recycle(MM::Recycler *r)
 * Recycles a TriggerExp object in a Recycler.
 * @param r Recycler object
 */
MM::VOID MM::TriggerExp::recycle(MM::Recycler *r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::Exp::recycle(r);
}

/**
 * @fn MM::TID MM::Exp::getTypeId()
 * @brief Retrieves the type id of a TriggerExp object.
 * @return type id
 */
MM::TID MM::TriggerExp::getTypeId()
{
  return MM::T_TriggerExp;
}

/**
 * @fn MM::BOOLEAN MM::TriggerExp::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::TriggerExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_TriggerExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

/**
 * @fn MM::VOID MM::TriggerExp::toString(MM::String * buf)
 * @brief Serializes a TriggerExp object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::TriggerExp::toString(MM::String * buf)
{
  buf->append(MM::TriggerExp::TRIGGER_CHAR);
}
