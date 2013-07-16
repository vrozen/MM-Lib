//
//  Edge.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "String.h"
#include "Element.h"
#include "Exp.h"
#include "Edge.h"
#include <vector>
#include "Node.h"

MM::Edge::Edge(MM::Node * src, MM::Exp * exp, MM::Node * tgt)
{
  this->src = src;
  this->exp = exp;
  this->tgt = tgt;
}

MM::Edge::~Edge()
{
}

MM::Node * MM::Edge::getSource()
{
  return this->src;
}

MM::Node * MM::Edge::getTarget()
{
  return this->tgt;
}