/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The VarExp abstraction defines expressions that reference a pools.
 * @package MM
 * @file    VarExp.cpp
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
//#include "Element.h"
//#include "Operator.h"
#include "Exp.h"
//#include "Edge.h"
//#include "NodeBehavior.h"
//#include "Node.h"
#include "VarExp.h"

/**
 * @fn MM::VarExp::VarExp(MM::Name * name) : MM::Exp()
 * Constructs an VarExp object.
 * @param exp expression
 * @return new VarExp object
 */
MM::VarExp::VarExp(MM::Name * name) : MM::Exp()
{
  this->name = name;
}

/**
 * @fn MM::VarExp::~VarExp()
 * Deconstructs a VarExp object.
 */
MM::VarExp::~VarExp()
{
  name = MM_NULL;
}

/**
 * @fn MM::VOID MM::VarExp::recycle(MM::Recycler * r)
 * Recycles an VarExp object in a Recycler.
 * @param r Recycler
 */
MM::VOID MM::VarExp::recycle(MM::Recycler * r)
{
  name->recycle(r);
  this->MM::Exp::recycle(r);
}

/**
 * @fn MM::TID MM::VarExp::getTypeId()
 * @brief Retrieves the type id of a VarExp object.
 * @return type id
 */
MM::TID MM::VarExp::getTypeId()
{
  return MM::T_VarExp;
}

/**
 * @fn MM::BOOLEAN MM::VarExp::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::VarExp::instanceof(MM::TID tid)
{
  if(tid == MM::T_VarExp)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Exp::instanceof(tid);
  }
}

MM::Name * MM::VarExp::getName()
{
  return name;
}


/**
 * @fn MM::VOID MM::VarExp::toString(MM::String * buf)
 * @brief Serializes an VarExp object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::VarExp::toString(MM::String * buf)
{
  name->toString(buf);
}
