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
#include "Map.h"
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Exp.h"
#include "Edge.h"
#include "Observer.h"
#include "Observable.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "DrainNodeBehavior.h"
#include "Declaration.h"
#include "Definition.h"
#include "Instance.h"

const MM::CHAR * MM::DrainNodeBehavior::DRAIN_STR = "drain";
const MM::UINT32 MM::DrainNodeBehavior::DRAIN_LEN =
  strlen(MM::DrainNodeBehavior::DRAIN_STR);

MM::DrainNodeBehavior::DrainNodeBehavior(MM::NodeBehavior::IO io,
                                         MM::NodeBehavior::When when,
                                         MM::NodeBehavior::How how):
  NodeBehavior(io, when, MM::NodeBehavior::ACT_PULL, how)
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

MM::UINT32 MM::DrainNodeBehavior::getCreateMessage()
{
  return MM::MSG_NEW_DRAIN;
}

MM::UINT32 MM::DrainNodeBehavior::getUpdateMessage()
{
  return MM::MSG_UPD_DRAIN;
}

MM::UINT32 MM::DrainNodeBehavior::getDeleteMessage()
{
  return MM::MSG_DEL_DRAIN;
}


MM::VOID MM::DrainNodeBehavior::add(MM::Instance * i,
                                    MM::Node * n,
                                    MM::UINT32 amount)
{
  //do nothing
}

MM::VOID MM::DrainNodeBehavior::sub(MM::Instance * i,
                                    MM::Node * n,
                                    MM::UINT32 amount)
{
  //do nothing
}

MM::UINT32 MM::DrainNodeBehavior::getCapacity(MM::Instance * i,
                                              MM::Node * n)
{
  return MM_MAX_RESOURCES;
}

MM::UINT32 MM::DrainNodeBehavior::getResources(MM::Instance * i,
                                               MM::Node * n)
{
  return 0;
}

MM::BOOLEAN MM::DrainNodeBehavior::hasCapacity(MM::Instance * i,
                                               MM::Node * n,
                                               MM::UINT32 amount)
{
  return MM_TRUE;
}

MM::BOOLEAN MM::DrainNodeBehavior::hasResources(MM::Instance * i,
                                                MM::Node * n,
                                                MM::UINT32 amount)
{
  return MM_FALSE;
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