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
 * \class     Node
 * \brief     The Node abstraction defines program nodes
 *            that are connected by edges,
 *            and its behavior can be modified by changing its node behavior.
 * \file      Node.h
 * \author    Riemer van Rozen
 * \date      July 10th 2013
 */
/******************************************************************************/

#ifndef __mm__Node__
#define __mm__Node__

namespace MM
{
  class Transition;
  
  class NodeBehavior;
  class Instance;
  class Evaluator;
  class Node : public MM::Element
  {
  private:
    MM::Vector<MM::Edge *> * input;      /**> resource connections (tgt = this node) */
    MM::Vector<MM::Edge *> * output;     /**> resource connections (src = this node) */
    MM::Vector<MM::Edge *> * conditions; /**> conditions for this node to act (tgt = this node) */
    MM::Vector<MM::Edge *> * triggers;   /**> triggers this node activates in the next state when it is active (src = this node) */
    MM::Vector<MM::Edge *> * aliases;    /**> other nodes that are defined by this node (tgt = this node) */
    MM::BOOLEAN isOwner;                 /**> node owns its edges or not */    
    MM::NodeBehavior * behavior;         /**> node behavior (strategy) */

  public:
    Node(MM::Name * name,
         MM::NodeBehavior * behavior);
    ~Node();
    MM::VOID recycle(MM::Recycler * r);
    
    virtual MM::TID getTypeId();
    virtual MM::BOOLEAN instanceof(MM::TID tid);
    
    class Compare
    {
    public:
      bool operator()(Node const * n1, Node const * n2) const
      {
        MM::BOOLEAN lt = (n1 < n2);
        return lt;
      }
    };

    MM::VOID setEdgeOwnership(MM::BOOLEAN isOwner);
    MM::BOOLEAN hasEdgeOwnership();
    
    virtual MM::NodeBehavior * getBehavior();
    MM::VOID setBehavior(MM::NodeBehavior * behavior);
    
    MM::VOID addInput(MM::Edge * edge);
    MM::VOID addOutput(MM::Edge * edge);
    MM::VOID addCondition(MM::Edge * edge);
    MM::VOID addTrigger(MM::Edge * edge);
    MM::VOID addAlias(MM::Edge * edge);
    
    MM::VOID removeInput(MM::Edge * edge);
    MM::VOID removeOutput(MM::Edge * edge);
    MM::VOID removeCondition(MM::Edge * edge);
    MM::VOID removeTrigger(MM::Edge * edge);
    MM::VOID removeAlias(MM::Edge * alias);
    
    MM::Vector<Edge *> * getInput();
    MM::Vector<Edge *> * getOutput();
    MM::Vector<Edge *> * getConditions();
    MM::Vector<Edge *> * getTriggers();
    MM::Vector<Edge *> * getAliases();
    
    MM::VOID setInput(MM::Vector<MM::Edge *> * input);
    MM::VOID setOutput(MM::Vector<MM::Edge *> * output);
    MM::VOID setConditions(MM::Vector<MM::Edge *> * conditions);
    MM::VOID setTriggers(MM::Vector<MM::Edge *> * triggers);
    MM::VOID setAliases(MM::Vector<MM::Edge *> * aliases);

    //query values on a state
    virtual MM::INT32 getAmount(MM::Instance * i,
                                MM::Machine * m);

    //set values in a state
    virtual MM::VOID setAmount(MM::Instance * i,
                               MM::Machine * m,
                               MM::INT32 val);
    
    //instance manipulation
    virtual MM::VOID begin(MM::Instance * i, MM::Machine * m);
    virtual MM::VOID end(MM::Instance * i, MM::Machine * m);
    virtual MM::VOID change(MM::Instance * i, MM::Machine * m);
    virtual MM::VOID add(MM::Instance * i, MM::Machine * m, MM::UINT32 amount);
    virtual MM::VOID sub(MM::Instance * i, MM::Machine * m, MM::UINT32 amount);
    virtual MM::INT32 getCapacity(MM::Instance * i, MM::Machine * m);
    virtual MM::INT32 getResources(MM::Instance * i, MM::Machine * m);
    virtual MM::BOOLEAN hasCapacity(MM::Instance * i, MM::UINT32 amount, MM::Machine * m);
    virtual MM::BOOLEAN hasResources(MM::Instance * i, MM::UINT32 amount, MM::Machine * m);
    
    MM::VOID step(MM::Instance * i,
                  MM::Machine * m,
                  MM::Transition * tr);
    
    MM::BOOLEAN isDisabled(MM::Instance * i,
                           MM::Evaluator * e,
                           MM::Recycler * r);
    
    MM::BOOLEAN isSatisfied(MM::Instance * i,
                            MM::Transition * tr);

    virtual MM::VOID activateTriggerTargets(MM::Instance * i,
                                            MM::Machine * m);
    
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}
#endif /* defined(__mm__Node__) */