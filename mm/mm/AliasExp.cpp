//
//  RefExp.cpp
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
#include "AliasExp.h"

const MM::CHAR * MM::AliasExp::ALIAS_STR = "=";
const MM::UINT32 MM::AliasExp::ALIAS_LEN = 1;

MM::AliasExp::AliasExp() : MM::Exp()
{
  this->loc = MM_NULL;
}

MM::AliasExp::AliasExp(MM::Location * loc) : MM::Exp()
{
  this->loc = loc;
}

MM::AliasExp::~AliasExp()
{
  if(loc != MM_NULL)
  {
    delete loc;
  }
}

MM::ValExp * MM::AliasExp::eval()
{
  //todo throw exception
  return 0;
}

MM::VOID MM::AliasExp::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::AliasExp::ALIAS_STR, MM::AliasExp::ALIAS_LEN);
}