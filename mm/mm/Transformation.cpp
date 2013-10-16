//
//  Transformation.cpp
//  mm
//
//  Created by Riemer van Rozen on 10/16/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "String.h"
#include "Location.h"
#include "Name.h"
#include "Vector.h"
#include "Recycler.h"
#include "Element.h"
#include "Transformation.h"

MM::Transformation::Transformation(MM::Vector<Element *> * elements)
{
  this->elements = elements;
}

MM::Transformation::~Transformation()
{
  this->elements = MM_NULL;
}

MM::VOID MM::Transformation::recycle(MM::Recycler *r)
{
  MM::Vector<Element *>::Iterator i = elements->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Element * element = i.getNext();
    element->recycle(r);
  }  
  delete elements; //TODO
  //r->recycle(elements);
  MM::Recyclable::recycle(r);
}

MM::BOOLEAN MM::Transformation::instanceof(MM::TID tid)
{
  if(tid == T_Transformation)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

MM::Vector<MM::Element *> * MM::Transformation::getElements()
{
  return elements;
}

MM::VOID MM::Transformation::clearElements()
{
  elements->clear();
}

MM::VOID MM::Transformation::toString(MM::String * buf)
{
  MM::Vector<Element *>::Iterator i = elements->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Element * element = i.getNext();
    element->toString(buf);
    buf->linebreak();
  }
}

