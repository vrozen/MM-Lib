//
//  Pool.cpp
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
#include "Event.h"
#include "FlowEvent.h"
#include "Transition.h"
#include "PoolNode.h"

#define MM_POOL_NODE_POOL_STR (const MM::CHAR*) "pool"
#define MM_POOL_NODE_AT_STR   (const MM::CHAR*) "at"
#define MM_POOL_NODE_MAX_STR  (const MM::CHAR*) "max"
#define MM_POOL_NODE_ADD_STR  (const MM::CHAR*) "add"

#define MM_POOL_NODE_POOL_LEN (const MM::CHAR*) 4
#define MM_POOL_NODE_AT_LEN   (const MM::CHAR*) 2
#define MM_POOL_NODE_MAX_LEN  (const MM::CHAR*) 3
#define MM_POOL_NODE_ADD_LEN  (const MM::CHAR*) 3


MM::PoolNode::PoolNode(When when, Act act, How how,
                       MM::String * name, MM::INT32 at, MM::UINT32 max,
                       MM::Exp * exp): Node(when, act, how, name)
{
  this->val = at;
  this->at = at;
  this->max = max;
  this->exp = exp;
  this->val_new = val;
  this->val_old = val;
}

MM::PoolNode::~PoolNode()
{
}



MM::Transition * MM::PoolNode::stepAll(std::vector<Edge*> * work)
{
  std::vector<Edge*>::iterator i;
  bool success = true;
  Transition * tr = new Transition();
  
  for(i = work->begin(); i != work->end(); i++)
  {
    Edge* edge = *i;
    MM::INT32 flow = 0;
    Node * src = edge->getSource();
    Node * tgt = edge->getTarget();
    
    if(flow > 0 && src->hasResources(flow) && tgt->hasCapacity(flow))
    {
      src->sub(flow);
      tgt->add(flow);
      tr->add(new FlowEvent(src,flow,tgt));
    }
    else
    {
      success = false;
      break;
    }
  }
  
  if(!success)
  {
    tr->back();
    tr->clear();
  }
  
  return tr;
}

MM::Transition * MM::PoolNode::stepAny(std::vector<Edge*> * work)
{
  std::vector<Edge*>::iterator i;
  std::vector<Edge*> rnd(work->size());
  rnd = *work;
  
  Transition * tr = new Transition();
  std::random_shuffle ( rnd.begin(), rnd.end() );
  
  for(i = rnd.begin(); i != rnd.end(); i++)
  {
    Edge* edge = *i;
    MM::INT32 flow = 0;
    Node * src = edge->getSource();
    Node * tgt = edge->getTarget();
    
    if(flow > 0 && src->hasResources() && tgt->hasCapacity())
    {
      if(src->hasResources(flow))
      {
        if(tgt->hasCapacity(flow))
        {
          src->sub(flow);
          tgt->add(flow);
          tr->add(new FlowEvent(src,flow,tgt));
        }
        else
        {
          flow = ((PoolNode*)tgt)->getCapacity();
          src->sub(flow);
          tgt->add(flow);
          tr->add(new FlowEvent(src,flow,tgt));
        }
      }
      else
      {
        flow = ((PoolNode*)src)->getResources();
        if(tgt->hasCapacity(flow))
        {
          src->sub(flow);
          tgt->add(flow);
          tr->add(new FlowEvent(src,flow,tgt));
        }
        else
        {
          flow = ((PoolNode*)tgt)->getCapacity();
          src->sub(flow);
          tgt->add(flow);
          tr->add(new FlowEvent(src,flow,tgt));
        }
      }
    }
  }
  
  return tr;
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

MM::Transition * MM::PoolNode::step()
{
  std::vector<Edge*> * work;
  if(this->getAct() == ACT_PULL)
  {
    work = this->getInput();
  }
  else if(this->getAct() == ACT_PUSH)
  {
    work = this->getOutput();
  }
  else
  {
    //error
  }
  
  if(this->getHow() == HOW_ALL)
  {
    return stepAll(work);
  }
  else
  {
    return stepAny(work);
  }
  
  //error
}


bool MM::PoolNode::hasCapacity()
{
  return (this->val_new < this->max);
}

bool MM::PoolNode::hasResources()
{
  return (this->val_old > 0);
}

bool MM::PoolNode::hasCapacity(MM::UINT32 amount)
{
  return (this->val_new + amount <= this->max);
}

bool MM::PoolNode::hasResources(MM::UINT32 amount)
{
  return (this->val_old >= amount);
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
  buf->append((MM::CHAR*)MM_POOL_NODE_POOL_STR, (MM::UINT32) MM_POOL_NODE_POOL_LEN);
  buf->space();
  buf->append(getName());
  buf->space();
  buf->append((MM::CHAR*)MM_POOL_NODE_AT_STR, (MM::UINT32) MM_POOL_NODE_AT_LEN);
  buf->space();
  buf->append(at);
  buf->space();
  buf->append((MM::CHAR*)MM_POOL_NODE_MAX_STR, (MM::UINT32) MM_POOL_NODE_MAX_LEN);
  buf->space();
  buf->append(max);
  buf->space();
  buf->append((MM::CHAR*)MM_POOL_NODE_ADD_STR, (MM::UINT32) MM_POOL_NODE_ADD_LEN);
  buf->space();
  //exp->toString(buf);
  buf->linebreak();
}
