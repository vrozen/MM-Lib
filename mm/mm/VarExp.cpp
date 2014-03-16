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
 * The VarExp abstraction defines expressions that reference a pool.
 * @package MM
 * @file    VarExp.cpp
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
//#include "Element.h"
//#include "Operator.h"
#include "Exp.h"
//#include "Edge.h"
//#include "NodeBehavior.h"
//#include "Node.h"
#include "VarExp.h"

/**
 * Constructs an VarExp object.
 * \param name Name of the pool this expression refers to.
 * \return new VarExp object
 */
MM::VarExp::VarExp(MM::Name * name) : MM::Exp()
{
  this->name = name;
}

/**
 * Deconstructs a VarExp object.
 * \note Only called by Recylcer.
 */
MM::VarExp::~VarExp()
{
  name = MM_NULL;
}

/**
 * Recycles an VarExp object in a Recycler.
 * \param r Recycler
 */
MM::VOID MM::VarExp::recycle(MM::Recycler * r)
{
  name->recycle(r);
  this->MM::Exp::recycle(r);
}

/**
 * \brief Retrieves the type id of a VarExp object.
 * \return type id
 */
MM::TID MM::VarExp::getTypeId()
{
  return MM::T_VarExp;
}

/**
 * \brief Assesses if an object is an instance of a type tid.
 * \param tid type id
 * \return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::VarExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_VarExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

MM::Name * MM::VarExp::getName()
{
  return name;
}


/**
 * \brief Serializes an VarExp object into a String buffer.
 * \param buf String buffer to serialize this object into
 */
MM::VOID MM::VarExp::toString(MM::String * buf)
{
  name->toString(buf);
}
