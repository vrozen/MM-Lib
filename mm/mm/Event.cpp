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
 * The Event abstraction is the abstract superclass of all transition elements.
 * @package MM
 * @file    Event.cpp
 * @author  Riemer van Rozen
 * @date    March 26th 2013
 */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Map.h"
#include "Location.h"
#include "Name.h"
#include "Recycler.h"
#include "Element.h"
#include "Event.h"

MM::Event::Event(MM::Name * name, MM::Instance * instance, MM::Element * element) : MM::Element(name)
{
  this->instance = instance;
  this->element = element;
}

MM::Event::~Event()
{
  this->instance = MM_NULL;
  this->element = MM_NULL;
}

MM::VOID MM::Event::recycle(MM::Recycler * r)
{
  this->MM::Element::recycle(r);
}

MM::TID MM::Event::getTypeId()
{
  return MM::T_Event;
}

MM::BOOLEAN MM::Event::instanceof(MM::TID tid)
{
  if(tid == MM::T_Event)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}

MM::Instance * MM::Event::getInstance()
{
  return instance;
}

MM::VOID MM::Event::setInstance(MM::Instance * instance)
{
  this->instance = instance;
}

MM::Element * MM::Event::getElement()
{
  return element;
}

MM::VOID MM::Event::setElement(MM::Element * element)
{
  this->element = element;
}
