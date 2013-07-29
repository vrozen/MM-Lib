//
//  Pool.cpp
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
#include "PoolNode.h"

const MM::CHAR * MM::PoolNode::POOL_STR = "pool";
const MM::CHAR * MM::PoolNode::AT_STR   = "at";
const MM::CHAR * MM::PoolNode::MAX_STR  = "max";
const MM::CHAR * MM::PoolNode::ADD_STR  = "add";
const MM::UINT32 MM::PoolNode::POOL_LEN = 4;
const MM::UINT32 MM::PoolNode::AT_LEN   = 2;
const MM::UINT32 MM::PoolNode::MAX_LEN  = 3;
const MM::UINT32 MM::PoolNode::ADD_LEN  = 3;

MM::PoolNode::PoolNode(MM::Node::IO    io,
                       MM::Node::When  when,
                       MM::Node::Act   act,
                       MM::Node::How   how,
                       MM::Name      * name,
                       MM::INT32       at,
                       MM::UINT32      max,
                       MM::Exp       * exp): MM::Node(io, when, act, how, name)
{
  this->val = at;
  this->at = at;
  this->max = max;
  this->exp = exp;
  //this->val_new = val;
  //this->val_old = val;
}

MM::PoolNode::~PoolNode()
{
}

//available resources
MM::INT32 MM::PoolNode::getResources()
{
  return val_old;
}

//available capacity
MM::INT32 MM::PoolNode::getCapacity()
{
  return max - val_new;
}


MM::BOOLEAN MM::PoolNode::hasCapacity()
{
  if(this->val_new < this->max)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::BOOLEAN MM::PoolNode::hasResources()
{
  if(this->val_old > 0)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::BOOLEAN MM::PoolNode::hasCapacity(MM::UINT32 amount)
{
  if(this->val_new + amount <= this->max)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::BOOLEAN MM::PoolNode::hasResources(MM::UINT32 amount)
{
  if(this->val_old >= amount)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::VOID MM::PoolNode::add(MM::UINT32 amount)
{
  this->val_new += amount;
}

MM::VOID MM::PoolNode::sub(MM::UINT32 amount)
{
  this->val_new -= amount;
  this->val_old -= amount;
}

void MM::PoolNode::toString(MM::String * buf)
{
  MM::Node::toString(buf);
  buf->append((MM::CHAR*)MM::PoolNode::POOL_STR, MM::PoolNode::POOL_LEN);
  buf->space();
  getName()->toString(buf);
  buf->space();
  if(at!= 0)
  {
    buf->append((MM::CHAR*)MM::PoolNode::AT_STR, MM::PoolNode::AT_LEN);
    buf->space();
    buf->append(at);
    buf->space();
  }
  if(max != 0)
  {
    buf->append((MM::CHAR*)MM::PoolNode::MAX_STR, MM::PoolNode::MAX_LEN);
    buf->space();
    buf->append(max);
    buf->space();
  }
  if(exp != MM_NULL)
  {
    buf->append((MM::CHAR*)MM::PoolNode::ADD_STR, MM::PoolNode::ADD_LEN);
    buf->space();
    exp->toString(buf);
  }
}
