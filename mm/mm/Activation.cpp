//
//  Activation.cpp
//  mm
//
//  Created by Riemer van Rozen on 11/22/13.
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
#include "Activation.h"

const MM::CHAR * MM::Activation::ACTIVATE_STR = "activate";
const MM::UINT32 MM::Activation::ACTIVATE_LEN = strlen(MM::Activation::ACTIVATE_STR);

MM::Activation::Activation(MM::Name * name) : MM::Element(name)
{
  this->loc = MM_NULL;
}

MM::Activation::Activation(MM::Location * loc, MM::Name * name) : MM::Element(name)
{
  this->loc = loc;
}

MM::Activation::~Activation()
{
  loc = MM_NULL;
}

MM::VOID MM::Activation::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->Element::recycle(r);
}

MM::TID MM::Activation::getTypeId()
{
  return MM::T_Activation;
}

MM::BOOLEAN MM::Activation::instanceof(MM::TID tid)
{
  if(tid == MM::T_Activation)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}

MM::Location * MM::Activation::getLocation()
{
  return loc;
}

MM::VOID MM::Activation::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::Activation::toString(MM::String * buf, MM::UINT32 indent)
{
  buf->space(indent);
  buf->append((MM::CHAR*)MM::Activation::ACTIVATE_STR, MM::Activation::ACTIVATE_LEN);
  buf->space();
  name->toString(buf);
}
