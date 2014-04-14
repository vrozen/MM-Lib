/******************************************************************************
 * Copyright (c) 2013-2014, Amsterdam University of Applied Sciences (HvA) and
 *                          Centrum Wiskunde & Informatica (CWI)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contributors:
 *   * Riemer van Rozen - rozen@cwi.nl - HvA / CWI
 ******************************************************************************/
/*!
 * The Name abstraction is used to compose identifiers.
 * @package MM
 * @file    Name.cpp
 * @author  Riemer van Rozen
 * @date    July 27th 2013
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

const MM::CHAR MM::Name::DOT_CHAR = '.';

/**
 * @fn MM::Name::Name(MM::CHAR * str, MM::UINT32 len) : MM::Recyclable()
 * Constructs a Name object.
 * @param str character buffer
 * @param len character buffer length
 * @return new Name object
 */
MM::Name::Name(MM::CHAR * str, MM::UINT32 len) : MM::Recyclable()
{
  this->str = str;
  this->len = len;
  this->loc = MM_NULL;
  this->name = MM_NULL;
  this->pre = MM_NULL;
}

/**
 * @fn MM::Name::~Name()
 * Destructs a Name object.
 */
MM::Name::~Name()
{
  this->str = MM_NULL;
  this->loc = MM_NULL;
  this->name = MM_NULL;
  this->pre = MM_NULL;
  this->len = 0;
}

/**
 * @fn MM::VOID MM::Name::recycle(MM::Recycler * r)
 * Recycles a Name object in a Recycler.
 * @param r Recycler object
 */
MM::VOID MM::Name::recycle(MM::Recycler * r)
{
  if(name != MM_NULL)
  {
    name->recycle(r);
  }
  if(loc != MM_NULL)
  {
    r->uncreate(loc);
  }
  if(pre != MM_NULL) //FIXME: prevent memory leaks
  {                  //NOTE: Edge owns pre or Name owns pre
    pre->recycle(r); //HACK: set pre to MM_NULL if Edge owns it
  }                  //BAD: pre means nothing if owned by Name
  r->uncreate(str);
  this->MM::Recyclable::recycle(r);
}

/**
 * @fn MM::TID MM::Name::getTypeId()
 * @brief Retrieves the type id of a Name object.
 * @return type id
 */
MM::TID MM::Name::getTypeId()
{
  return MM::T_Name;
}

/**
 * @fn MM::BOOLEAN MM::Name::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::Name::instanceof(MM::TID tid)
{
  if(tid == MM::T_Name)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

MM::BOOLEAN MM::Name::equals(MM::Name * name)
{
  MM::CHAR * str = name->getBuffer();  
  MM::UINT32 len = name->getLength();
  return equals(str, len);
}

MM::BOOLEAN MM::Name::equals(MM::CHAR * str, MM::UINT32 len)
{
  MM::BOOLEAN equal = MM_FALSE;
  if(len == this->len)
  {
    if(strncmp(str, this->str, len) == 0)
    {
      equal = MM_TRUE;
    }
  }
  return equal;
}

/**
 * @fn MM::UINT32 MM::Name::getLength()
 * @brief Retrieves the length of a Name object.
 * @return column number
 */
MM::UINT32 MM::Name::getLength()
{
  return len;
}

/**
 * @fn MM::VOID MM::Name::setName(MM::Name * name)
 * @brief Stores the sub name in this name.
 * @param name sub name
 * @return column number
 */
MM::VOID MM::Name::setName(MM::Name * name)
{
  this->name = name;
}

/**
 * @fn MM::Name * MM::Name::getName()
 * @brief Retrieves the sub name of this name.
 * @return sub name
 */
MM::Name * MM::Name::getName()
{
  return name;
}

/**
 * @fn MM::Name * MM::Name::getName()
 * @brief Retrieves the sub name of this name.
 * @return sub name
 */
MM::CHAR * MM::Name::getBuffer()
{
  return str;
}

/**
 * @fn MM::Location * MM::Name::getLocation()
 * @brief Retrieves the location of this name.
 * @return location
 */
MM::Location * MM::Name::getLocation()
{
  return loc;
}

/**
 * @fn MM::VOID MM::Name::setLocation(MM::Location * loc)
 * @brief Stores a location in this name.
 * @param loc location
 */
MM::VOID MM::Name::setLocation(MM::Location * loc)
{
  this->loc = loc;
}

/**
 * @fn MM::VOID MM::Name::setPreName(MM::Name * name)
 * @brief Stores a prefix name in this name.
 * @param name to be stored as prefix
 * @note used for naming edges
 */
MM::VOID MM::Name::setPreName(MM::Name * name)
{
  this->pre = name;
}


MM::VOID MM::Name::append(MM::Name * name)
{
  MM::Name * n = this;
  while(n->getName() != MM_NULL)
  {
    n = n->getName();
  }
  n->setName(name);
}

/**
 * @fn MM::Location * MM::Name::getLocation()
 * @brief Retrieves the prefix name of this name.
 * @return prefix name
 * @note used for naming edges
 */
MM::Name * MM::Name::getPreName()
{
  return pre;
}

/**
 * @fn MM::VOID MM::Name::toString(MM::String * buf)
 * @brief Serializes a Name object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::Name::toString(MM::String * buf)
{
  buf->append(str, getLength());
  if(name != MM_NULL)
  {
    buf->append(MM::Name::DOT_CHAR);
    name->toString(buf);
  }
}

/**
 * @fn MM::VOID MM::Name::print()
 * @brief Prints a name on the screen.
 * @note debug only
 */
MM::VOID MM::Name::print()
{
  for(MM::UINT32 i=0; i<len; i++)
  {
    MM_printf("%c",str[i]);
  }
  if(name != MM_NULL)
  {
    MM_printf(".");
    name->print();
  }
}
