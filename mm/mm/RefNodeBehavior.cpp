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
#include "RefNodeBehavior.h"
#include "Declaration.h"
#include "Definition.h"
#include "Instance.h"
#include "InterfaceNode.h"

const MM::CHAR * MM::RefNodeBehavior::REF_STR = "ref";
const MM::UINT32 MM::RefNodeBehavior::REF_LEN =
  strlen(MM::RefNodeBehavior::REF_STR);

MM::RefNodeBehavior::RefNodeBehavior(MM::NodeBehavior::IO io):
  NodeBehavior(io, WHEN_ERROR, ACT_ERROR, HOW_ERROR)
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

//resolve reference via alias edge and i to the correct i and node
MM::Instance * MM::RefNodeBehavior::resolveInstance(MM::Instance * i,
                                                    MM::Node * aliasSrc,
                                                    MM::Node * aliasTgt)
{
  MM::Instance * aliasInstance = i;
  if(aliasTgt->instanceof(MM::T_InterfaceNode) == MM_TRUE)
  {
    aliasInstance = i->getParent();
  }

  if(aliasSrc->instanceof(MM::T_InterfaceNode) == MM_TRUE)
  {
    MM::InterfaceNode * iNode = (MM::InterfaceNode *) aliasSrc;
    MM::Declaration * decl = iNode->getDeclaration();
    aliasInstance = aliasInstance->getInstance(decl);
  }
  
  return aliasInstance;
}

MM::VOID MM::RefNodeBehavior::add(MM::Instance * i,
                                  MM::Node * n,
                                  MM::UINT32 amount)
{
  MM::Node * aliasSrc = alias->getSource();
  MM::Node * aliasTgt = alias->getTarget();
  MM::Instance * aliasInstance = resolveInstance(i, aliasSrc, aliasTgt);
  aliasSrc->add(aliasInstance, amount);
}

MM::VOID MM::RefNodeBehavior::sub(MM::Instance * i,
                                  MM::Node * n,
                                  MM::UINT32 amount)
{
  MM::Node * aliasSrc = alias->getSource();
  MM::Node * aliasTgt = alias->getTarget();
  MM::Instance * aliasInstance = resolveInstance(i, aliasSrc, aliasTgt);
  aliasSrc->sub(aliasInstance, amount);
}

MM::UINT32 MM::RefNodeBehavior::getCapacity(MM::Instance * i,
                                            MM::Node * n)
{
  MM::Node * aliasSrc = alias->getSource();
  MM::Node * aliasTgt = alias->getTarget();
  MM::Instance * aliasInstance = resolveInstance(i, aliasSrc, aliasTgt);
  return aliasSrc->getCapacity(aliasInstance);
}

MM::UINT32 MM::RefNodeBehavior::getResources(MM::Instance * i,
                                             MM::Node * n)
{
  MM::Node * aliasSrc = alias->getSource();
  MM::Node * aliasTgt = alias->getTarget();
  MM::Instance * aliasInstance = resolveInstance(i, aliasSrc, aliasTgt);
  return aliasSrc->getResources(aliasInstance);
}

MM::BOOLEAN MM::RefNodeBehavior::hasCapacity(MM::Instance * i,
                                             MM::Node * n,
                                             MM::UINT32 amount)
{
  MM::Node * aliasSrc = alias->getSource();
  MM::Node * aliasTgt = alias->getTarget();
  MM::Instance * aliasInstance = resolveInstance(i, aliasSrc, aliasTgt);
  return aliasSrc->hasCapacity(aliasInstance, amount);
}

MM::BOOLEAN MM::RefNodeBehavior::hasResources(MM::Instance * i,
                                              MM::Node * n,
                                              MM::UINT32 amount)
{ 
  MM::Node * aliasSrc = alias->getSource();
  MM::Node * aliasTgt = alias->getTarget();
  MM::Instance * aliasInstance = resolveInstance(i, aliasSrc, aliasTgt);
  return aliasSrc->hasResources(aliasInstance, amount);
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