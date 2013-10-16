/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The OverrideExp abstraction expresses an overriden expression.
 * @package MM
 * @file    OverrideExp.cpp
 * @author  Riemer van Rozen
 * @date    July 20th 2013
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
#include "Exp.h"
#include "OverrideExp.h"

const MM::CHAR MM::OverrideExp::LPAREN_CHAR = '(';
const MM::CHAR MM::OverrideExp::RPAREN_CHAR = ')';

/**
 * @fn MM::OverrideExp::OverrideExp(MM::Exp * exp)
 * Constructs an OverrideExp object.
 * @param exp expression
 * @return new OverrideExp object
 */
MM::OverrideExp::OverrideExp(MM::Exp * exp)
{
  this->exp = exp;
  this->lparenLoc = MM_NULL;
  this->rparenLoc = MM_NULL;
}

/**
 * @fn MM::OverrideExp::OverrideExp(MM::Exp * exp)
 * Constructs an OverrideExp object.
 * @param exp expression
 * @param lparenLoc left parenthesis source location
 * @param rparenLoc right parenthesis source location
 * @return new OverrideExp object
 */
MM::OverrideExp::OverrideExp(MM::Exp      * exp,
                             MM::Location * lparenLoc,
                             MM::Location * rparenLoc)
{
  this->exp = exp;
  this->lparenLoc = lparenLoc;
  this->rparenLoc = rparenLoc;
}

/**
 * @fn MM::OverrideExp::~OverrideExp()
 * Deconstructs a OverrideExp object.
 */
MM::OverrideExp::~OverrideExp()
{
  exp = MM_NULL;
  lparenLoc = MM_NULL;
  rparenLoc = MM_NULL;
}

/**
 * @fn MM::VOID MM::OverrideExp::recycle(MM::Recycler *r)
 * Recycles an OverrideExp object in a Recycler.
 * @param r Recycler
 */
MM::VOID MM::OverrideExp::recycle(MM::Recycler *r)
{
  exp->recycle(r);
  if(lparenLoc != MM_NULL)
  {
    lparenLoc->recycle(r);
  }
  if(rparenLoc != MM_NULL)
  {
    rparenLoc->recycle(r);
  }
  this->MM::Exp::recycle(r);
}

/**
 * @fn MM::TID MM::OverrideExp::getTypeId()
 * @brief Retrieves the type id of a OverrideExp object.
 * @return type id
 */
MM::TID MM::OverrideExp::getTypeId()
{
  return MM::T_OverrideExp;
}

/**
 * @fn MM::BOOLEAN MM::OverrideExp::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::OverrideExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_OverrideExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

/**
 * @fn MM::Exp * MM::OverrideExp::getExp()
 * @brief Retrieves the expression of an OverrideExp object.
 * @return overriden expression
 */
MM::Exp * MM::OverrideExp::getExp()
{
  return exp;
}

/**
 * @fn MM::VOID MM::OverrideExp::toString(MM::String * buf)
 * @brief Serializes an OverrideExp object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::OverrideExp::toString(MM::String * buf)
{
  buf->append(MM::OverrideExp::LPAREN_CHAR);
  exp->toString(buf);
  buf->append(MM::OverrideExp::RPAREN_CHAR);
}
