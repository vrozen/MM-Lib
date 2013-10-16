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
#include "Delete.h"

const MM::CHAR * MM::Delete::DELETE_STR = "delete";
const MM::UINT32 MM::Delete::DELETE_LEN = strlen(MM::Delete::DELETE_STR);

MM::Delete::Delete(MM::Name * name) : MM::Element(name)
{
}

MM::Delete::~Delete()
{
}

MM::VOID MM::Delete::recycle(MM::Recycler * r)
{
  this->Element::recycle(r);
}

MM::TID MM::Delete::getTypeId()
{
  return MM::T_Delete;
}

MM::BOOLEAN MM::Delete::instanceof(MM::TID tid)
{
  if(tid == MM::T_Delete)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}

//MM::Location * MM::Delete::getLocation()
//{
//  return loc;
//}

MM::VOID MM::Delete::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::Delete::toString(MM::String * buf, MM::UINT32 indent)
{
  buf->space(indent);
  buf->append((MM::CHAR*)MM::Delete::DELETE_STR, MM::Delete::DELETE_LEN);
  buf->space();
  name->toString(buf);
}