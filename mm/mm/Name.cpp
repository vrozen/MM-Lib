//
//  Name.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/27/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <iostream>
#include "Types.h"
#include "Location.h"
#include "String.h"
#include "Name.h"

const MM::CHAR * MM::Name::DOT_STR = ".";
const MM::UINT32 MM::Name::DOT_LEN = 1;

MM::Name::Name(MM::CHAR * str)
{
  this->str = str;
  this->sub = MM_NULL;
}

MM::Name::Name(MM::CHAR * str, MM::Location * loc)
{
  this->str = str;
  this->loc = loc;
  this->sub = MM_NULL;
}

MM::Name::~Name()
{
  delete str;
  if(sub != MM_NULL)
  {
    delete sub;
  }
}

MM::VOID MM::Name::setSubName(MM::Name * sub)
{
  this->sub = sub;
}

MM::UINT32 MM::Name::getLength()
{
  MM::UINT32 len = 0;
  if(loc == MM_NULL)
  {
    len = strlen(str);
  }
  else
  {
    len = loc->getLength();
  }
  return len;
}

MM::CHAR * MM::Name::getBuffer()
{
  return str;
}

MM::Location * MM::Name::getLocation()
{
  return loc;
}

MM::VOID MM::Name::toString(String * buf)
{
  buf->append(str, getLength());
  if(sub != MM_NULL)
  {
    buf->append((MM::CHAR*)MM::Name::DOT_STR, MM::Name::DOT_LEN);
    sub->toString(buf);
  }
}