//
//  SourceNode.cpp
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
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "NodeBehavior.h"
#include "SourceNodeBehavior.h"

const MM::CHAR * MM::SourceNodeBehavior::SOURCE_STR  = "source";
const MM::UINT32  MM::SourceNodeBehavior::SOURCE_LEN =
  strlen(MM::SourceNodeBehavior::SOURCE_STR);

MM::SourceNodeBehavior::SourceNodeBehavior(MM::NodeBehavior::IO io,
                                           MM::NodeBehavior::When when,
                                           MM::NodeBehavior::Act act,
                                           MM::NodeBehavior::How how):
  MM::NodeBehavior(io, when, act, how)
{
}

MM::SourceNodeBehavior::~SourceNodeBehavior()
{
}

MM::VOID MM::SourceNodeBehavior::recycle(MM::Recycler *r)
{
  this->MM::NodeBehavior::recycle(r);
}

MM::TID MM::SourceNodeBehavior::getTypeId()
{
  return MM::T_SourceNodeBehavior;
}

MM::BOOLEAN MM::SourceNodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_SourceNodeBehavior)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::NodeBehavior::instanceof(tid);
  }
}

MM::VOID MM::SourceNodeBehavior::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::SourceNodeBehavior::SOURCE_STR,
              MM::SourceNodeBehavior::SOURCE_LEN);
}

MM::VOID MM::SourceNodeBehavior::toString(MM::String * buf, MM::Name * name)
{
  MM::NodeBehavior::toString(buf,name);
  toString(buf);
  buf->space();
  name->toString(buf);
}