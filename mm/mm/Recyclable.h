//
//  Recyclable.h
//  mm
//
//  Created by Riemer van Rozen on 8/1/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Recyclable__
#define __mm__Recyclable__

namespace MM
{
  class String;
  class Recycler;
  class Recyclable
  {
  private:
    //static const MM::Recycler * r;
  public:
    Recyclable();
    virtual ~Recyclable();
    //static const MM::VOID setRecycler(const MM::Recycler * r);
    virtual MM::TID getTypeId();
    virtual MM::BOOLEAN instanceof(MM::TID tid);
    virtual MM::VOID recycle(MM::Recycler * r);
    virtual MM::VOID toString(MM::String * buf) = 0;
  };
}

#endif /* defined(__mm__Recyclable__) */
