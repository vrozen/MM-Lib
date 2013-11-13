/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The BinExp abstraction defines binary expressions.
 * @package MM
 * @file    BinExp.h
 * @author  Riemer van Rozen
 * @date    July 18th 2013
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
#include "BinExp.h"

MM::BinExp::BinExp(Exp              * e1,
                   MM::Operator::OP   op,
                   Exp              * e2) : MM::Exp()
{
  this->e1  = e1;
  this->op  = op;
  this->e2  = e2;
  this->loc = MM_NULL;
}

MM::BinExp::BinExp(Exp              * e1,
                   MM::Operator::OP   op,
                   Exp              * e2,
                   MM::Location     * loc) : MM::Exp()
{
  this->e1  = e1;
  this->op  = op;
  this->e2  = e2;
  this->loc = loc;
}

MM::BinExp::~BinExp()
{
  e1 = MM_NULL;
  e2 = MM_NULL;
  loc = MM_NULL;
}

MM::VOID MM::BinExp::recycle(MM::Recycler * r)
{
  e1->recycle(r);
  e2->recycle(r);
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::Exp::recycle(r);
}

MM::TID MM::BinExp::getTypeId()
{
  return MM::T_BinExp;
}

MM::BOOLEAN MM::BinExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_BinExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

MM::BOOLEAN MM::BinExp::isTriggerExp()
{
  MM::BOOLEAN r = MM_FALSE;
  if(op == Operator::OP_MUL &&
    e1->getTypeId() == MM::T_OneExp &&
    e2->getTypeId() == MM::T_OneExp)
  {
    r = MM_TRUE;
  }
  return r;
}

MM::Exp * MM::BinExp::getLhsExp()
{
  return this->e1;
}

MM::Exp * MM::BinExp::getRhsExp()
{
  return this->e2;
}

MM::Operator::OP MM::BinExp::getOperator()
{
  return this->op;
}

MM::VOID MM::BinExp::toString(MM::String * buf)
{
  e1->toString(buf);
  buf->space();
  buf->append((MM::CHAR*) MM::Operator::OP_STR[op], MM::Operator::OP_LEN[op]);
  buf->space();
  e2->toString(buf);
}
