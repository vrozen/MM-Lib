//
//  ReferenceNode.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/28/13.
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
#include "Exp.h"
#include "Edge.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "RefNodeBehavior.h"

const MM::CHAR * MM::RefNodeBehavior::REF_STR = "ref";
const MM::UINT32 MM::RefNodeBehavior::REF_LEN =
  strlen(MM::RefNodeBehavior::REF_STR);

MM::RefNodeBehavior::RefNodeBehavior():
  NodeBehavior(IO_ERROR, WHEN_ERROR, ACT_ERROR, HOW_ERROR)
{
  alias = MM_NULL;
}

MM::RefNodeBehavior::~RefNodeBehavior()
{
  alias = MM_NULL;
}

MM::VOID MM::RefNodeBehavior::recycle(MM::Recycler *r)
{
  this->MM::NodeBehavior::recycle(r);
}

MM::TID MM::RefNodeBehavior::getTypeId()
{
  return MM::T_RefNodeBehavior;
}

MM::BOOLEAN MM::RefNodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_RefNodeBehavior)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::NodeBehavior::instanceof(tid);
  }
}

MM::Edge * MM::RefNodeBehavior::getAlias()
{
  return alias;
}

MM::VOID MM::RefNodeBehavior::setAlias(MM::Edge * edge)
{
  if(alias != MM_NULL)
  {
    printf("Warning: reset alias");
  }
  this->alias = edge;
}

MM::Node * MM::RefNodeBehavior::getReference()
{
  if(alias != MM_NULL)
  {
    MM::Node * src = alias->getSource();
    MM::NodeBehavior * behavior = src->getBehavior();
    if(behavior->getTypeId() == MM::T_RefNodeBehavior)
    {
      MM::RefNodeBehavior * ref = (MM::RefNodeBehavior *) behavior;
      return ref->getReference();
    }
    else
    {
      return src;
    }
  }
  else
  {
    //TODO: error
    printf("Error: unresolved alias");
    return MM_NULL;
  }
}

MM::UINT32 MM::RefNodeBehavior::getCreateMessage()
{
  return MM::MSG_NEW_REF;
}

MM::UINT32 MM::RefNodeBehavior::getUpdateMessage()
{
  return MM::MSG_UPD_REF;
}

MM::UINT32 MM::RefNodeBehavior::getDeleteMessage()
{
  return MM::MSG_DEL_REF;
}

MM::VOID MM::RefNodeBehavior::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::RefNodeBehavior::REF_STR,
              MM::RefNodeBehavior::REF_LEN);
}

MM::VOID MM::RefNodeBehavior::toString(MM::String * buf, MM::Name * name)
{
  toString(buf);
  buf->space();
  name->toString(buf);
}