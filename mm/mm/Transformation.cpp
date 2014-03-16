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
//  Transformation.cpp
//  mm
//
//  Created by Riemer van Rozen on 10/16/13.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "String.h"
#include "Location.h"
#include "Name.h"
#include "Vector.h"
#include "Recycler.h"
#include "Element.h"
#include "Transformation.h"

MM::Transformation::Transformation(MM::Vector<Element *> * elements)
{
  this->elements = elements;
}

MM::Transformation::~Transformation()
{
  this->elements = MM_NULL;
}

MM::VOID MM::Transformation::recycle(MM::Recycler *r)
{
  MM::Vector<Element *>::Iterator i = elements->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Element * element = i.getNext();
    element->recycle(r);
  }  
  delete elements; //TODO
  //r->recycle(elements);
  MM::Recyclable::recycle(r);
}

MM::BOOLEAN MM::Transformation::instanceof(MM::TID tid)
{
  if(tid == T_Transformation)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

MM::VOID MM::Transformation::addElement(MM::Element * element)
{
  elements->add(element);
}

MM::Vector<MM::Element *> * MM::Transformation::getElements()
{
  return elements;
}

MM::VOID MM::Transformation::clearElements()
{
  elements->clear();
}

MM::VOID MM::Transformation::toString(MM::String * buf)
{
  MM::Vector<Element *>::Iterator i = elements->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Element * element = i.getNext();
    element->toString(buf);
    buf->linebreak();
  }
}

