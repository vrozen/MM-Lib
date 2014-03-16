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
//  Assert.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/29/13.
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
#include "Exp.h"
#include "Assertion.h"

const MM::CHAR * MM::Assertion::ASSERT_STR = "assert";
const MM::UINT32 MM::Assertion::ASSERT_LEN = strlen(MM::Assertion::ASSERT_STR);
const MM::CHAR   MM::Assertion::COLON_CHAR = ':';

MM::Assertion::Assertion(MM::Name     * name,
                         MM::Exp      * exp,
                         MM::CHAR     * msg,
                         MM::Location * loc) : MM::Element(name)
{
  this->exp = exp;
  this->msg = msg;
  this->loc = loc;
}

MM::Assertion::Assertion(MM::Name     * name,
                         MM::Exp      * exp,
                         MM::CHAR     * msg) : MM::Element(name)
{
  this->exp = exp;
  this->msg = msg;
  this->loc = MM_NULL;
}

MM::Assertion::~Assertion()
{
  name = MM_NULL;
  exp = MM_NULL;
  msg = MM_NULL;
  loc = MM_NULL;
}

MM::VOID MM::Assertion::recycle(MM::Recycler * r)
{
  exp->recycle(r);
  r->uncreate(msg);
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->Element::recycle(r);
}

MM::TID MM::Assertion::getTypeId()
{
  return MM::T_Assertion;
}

MM::BOOLEAN MM::Assertion::instanceof(MM::TID tid)
{
  if(tid == MM::T_Assertion)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}

MM::Exp * MM::Assertion::getExp()
{
  return exp;
}

MM::CHAR * MM::Assertion::getMessage()
{
  return msg;
}

MM::UINT32 MM::Assertion::getMessageLength()
{
  /*MM::UINT32 len = 0;
  if(loc != MM_NULL)
  {
    len = loc->getLength();
  }
  else
  {
    len = strlen(msg);
  }
  return len;*/
  return strlen(msg);
}

MM::Location * MM::Assertion::getLocation()
{
  return loc;
}

MM::VOID MM::Assertion::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::Assertion::toString(MM::String * buf, MM::UINT32 indent)
{
  buf->space(indent);
  buf->append((MM::CHAR*)MM::Assertion::ASSERT_STR,
              MM::Assertion::ASSERT_LEN);
  buf->space();
  name->toString(buf);
  buf->space();
  buf->append(MM::Assertion::COLON_CHAR);
  buf->space();
  exp->toString(buf);
  buf->space();
  buf->append(msg, getMessageLength());
}