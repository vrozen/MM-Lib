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
 * The ActiveExp abstraction expresses that a target of a state edge
 * with an ActiveExp is only active if the source is active.
 * \package MM
 * \file    ActiveExp.h
 * \author  Riemer van Rozen
 * \date    July 21th 2013
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
#include "Exp.h"
#include "ActiveExp.h"

const MM::CHAR * MM::ActiveExp::ACTIVE_STR = "active";
const MM::UINT32 MM::ActiveExp::ACTIVE_LEN = 6;

/**
 * Constructs a ActiveExp object.
 * \param name name
 * \return new ActiveExp object
 */
MM::ActiveExp::ActiveExp(MM::Name * name) : MM::Exp()
{
  this->name = name;
  this->loc = MM_NULL;
}

/**
 * Constructs a ActiveExp object.
 * \param name name
 * \param loc source location
 * \return new ActiveExp object
 */
MM::ActiveExp::ActiveExp(MM::Name * name, MM::Location * loc) : MM::Exp()
{
  this->name = name;
  this->loc = loc;
}

/**
 * Destructs an ActiveExp object.
 */
MM::ActiveExp::~ActiveExp()
{
  name = MM_NULL;
  loc = MM_NULL;
}

/**
 * Recycles an ActiveExp object in a Recycler.
 * \param r Recycler
 */
MM::VOID MM::ActiveExp::recycle(MM::Recycler *r)
{
  name->recycle(r);
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::Exp::recycle(r);
}

/**
 * \brief Retrieves the type id of a ActiveExp object.
 * \return type id
 */
MM::TID MM::ActiveExp::getTypeId()
{
  return MM::T_ActiveExp;
}

/**
 * \brief Assesses if an object is an instance of a type tid.
 * \param tid type id
 * \return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::ActiveExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_ActiveExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

/**
 * \brief Retrieves the name of an ActiveExp object.
 * \return name
 */
MM::Name * MM::ActiveExp::getName()
{
  return name;
}

/**
 * \brief Serializes an ActiveExp object into a String buffer.
 * \param buf String buffer to serialize this object into
 */
MM::VOID MM::ActiveExp::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::ActiveExp::ACTIVE_STR,
              MM::ActiveExp::ACTIVE_LEN);
  buf->space();
  name->toString(buf);
}
