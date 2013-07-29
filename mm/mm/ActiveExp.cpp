//
//  ActiveExp.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/21/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Exp.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "Edge.h"
#include <vector>
#include "Node.h"
#include "ValExp.h"
#include "BooleanValExp.h"
#include "ActiveExp.h"

const MM::CHAR * MM::ActiveExp::ACTIVE_STR = "active";
const MM::UINT32 MM::ActiveExp::ACTIVE_LEN = 6;

MM::ActiveExp::ActiveExp(MM::Name * name) : MM::Exp()
{
  this->name = name;
  this->loc = MM_NULL;
  this->ref = MM_NULL;
}

MM::ActiveExp::ActiveExp(MM::Name * name, MM::Location * loc) : MM::Exp()
{
  this->name = name;
  this->loc = loc;
  this->ref = MM_NULL;
}

MM::ActiveExp::~ActiveExp()
{
  delete name;
  
  if(loc != MM_NULL)
  {
    delete loc;
  }
}

MM::ValExp * MM::ActiveExp::eval()
{
  MM::BOOLEAN val = MM_FALSE;  
  //todo: set val to true if the node is active, to false if it is not
  return new BooleanValExp(val);
}

MM::VOID MM::ActiveExp::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::ActiveExp::ACTIVE_STR, MM::ActiveExp::ACTIVE_LEN);
  buf->space();
  name->toString(buf);
}
