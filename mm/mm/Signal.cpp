//
//  Signal.cpp
//  mm
//
//  Created by Riemer van Rozen on 10/16/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
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