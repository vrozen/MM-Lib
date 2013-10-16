/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The Exp abstraction is the abstract super class of all expessions.
 * @package MM
 * @file    Exp.cpp
 * @author  Riemer van Rozen
 * @date    July 11th 2013
 */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Recycler.h"
#include "String.h"
#include "Exp.h"

/**
 * @fn MM::Exp::Exp() : MM::Recyclable()
 * Constructs an Exp object.
 * @return new Exp object
 */
MM::Exp::Exp() : MM::Recyclable()
{
}

/**
 * @fn MM::Exp::~Exp()
 * Destructs an Exp object.
 */
MM::Exp::~Exp()
{
}

/**
 * @fn MM::VOID MM::Exp::recycle(MM::Recycler *r)
 * Recycles an Exp object in a Recycler.
 * @param r Recycler object
 */
MM::VOID MM::Exp::recycle(MM::Recycler *r)
{
  this->MM::Recyclable::recycle(r);
}

/**
 * @fn MM::TID MM::Exp::getTypeId()
 * @brief Retrieves the type id of a Exp object.
 * @return type id
 */
MM::TID MM::Exp::getTypeId()
{
  return MM::T_Exp;
}

/**
 * @fn MM::BOOLEAN MM::Exp::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::Exp::instanceof(MM::TID tid)
{
  if(tid == MM::T_Exp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}
