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
 * \class     PoolNodeBehavior
 * \brief     The PoolNodeBehavior abstraction defines
 *            the behavior of pool nodes.
 * \note      Strategy
 * \file      PoolNodeBehavior.h
 * \author    Riemer van Rozen
 * \date      October 7th 2013
 */
/******************************************************************************/

#ifndef __mm__PoolNodeBehavior__
#define __mm__PoolNodeBehavior__

namespace MM
{
  class Definition;
  class PoolNodeBehavior : public MM::NodeBehavior, public MM::Observer
  {
  private:
    static const MM::CHAR * POOL_STR; /**> pool keyword */
    static const MM::CHAR * OF_STR;   /**> of keyword */
    static const MM::CHAR * AT_STR;   /**> at keyword */
    static const MM::CHAR * MAX_STR;  /**> max keyword */
    static const MM::CHAR * ADD_STR;  /**> add keyword */
    static const MM::CHAR * SELF_STR; /**> self keyword */

    static const MM::UINT32 POOL_LEN; /**> pool keyword length */
    static const MM::UINT32 OF_LEN;   /**> of keyword length */
    static const MM::UINT32 AT_LEN;   /**> at keyword length */
    static const MM::UINT32 MAX_LEN;  /**> max keyword length */
    static const MM::UINT32 ADD_LEN;  /**> add keyword length */
    static const MM::UINT32 SELF_LEN; /**> self keyword length */
    
    MM::Name * of;          /**> type name */
    MM::UINT32 at;          /**> start value */
    MM::UINT32 max;         /**> maximum value */
    MM::Exp * exp;          /**> expression added when queried */    
    MM::Definition * def;   /**> type definition (resolved) */
    
    //declarations observe definitions to spawn and delete interfaces
    //for observable nodes
    MM::Map<MM::Name *, //interface name
    MM::Node *, //interface node
    MM::Name::Compare> * interfaces; /**> interfaces resulting from definition */
    
  public:
    PoolNodeBehavior(MM::NodeBehavior::IO   io,
                     MM::NodeBehavior::When when,
                     MM::NodeBehavior::Act  act,
                     MM::NodeBehavior::How  how,
                     MM::Name             * of,
                     MM::UINT32             at,
                     MM::UINT32             max,
                     MM::Exp              * exp,
                     MM::Map<MM::Name *, Node *, MM::Name::Compare> * interfaces);
    ~PoolNodeBehavior();
    MM::VOID recycle(MM::Recycler *r);

    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::VOID update(MM::Observable * observable,
                    MM::VOID * aux,
                    MM::UINT32 message,
                    MM::VOID * object);
    
    MM::Name * getTypeName();
    
    MM::VOID setDefinition(MM::Definition * def);
    MM::Definition * getDefinition();
    
    MM::Node * getInterface(MM::Name * name);
    MM::VOID addInterface(MM::Machine * m, MM::Node * node);
    MM::VOID removeInterface(MM::Machine * m, MM::Node * node);
    
    MM::Name * getOf();
    MM::UINT32 getAt();
    MM::UINT32 getMax();
    MM::Exp * getAdd();
    
    MM::VOID setAt(MM::UINT32 at);
    MM::VOID setMax(MM::UINT32 max);
    MM::VOID setAdd(MM::Exp * exp);
    
    MM::UINT32 getCreateMessage();
    MM::UINT32 getUpdateMessage();
    MM::UINT32 getDeleteMessage();
    
    //any has inherited behavior
    
    MM::VOID stepPullAll(MM::Node * tgtNode,
                         MM::Instance * tgtInstance,
                         MM::Vector<MM::NodeWorkItem *> * work,
                         MM::Machine * m,
                         MM::Transition * tr);

    MM::VOID stepPushAll(MM::Node * srcNode,
                         MM::Instance * srcInstance,
                         MM::Vector<MM::NodeWorkItem *> * work,
                         MM::Machine * m,
                         MM::Transition * tr);

    //instance manipulation during modifications
    MM::VOID begin(MM::Instance * i,
                   MM::Machine  * m,
                   MM::Node     * n);
    MM::VOID end(MM::Instance * i,
                 MM::Machine  * m,
                 MM::Node     * n);
    MM::VOID change(MM::Instance * i,
                    MM::Machine  * m,
                    MM::Node     * n);

    //query values on a complete state between steps
    MM::INT32 getAmount(MM::Instance * i, MM::Machine * m, MM::Node * n);
    
    //instance manipulation during transitions
    MM::VOID add(MM::Instance * i,
                 MM::Machine  * m,
                 MM::Node     * n,
                 MM::UINT32     amount);
    MM::VOID sub(MM::Instance * i,
                 MM::Machine  * m,
                 MM::Node     * n,
                 MM::UINT32     amount);
    MM::INT32 getCapacity(MM::Instance * i, MM::Node * n, MM::Machine * m);
    MM::INT32 getResources(MM::Instance * i, MM::Node * n, MM::Machine * m);
    MM::BOOLEAN hasCapacity(MM::Instance * i, MM::Node * n, MM::UINT32 amount, MM::Machine * m);
    MM::BOOLEAN hasResources(MM::Instance * i, MM::Node * n, MM::UINT32 amount, MM::Machine * m);
    
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::Name * name);

  };
}
#endif /* defined(__mm__PoolNodeBehavior__) */
