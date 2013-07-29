//
//  BooleanValExp.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/19/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "Edge.h"
#include <vector>
#include "Node.h"
#include "PoolNode.h"
#include "ValExp.h"
#include "Operator.h"
#include "BooleanValExp.h"

const MM::CHAR * MM::BooleanValExp::TRUE_STR  = "true";
const MM::CHAR * MM::BooleanValExp::FALSE_STR = "false";
const MM::UINT32 MM::BooleanValExp::TRUE_LEN  = 4;
const MM::UINT32 MM::BooleanValExp::FALSE_LEN = 5;

MM::BooleanValExp::BooleanValExp(MM::BOOLEAN val) : MM::ValExp()
{
  this->val = val;
  this->loc = MM_NULL;
}

MM::BooleanValExp::BooleanValExp(MM::BOOLEAN val,
                                 MM::Location * loc) : MM::ValExp()
{
  this->val = val;
  this->loc = loc;
}

MM::BooleanValExp::~BooleanValExp()
{
  if(loc != MM_NULL)
  {
    delete loc;
  }
}

MM::ValExp::TYPE MM::BooleanValExp::getType()
{
  return MM::ValExp::T_BOOLEAN;
}

MM::BOOLEAN MM::BooleanValExp::getValue()
{
  return val;
}

MM::INT32 MM::BooleanValExp::getIntValue()
{
  return val;
}

MM::ValExp * MM::BooleanValExp::eval()
{
  return new BooleanValExp(val);
}

MM::ValExp * MM::BooleanValExp::eval(MM::Operator::OP op)
{
  MM::BOOLEAN valr = MM_FALSE;
  switch(op)
  {
    case MM::Operator::OP_NOT:
    {
      if(val == MM_FALSE)
      {
        valr = MM_TRUE;
      }
      else
      {
        valr = MM_FALSE;
      }
      break;
    }
    default:
    {
      //todo: exception
      break;
    }
  }
  return new BooleanValExp(valr);
}

MM::ValExp * MM::BooleanValExp::eval(MM::Operator::OP op, MM::ValExp * v)
{
  MM::BOOLEAN val2 = MM_FALSE;
  MM::BOOLEAN valr = MM_FALSE;
  if(v->getType() == MM::ValExp::T_BOOLEAN)
  {
    MM::BooleanValExp * v2 =(MM::BooleanValExp*) v;
    val2 = v2->getValue();
  }
  else
  {
    //todo: type error
  }
  
  switch(op)
  {
    case MM::Operator::OP_AND:
    {
      if(val == MM_TRUE && val2 == MM_TRUE)
      {
        valr = MM_TRUE;
      }
      else
      {
        valr = MM_FALSE;
      }
      break;
    }
    case MM::Operator::OP_OR:
    {
      if(val == MM_TRUE || val2 == MM_TRUE)
      {
        valr = MM_TRUE;
      }
      else
      {
        valr = MM_FALSE;
      }
    }
    case MM::Operator::OP_EQ:
    {
      if(val == val2)
      {
        valr = MM_TRUE;
      }
      else
      {
        valr = MM_FALSE;
      }
    }
    case MM::Operator::OP_NEQ:
    {
      if(val != val2)
      {
        valr = MM_TRUE;
      }
      else
      {
        valr = MM_FALSE;
      }
    }
    default:
    {
      //todo: exception
      break;
    }
  }
  
  return new BooleanValExp(valr);
}

MM::Location *  MM::BooleanValExp::getLocation()
{
  return loc;
}

MM::VOID MM::BooleanValExp::toString(MM::String * buf)
{
  if(val == MM_FALSE)
  {
    buf->append((MM::CHAR*)MM::BooleanValExp::FALSE_STR, MM::BooleanValExp::FALSE_LEN);
  }
  else
  {
    buf->append((MM::CHAR*)MM::BooleanValExp::TRUE_STR, MM::BooleanValExp::TRUE_LEN);
  }
}