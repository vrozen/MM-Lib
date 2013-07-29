//
//  Transition.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Transition__
#define __mm__Transition__

namespace MM
{
  class Transition
  {
  private:
    std::vector<Event*> * steps;
  public:
    Transition();
    ~Transition();
    MM::VOID add(Event * event);
    MM::VOID clear();
    MM::VOID step();
    MM::VOID back();
    MM::VOID toString(MM::String * str);
  };
}
#endif /* defined(__mm__Transition__) */
