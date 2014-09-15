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
/*!
 * \namespace MM
 * \class     PoolNodeInstance
 * \brief     The PoolNodeInstance abstraction encapsulates the value
 *            of instantiated Nodes with PoolNodeBehaviors.
 *
 * \file      PoolNodeInstance.h
 * \author    Riemer van Rozen
 * \date      September 14th 2014
 */
/******************************************************************************/
#ifndef __mm__PoolNodeInstance__
#define __mm__PoolNodeInstance__

namespace MM
{
  class PoolNodeInstance : /*public Recyclable,*/
                           public Observable,
                           public Observer
  {
  private:
    MM::Node     * poolNode; //pool node definition this is an instance of
    MM::Instance * instance; //instance this poolNodeInstance is part of
    MM::INT32 val;            //current value of this poolNodeInstance (after a step)
    MM::INT32 oldVal;         //old value of this poolNodeInstance (during a step)
    MM::INT32 newVal;         //new value of this poolNodeInstance (during a step)
    MM::BOOLEAN dirty;        //if during a step change to actual or observable occurred
                             //this flag is set to true. based on this at the
                             //end of the step MSG_HAS_VAL messages are sent
                             //by the parent instance, and the flag is cleared to false.
    MM::Vector<MM::PoolNodeInstance *> * observing;

  public:
    PoolNodeInstance(MM::Node * poolNode,
                     MM::Instance * instance,
                     MM::INT32 initVal);
    ~PoolNodeInstance();
    //MM::VOID recycle(MM::Recycler * r);    
    //MM::TID getTypeId();
    //MM::BOOLEAN instanceof(MM::TID tid);

    MM::Node * getNode();
    MM::Instance * getInstance();

    MM::VOID setValue(MM::INT32 val);
    MM::VOID setOldValue(MM::INT32 val);
    MM::VOID setNewValue(MM::INT32 val);
    
    MM::INT32 getValue();
    MM::INT32 getOldValue();
    MM::INT32 getNewValue();

    MM::VOID setDirty(MM::BOOLEAN dirty);
    MM::BOOLEAN isDirty();

    MM::VOID begin();    //begin step
    MM::VOID finalize(); //finalize step
    
    MM::VOID update(MM::Observable * observable,
                    MM::VOID * aux,
                    MM::UINT32 message,
                    MM::VOID * object);

    MM::VOID initExp(MM::Exp * exp);
    MM::VOID deinitExp();
  };

}

#endif /* defined(__mm__PoolNodeInstance__) */
