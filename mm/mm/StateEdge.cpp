//
//  StateEdge.cpp
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
#include "StateEdge.h"

const MM::CHAR * MM::StateEdge::DOT_STR   = ".";
const MM::CHAR * MM::StateEdge::DOTGT_STR = ".>";
const MM::UINT32 MM::StateEdge::DOT_LEN   = 1;
const MM::UINT32 MM::StateEdge::DOTGT_LEN = 2;

MM::StateEdge::StateEdge(MM::Name * src, MM::Exp * exp, MM::Name * tgt) : MM::Edge(src, exp, tgt)
{
}

MM::StateEdge::~StateEdge()
{
}

MM::VOID MM::StateEdge::toString(MM::String * buf)
{
  Element * src = getSource();
  Element * tgt = getTarget();
  
  if(src != MM_NULL && tgt != MM_NULL)
  {
    getSource()->toString(buf);
    buf->append((MM::CHAR*)MM::StateEdge::DOT_STR, MM::StateEdge::DOT_LEN);
    getExp()->toString(buf);
    buf->append((MM::CHAR*)MM::StateEdge::DOTGT_STR, MM::StateEdge::DOTGT_LEN);
    getTarget()->toString(buf);
  }
}
