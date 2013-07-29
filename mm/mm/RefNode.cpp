//
//  ReferenceNode.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/28/13.
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
#include "RefNode.h"

const MM::CHAR * MM::RefNode::REF_STR = "ref";
const MM::UINT32 MM::RefNode::REF_LEN = 3;

MM::RefNode::RefNode(MM::Name * name): Node(IO_ERROR, WHEN_ERROR, ACT_ERROR, HOW_ERROR, name)
{
}

MM::RefNode::~RefNode()
{
}

MM::BOOLEAN MM::RefNode::hasCapacity()
{
  return ref->hasCapacity();
}

MM::BOOLEAN MM::RefNode::hasResources()
{
  return ref->hasResources();
}

MM::BOOLEAN MM::RefNode::hasCapacity(MM::UINT32 amount)
{
  return ref->hasCapacity(amount);
}

MM::BOOLEAN MM::RefNode::hasResources(MM::UINT32 amount)
{
  return ref->hasResources(amount);
}

MM::VOID MM::RefNode::add(MM::UINT32 amount)
{
  return ref->add(amount);
}

MM::VOID MM::RefNode::sub(MM::UINT32 amount)
{
  return ref->sub(amount);
}

MM::VOID MM::RefNode::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::RefNode::REF_STR, MM::RefNode::REF_LEN);
  buf->space();
  getName()->toString(buf);
}