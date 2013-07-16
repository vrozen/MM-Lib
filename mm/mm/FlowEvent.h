//
//  FlowEvent.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__FlowEvent__
#define __mm__FlowEvent__

namespace MM
{
  class FlowEvent : public Event
  {
  private:
    MM::Node * src;
    MM::Node * tgt;
    MM::INT32 amount;
  public:
    FlowEvent(MM::Node * src, MM::INT32 amount, MM::Node * tgt);
    ~FlowEvent();
    MM::VOID toString(MM::String * buf);
    MM::VOID step();
    MM::VOID back();
  };
}
#endif /* defined(__mm__FlowEvent__) */
