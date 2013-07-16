//
//  Event.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Event__
#define __mm__Event__

namespace MM
{
  class Event
  {
  public:
    Event();
    virtual ~Event();
  public:
    virtual MM::VOID toString(MM::String * buf) = 0;
    virtual MM::VOID step() = 0;
    virtual MM::VOID back() = 0;
  };
}
#endif /* defined(__mm__Event__) */
