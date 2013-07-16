//
//  StateEdge.cpp
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
#include "StateEdge.h"

#define MM_STATE_EDGE_DOT_STR    (const MM::CHAR*) "."
#define MM_STATE_EDGE_DOTGT_STR  (const MM::CHAR*) ".>"
#define MM_STATE_EDGE_DOT_LEN    1
#define MM_STATE_EDGE_DOTGT_LEN  2

MM::StateEdge::StateEdge(MM::Node * src, MM::Exp * exp, MM::Node * tgt) : MM::Edge(src, exp, tgt)
{
}

MM::StateEdge::~StateEdge()
{
}

MM::VOID MM::StateEdge::toString(MM::String * buf)
{
  buf->append(getSource()->getName());
  buf->append((MM::CHAR*)MM_STATE_EDGE_DOT_STR, MM_STATE_EDGE_DOT_LEN);
  //exp->toString(buf);
  buf->append((MM::CHAR*)MM_STATE_EDGE_DOTGT_STR, MM_STATE_EDGE_DOTGT_LEN);
  buf->append(getTarget()->getName());
  buf->linebreak();
}
