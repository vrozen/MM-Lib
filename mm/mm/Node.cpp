//
//  Node.cpp
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
#include "Event.h"
#include "FlowEvent.h"
#include "Transition.h"
#include "PoolNode.h"

const MM::CHAR * MM::Node::IO_STR[] =
{
  "error",
  "", //epsilon = private
  "in",
  "out",
  "inout"
};

const MM::CHAR * MM::Node::WHEN_STR[] =
{
  "error",
  "", //epsilon = passive
  "auto",
  "user",
  "start"
};

const MM::CHAR * MM::Node::ACT_STR[] =
{
  "error",
  "", //epsilon = pull
  "push"
};

const MM::CHAR * MM::Node::HOW_STR[] =
{
  "error",
  "", //epsilon = any
  "all"
};

const MM::UINT32 MM::Node::IO_LEN[] =
{
  5, //error
  0, //epsilon (private)
  2, //in
  3, //out
  5  //inout
};

const MM::UINT32 MM::Node::WHEN_LEN[] =
{
  5, //error
  0, //epsilon (passive)
  4, //auto
  4, //user
  5  //start
};

const MM::UINT32 MM::Node::ACT_LEN[] =
{
  5, //error
  0, //epsilon (pull)
  4  //push
};

const MM::UINT32 MM::Node::HOW_LEN[] =
{
  5, //error
  0, //any
  3  //all
};

MM::Node::Node(MM::Node::IO io,
               MM::Node::When when,
               MM::Node::Act act,
               MM::Node::How how,
               MM::Name * name): MM::Element()
{
  this->io = io;
  this->when = when;
  this->act = act;
  this->how = how;
  this->name = name;
  this->input = new std::vector<Edge*>();
  this->output = new std::vector<Edge*>();
  this->cond = new std::vector<Edge*>();
}

MM::Node::~Node()
{
  delete name;
  delete input;
  delete output;
  delete cond;
}

MM::Name * MM::Node::getName()
{
  return name;
}

MM::VOID MM::Node::addInput(MM::Edge * edge)
{
  this->input->push_back(edge);
}

MM::VOID MM::Node::addOutput(MM::Edge * edge)
{
  this->output->push_back(edge);
}

MM::VOID MM::Node::addCondition(MM::Edge * edge)
{
  this->cond->push_back(edge);
}

MM::VOID MM::Node::removeInput(MM::Edge * edge)
{
  //todo
}

MM::VOID MM::Node::removeOutput(MM::Edge * edge)
{
  //todo
}


MM::VOID MM::Node::removeCondition(MM::Edge * edge)
{
  //todo
}

MM::Node::When MM::Node::getWhen()
{
  return when;
}

MM::Node::Act MM::Node::getAct()
{
  return act;
}

MM::Node::How MM::Node::getHow()
{
  return how;
}

std::vector<MM::Edge*> * MM::Node::getInput()
{
  return input;
}

std::vector<MM::Edge*> * MM::Node::getOutput()
{
  return output;
}

std::vector<MM::Edge*> * MM::Node::getCond()
{
  return cond;
}

MM::VOID MM::Node::setWhen(MM::Node::When when)
{
  this->when = when;
}

MM::VOID MM::Node::setAct(MM::Node::Act act)
{
  this->act = act;
}

MM::VOID MM::Node::setHow(MM::Node::How how)
{
  this->how = how;
}

MM::BOOLEAN MM::Node::isActive()
{
  //return active;
  //note this should be calculated based on instantiations,
  //not on the static types
  return MM_TRUE;
}

MM::Transition * MM::Node::step()
{
  MM::Transition * tr = NULL;
  std::vector<Edge*> * work = NULL;
  
  if(this->getAct() == ACT_PULL)
  {
    work = this->getInput();
  }
  else //act must must be push
  {
    work = this->getOutput();
  }
  
  if(this->getHow() == HOW_ANY)
  {
    tr = stepAny(work);
  }
  else //how must be all
  {
    tr = stepAll(work);
  }
  
  return tr;
}

MM::Transition * MM::Node::stepAll(std::vector<Edge*> * work)
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
    
    //TODO: evaluate flow amount
    
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

MM::Transition * MM::Node::stepAny(std::vector<Edge*> * work)
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
    
    //TODO: evaluate flow amount
    
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

MM::VOID MM::Node::toString(MM::String * buf)
{
  if(io != MM::Node::IO_PRIVATE)
  {
    buf->append((MM::CHAR*)MM::Node::IO_STR[io], MM::Node::IO_LEN[io]);
    buf->space();
  }
  if(when != MM::Node::WHEN_PASSIVE)
  {
    buf->append((MM::CHAR*)MM::Node::WHEN_STR[when], MM::Node::WHEN_LEN[when]);
    buf->space();
  }
  if(act != MM::Node::ACT_PULL)
  {
    buf->append((MM::CHAR*)MM::Node::ACT_STR[act], MM::Node::ACT_LEN[act]);
    buf->space();
  }
  if(how != MM::Node::HOW_ANY)
  {
    buf->append((MM::CHAR*)MM::Node::HOW_STR[how], MM::Node::HOW_LEN[how]);
    buf->space();
  }
}
