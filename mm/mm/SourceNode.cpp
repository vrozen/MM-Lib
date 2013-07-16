//
//  SourceNode.cpp
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
#include "SourceNode.h"

#define MM_SOURCE_NODE_SOURCE_STR (const MM::CHAR*)  "source"

#define MM_SOURCE_NODE_SOURCE_LEN (const MM::UINT32) 6

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
  buf->append((MM::CHAR*)MM_SOURCE_NODE_SOURCE_STR, (MM::UINT32)MM_SOURCE_NODE_SOURCE_LEN);
  buf->linebreak();
}