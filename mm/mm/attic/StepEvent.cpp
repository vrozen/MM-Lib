//
//  StepEvent.cpp
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
#include "StepEvent.h"

#define MM_FLOW_EVENT_STEP_STR "step"

MM::StepEvent::StepEvent() : MM::Event()
{
}

MM::StepEvent::~StepEvent()
{
}

MM::VOID MM::StepEvent::recycle(MM::Recycler *r)
{
  this->MM::Event::recycle(r);
}

MM::TID MM::StepEvent::getTypeId()
{
  return MM::T_StepEvent;
}

MM::BOOLEAN MM::StepEvent::instanceof(MM::TID tid)
{
  if(tid == MM::T_StepEvent)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Event::instanceof(tid);
  }
}

MM::VOID MM::StepEvent::step()
{
}

MM::VOID MM::StepEvent::back()
{
}

MM::VOID MM::StepEvent::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM_FLOW_EVENT_STEP_STR, sizeof(MM_FLOW_EVENT_STEP_STR));
  buf->linebreak();
}