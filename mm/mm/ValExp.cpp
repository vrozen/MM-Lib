/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The ValExp abstraction defines value expressions.
 * @package MM
 * @file    ValExp.cpp
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

MM::ValExp::ValExp() : MM::Exp()
{
}

MM::ValExp::~ValExp()
{
}

MM::VOID MM::ValExp::recycle(MM::Recycler * r)
{
  this->MM::Exp::recycle(r);
}

MM::TID MM::ValExp::getTypeId()
{
  return MM::T_ValExp;
}

MM::BOOLEAN MM::ValExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_ValExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}
