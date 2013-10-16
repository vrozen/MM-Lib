/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The TriggerExp abstraction expresses that a source of a state edge
 * activates the target of that edge if all of the edge the source operates
 * on are satisfied (meaning a flow of one or more exists for that edge).
 * @note The notion of satisfied does not respect all or any modifiers of nodes.
 * @package MM
 * @file    TriggerExp.cpp
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
#include "TriggerExp.h"

const MM::CHAR MM::TriggerExp::TRIGGER_CHAR = '*';

/**
 * @fn MM::Exp::Exp() : MM::Recyclable()
 * Constructs a TriggerExp object.
 * @return new TriggerExp object
 */
MM::TriggerExp::TriggerExp() : MM::Exp()
{
  this->loc = MM_NULL;
}

/**
 * @fn MM::TriggerExp::TriggerExp(MM::Location * loc) : MM::Exp()
 * Constructs a TriggerExp object.
 * @param loc source location
 * @return new TriggerExp object
 */
MM::TriggerExp::TriggerExp(MM::Location * loc) : MM::Exp()
{
  this->loc = loc;
}

/**
 * @fn MM::TriggerExp::~TriggerExp()
 * Descructs a TriggerExp object.
 */
MM::TriggerExp::~TriggerExp()
{
}

/**
 * @fn MM::VOID MM::TriggerExp::recycle(MM::Recycler *r)
 * Recycles a TriggerExp object in a Recycler.
 * @param r Recycler object
 */
MM::VOID MM::TriggerExp::recycle(MM::Recycler *r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  this->MM::Exp::recycle(r);
}

/**
 * @fn MM::TID MM::Exp::getTypeId()
 * @brief Retrieves the type id of a TriggerExp object.
 * @return type id
 */
MM::TID MM::TriggerExp::getTypeId()
{
  return MM::T_TriggerExp;
}

/**
 * @fn MM::BOOLEAN MM::TriggerExp::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::TriggerExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_TriggerExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

/**
 * @fn MM::VOID MM::TriggerExp::toString(MM::String * buf)
 * @brief Serializes a TriggerExp object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::TriggerExp::toString(MM::String * buf)
{
  buf->append(MM::TriggerExp::TRIGGER_CHAR);
}
