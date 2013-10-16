//
//  Edge.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
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
#include "Operator.h"
#include "Observer.h"
#include "Observable.h"
#include "Exp.h"
#include "Edge.h"
#include "NodeBehavior.h"
#include "Node.h"

const MM::CHAR MM::Edge::COLON_CHAR = ':';

MM::Edge::Edge(MM::Name * name,
               MM::Name * src,
               MM::Exp * exp,
               MM::Name * tgt): MM::Element(name)
{
  this->srcName = src;
  this->exp = exp;
  this->tgtName = tgt;
  this->srcNode = MM_NULL;
  this->tgtNode = MM_NULL;
}

MM::Edge::~Edge()
{
  srcName = MM_NULL;
  tgtName = MM_NULL;
  srcNode = MM_NULL;
  tgtNode = MM_NULL;
  exp = MM_NULL;
}

MM::VOID MM::Edge::recycle(MM::Recycler * r)
{
  srcName->recycle(r);
  tgtName->recycle(r);
  exp->recycle(r);
  this->Element::recycle(r);
}

MM::TID MM::Edge::getTypeId()
{
  return MM::T_Edge;
}

MM::BOOLEAN MM::Edge::instanceof(MM::TID tid)
{
  if(tid == MM::T_Edge)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}

MM::Node * MM::Edge::getSource()
{
  return this->srcNode;
}

MM::Node * MM::Edge::getTarget()
{
  return this->tgtNode;
}

MM::Exp * MM::Edge::getExp()
{
  return this->exp;
}

MM::VOID MM::Edge::setExp(MM::Exp * exp)
{
  this->exp = exp;
}

MM::VOID MM::Edge::setSource(MM::Node * src)
{
  this->srcNode = src;
}

MM::VOID MM::Edge::setTarget(MM::Node * tgt)
{
  this->tgtNode = tgt;
}

MM::Name * MM::Edge::getSourceName()
{
  return this->srcName;
}

MM::Name * MM::Edge::getTargetName()
{
  return this->tgtName;
}

MM::VOID MM::Edge::toString(MM::String * buf, MM::UINT32 indent)
{
  buf->space(indent);
  if(name != MM_NULL)
  {
    name->toString(buf);
    buf->append(MM::Edge::COLON_CHAR);
    buf->space();
  }
}

