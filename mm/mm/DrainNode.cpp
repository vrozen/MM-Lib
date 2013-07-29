//
//  DrainNode.cpp
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
#include "DrainNode.h"

const MM::CHAR * MM::DrainNode::DRAIN_STR = "drain";
const MM::UINT32  MM::DrainNode::DRAIN_LEN = 5;

MM::DrainNode::DrainNode(MM::Node::IO io,
                         MM::Node::When when,
                         MM::Node::Act act,
                         MM::Node::How how,
                         MM::Name * name): Node(io, when, act, how, name)
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

MM::VOID MM::DrainNode::toString(MM::String * buf)
{
  MM::Node::toString(buf);
  buf->append((MM::CHAR*)MM::DrainNode::DRAIN_STR, MM::DrainNode::DRAIN_LEN);
  buf->space();
  getName()->toString(buf);
}