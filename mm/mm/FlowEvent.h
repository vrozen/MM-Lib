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
 * \class     FlowEvent
 * \brief     The FlowEvent abstraction defines the amount of resources that
 *            flows between source and target node instances during a step.
 * \file      FlowEvent.h
 * \author    Riemer van Rozen
 * \date      January 30th 2014
 */
/******************************************************************************/

#ifndef __mm__FlowEvent__
#define __mm__FlowEvent__

namespace MM
{
  class Node;
  class Instance;
  class Edge;
  class FlowEvent : public MM::Element
  {
  private:
    //which node instance is responsible?
    MM::Node     * actNode;     /**> acting node */
    MM::Instance * actInstance; /**> instance in which the acting node lives */
    
    //on which edge did the node act?
    MM::Edge     * actEdge;     /**> edge the node instance acted on*/
    
    //resolved node instances
    MM::Node     * srcNode;     /**> source node */
    MM::Node     * tgtNode;     /**> target node */
    MM::Instance * srcInstance; /**> source instance */
    MM::Instance * tgtInstance; /**> target instance */

    MM::UINT32 amount;          /**> amount of resources that flowed from source to target */
  public:
    FlowEvent(MM::Instance * actInstance,
              MM::Node     * actNode,
              MM::Edge     * actEdge,
              MM::Instance * srcInstance,
              MM::Node     * srcNode,
              MM::UINT32     amount,
              MM::Instance * tgtInstance,
              MM::Node     * tgtNode);
    ~FlowEvent();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::Node * getSourceNode();
    MM::UINT32 getAmount();
    MM::Node * getTargetNode();
    
    MM::Instance * getActInstance();
    MM::Node * getActNode();
    MM::Edge * getActEdge();

    MM::Instance * getSourceInstance();
    MM::Instance * getTargetInstance();
    MM::VOID setSourceInstance(MM::Instance * instance);
    MM::VOID setTargetInstance(MM::Instance * instance);
    
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}
#endif /* defined(__mm__FlowEvent__) */
