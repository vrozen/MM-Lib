//
//  OverrideExp.cpp
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
#include "OverrideExp.h"

const MM::CHAR * MM::OverrideExp::LPAREN_STR = "(";
const MM::CHAR * MM::OverrideExp::RPAREN_STR = ")";
const MM::UINT32 MM::OverrideExp::LPAREN_LEN = 1;
const MM::UINT32 MM::OverrideExp::RPAREN_LEN = 1;

MM::OverrideExp::OverrideExp(MM::Exp * exp)
{
  this->exp = exp;
  this->lparenLoc = MM_NULL;
  this->rparenLoc = MM_NULL;
}

MM::OverrideExp::OverrideExp(MM::Exp      * exp,
                             MM::Location * lparenLoc,
                             MM::Location * rparenLoc)
{
  this->exp = exp;
  this->lparenLoc = lparenLoc;
  this->rparenLoc = rparenLoc;
}

MM::OverrideExp::~OverrideExp()
{
  delete exp;
  
  if(lparenLoc != MM_NULL)
  {
    delete lparenLoc;
  }
  
  if(rparenLoc != MM_NULL)
  {
    delete rparenLoc;
  }
}

MM::ValExp * MM::OverrideExp::eval()
{
  return exp->eval();
}

MM::VOID MM::OverrideExp::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::OverrideExp::LPAREN_STR, MM::OverrideExp::LPAREN_LEN);
  exp->toString(buf);
  buf->append((MM::CHAR*)MM::OverrideExp::RPAREN_STR, MM::OverrideExp::RPAREN_LEN);
}