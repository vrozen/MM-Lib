//
//  Observer.h
//  mm
//
//  Created by Riemer van Rozen on 9/26/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Observer__
#define __mm__Observer__

namespace MM
{
  class Observable;
  class Observer
  {
  public:
    Observer();
    ~Observer();
    //MM::VOID recylce(MM::Recycler * r);
    virtual MM::TID getTypeId();
    virtual MM::BOOLEAN instanceof(MM::TID tid);

    virtual MM::VOID update(MM::Observable * observable,
                            MM::VOID * aux,
                            MM::UINT32 message,
                            MM::VOID * object) = 0;
  };
}


#endif /* defined(__mm__Observer__) */
