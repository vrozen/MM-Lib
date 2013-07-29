//
//  UnExp.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/19/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <iostream>
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
#include "UnExp.h"

MM::UnExp::UnExp(MM::Operator::OP op,
                 Exp * exp) : MM::Exp()
{
  this->exp = exp;
  this->op = op;
}

MM::UnExp::UnExp(MM::Operator::OP op,
                 Exp * exp,                 
                 MM::Location * loc) : MM::Exp()
{
  this->exp = exp;
  this->op = op;
  this->loc = loc;
}

MM::UnExp::~UnExp()
{
  delete exp;
  if(loc != MM_NULL)
  {
    delete loc;
  }
}

MM::ValExp * MM::UnExp::eval()
{
  ValExp * val = exp->eval();
  ValExp * ret = val->eval(op);
  delete val;
  return ret;
}

MM::VOID MM::UnExp::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::Operator::OP_STR[op], MM::Operator::OP_LEN[op]);
  exp->toString(buf);
}