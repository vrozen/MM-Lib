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
//  Violation.cpp
//  mm
//
//  Created by Riemer van Rozen on March 26th 2014 
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Map.h"
#include "Recycler.h"
#include "Observer.h"
#include "Observable.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Transformation.h"
#include "Program.h"
#include "Modification.h"
#include "Transition.h"
#include "Event.h"
#include "Violation.h"
#include "Operator.h"
#include "Exp.h"
#include "VarExp.h"
#include "Assertion.h"
#include "Edge.h"
#include "NodeWorkItem.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "Declaration.h"
#include "Definition.h"
#include "Instance.h"

const MM::CHAR * MM::Violation::VIOLATE_STR = "violate";
const MM::UINT32 MM::Violation::VIOLATE_LEN = strlen(MM::Violation::VIOLATE_STR);

MM::Violation::Violation(MM::Name * name) : MM::Event(name, MM_NULL, MM_NULL)
{
  this->loc = MM_NULL;
}

MM::Violation::Violation(MM::Location * loc, MM::Name * name) : MM::Event(name, MM_NULL, MM_NULL)
{
  this->loc = loc;
}

MM::Violation::Violation(MM::Instance  * instance,
	                     MM::Assertion * assertion) : MM::Event(MM_NULL, instance, (MM::Element*) assertion)
{
  this->loc = MM_NULL;
}

MM::Violation::~Violation()
{
  this->loc = MM_NULL;
}

MM::VOID MM::Violation::recycle(MM::Recycler * r)
{
  if(loc == MM_NULL)
  {
    loc->recycle(r);
  }
  if(name == MM_NULL)
  {
    name->recycle(r);
  }
  MM::Event::recycle(r);
}

MM::TID MM::Violation::getTypeId()
{
  return MM::T_Violation;
}

MM::BOOLEAN MM::Violation::instanceof(MM::TID tid)
{
  if(tid == MM::T_Violation)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Event::instanceof(tid);
  }
}

MM::Location * MM::Violation::getLocation()
{
  return loc;
}

MM::MESSAGE MM::Violation::getMessage()
{
  return MM::MSG_VIOLATE;
}

MM::VOID MM::Violation::toString(MM::String * buf)
{
  return toString(buf, 0);
}

MM::VOID MM::Violation::toString(MM::String * buf, MM::UINT32 indent)
{
  if(name != MM_NULL)
  {
    buf->append((MM::CHAR*)MM::Violation::VIOLATE_STR, MM::Violation::VIOLATE_LEN);
    buf->space();
    getName()->toString(buf);
  }
  else if(instance != MM_NULL && element != MM_NULL)
  {
    buf->append((MM::CHAR*)MM::Violation::VIOLATE_STR, MM::Violation::VIOLATE_LEN);
    buf->space();
	instance->nameToString(element, buf);
  }
  else
  {
     //TODO: failure
  }
}