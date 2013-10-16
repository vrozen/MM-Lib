//
//  Program.cpp
//  mm
//
//  Created by Riemer van Rozen on 10/16/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "String.h"
#include "Recycler.h"
#include "Location.h"
#include "Name.h"
#include "Element.h"
#include "Transformation.h"
#include "Program.h"

MM::Program::Program(MM::Vector<MM::Transformation *> * transformations):
  MM::Recyclable()
{
  this->transformations = transformations;
}

MM::Program::~Program()
{
  transformations = MM_NULL;
}

MM::VOID MM::Program::recycle(MM::Recycler *r)
{
  MM::Vector<MM::Transformation *>::Iterator i = transformations->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Transformation * t = i.getNext();
    t->recycle(r);
  }
  delete transformations; //FIXME
  MM::Recyclable::recycle(r);
}

MM::TID MM::Program::getTypeId()
{
  return MM::T_Program;
}

MM::BOOLEAN MM::Program::instanceof(MM::TID tid)
{
  if(tid == MM::T_Program)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

MM::Vector<MM::Transformation *> * MM::Program::getTransformations()
{
  return this->transformations;
}

MM::VOID MM::Program::toString(MM::String * buf)
{
  MM::Vector<MM::Transformation *>::Iterator i = transformations->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Transformation * t = i.getNext();
    t->toString(buf);
    buf->linebreak();
  }
}
