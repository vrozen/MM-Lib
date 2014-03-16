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
 * The Element abstraction is the abstract superclass of all program elements.
 * @package MM
 * @file    Element.cpp
 * @author  Riemer van Rozen
 * @date    July 10th 2013
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
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"

MM::Element::Element(MM::Name * name) : MM::Recyclable()
{
  this->name = name;
  this->visible = MM_TRUE;
}

MM::Element::~Element()
{
  this->name = MM_NULL;
  this->visible = MM_FALSE;
}

MM::VOID MM::Element::recycle(MM::Recycler * r)
{
  if(name != MM_NULL)
  {
    name->recycle(r);
  }
  this->MM::Recyclable::recycle(r);
}

MM::TID MM::Element::getTypeId()
{
  return MM::T_Element;
}

MM::BOOLEAN MM::Element::instanceof(MM::TID tid)
{
  if(tid == MM::T_Element)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

MM::Name * MM::Element::getName()
{
  return name;
}

MM::VOID MM::Element::setName(MM::Name * name)
{
  this->name = name;
}

MM::BOOLEAN MM::Element::isVisible()
{
  return visible;
}

MM::VOID MM::Element::setVisible(MM::BOOLEAN visible)
{
  this->visible = visible;
}

//what happens when an element is added to an instance
MM::VOID MM::Element::begin(MM::Instance * i)
{
  //nothing happens by default
}

MM::VOID MM::Element::end(MM::Instance * i)
{
  //nothing happens by default
}

MM::VOID MM::Element::change(MM::Instance * i)
{
  //nothing happens by default
}

MM::VOID MM::Element::toString(MM::String * buf)
{
  toString(buf, 0);
}
