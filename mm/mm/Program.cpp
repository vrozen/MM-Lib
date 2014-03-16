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
//  Program.cpp
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
#include "String.h"
#include "Recycler.h"
#include "Location.h"
#include "Name.h"
#include "Element.h"
#include "Transformation.h"
#include "Program.h"

MM::Program::Program(MM::Vector<MM::Transformation *> * transformations):
  MM::Recyclable()
{
  this->transformations = transformations;
}

MM::Program::~Program()
{
  transformations = MM_NULL;
}

MM::VOID MM::Program::recycle(MM::Recycler *r)
{
  MM::Vector<MM::Transformation *>::Iterator i = transformations->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Transformation * t = i.getNext();
    t->recycle(r);
  }
  delete transformations; //FIXME
  MM::Recyclable::recycle(r);
}

MM::TID MM::Program::getTypeId()
{
  return MM::T_Program;
}

MM::BOOLEAN MM::Program::instanceof(MM::TID tid)
{
  if(tid == MM::T_Program)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

MM::VOID MM::Program::addTransformation(MM::Transformation * tr)
{
  transformations->add(tr);
}

MM::Vector<MM::Transformation *> * MM::Program::getTransformations()
{
  return this->transformations;
}

MM::VOID MM::Program::toString(MM::String * buf)
{
  MM::Vector<MM::Transformation *>::Iterator i =
    transformations->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Transformation * t = i.getNext();
    t->toString(buf);
    buf->linebreak();
  }
}
