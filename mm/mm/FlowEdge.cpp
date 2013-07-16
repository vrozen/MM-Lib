//
//  FlowEdge.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/11/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "String.h"
#include "Element.h"
#include "Exp.h"
#include "Edge.h"
#include <vector>
#include "Node.h"
#include "FlowEdge.h"

#define MM_FLOW_EDGE_MIN_STR    (const MM::CHAR*) "-"
#define MM_FLOW_EDGE_MINGT_STR  (const MM::CHAR*) "->"

MM::FlowEdge::FlowEdge(MM::Node * src, MM::Exp * exp, MM::Node * tgt) : MM::Edge(src, exp, tgt)
{
}

MM::FlowEdge::~FlowEdge()
{
}

MM::VOID MM::FlowEdge::toString(MM::String * buf)
{
  buf->append(getSource()->getName());
  buf->append((MM::CHAR*)MM_FLOW_EDGE_MIN_STR, sizeof(MM_FLOW_EDGE_MIN_STR));
  //exp->toString(buf);
  buf->append((MM::CHAR*)MM_FLOW_EDGE_MINGT_STR, sizeof(MM_FLOW_EDGE_MINGT_STR));
  buf->append(getTarget()->getName());
  buf->linebreak();
}
