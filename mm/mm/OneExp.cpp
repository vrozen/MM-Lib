//
//  OneExp.cpp
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
#include "NumberValExp.h"
#include "OneExp.h"

MM::OneExp::OneExp() : MM::Exp()
{
  this->loc = MM_NULL;
}

MM::OneExp::OneExp(MM::Location * loc) : MM::Exp()
{
  this->loc = loc;
}

MM::OneExp::~OneExp()
{
  if(loc != MM_NULL)
  {
    delete loc;
  }
}

MM::ValExp * MM::OneExp::eval()
{
  return new NumberValExp(1);
}

MM::VOID MM::OneExp::toString(MM::String * buf)
{
  //write nothing
}