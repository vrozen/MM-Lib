//
//  StateEdge.cpp
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
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "BinExp.h"
#include "Edge.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "StateEdge.h"

const MM::CHAR * MM::StateEdge::DOT_STR   = ".";
const MM::CHAR * MM::StateEdge::DOTGT_STR = ".>";
const MM::UINT32 MM::StateEdge::DOT_LEN   = strlen(MM::StateEdge::DOT_STR);
const MM::UINT32 MM::StateEdge::DOTGT_LEN = strlen(MM::StateEdge::DOTGT_STR);

MM::StateEdge::StateEdge(MM::Name * name,
                         MM::Name * src,
                         MM::Exp  * exp,
                         MM::Name * tgt) : MM::Edge(name, src, exp, tgt)
{
}

MM::StateEdge::~StateEdge()
{
}

MM::VOID MM::StateEdge::recycle(MM::Recycler *r)
{
  this->MM::Edge::recycle(r);
}

MM::TID MM::StateEdge::getTypeId()
{
  return MM::T_StateEdge;
}

MM::BOOLEAN MM::StateEdge::instanceof(MM::TID tid)
{
  if(tid == MM::T_StateEdge)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Edge::instanceof(tid);
  }
}

MM::BOOLEAN MM::StateEdge::isTrigger()
{
  MM::BOOLEAN r = MM_FALSE;
  MM::Exp * exp = this->getExp();
  if(exp != MM_NULL)
  {
    if(exp->getTypeId() == MM::T_BinExp)
    {
      MM::BinExp * binExp = (MM::BinExp *) this;
      r = binExp->isTriggerExp();
    }
  }
  return r;
}

MM::BOOLEAN MM::StateEdge::isAlias()
{
  MM::BOOLEAN r = MM_FALSE;
  MM::Exp * exp = this->getExp();
  if(exp != MM_NULL)
  {
    if(exp->getTypeId() == MM::T_AliasExp)
    {
      r = MM_TRUE;
    }
  }
  return r;
}

MM::BOOLEAN MM::StateEdge::isCondition()
{
  MM::BOOLEAN r = MM_FALSE;
  if(isTrigger() == MM_FALSE && isAlias() == MM_FALSE)
  {
    r = MM_TRUE;
  }
  return r;
}

MM::VOID MM::StateEdge::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::StateEdge::toString(MM::String * buf, MM::UINT32 indent)
{
  MM::Edge::toString(buf, indent);
  getSourceName()->toString(buf);
  buf->space();
  buf->append((MM::CHAR*)MM::StateEdge::DOT_STR, MM::StateEdge::DOT_LEN);
  getExp()->toString(buf);
  buf->append((MM::CHAR*)MM::StateEdge::DOTGT_STR, MM::StateEdge::DOTGT_LEN);
  buf->space();
  getTargetName()->toString(buf);
}
