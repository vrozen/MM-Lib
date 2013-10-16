//
//  FlowEvent.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "Edge.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "Event.h"
#include "FlowEvent.h"

MM::FlowEvent::FlowEvent(MM::Node* src,
                         MM::UINT32 amount,
                         MM::Node* tgt) : MM::Event()
{
  this->src = src;
  this->amount = amount;
  this->tgt = tgt;
}

MM::FlowEvent::~FlowEvent()
{
  src = MM_NULL;
  tgt = MM_NULL;
  amount = 0;
}

MM::VOID MM::FlowEvent::recycle(MM::Recycler *r)
{
  this->MM::Event::recycle(r);
}

MM::TID MM::FlowEvent::getTypeId()
{
  return MM::T_FlowEvent;
}

MM::BOOLEAN MM::FlowEvent::instanceof(MM::TID tid)
{
  if(tid == MM::T_FlowEvent)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Event::instanceof(tid);
  }
}

MM::Node * MM::FlowEvent::getSource()
{
  return src;
}

MM::UINT32 MM::FlowEvent::getAmount()
{
  return amount;
}

MM::Node * MM::FlowEvent::getTarget()
{
  return tgt;
}

//This should be with respect to a Machine and an Instance
MM::VOID MM::FlowEvent::step()
{
  //src->sub(amount);
  //tgt->add(amount);
}

MM::VOID MM::FlowEvent::back()
{
  //src->sub(-amount);
  //tgt->add(-amount);
}

MM::VOID MM::FlowEvent::toString(MM::String * buf)
{
  src->getName()->toString(buf);
  buf->space();
  buf->appendInt(amount);
  buf->space();
  tgt->getName()->toString(buf);
  buf->linebreak();
}