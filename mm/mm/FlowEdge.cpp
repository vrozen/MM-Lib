//
//  FlowEdge.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/11/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "Edge.h"
#include <vector>
#include "Node.h"
#include "FlowEdge.h"

const MM::CHAR* MM::FlowEdge::MIN_STR    = "-";
const MM::CHAR* MM::FlowEdge::MINGT_STR  = "->";
const MM::UINT32 MM::FlowEdge::MIN_LEN   = 1;
const MM::UINT32 MM::FlowEdge::MINGT_LEN = 2;

MM::FlowEdge::FlowEdge(MM::Name * src, MM::Exp * exp, MM::Name * tgt) : MM::Edge(src, exp, tgt)
{
}

MM::FlowEdge::~FlowEdge()
{
}

MM::VOID MM::FlowEdge::toString(MM::String * buf)
{
  Element * src = getSource();
  Element * tgt = getTarget();
  
  if(src != MM_NULL && tgt != MM_NULL)
  {
    getSource()->toString(buf);
    buf->append((MM::CHAR*)MM::FlowEdge::MIN_STR, MM::FlowEdge::MIN_LEN);
    getExp()->toString(buf);
    buf->append((MM::CHAR*)MM::FlowEdge::MINGT_STR, MM::FlowEdge::MINGT_LEN);
    getTarget()->toString(buf);
  }
}
