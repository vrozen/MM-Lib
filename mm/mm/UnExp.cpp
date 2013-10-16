/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The UnExp abstraction defines unary expressions.
 * @package MM
 * @file    UnExp.cpp
 * @author  Riemer van Rozen
 * @date    July 19th 2013
 */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Operator.h"
#include "Exp.h"
#include "UnExp.h"

MM::UnExp::UnExp(MM::Operator::OP op,
                 Exp * exp) : MM::Exp()
{
  this->exp = exp;
  this->op = op;
}

MM::UnExp::UnExp(MM::Operator::OP op,
                 Exp * exp,                 
                 MM::Location * loc) : MM::Exp()
{
  this->exp = exp;
  this->op = op;
  this->loc = loc;
}

MM::UnExp::~UnExp()
{
  exp = MM_NULL;
  loc = MM_NULL;
}

MM::VOID MM::UnExp::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  exp->recycle(r);
  this->MM::Exp::recycle(r);
}

MM::TID MM::UnExp::getTypeId()
{
  return MM::T_UnExp;
}

MM::BOOLEAN MM::UnExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_UnExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

MM::Exp * MM::UnExp::getExp()
{
  return this->exp;
}

MM::Operator::OP MM::UnExp::getOperator()
{
  return this->op;
}

MM::VOID MM::UnExp::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::Operator::OP_STR[op], MM::Operator::OP_LEN[op]);
  buf->space();
  exp->toString(buf);
}