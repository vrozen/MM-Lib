//
//  Delete.cpp
//  mm
//
//  Created by Riemer van Rozen on 9/29/13.
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
#include "Deletion.h"

const MM::CHAR * MM::Deletion::DELETE_STR = "delete";
const MM::UINT32 MM::Deletion::DELETE_LEN = strlen(MM::Deletion::DELETE_STR);

MM::Deletion::Deletion(MM::Name * name) : MM::Element(name)
{
  this->loc = MM_NULL;
}

MM::Deletion::Deletion(MM::Location * loc, MM::Name * name) : MM::Element(name)
{
  this->loc = loc;
}

MM::Deletion::~Deletion()
{
  loc = MM_NULL;
}

MM::VOID MM::Deletion::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->Element::recycle(r);
}

MM::TID MM::Deletion::getTypeId()
{
  return MM::T_Deletion;
}

MM::BOOLEAN MM::Deletion::instanceof(MM::TID tid)
{
  if(tid == MM::T_Deletion)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}

MM::Location * MM::Deletion::getLocation()
{
  return loc;
}

MM::VOID MM::Deletion::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::Deletion::toString(MM::String * buf, MM::UINT32 indent)
{
  buf->space(indent);
  buf->append((MM::CHAR*)MM::Deletion::DELETE_STR, MM::Deletion::DELETE_LEN);
  buf->space();
  name->toString(buf);
}
