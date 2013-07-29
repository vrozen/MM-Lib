//
//  RangeValExp.cpp
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
#include "ValExp.h"
#include <stdlib.h>
#include "NumberValExp.h"
#include "BooleanValExp.h"
#include "RangeValExp.h"

const MM::CHAR * MM::RangeValExp::DOTDOT_STR = "..";
const MM::UINT32 MM::RangeValExp::DOTDOT_LEN = 2;

MM::RangeValExp::RangeValExp(MM::UINT32 min,
                             MM::UINT32 max) : MM::ValExp()
{
  this->min = min;
  this->max = max;
  this->minLoc = MM_NULL;
  this->rangeLoc = MM_NULL;
  this->maxLoc = MM_NULL;
}

MM::RangeValExp::RangeValExp(MM::UINT32     min,
                             MM::UINT32     max,
                             MM::Location * minLoc,
                             MM::Location * rangeLoc,
                             MM::Location * maxLoc) : MM::ValExp()
{
  this->min = min;
  this->max = max;
  this->minLoc = minLoc;
  this->rangeLoc = rangeLoc;
  this->maxLoc = maxLoc;
}

MM::RangeValExp::~RangeValExp()
{
  if(minLoc != MM_NULL)
  {
    delete minLoc;
  }
  if(maxLoc != MM_NULL)
  {
    delete maxLoc;
  }
  if(rangeLoc != MM_NULL)
  {
    delete rangeLoc;
  }
}

MM::UINT32 MM::RangeValExp::getMin()
{
  return this->min;
}

MM::UINT32 MM::RangeValExp::getMax()
{
  return this->max;
}

MM::INT32 MM::RangeValExp::getIntValue()
{
  return (rand() % (max-min+1) + min); //random number between min and max
}

MM::ValExp::TYPE MM::RangeValExp::getType()
{
  return MM::ValExp::T_RANGE;
}

MM::ValExp * MM::RangeValExp::eval()
{
  return new MM::RangeValExp(min, max);
}

MM::ValExp * MM::RangeValExp::eval(MM::Operator::OP op)
{
  //todo: type error
  return NULL;
}

MM::ValExp * MM::RangeValExp::eval(MM::Operator::OP op, MM::ValExp * v)
{
  MM::ValExp * r = NULL;
  MM::ValExp::TYPE rtype = T_ERROR;
  MM::UINT32 rrmin = 0;
  MM::UINT32 rrmax = 0;
  MM::BOOLEAN rbval = MM_FALSE;
  MM::INT32 val = 0;
  
  if(v->getType() == MM::ValExp::T_NUMBER)
  {
    val = ((MM::NumberValExp*)v)->getIntValue();
  }
  else
  {
    //todo: type error
  }
  
  switch(op)
  {
    case MM::Operator::OP_ADD:
    {
      rrmin = min + val;
      rrmax = max + val;
      rtype = MM::ValExp::T_RANGE;
      break;
    }
    case MM::Operator::OP_SUB:
    {
      rrmin = min - val;
      rrmax = max - val;
      rtype = MM::ValExp::T_RANGE;
      break;
    }
    case MM::Operator::OP_MUL:
    {
      rrmin = min * val;
      rrmax = max * val;
      rtype = MM::ValExp::T_RANGE;
      break;
    }
    case MM::Operator::OP_DIV:
    {
      rrmin = min / val;
      rrmax = max / val;
      rtype = MM::ValExp::T_RANGE;
      break;
    }
    case MM::Operator::OP_EQ:
    {
      rbval = MM_FALSE;
      rtype = MM::ValExp::T_BOOLEAN;
      break;
    }
    case MM::Operator::OP_NEQ:
    {
      rbval = MM_TRUE;
      rtype = MM::ValExp::T_BOOLEAN;
      break;
    }
    case MM::Operator::OP_GT:
    {
      if(min > val)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::ValExp::T_BOOLEAN;
      break;
    }
    case MM::Operator::OP_LT:
    {
      if(max < val)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::ValExp::T_BOOLEAN;
      break;
    }
    case MM::Operator::OP_LE:
    {
      if(max <= val)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::ValExp::T_BOOLEAN;
      break;
    }
    case MM::Operator::OP_GE:
    {
      if(min >= val)
      {
        rbval = MM_TRUE;
      }
      else
      {
        rbval = MM_FALSE;
      }
      rtype = MM::ValExp::T_BOOLEAN;
      break;
    }
    default:
    {
      //todo: operand error
      break;
    }
  }
  
  switch(rtype)
  {
    case MM::ValExp::T_BOOLEAN:
      r = new MM::BooleanValExp(rbval);
      break;
    case MM::ValExp::T_RANGE:
      r = new MM::RangeValExp(rrmin, rrmax);
      break;
    default:
      //todo: return type error
      break;
  }
  
  return r;
}

MM::VOID MM::RangeValExp::toString(MM::String * buf)
{
  buf->append(min);
  buf->append((MM::CHAR*)MM::RangeValExp::DOTDOT_STR, MM::RangeValExp::DOTDOT_LEN);
  buf->append(max);
}