//
//  Assert.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/29/13.
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
#include "Exp.h"
#include "Assert.h"

const MM::CHAR * MM::Assert::ASSERT_STR = "assert";
const MM::UINT32 MM::Assert::ASSERT_LEN = strlen(MM::Assert::ASSERT_STR);
const MM::CHAR   MM::Assert::COLON_CHAR  = ':';

MM::Assert::Assert(MM::Name     * name,
                   MM::Exp      * exp,
                   MM::CHAR     * msg,
                   MM::Location * loc) : MM::Element(name)
{
  this->exp = exp;
  this->msg = msg;
  this->loc = loc;
}

MM::Assert::~Assert()
{
  name = MM_NULL;
  exp = MM_NULL;
  msg = MM_NULL;
  loc = MM_NULL;
}

MM::VOID MM::Assert::recycle(MM::Recycler * r)
{
  exp->recycle(r);
  r->uncreate(msg);
  loc->recycle(r);
  this->Element::recycle(r);
}

MM::TID MM::Assert::getTypeId()
{
  return MM::T_Assert;
}

MM::BOOLEAN MM::Assert::instanceof(MM::TID tid)
{
  if(tid == MM::T_Assert)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
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
  toString(buf, 0);
}

MM::VOID MM::Assert::toString(MM::String * buf, MM::UINT32 indent)
{
  buf->space(indent);
  buf->append((MM::CHAR*)MM::Assert::ASSERT_STR, MM::Assert::ASSERT_LEN);
  buf->space();
  name->toString(buf);
  buf->space();
  buf->append(MM::Assert::COLON_CHAR);
  buf->space();
  exp->toString(buf);
  buf->space();
  buf->append(msg, getMessageLength());
}