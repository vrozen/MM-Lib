//
//  FlowEdge.cpp
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
#include "Edge.h"
#include "NodeWorkItem.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "FlowEdge.h"

const MM::CHAR* MM::FlowEdge::MIN_STR    = "-";
const MM::CHAR* MM::FlowEdge::MINGT_STR  = "->";
const MM::UINT32 MM::FlowEdge::MIN_LEN   = strlen(MM::FlowEdge::MIN_STR);
const MM::UINT32 MM::FlowEdge::MINGT_LEN = strlen(MM::FlowEdge::MINGT_STR);

MM::FlowEdge::FlowEdge(MM::Name * name,
                       MM::Name * src,
                       MM::Exp  * exp,
                       MM::Name * tgt) : MM::Edge(name, src, exp, tgt)
{
}

MM::FlowEdge::~FlowEdge()
{
}

MM::VOID MM::FlowEdge::recycle(MM::Recycler *r)
{
  this->MM::Edge::recycle(r);
}

MM::TID MM::FlowEdge::getTypeId()
{
  return MM::T_FlowEdge;
}

MM::BOOLEAN MM::FlowEdge::instanceof(MM::TID tid)
{
  if(tid == MM::T_FlowEdge)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Edge::instanceof(tid);
  }
}

MM::VOID MM::FlowEdge::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::FlowEdge::toString(MM::String * buf, MM::UINT32 indent)
{
  MM::Edge::toString(buf, indent);
  getSourceName()->toString(buf);
  buf->space();
  buf->append((MM::CHAR*)MM::FlowEdge::MIN_STR, MM::FlowEdge::MIN_LEN);
  getExp()->toString(buf);
  buf->append((MM::CHAR*)MM::FlowEdge::MINGT_STR, MM::FlowEdge::MINGT_LEN);
  buf->space();
  getTargetName()->toString(buf);
}
