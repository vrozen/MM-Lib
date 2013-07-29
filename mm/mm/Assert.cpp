//
//  Assert.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/29/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <iostream>
#include "Types.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Exp.h"
#include "Assert.h"

const MM::CHAR * MM::Assert::ASSERT_STR = "assert";
const MM::UINT32 MM::Assert::ASSERT_LEN = 6;

const MM::CHAR * MM::Assert::COLON_STR  = ":";
const MM::UINT32 MM::Assert::COLON_LEN  = 1;

MM::Assert::Assert(MM::Name     * name,
                   MM::Exp      * exp,
                   MM::CHAR     * msg,
                   MM::Location * loc) : MM::Element()
{
  this->name = name;
  this->exp = exp;
  this->msg = msg;
  this->loc = loc;
}

MM::Assert::~Assert()
{
  delete name;
  delete exp;
  delete msg;
  delete loc;
}

MM::Name * MM::Assert::getName()
{
  return name;
}

MM::Exp * MM::Assert::getExp()
{
  return exp;
}

MM::CHAR * MM::Assert::getMessage()
{
  return msg;
}

MM::UINT32 MM::Assert::getMessageLength()
{
  MM::UINT32 len = 0;
  if(loc != MM_NULL)
  {
    len = loc->getLength();
  }
  else
  {
    len = strlen(msg);
  }
  return len;
}

MM::Location * MM::Assert::getLocation()
{
  return loc;
}

MM::VOID MM::Assert::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::Assert::ASSERT_STR, MM::Assert::ASSERT_LEN);
  buf->space();
  name->toString(buf);
  buf->space();
  exp->toString(buf);
  buf->space();
  buf->append((MM::CHAR*)MM::Assert::COLON_STR, MM::Assert::COLON_LEN);
  buf->space();
  buf->append(msg, getMessageLength());
}