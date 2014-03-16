/******************************************************************************
 * Copyright (c) 2013-2014, Amsterdam University of Applied Sciences (HvA) and
 *                          Centrum Wiskunde & Informatica (CWI)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contributors:
 *   * Riemer van Rozen - rozen@cwi.nl - HvA / CWI
 ******************************************************************************/
//
//  Observable.cpp
//  mm
//
//  Created by Riemer van Rozen on 9/26/13.
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

MM::VOID MM::Observable::addObserver(MM::Observer * observer)
{
  observers->add(observer);
}

MM::VOID MM::Observable::removeObserver(MM::Observer * observer)
{
  observers->remove(observer);
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
