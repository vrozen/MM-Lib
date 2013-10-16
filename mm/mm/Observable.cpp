//
//  Observable.cpp
//  mm
//
//  Created by Riemer van Rozen on 9/26/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "Vector.h"
#include "Recyclable.h"
#include "Recycler.h"
#include "Observer.h"
#include "Observable.h"

MM::Observable::Observable() //: MM::Recyclable()
{
  //FIXME: let the Machine create vectors
  this->observers =  new MM::Vector<Observer *>();
}

MM::Observable::~Observable()
{
  //FIXME: let Machine create vectors
  delete this->observers;
}

MM::VOID MM::Observable::recylce(MM::Recycler * r)
{
  //FIXME: let recycle clean up vectors
}

MM::TID MM::Observable::getTypeId()
{
  return MM::T_Observable;
}

MM::BOOLEAN MM::Observable::instanceof(MM::TID tid)
{
  if(tid == MM::T_Observable)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::VOID MM::Observable::notifyObservers(MM::Observable * observable,
                                         MM::VOID * aux,
                                         MM::UINT32 message,
                                         MM::VOID * object)
{
  MM::Vector<Observer *>::Iterator iter = observers->getIterator();
  
  while(iter.hasNext())
  {
    MM::Observer * observer = iter.getNext();
    observer->update(observable, aux, message, object);
  }
}
