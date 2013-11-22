//
//  Activation.h
//  mm
//
//  Created by Riemer van Rozen on 11/22/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Activation__
#define __mm__Activation__

namespace MM
{
  class Activation : public MM::Element
  {
  public:
    static const MM::CHAR * ACTIVATE_STR;
    static const MM::UINT32 ACTIVATE_LEN;
  private:
    MM::Location * loc; /**> activation source location*/
  public:
    Activation(MM::Name * name);
    Activation(MM::Location * loc, MM::Name * name);
    ~Activation();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::Location * getLocation();
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}

#endif /* defined(__mm__Activation__) */


