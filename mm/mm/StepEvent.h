//
//  StepEvent.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__StepEvent__
#define __mm__StepEvent__
namespace MM
{
  class StepEvent : public MM::Event
  {
  private:
  public:
    StepEvent();
    ~StepEvent();
    MM::VOID toString(MM::String * buf);
    MM::VOID step();
    MM::VOID back();
  };
}
#endif /* defined(__mm__StepEvent__) */
