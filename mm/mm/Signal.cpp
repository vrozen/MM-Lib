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
//  Signal.cpp
//  mm
//
//  Created by Riemer van Rozen on 10/16/13.
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
#include "Signal.h"

const MM::CHAR * MM::Signal::SIGNAL_STR = "signal";
const MM::UINT32 MM::Signal::SIGNAL_LEN = strlen(MM::Signal::SIGNAL_STR);

MM::Signal::Signal(MM::Location * loc, MM::Name * name) : MM::Element(name)
{
  this->loc = loc;
}

MM::Signal::Signal(MM::Name * name) : MM::Element(name)
{
  this->loc = MM_NULL;
}

MM::Signal::~Signal()
{
  this->loc = MM_NULL;
}

MM::VOID MM::Signal::recycle(MM::Recycler * r)
{
  if(loc == MM_NULL)
  {
    loc->recycle(r);
  }
  MM::Element::recycle(r);
}

MM::TID MM::Signal::getTypeId()
{
  return MM::T_Signal;
}

MM::BOOLEAN MM::Signal::instanceof(MM::TID tid)
{
  if(tid == MM::T_Signal)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}

MM::Location * MM::Signal::getLocation()
{
  return loc;
}

MM::VOID MM::Signal::toString(MM::String * buf)
{
  return toString(buf, 0);
}

MM::VOID MM::Signal::toString(MM::String * buf, MM::UINT32 indent)
{
  buf->append((MM::CHAR*)MM::Signal::SIGNAL_STR, MM::Signal::SIGNAL_LEN);
  buf->space();
  getName()->toString(buf);
}