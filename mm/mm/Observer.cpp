//
//  Observer.cpp
//  mm
//
//  Created by Riemer van Rozen on 9/26/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "Vector.h"
#include "Recyclable.h"
#include "Recycler.h"
#include "Observer.h"
#include "Observable.h"

MM::Observer::Observer()
{
}

MM::Observer::~Observer()
{
}

MM::TID MM::Observer::getTypeId()
{
  return MM::T_Observer;
}

MM::BOOLEAN MM::Observer::instanceof(MM::TID tid)
{
  if(tid == MM::T_Observer)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}