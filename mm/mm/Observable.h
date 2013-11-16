//
//  Observable.h
//  mm
//
//  Created by Riemer van Rozen on 9/26/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Observable__
#define __mm__Observable__

namespace MM
{
  class Observable
  {
  private:
    MM::Vector<Observer *> * observers;
  public:
    Observable();
    ~Observable();
    MM::VOID recylce(MM::Recycler * r);
    virtual MM::TID getTypeId();
    virtual MM::BOOLEAN instanceof(MM::TID tid);

    MM::VOID addObserver(MM::Observer * observer);
    MM::VOID removeObserver(MM::Observer * observer);
    MM::VOID notifyObservers(MM::Observable * observable, //observable object
                             MM::VOID * aux,              //auxiliary context
                             MM::UINT32 message,          //message
                             MM::VOID * object);          //subject object
  };
}

#endif /* defined(__mm__Observable__) */
