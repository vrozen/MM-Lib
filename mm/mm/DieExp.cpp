//
//  DieExp.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/20/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "Location.h"
#include "String.h"
#include "Operator.h"
#include "Exp.h"
#include "ValExp.h"
#include "RangeValExp.h"
#include "DieExp.h"

const MM::CHAR * MM::DieExp::DIE_STR = "dice";
const MM::UINT32 MM::DieExp::DIE_LEN = 4;

MM::DieExp::DieExp(MM::UINT32 max) : MM::Exp()
{
  this->max = max;
  this->maxLoc = MM_NULL;
  this->dieLoc = MM_NULL;
}

MM::DieExp::DieExp(MM::UINT32     max,
                   MM::Location * maxLoc,
                   MM::Location * dieLoc) : MM::Exp()
{
  this->max = max;
  this->maxLoc = maxLoc;
  this->dieLoc = dieLoc;
}

MM::DieExp::~DieExp()
{
  if(maxLoc != MM_NULL)
  {
    delete maxLoc;
  }
  if(dieLoc != MM_NULL)
  {
    delete dieLoc;
  }
}

MM::ValExp * MM::DieExp::eval()
{
  return new MM::RangeValExp(1, max);
}

MM::VOID MM::DieExp::toString(MM::String * buf)
{
  buf->append(max);
  buf->space();
  buf->append((MM::CHAR*)MM::DieExp::DIE_STR, MM::DieExp::DIE_LEN);
}
