//
//  VarValExp.cpp
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
#include "VarExp.h"

MM::VarExp::VarExp(MM::Name * name) : MM::Exp()
{
  this->name = name;
  this->ref = MM_NULL;
}

MM::VarExp::~VarExp()
{
  delete name;
}

MM::ValExp * MM::VarExp::eval()
{
  //return the NumberValExp representing the value of the pool
  return NULL;
}

MM::VOID MM::VarExp::toString(MM::String * buf)
{
  name->toString(buf);
}
