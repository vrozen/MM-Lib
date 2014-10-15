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
 * \class     Evaluator
 * \brief     The Evaluator evaluates program steps
 *            and the resulting changes to instances.
 * \note      Expressions are visited whereas nodes are interpreted.
 * \file      Evaluator.h
 * \author    Riemer van Rozen
 * \date      September 26th 2013
 */
/******************************************************************************/

#ifndef __mm__Evaluator__
#define __mm__Evaluator__

namespace MM
{
  class Evaluator : public Recyclable
  {
  private:
    MM::Machine * m;

    class Instance;
    class NodeInstance
    {
    private:
      MM::Instance * instance;
      MM::Node * node;
    public:
      NodeInstance(MM::Instance * instance, MM::Node * node);
      ~NodeInstance();
      MM::Instance * getInstance();
      MM::Node * getNode();
    };
    
  private:
    MM::Vector<MM::Evaluator::NodeInstance *> * pullAllWork; //pull all work set
    MM::Vector<MM::Evaluator::NodeInstance *> * pullAnyWork; //pull any work set
    MM::Vector<MM::Evaluator::NodeInstance *> * pushAllWork; //push all work set
    MM::Vector<MM::Evaluator::NodeInstance *> * pushAnyWork; //push any work set
    
  public:
    Evaluator(MM::Machine * m);
    
    ~Evaluator();
    
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);

    MM::VOID toString(MM::String * buf);
        
    //MM::Instance * getInitialState(MM::Definition * def);
    
    MM::VOID step (MM::Transition * tr);
    //MM::VOID step (MM::Instance * i, MM::Transition * tr);

  private:
    //phase 1: prepare
    MM::VOID prepareAll(MM::Instance * instance);
    
    MM::VOID prepare(MM::Instance * instance);

    //phase 2: step
    MM::VOID stepLevel(MM::Transition * transition,
                       MM::Vector<MM::Evaluator::NodeInstance *> * work);
    
    //phase 3: finalize
    MM::VOID finalize(MM::Instance * instance, MM::Transition * tr);
    
    MM::VOID finalizeAll(MM::Instance * instance, MM::Transition * tr);
    
  private:
    MM::VOID clearActiveNodes(MM::Instance * i);

	  MM::VOID setActiveNodes(MM::Instance * i,
		                        MM::Transition * tr);
    
    MM::VOID setEnabledNodes(MM::Instance * i,
                             MM::Transition * tr);
    
    MM::VOID notifyFlow(MM::Transition * tr);
    
    MM::VOID notifyValues(MM::Instance * instance);
        
    //------------------------------------------------------------
    //Visitor
    //------------------------------------------------------------
  public:
    //FIXME: source node and target node instead of Edge -->
    //       edge is currently not used and we need it for implicit args
    //       and we can only do it if all other evals are private
    MM::ValExp * eval(MM::Instance * i,
                      MM::Edge * e);
    
    //FIXME: private -->
    
    MM::ValExp * eval(MM::Exp * exp,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::OneExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::ActiveExp * exp,
                      MM::Instance *i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::DieExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::OverrideExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::VarExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::AllExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::BinExp * exp,
                      MM::Instance *i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::UnExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::BooleanValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::NumberValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::RangeValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    //------------------------------------------------------------
    //BinExp Visitor
    //------------------------------------------------------------    
    MM::ValExp * eval(MM::ValExp * e1,
                      MM::Operator::OP op,
                      MM::ValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::BooleanValExp * e1,
                      MM::Operator::OP op,
                      MM::BooleanValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::BooleanValExp * e1,
                      MM::Operator::OP op,
                      MM::NumberValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::BooleanValExp * e1,
                      MM::Operator::OP op,
                      MM::RangeValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::NumberValExp * e1,
                      MM::Operator::OP op,
                      MM::BooleanValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::NumberValExp * e1,
                      MM::Operator::OP op,
                      MM::NumberValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::NumberValExp * e1,
                      MM::Operator::OP op,
                      MM::RangeValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::RangeValExp * e1,
                      MM::Operator::OP op,
                      MM::BooleanValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::RangeValExp * e1,
                      MM::Operator::OP op,
                      MM::NumberValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e); 

    MM::ValExp * eval(MM::RangeValExp * e1,
                      MM::Operator::OP op,
                      MM::RangeValExp * e2,
                      MM::Instance * i,
                      MM::Edge * e);
    
    //------------------------------------------------------------
    //UnExp Visitor
    //------------------------------------------------------------
    MM::ValExp * eval(MM::Operator::OP op,
                      MM::ValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
    
    MM::ValExp * eval(MM::Operator::OP op,
                      MM::BooleanValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::Operator::OP op,
                      MM::NumberValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);

    MM::ValExp * eval(MM::Operator::OP op,
                      MM::RangeValExp * exp,
                      MM::Instance * i,
                      MM::Edge * e);
  };
}
#endif /* defined(__mm__Evaluator__) */
