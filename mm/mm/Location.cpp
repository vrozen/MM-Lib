/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The Location abstraction defines textual source locations.
 * @package MM
 * @file    Location.cpp
 * @author  Riemer van Rozen
 * @date    July 27th 2013
 */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "String.h"
#include "Vector.h"
#include "Recycler.h"
#include "Location.h"

const MM::CHAR * MM::Location::LOCATION_STR = "location";
const MM::UINT32 MM::Location::LOCATION_LEN = strlen(LOCATION_STR);
const MM::CHAR * MM::Location::LINE_STR = "line";
const MM::UINT32 MM::Location::LINE_LEN = strlen(LINE_STR);
const MM::CHAR * MM::Location::COLUMN_STR = "column";
const MM::UINT32 MM::Location::COLUMN_LEN = strlen(COLUMN_STR);
const MM::CHAR * MM::Location::LENGTH_STR = "length";
const MM::UINT32 MM::Location::LENGTH_LEN = strlen(LENGTH_STR);

/**
 * @fn MM::Location::Location(MM::UINT32 beginLine,
         MM::UINT32 beginCol,
         MM::UINT32 endLine,
         MM::UINT32 endCol) : MM::Recyclable()
 * @brief Constructs a Location object.
 * @param beginLine line on which the location starts
 * @param beginCol column on which the location starts
 * @param endLine line on which the location ends
 * @param endCol column on which the location ends
 * @return new Location object
 */
MM::Location::Location(MM::UINT32 beginLine,
                       MM::UINT32 beginCol,
                       MM::UINT32 endLine,
                       MM::UINT32 endCol) : MM::Recyclable()
{
  this->line = beginLine;
  this->col = beginCol;
  this->endLine = endLine;
  this->endCol = endCol;
}

/**
 * @fn MM::Location::~Location()
 * @brief Destructs a Location.
 */
MM::Location::~Location()
{
  line = 0;
  col = 0;
  endLine = 0;
  endCol = 0;
}

/**
 * @fn MM::VOID MM::Location::recycle(MM::Recycler * r)
 * @brief Recycles a Location object in a Recycler.
 * @param r Recycler object
 */
MM::VOID MM::Location::recycle(MM::Recycler * r)
{
  this->MM::Recyclable::recycle(r);
}

/**
 * @fn MM::TID MM::Location::getTypeId()
 * @brief Retrieves the type id of a Location object.
 * @return type id
 */
MM::TID MM::Location::getTypeId()
{
  return MM::T_Location;
}

/**
 * @fn MM::BOOLEAN MM::Location::instanceof(MM::TID tid)
 * @brief Assesses if an object is an instance of a type tid.
 * @param tid type id
 * @return MM_TRUE if this object is instance of tid, MM_FALSE otherwise
 */
MM::BOOLEAN MM::Location::instanceof(MM::TID tid)
{
  if(tid == MM::T_Location)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

/**
 * @fn MM::UINT32 MM::Location::getLine()
 * @brief Retrieves the begin line number of a Location object.
 * @return line number
 */
MM::UINT32 MM::Location::getLine()
{
  return line;
}

/**
 * @fn MM::UINT32 MM::Location::getColumn()
 * @brief Retrieves the begin column number of a Location object.
 * @return column number
 */
MM::UINT32 MM::Location::getColumn()
{
  return col;
}

/**
 * @fn MM::UINT32 MM::Location::getLength()
 * @brief Retrieves the length of a Location object.
 * @return column number
 */
MM::UINT32 MM::Location::getLength()
{
  return endCol - col + 1;
}

/**
 * @fn MM::VOID MM::Location::toString(MM::String * buf)
 * @brief Serializes a Location object into a String buffer.
 * @param buf String buffer to serialize this object into
 */
MM::VOID MM::Location::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::Location::LOCATION_STR,
              MM::Location::LOCATION_LEN);
  buf->space();
  buf->append((MM::CHAR*)MM::Location::LINE_STR,
              MM::Location::LINE_LEN);
  buf->appendInt(line);
  buf->space();
  buf->append((MM::CHAR*)MM::Location::COLUMN_STR,
              MM::Location::COLUMN_LEN);
  buf->space();
  buf->appendInt(col);
  buf->space();
  buf->append((MM::CHAR*)MM::Location::LENGTH_STR,
              MM::Location::LENGTH_LEN);
  buf->space();
  buf->appendInt(getLength());
}
