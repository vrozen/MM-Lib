//
//  Transition.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Transformation.h"
#include "Transition.h"

const MM::CHAR * MM::Transition::STEP_STR = "step";
const MM::UINT32 MM::Transition::STEP_LEN =
strlen(MM::Transition::STEP_STR);

MM::Transition::Transition(MM::Vector<MM::Element *> * elements):
  MM::Transformation(elements)
{
  this->loc = MM_NULL;
  this->str = MM_NULL;
}

MM::Transition::Transition(MM::Vector<MM::Element *> * elements,
                           MM::Location * loc):
  MM::Transformation(elements)
{
  this->loc = loc;
  this->str = MM_NULL;
}

MM::Transition::~Transition()
{
  this->loc = MM_NULL;
  this->str = MM_NULL;
}

MM::VOID MM::Transition::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  if(str != MM_NULL)
  {
    str->recycle(r);
  }
  MM::Transformation::recycle(r);
}

MM::TID MM::Transition::getTypeId()
{
  return MM::T_Transition;
}

MM::BOOLEAN MM::Transition::instanceof(MM::TID tid)
{
  if(tid == MM::T_Transition)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Transformation::instanceof(tid);
  }
}

MM::VOID MM::Transition::toString(MM::String * buf)
{
  MM::Transformation::toString(buf);
  buf->append((MM::CHAR*)MM::Transition::STEP_STR,
              MM::Transition::STEP_LEN);
  buf->linebreak();
}