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
    virtual MM::TID getTypeId();
    virtual MM::BOOLEAN instanceof(MM::TID tid);
    virtual MM::VOID update(MM::Observable * observable, //observable object
                            MM::VOID * aux,              //auxiliary context
                            MM::UINT32 message,          //message
                            MM::VOID * object) = 0;      //subject object
  };
}


#endif /* defined(__mm__Observer__) */
