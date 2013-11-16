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
#include "SourceNodeBehavior.h"
#include "Declaration.h"
#include "Definition.h"
#include "Instance.h"

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

MM::UINT32 MM::SourceNodeBehavior::getCreateMessage()
{
  return MM::MSG_NEW_SOURCE;
}

MM::UINT32 MM::SourceNodeBehavior::getUpdateMessage()
{
  return MM::MSG_UPD_SOURCE;
}

MM::UINT32 MM::SourceNodeBehavior::getDeleteMessage()
{
  return MM::MSG_DEL_SOURCE;
}


MM::VOID MM::SourceNodeBehavior::add(MM::Instance * i,
                                     MM::Node * n,
                                     MM::UINT32 amount)
{
  //do nothing
}

MM::VOID MM::SourceNodeBehavior::sub(MM::Instance * i,
                                     MM::Node * n,
                                     MM::UINT32 amount)
{
  //do nothing
}

MM::UINT32 MM::SourceNodeBehavior::getCapacity(MM::Instance * i,
                                               MM::Node * n)
{
  return 0;
}

MM::UINT32 MM::SourceNodeBehavior::getResources(MM::Instance * i,
                                                MM::Node * n)
{
  return MM_MAX_RESOURCES;
}

MM::BOOLEAN MM::SourceNodeBehavior::hasCapacity(MM::Instance * i,
                                                MM::Node * n,
                                                MM::UINT32 amount)
{
  return MM_FALSE;
}

MM::BOOLEAN MM::SourceNodeBehavior::hasResources(MM::Instance * i,
                                                 MM::Node * n,
                                                 MM::UINT32 amount)
{
  return MM_TRUE;
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