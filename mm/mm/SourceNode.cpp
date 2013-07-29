//
//  SourceNode.cpp
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
#include "Event.h"
#include "FlowEvent.h"
#include "Transition.h"
#include "SourceNode.h"

const MM::CHAR * MM::SourceNode::SOURCE_STR = "source";
const MM::UINT32  MM::SourceNode::SOURCE_LEN = 6;

MM::SourceNode::SourceNode(MM::Node::IO io,
                           MM::Node::When when,
                           MM::Node::Act act,
                           MM::Node::How how,
                           MM::Name * name): Node(io, when, act, how, name)
{
}

MM::SourceNode::~SourceNode()
{
}

MM::BOOLEAN MM::SourceNode::hasCapacity()
{
  return MM_TRUE;
}

MM::BOOLEAN MM::SourceNode::hasResources()
{
  return MM_FALSE;
}

MM::BOOLEAN MM::SourceNode::hasCapacity(MM::UINT32 amount)
{
  return MM_TRUE;
}

MM::BOOLEAN MM::SourceNode::hasResources(MM::UINT32 amount)
{
  return MM_FALSE;
}

MM::VOID MM::SourceNode::add(MM::UINT32 amount)
{
  //TODO: throw exception
}

MM::VOID MM::SourceNode::sub(MM::UINT32 amount)
{
  //amount remains infinite
}

MM::VOID MM::SourceNode::toString(MM::String *buf)
{
  MM::Node::toString(buf);
  buf->append((MM::CHAR*)MM::SourceNode::SOURCE_STR, MM::SourceNode::SOURCE_LEN);
  buf->space();
  getName()->toString(buf);
}