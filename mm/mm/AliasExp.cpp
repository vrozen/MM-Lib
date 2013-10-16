/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The AliasExp abstraction expresses that a source of a state edge
 * with an AliasExp is an alias of the target of that edge.
 * @package MM
 * @file    AliasExp.cpp
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
#include "AliasExp.h"

const MM::CHAR MM::AliasExp::ALIAS_CHAR = '=';

/**
 * @fn MM::AliasExp::AliasExp() : MM::Exp()
 * Constructs an AliasExp object.
 * @return new AliasExp object
 */
MM::AliasExp::AliasExp() : MM::Exp()
{
  this->loc = MM_NULL;
}

/**
 * @fn MM::AliasExp::AliasExp() : MM::Exp()
 * Constructs an AliasExp object.
 * @param loc source location
 * @return new AliasExp object
 */
MM::AliasExp::AliasExp(MM::Location * loc) : MM::Exp()
{
  this->loc = loc;
}

/**
 * @fn MM::AliasExp::AliasExp(MM::Location * loc) : MM::Exp()
 * Destructs an AliasExp object.
 */
MM::AliasExp::~AliasExp()
{
  loc = MM_NULL;
}

/**
 * @fn MM::VOID MM::AliasExp::recycle(MM::Recycler *r)
 * Recycles an AliasExp object in a Recycler.
 * @param r Recycler
 */
MM::VOID MM::AliasExp::recycle(MM::Recycler *r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::Exp::recycle(r);
}

/**
 * @fn MM::TID MM::AliasExp::getTypeId()
 * @brief Retrieves the type id of a AliasExp object.
 * @return type id
 */
MM::TID MM::AliasExp::getTypeId()
{
  return MM::T_AliasExp;
}

/**
 * @fn MM::BOOLEAN MM::AliasExp::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::AliasExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_AliasExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

/**
 * @fn MM::VOID MM::AliasExp::toString(MM::String * buf)
 * @brief Serializes an AliasExp object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::AliasExp::toString(MM::String * buf)
{
  buf->append(MM::AliasExp::ALIAS_CHAR);
}
