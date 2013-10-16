/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The DieExp abstraction expresses that a target of a state edge
 * with an DieExp is only active if the source is active.
 * @package MM
 * @file    DieExp.cpp
 * @author  Riemer van Rozen
 * @date    July 20th 2013
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
#include "Exp.h"
#include "DieExp.h"

const MM::CHAR * MM::DieExp::DIE_STR = "dice";
const MM::UINT32 MM::DieExp::DIE_LEN = 4;

/**
 * @fn MM::DieExp::DieExp(MM::UINT32 max) : MM::Exp()
 * Constructs a DieExp object.
 * @param name name
 * @return new DieExp object
 */
MM::DieExp::DieExp(MM::UINT32 max) : MM::Exp()
{
  this->max = max;
  this->maxLoc = MM_NULL;
  this->dieLoc = MM_NULL;
}

/**
 * @fn MM::DieExp::DieExp(MM::UINT32     max,
       MM::Location * maxLoc,
       MM::Location * dieLoc) : MM::Exp()
 * Constructs a DieExp object.
 * @param max maximum die roll
 * @param maxLoc source location of max keyword
 * @param dieLoc source location of die keyword
 * @return new DieExp object
 */
MM::DieExp::DieExp(MM::UINT32     max,
                   MM::Location * maxLoc,
                   MM::Location * dieLoc) : MM::Exp()
{
  this->max = max;
  this->maxLoc = maxLoc;
  this->dieLoc = dieLoc;
}

/**
 * @fn MM::DieExp::~DieExp()
 * Deconstructs a DieExp object.
 */
MM::DieExp::~DieExp()
{
  max = 0;
  maxLoc = 0;
  dieLoc = 0;
}

/**
 * @fn MM::VOID MM::DieExp::recycle(MM::Recycler *r)
 * Recycles an DieExp object in a Recycler.
 * @param r Recycler
 */
MM::VOID MM::DieExp::recycle(MM::Recycler *r)
{
  if(maxLoc != MM_NULL)
  {
    maxLoc->recycle(r);
  }
  if(dieLoc != MM_NULL)
  {
    dieLoc->recycle(r);
  }
  this->MM::Exp::recycle(r);
}

/**
 * @fn MM::TID MM::DieExp::getTypeId()
 * @brief Retrieves the type id of a DieExp object.
 * @return type id
 */
MM::TID MM::DieExp::getTypeId()
{
  return MM::T_DieExp;
}

/**
 * @fn MM::BOOLEAN MM::DieExp::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::DieExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_DieExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

/**
 * @fn MM::UINT32 MM::DieExp::getMax()
 * @brief Serializes a DieExp object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::UINT32 MM::DieExp::getMax()
{
  return max;
}

/**
 * @fn MM::VOID MM::DieExp::toString(MM::String * buf)
 * @brief Serializes a DieExp object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::DieExp::toString(MM::String * buf)
{
  buf->appendInt(max);
  buf->space();
  buf->append((MM::CHAR*)MM::DieExp::DIE_STR, MM::DieExp::DIE_LEN);
}
