//
//  BinExp.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/18/13.
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
#include "BinExp.h"

MM::BinExp::BinExp(Exp              * e1,
                   MM::Operator::OP   op,
                   Exp              * e2) : MM::Exp()
{
  this->e1  = e1;
  this->op  = op;
  this->e2  = e2;
  this->loc = MM_NULL;
}

MM::BinExp::BinExp(Exp              * e1,
                   MM::Operator::OP   op,
                   Exp              * e2,
                   MM::Location     * loc) : MM::Exp()
{
  this->e1  = e1;
  this->op  = op;
  this->e2  = e2;
  this->loc = loc;
}

MM::BinExp::~BinExp()
{
  delete e1;
  delete e2;
  
  if(loc != MM_NULL)
  {
    delete loc;
  }
}

MM::ValExp * MM::BinExp::eval()
{
  MM::ValExp * r  = NULL;
  MM::ValExp * v1 = e1->eval();
  MM::ValExp * v2 = e2->eval();
  r = v1->eval(this->op, v2);
  delete v1;
  delete v2;
  return r;
}

MM::VOID MM::BinExp::toString(MM::String * buf)
{
  e1->toString(buf);
  buf->append((MM::CHAR*) MM::Operator::OP_STR[op], MM::Operator::OP_LEN[op]);
  e2->toString(buf);
}
