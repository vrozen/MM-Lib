//
//  Instance.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/23/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Declaration.h"

MM::Declaration::Declaration(MM::Name * type,
                             MM::Name * name) : MM::Element()
{
  this->type = type;
  this->name = name;
  this->def = MM_NULL;
}

MM::Declaration::~Declaration()
{
  delete type;
  delete name;
}

MM::Definition * MM::Declaration::getDefinition()
{
  return def;
}

MM::VOID MM::Declaration::toString(MM::String * buf)
{
  type->toString(buf);
  buf->space();
  name->toString(buf);
}