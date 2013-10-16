/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The OneExp abstraction expresses shorthand on edges
 *  -->    : OneExp has a flow of one: NumberValueExp(1)
 *  . * .> : BinExp has lhs OneExp and rhs OneExp: isTrigger() = MM_TRUE
 *  . == .>: BinExp has lhs OneExp and rhs OneExp:
 *           lhs OneExp refers to source and rhs OneExp refers to target
 * @package MM
 * @file    AliasExp.h
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
#include "OneExp.h"

/**
 * @fn MM::OneExp::OneExp() : MM::Exp()
 * Constructs a OneExp object.
 * @return new OneExp object
 */
MM::OneExp::OneExp() : MM::Exp()
{
  this->loc = MM_NULL;
}

/**
 * @fn MM::OneExp::OneExp(MM::Location * loc) : MM::Exp()
 * Constructs a OneExp object.
 * @param loc source location
 * @return new OneExp object
 */
MM::OneExp::OneExp(MM::Location * loc) : MM::Exp()
{
  this->loc = loc;
}

/**
 * @fn MM::OneExp::~OneExp()
 * Destructs an OneExp object.
 */
MM::OneExp::~OneExp()
{
  loc = MM_NULL;
}

/**
 * @fn MM::VOID MM::OneExp::recycle(MM::Recycler * r)
 * Recycles an OneExp object in a Recycler.
 * @param r Recycler
 */
MM::VOID MM::OneExp::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::Exp::recycle(r);
}

/**
 * @fnMM::TID MM::OneExp::getTypeId()
 * @brief Retrieves the type id of a OneExp object.
 * @return type id
 */
MM::TID MM::OneExp::getTypeId()
{
  return MM::T_OneExp;
}

/**
 * @fn MM::BOOLEAN MM::OneExp::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::OneExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_OneExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

/**
 * @fn MM::VOID MM::OneExp::toString(MM::String * buf)
 * @brief Serializes an OneExp object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::OneExp::toString(MM::String * buf)
{
  //write nothing
}
