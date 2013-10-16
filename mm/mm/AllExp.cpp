/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The AllExp abstraction expresses a that the full available amount will
 * flow along a FlowEdge from a source node to target node.
 * @note A - all -> B equals A - A -> B
 * @package MM
 * @file    AllExp.cpp
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
#include "AllExp.h"

const MM::CHAR * MM::AllExp::ALL_STR = "all";
const MM::UINT32 MM::AllExp::ALL_LEN = strlen(MM::AllExp::ALL_STR);

/**
 * @fn MM::AllExp::AllExp() : MM::Exp()
 * Constructs an AllExp object.
 * @return new AllExp object
 */
MM::AllExp::AllExp() : MM::Exp()
{
  this->loc = MM_NULL;
}

/**
 * @fn MM::AllExp::AllExp() : MM::Exp()
 * Constructs an AllExp object.
 * @param source location
 * @return new AllExp object
 */

MM::AllExp::AllExp(MM::Location * loc) : MM::Exp()
{
  this->loc = loc;
}

/**
 * @fn MM::AllExp::~AllExp()
 * Deconstructs a VarExp object.
 */
MM::AllExp::~AllExp()
{
  loc = MM_NULL;
}

/**
 * @fn MM::VOID MM::AllExp::recycle(MM::Recycler * r)
 * Recycles an AllExp object in a Recycler.
 * @param r Recycler
 */
MM::VOID MM::AllExp::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::Exp::recycle(r);
}

/**
 * @fn MM::TID MM::AllExp::getTypeId()
 * @brief Retrieves the type id of a AllExp object.
 * @return type id
 */
MM::TID MM::AllExp::getTypeId()
{
  return MM::T_AllExp;
}

/**
 * @fn MM::BOOLEAN MM::AllExp::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::AllExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_AllExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

/**
 * @fn MM::VOID MM::AllExp::toString(MM::String * buf)
 * @brief Serializes an AllExp object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::AllExp::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::AllExp::ALL_STR, MM::AllExp::ALL_LEN);
}

