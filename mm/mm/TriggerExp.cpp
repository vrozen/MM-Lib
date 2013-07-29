//
//  TriggerExp.cpp
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
#include "TriggerExp.h"

const MM::CHAR * MM::TriggerExp::TRIGGER_STR = "*";
const MM::UINT32 MM::TriggerExp::TRIGGER_LEN = 1;

MM::TriggerExp::TriggerExp() : MM::Exp()
{
  this->loc = MM_NULL;
}

MM::TriggerExp::TriggerExp(MM::Location * loc) : MM::Exp()
{
  this->loc = loc;
}

MM::TriggerExp::~TriggerExp()
{
  if(loc != MM_NULL)
  {
    delete loc;
  }
}

MM::ValExp * MM::TriggerExp::eval()
{
  //todo throw exception
  return 0;
}

MM::VOID MM::TriggerExp::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::TriggerExp::TRIGGER_STR, MM::TriggerExp::TRIGGER_LEN);
}