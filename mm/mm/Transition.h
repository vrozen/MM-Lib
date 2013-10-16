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
  class Transition : public MM::Transformation
  {
  public:
    const static MM::CHAR * STEP_STR;
    const static MM::UINT32 STEP_LEN;
  private:
    MM::Location * loc; /**> step source location*/
  public:
    Transition(MM::Vector<MM::Element *> * elements);
    Transition(MM::Vector<MM::Element *> * elements, MM::Location * loc);
    ~Transition();
    MM::VOID recycle(MM::Recycler *r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    //MM::VOID step();
    //MM::VOID back();     
    MM::VOID toString(MM::String * str);
  };
}
#endif /* defined(__mm__Transition__) */
