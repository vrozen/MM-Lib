//
//  Signal.h
//  mm
//
//  Created by Riemer van Rozen on 10/16/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Signal__
#define __mm__Signal__

namespace MM
{
  class Signal : public MM::Element
  {
  public:
    static const MM::CHAR * SIGNAL_STR;
    static const MM::UINT32 SIGNAL_LEN;
  private:
    MM::Location * loc;
  public:
    Signal(MM::Location * loc,
           MM::Name * name);
    Signal(MM::Name * name);
    ~Signal();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::Location * getLocation();
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}

#endif /* defined(__mm__Signal__) */
