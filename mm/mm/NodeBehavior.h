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
 * \class     NodeBehavior
 * \brief     The NodeBehavior abstraction is the abstract super class of
 *            all node behaviors and makes node behavior a modifiable strategy.
 * \file      NodeBehavior.h
 * \author    Riemer van Rozen
 * \date      October 9th 2013
 */
/******************************************************************************/

#ifndef __mm__NodeBehavior__
#define __mm__NodeBehavior__

namespace MM
{
  class Transition;
  class Instance;
  class NodeBehavior : public Recyclable
  {
  public:
    typedef enum __IO
    {
      IO_ERROR,
      IO_PRIVATE,
      IO_IN,
      IO_OUT,
      IO_INOUT
    } IO;
    
    typedef enum __When
    {
      WHEN_ERROR,
      WHEN_PASSIVE,
      WHEN_AUTO,
      WHEN_USER,
      WHEN_START
    } When;
    
    typedef enum __Act
    {
      ACT_ERROR,
      ACT_PULL,
      ACT_PUSH
    } Act;
    
    typedef enum __How
    {
      HOW_ERROR,
      HOW_ANY,
      HOW_ALL
    } How;
    
    static const MM::CHAR * IO_STR[];
    static const MM::CHAR * WHEN_STR[];
    static const MM::CHAR * ACT_STR[];
    static const MM::CHAR * HOW_STR[];
    
    static const MM::UINT32 IO_LEN[];
    static const MM::UINT32 WHEN_LEN[];
    static const MM::UINT32 ACT_LEN[];
    static const MM::UINT32 HOW_LEN[];
    
  private:
    MM::NodeBehavior::IO io;     /**> the visibility modifier determines interfaces of declarations and instance pools*/
    MM::NodeBehavior::When when; /**> the when modifier determines when a node acts*/
    MM::NodeBehavior::Act act;   /**> the act modifier determines what a node does when it acts*/
    MM::NodeBehavior::How how;   /**> the how modifier determines how a node performs its act*/
  protected:
    NodeBehavior(MM::NodeBehavior::IO io,
                 MM::NodeBehavior::When when,
                 MM::NodeBehavior::Act act,
                 MM::NodeBehavior::How how);
  public:
    virtual ~NodeBehavior();
    MM::VOID recycle(MM::Recycler * r);
    
    virtual MM::TID getTypeId();
    virtual MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::NodeBehavior::IO getIO();
    MM::NodeBehavior::When getWhen();
    MM::NodeBehavior::Act getAct();
    MM::NodeBehavior::How getHow();
    
    virtual MM::UINT32 getCreateMessage() = 0;
    virtual MM::UINT32 getUpdateMessage() = 0;
    virtual MM::UINT32 getDeleteMessage() = 0;
    
    MM::VOID setIO(MM::NodeBehavior::IO io);
    MM::VOID setWhen(MM::NodeBehavior::When when);
    MM::VOID setAct(MM::NodeBehavior::Act act);
    MM::VOID setHow(MM::NodeBehavior::How how);
    
    MM::BOOLEAN conformsTo(MM::NodeBehavior::IO direction);
    
    //default node behavior is overridable
    MM::VOID getWork(MM::Node * node,
                     MM::Instance * intance,
                     MM::Edge * edge,
                     MM::Vector<MM::NodeWorkItem *> * work);
    
    MM::INT32 evaluateExpression(MM::Instance * instance,
                                 MM::Exp * exp,
                                 MM::Edge * edge,
                                 MM::Machine *);

    virtual MM::VOID step(MM::Node * n,
                          MM::Instance * i,
                          MM::Machine * m,
                          MM::Transition * t);
    
    virtual MM::VOID stepPullAny(MM::Node * node,
                                 MM::Instance * i,
                                 MM::Vector<MM::NodeWorkItem *> * work,
                                 MM::Machine * m,
                                 MM::Transition * tr);
    
    virtual MM::VOID stepPushAny(MM::Node * node,
                                 MM::Instance * i,
                                 MM::Vector<MM::NodeWorkItem *> * work,
                                 MM::Machine * m,
                                 MM::Transition * tr);
    
    
    virtual MM::VOID stepPullAll(MM::Node * node,
                                 MM::Instance * i,
                                 MM::Vector<MM::NodeWorkItem *> * work,
                                 MM::Machine * m,
                                 MM::Transition * tr) = 0;

    virtual MM::VOID stepPushAll(MM::Node * node,
                                 MM::Instance * i,
                                 MM::Vector<MM::NodeWorkItem *> * work,
                                 MM::Machine * m,
                                 MM::Transition * tr) = 0;
   
  private:
    MM::VOID stepAny(MM::NodeBehavior::Act act,
                     MM::Node * node,
                     MM::Instance * i,
                     MM::Vector<MM::NodeWorkItem *> * work,
                     MM::Machine * m,
                     MM::Transition * tr);
    
  public:    
    //instance manipulation during modifications
    virtual MM::VOID begin(MM::Instance * i,
                           MM::Machine  * m,
                           MM::Node     * n) = 0;
    virtual MM::VOID end(MM::Instance * i,
                         MM::Machine  * m,
                         MM::Node     * n) = 0;
    virtual MM::VOID change(MM::Instance * i,
                            MM::Machine  * m,
                            MM::Node     * n) = 0;

    //query values on a state
    virtual MM::INT32 getAmount(MM::Instance * i,
                                MM::Machine * m,
                                MM::Node * n);
    
    //instance manipulation during transitions/steps
    virtual MM::VOID add(MM::Instance * i,
                         MM::Machine * m,
                         MM::Node * n,
                         MM::UINT32 amount) = 0;
    virtual MM::VOID sub(MM::Instance * i,
                         MM::Machine * m,
                         MM::Node * n,
                         MM::UINT32 amount) = 0;
    virtual MM::INT32 getCapacity(MM::Instance * i,
                                  MM::Node * n,
                                  MM::Machine * m) = 0;
    virtual MM::INT32 getResources(MM::Instance * i,
                                   MM::Node * n,
                                   MM::Machine * m) = 0;
    virtual MM::BOOLEAN hasCapacity(MM::Instance * i,
                                    MM::Node * n,
                                    MM::UINT32 amount,
                                    MM::Machine * m) = 0;
    virtual MM::BOOLEAN hasResources(MM::Instance * i,
                                     MM::Node * n,
                                     MM::UINT32 amount,
                                     MM::Machine * m) = 0;
    
    virtual MM::VOID activateTriggerTargets(MM::Node *,
                                            MM::Instance * i,
                                            MM::Machine * m);
    
    
  public:
    virtual MM::VOID toString(MM::String * buf, MM::Name * name);
  };
}

#endif /* defined(__mm__NodeBehavior__) */
