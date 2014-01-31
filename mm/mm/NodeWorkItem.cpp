//
//  NodeWorkItem.cpp
//  mm
//
//  Created by Riemer van Rozen on 1/27/14.
//  Copyright (c) 2014 Riemer van Rozen. All rights reserved.
//

#include "NodeWorkItem.h"

MM::NodeWorkItem::NodeWorkItem(MM::Instance * instance,
                               MM::Node * node,
                               MM::Edge * edge)
{
  this->instance = instance;
  this->node = node;
  this->edge = edge;
}

MM::NodeWorkItem::NodeWorkItem::~NodeWorkItem()
{
}

MM::Instance * MM::NodeWorkItem::getInstance()
{
  return instance;
}

MM::Node * MM::NodeWorkItem::getNode()
{
  return node;
}

MM::Edge * MM::NodeWorkItem::getEdge()
{
  return edge;
}
