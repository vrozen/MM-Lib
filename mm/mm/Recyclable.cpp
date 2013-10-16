//
//  Recyclable.cpp
//  mm
//
//  Created by Riemer van Rozen on 8/1/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "String.h"
#include "Vector.h"
#include "Recycler.h"

MM::Recyclable::Recyclable()
{
}

MM::Recyclable::~Recyclable()
{
}

MM::TID MM::Recyclable::getTypeId()
{
  return MM::T_Recyclable;
}

MM::BOOLEAN MM::Recyclable::instanceof(MM::TID tid)
{
  if(tid == MM::T_Recyclable)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::VOID MM::Recyclable::recycle(MM::Recycler * r)
{
  r->uncreate(this);
}

//const MM::VOID MM::Recyclable::setRecycler(const MM::Recycler * r)
//{
//  MM::Recyclable::r = r;
//}

