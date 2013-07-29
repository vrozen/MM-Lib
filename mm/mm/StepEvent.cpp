//
//  StepEvent.cpp
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
#include "StepEvent.h"

#define MM_FLOW_EVENT_STEP_STR "step"

MM::StepEvent::StepEvent()
{
}

MM::StepEvent::~StepEvent()
{
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