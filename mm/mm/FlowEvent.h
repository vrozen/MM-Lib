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
  class FlowEvent : public MM::Event
  {
  private:
    MM::Node * src;
    MM::Node * tgt;
    MM::UINT32 amount;
  public:
    FlowEvent(MM::Node * src, MM::UINT32 amount, MM::Node * tgt);
    ~FlowEvent();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID toString(MM::String * buf);
    MM::Node * getSource();
    MM::UINT32 getAmount();
    MM::Node * getTarget();
    MM::VOID step();
    MM::VOID back();
  };
}
#endif /* defined(__mm__FlowEvent__) */
