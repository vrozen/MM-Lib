/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The BooleanValExp abstraction defines boolean value expressions.
 * @package MM
 * @file    BooleanValExp.cpp
 * @author  Riemer van Rozen
 * @date    July 19th 2013
 */
/******************************************************************************/
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
#include "Exp.h"
#include "ValExp.h"
#include "BooleanValExp.h"

const MM::CHAR * MM::BooleanValExp::TRUE_STR  = "true";
const MM::CHAR * MM::BooleanValExp::FALSE_STR = "false";
const MM::UINT32 MM::BooleanValExp::TRUE_LEN  =
  strlen(MM::BooleanValExp::TRUE_STR);
const MM::UINT32 MM::BooleanValExp::FALSE_LEN =
  strlen(MM::BooleanValExp::FALSE_STR);

MM::BooleanValExp::BooleanValExp(MM::BOOLEAN val) : MM::ValExp()
{
  this->val = val;
  this->loc = MM_NULL;
}

MM::BooleanValExp::BooleanValExp(MM::BOOLEAN val,
                                 MM::Location * loc) : MM::ValExp()
{
  this->val = val;
  this->loc = loc;
}

MM::BooleanValExp::~BooleanValExp()
{
  val = MM_FALSE;
  loc = MM_NULL;
}

MM::VOID MM::BooleanValExp::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::ValExp::recycle(r);
}

MM::TID MM::BooleanValExp::getTypeId()
{
  return MM::T_BooleanValExp;
}

MM::BOOLEAN MM::BooleanValExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_BooleanValExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::ValExp::instanceof(tid);
  }
}

MM::BOOLEAN MM::BooleanValExp::getValue()
{
  return val;
}

MM::Location *  MM::BooleanValExp::getLocation()
{
  return loc;
}

MM::BOOLEAN MM::BooleanValExp::greaterEquals(MM::UINT32 val)
{
  return MM_FALSE;
}

MM::VOID MM::BooleanValExp::toString(MM::String * buf)
{
  if(val == MM_FALSE)
  {
    buf->append((MM::CHAR*)MM::BooleanValExp::FALSE_STR,
                MM::BooleanValExp::FALSE_LEN);
  }
  else
  {
    buf->append((MM::CHAR*)MM::BooleanValExp::TRUE_STR,
                MM::BooleanValExp::TRUE_LEN);
  }
}
