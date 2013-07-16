//
//  DrainNode.cpp
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
#include "Event.h"
#include "FlowEvent.h"
#include "Transition.h"
#include "DrainNode.h"

#define MM_DRAIN_NODE_DRAIN_STR (const MM::CHAR*)  "drain"

#define MM_DRAIN_NODE_DRAIN_LEN (const MM::UINT32) 5


MM::DrainNode::DrainNode(When when, Act act, How how,
                       MM::String * name): Node(when, act, how, name)
{
}

MM::DrainNode::~DrainNode()
{
}

MM::BOOLEAN MM::DrainNode::hasCapacity()
{
  return MM_TRUE;
}

MM::BOOLEAN MM::DrainNode::hasResources()
{
  return MM_FALSE;
}

MM::BOOLEAN MM::DrainNode::hasCapacity(MM::UINT32 amount)
{
  return MM_TRUE;
}

MM::BOOLEAN MM::DrainNode::hasResources(MM::UINT32 amount)
{
  return MM_FALSE;
}

MM::VOID MM::DrainNode::add(MM::UINT32 amount)
{
  //amount remains infinitely negative
}

MM::VOID MM::DrainNode::sub(MM::UINT32 amount)
{
  //TODO: throw exception
}

MM::VOID MM::DrainNode::toString(MM::String *buf)
{

  MM::Node::toString(buf);
  buf->append((MM::CHAR*)MM_DRAIN_NODE_DRAIN_STR, (MM::UINT32)MM_DRAIN_NODE_DRAIN_LEN);
  buf->linebreak();
}