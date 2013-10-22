//
//  GateNodeBehavior.cpp
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
#include "Recycler.h"
#include "String.h"
#include "Location.h"
#include "Name.h"
#include "NodeBehavior.h"
#include "GateNodeBehavior.h"

const MM::CHAR * MM::GateNodeBehavior::GATE_STR = "gate";
const MM::UINT32 MM::GateNodeBehavior::GATE_LEN =
  strlen(MM::GateNodeBehavior::GATE_STR);

MM::GateNodeBehavior::GateNodeBehavior(MM::NodeBehavior::IO   io,
                                       MM::NodeBehavior::When when,
                                       MM::NodeBehavior::Act  act,
                                       MM::NodeBehavior::How  how):
  NodeBehavior(io, when, act, how)
{
}

MM::GateNodeBehavior::~GateNodeBehavior()
{
}

MM::VOID MM::GateNodeBehavior::recycle(MM::Recycler *r)
{
  this->MM::NodeBehavior::recycle(r);
}

MM::TID MM::GateNodeBehavior::getTypeId()
{
  return MM::T_GateNodeBehavior;
}

MM::BOOLEAN MM::GateNodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_GateNodeBehavior)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::NodeBehavior::instanceof(tid);
  }
}

MM::UINT32 MM::GateNodeBehavior::getCreateMessage()
{
  return MM::MSG_NEW_GATE;
}

MM::UINT32 MM::GateNodeBehavior::getUpdateMessage()
{
  return MM::MSG_UPD_GATE;
}

MM::UINT32 MM::GateNodeBehavior::getDeleteMessage()
{
  return MM::MSG_DEL_GATE;
}

MM::VOID MM::GateNodeBehavior::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::GateNodeBehavior::GATE_STR,
              MM::GateNodeBehavior::GATE_LEN);
}

MM::VOID MM::GateNodeBehavior::toString(MM::String * buf, MM::Name * name)
{
  MM::NodeBehavior::toString(buf, name);
  toString(buf);
  buf->space();
  name->toString(buf);
}