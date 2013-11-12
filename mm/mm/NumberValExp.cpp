/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The NumberValExp abstraction defines number value expressions.
 * @package MM
 * @file    NumberValExp.cpp
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
#include "NumberValExp.h"

const MM::CHAR MM::NumberValExp::DOT_CHAR = '.';

MM::NumberValExp::NumberValExp(MM::INT32 val) : MM::ValExp()
{
  this->val = val * 100;
  this->loc = MM_NULL;
}

MM::NumberValExp::NumberValExp(MM::INT32 val,
                               MM::Location * loc) : MM::ValExp()
{
  this->val = val * 100;
  this->loc = loc;
}

MM::NumberValExp::NumberValExp(MM::INT32 val,
                               MM::UINT8 fraction) : MM::ValExp()
{
  this->val = (val * 100) + (fraction % 100);
  this->loc = MM_NULL;
}

MM::NumberValExp::NumberValExp(MM::INT32 val,
                               MM::UINT8 fraction,
                               MM::Location * loc) : MM::ValExp()
{
  this->val = val * 100 + (fraction %100);
  this->loc = loc;
}

MM::NumberValExp::~NumberValExp()
{
  this->val = 0;
  this->loc = MM_NULL;
}

MM::VOID MM::NumberValExp::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::ValExp::recycle(r);
}

MM::TID MM::NumberValExp::getTypeId()
{
  return MM::T_NumberValExp;
}

MM::BOOLEAN MM::NumberValExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_NumberValExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::ValExp::instanceof(tid);
  }
}

MM::INT32 MM::NumberValExp::getValue()
{
  return val;
}

MM::INT32 MM::NumberValExp::getIntValue()
{
  return val / 100;
}

MM::Location *  MM::NumberValExp::getLocation()
{
  return loc;
}

MM::BOOLEAN MM::NumberValExp::greaterEquals(MM::UINT32 val)
{
  if(val >= this->val)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::VOID MM::NumberValExp::toString(MM::String * buf)
{
  buf->appendInt(val / 100);
  if(val % 100 != 0)
  {
    buf->append(MM::NumberValExp::DOT_CHAR);
    buf->appendInt(val % 100);
  }
}

