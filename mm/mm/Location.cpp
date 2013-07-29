//
//  Location.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/27/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "Location.h"

MM::Location::Location(MM::UINT32 beginLine,
                       MM::UINT32 beginCol,
                       MM::UINT32 endLine,
                       MM::UINT32 endCol)
{
  this->line = beginLine;
  this->col = beginCol;
  this->endLine = endLine;
  this->endCol = endCol;
}

MM::Location::~Location()
{
}

MM::UINT32 MM::Location::getLine()
{
  return line;
}

MM::UINT32 MM::Location::getColumn()
{
  return col;
}

MM::UINT32 MM::Location::getLength()
{
  return endCol - col + 1;
}
