//
//  Event.cpp
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
#include "Operator.h"
#include "Exp.h"
#include "Edge.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "Event.h"

MM::Event::Event() : MM::Recyclable()
{
};

MM::Event::~Event()
{
};

MM::VOID MM::Event::recycle(MM::Recycler *r)
{
  this->MM::Recyclable::recycle(r);
}

MM::TID MM::Event::getTypeId()
{
  return MM::T_Event;
}

MM::BOOLEAN MM::Event::instanceof(MM::TID tid)
{
  if(tid == MM::T_Event)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}
