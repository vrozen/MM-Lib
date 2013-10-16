//
//  DrainNode.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/11/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Recycler.h"
#include "String.h"
#include "Location.h"
#include "Name.h"
#include "NodeBehavior.h"
#include "DrainNodeBehavior.h"

const MM::CHAR * MM::DrainNodeBehavior::DRAIN_STR = "drain";
const MM::UINT32 MM::DrainNodeBehavior::DRAIN_LEN =
  strlen(MM::DrainNodeBehavior::DRAIN_STR);

MM::DrainNodeBehavior::DrainNodeBehavior(MM::NodeBehavior::IO io,
                                         MM::NodeBehavior::When when,
                                         MM::NodeBehavior::Act act,
                                         MM::NodeBehavior::How how):
  NodeBehavior(io, when, act, how)
{
}

MM::DrainNodeBehavior::~DrainNodeBehavior()
{
}

MM::VOID MM::DrainNodeBehavior::recycle(MM::Recycler *r)
{
  this->MM::NodeBehavior::recycle(r);
}

MM::TID MM::DrainNodeBehavior::getTypeId()
{
  return MM::T_DrainNodeBehavior;
}

MM::BOOLEAN MM::DrainNodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_DrainNodeBehavior)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::NodeBehavior::instanceof(tid);
  }
}

MM::VOID MM::DrainNodeBehavior::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::DrainNodeBehavior::DRAIN_STR,
              MM::DrainNodeBehavior::DRAIN_LEN);
}

MM::VOID MM::DrainNodeBehavior::toString(MM::String * buf, MM::Name * name)
{
  MM::NodeBehavior::toString(buf, name);
  toString(buf);
  buf->space();
  name->toString(buf);
}