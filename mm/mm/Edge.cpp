//
//  Edge.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
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

MM::Edge::Edge(MM::Name * src, MM::Exp * exp, MM::Name * tgt) : MM::Element()
{
  this->srcName = src;
  this->exp = exp;
  this->tgtName = tgt;
  this->srcNode = MM_NULL;
  this->tgtNode = MM_NULL;
}

MM::Edge::~Edge()
{
  delete srcName;
  delete tgtName;
}

MM::Node * MM::Edge::getSource()
{
  return this->srcNode;
}

MM::Node * MM::Edge::getTarget()
{
  return this->tgtNode;
}

MM::Exp * MM::Edge::getExp()
{
  return this->exp;
}

MM::VOID MM::Edge::setSource(MM::Node * src)
{
  this->srcNode = src;
}

MM::VOID MM::Edge::setTarget(MM::Node * tgt)
{
  this->tgtNode = tgt;
}