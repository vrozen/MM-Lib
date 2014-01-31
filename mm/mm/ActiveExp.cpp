/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The ActiveExp abstraction expresses that a target of a state edge
 * with an ActiveExp is only active if the source is active.
 * @package MM
 * @file    ActiveExp.h
 * @author  Riemer van Rozen
 * @date    July 21th 2013
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
#include "Exp.h"
#include "ActiveExp.h"

const MM::CHAR * MM::ActiveExp::ACTIVE_STR = "active";
const MM::UINT32 MM::ActiveExp::ACTIVE_LEN = 6;

/**
 * @fn MM::ActiveExp::ActiveExp(MM::Name * name) : MM::Exp()
 * Constructs a ActiveExp object.
 * @param name name
 * @return new ActiveExp object
 */
MM::ActiveExp::ActiveExp(MM::Name * name) : MM::Exp()
{
  this->name = name;
  this->loc = MM_NULL;
}

/**
 * @fn MM::ActiveExp::ActiveExp(MM::Name * name, MM::Location * loc) : MM::Exp()
 * Constructs a ActiveExp object.
 * @param name name
 * @param loc source location
 * @return new ActiveExp object
 */
MM::ActiveExp::ActiveExp(MM::Name * name, MM::Location * loc) : MM::Exp()
{
  this->name = name;
  this->loc = loc;
}

/**
 * @fn MM::ActiveExp::~ActiveExp()
 * Destructs an ActiveExp object.
 */
MM::ActiveExp::~ActiveExp()
{
  name = MM_NULL;
  loc = MM_NULL;
}

/**
 * @fn MM::VOID MM::ActiveExp::recycle(MM::Recycler *r)
 * Recycles an ActiveExp object in a Recycler.
 * @param r Recycler
 */
MM::VOID MM::ActiveExp::recycle(MM::Recycler *r)
{
  name->recycle(r);
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::Exp::recycle(r);
}

/**
 * @fn MM::TID MM::ActiveExp::getTypeId()
 * @brief Retrieves the type id of a ActiveExp object.
 * @return type id
 */
MM::TID MM::ActiveExp::getTypeId()
{
  return MM::T_ActiveExp;
}

/**
 * @fn MM::BOOLEAN MM::ActiveExp::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::ActiveExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_ActiveExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

/**
 * @fn MM::Name * MM::ActiveExp::getName()
 * @brief Retrieves the name of an ActiveExp object.
 * @return name
 */
MM::Name * MM::ActiveExp::getName()
{
  return name;
}

/**
 * @fn MM::VOID MM::ActiveExp::toString(MM::String * buf)
 * @brief Serializes an ActiveExp object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::ActiveExp::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::ActiveExp::ACTIVE_STR,
              MM::ActiveExp::ACTIVE_LEN);
  buf->space();
  name->toString(buf);
}
