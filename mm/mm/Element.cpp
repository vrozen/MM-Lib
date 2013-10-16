/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The Element abstraction is the abstract superclass of all program elements.
 * @package MM
 * @file    Element.cpp
 * @author  Riemer van Rozen
 * @date    July 10th 2013
 */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Map.h"
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"

MM::Element::Element(MM::Name * name) : MM::Recyclable()
{
  this->name = name;
}

MM::Element::~Element()
{
}

MM::VOID MM::Element::recycle(MM::Recycler * r)
{
  if(name != MM_NULL)
  {
    name->recycle(r);
  }
  this->MM::Recyclable::recycle(r);
}

MM::TID MM::Element::getTypeId()
{
  return MM::T_Element;
}

MM::BOOLEAN MM::Element::instanceof(MM::TID tid)
{
  if(tid == MM::T_Element)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

MM::Name * MM::Element::getName()
{
  return name;
}

MM::VOID MM::Element::setName(MM::Name * name)
{
  this->name = name;
}

MM::VOID MM::Element::toString(MM::String * buf)
{
  toString(buf, 0);
}
