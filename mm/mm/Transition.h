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
  class Transition : public MM::Recyclable
  {
  private:
    std::vector<Event*> * steps;
  public:
    Transition();
    ~Transition();
    MM::VOID recycle(MM::Recycler *r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::VOID add(Event * event);
    MM::VOID clear(MM::Recycler * r);
    MM::VOID step();
    MM::VOID back();
 
    //MM::FlowEvent * getFlow(MM::Instance * i, MM::Node * src, MM::Node * tgt);
    
    MM::VOID toString(MM::String * str);
  };
}
#endif /* defined(__mm__Transition__) */
