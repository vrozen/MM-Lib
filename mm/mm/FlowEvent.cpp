//
//  FlowEvent.cpp
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

MM::FlowEvent::FlowEvent(MM::Node* src, MM::INT32 amount, MM::Node* tgt)
{
  this->src = src;
  this->amount = amount;
  this->tgt = tgt;
}

MM::FlowEvent::~FlowEvent()
{
}

MM::VOID MM::FlowEvent::step()
{
  src->sub(amount);
  tgt->add(amount);
}

MM::VOID MM::FlowEvent::back()
{
  src->sub(-amount);
  tgt->add(-amount);
}

MM::VOID MM::FlowEvent::toString(MM::String * buf)
{
  buf->append(src->getName());
  buf->space();
  //exp->toString(buf);
  buf->space();
  buf->append(tgt->getName());
  buf->linebreak();
}