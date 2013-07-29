//
//  AllValExp.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/19/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "Location.h"
#include "String.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "AllExp.h"

const MM::CHAR * MM::AllExp::ALL_STR = "all";
const MM::UINT32 MM::AllExp::ALL_LEN = 3;

MM::AllExp::AllExp() : MM::Exp()
{
  this->loc = MM_NULL;
}

MM::AllExp::AllExp(MM::Location * loc) : MM::Exp()
{
  this->loc = loc;
}

MM::AllExp::~AllExp()
{
  if(loc != MM_NULL)
  {
    delete loc;
  }
}

MM::ValExp * MM::AllExp::eval()
{
  //return the NumberValExp representing the value of the pool
  return 0;
}

MM::VOID MM::AllExp::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::AllExp::ALL_STR, MM::AllExp::ALL_LEN);
}

