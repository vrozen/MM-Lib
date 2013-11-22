//
//  Evaluator.h
//  mm
//
//  Created by Riemer van Rozen on 9/26/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

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
    
    
    MM::Instance * getInitialState(MM::Definition * def);
    
    MM::VOID step(MM::Transition * buf);
    
    
    MM::VOID initStartState(MM::Instance * i);

  private:
    //phase 1
    MM::VOID prepare(MM::Instance * instance);

    
    
    //phase 2: step
    MM::VOID stepLevel(MM::Transition * transition,
                       MM::Vector<MM::Evaluator::NodeInstance *> * work);
    
    //MM::VOID stepNode(MM::Transition * transition,
    //                 MM::Instance * instance,
    //                  MM::Node * node);
    
    //MM::VOID stepNodeAll(MM::Transition * transition,
    //                     MM::Instance * instance,
    //                     MM::Node * node,
    //                     MM::Vector<Edge *> * work);

    //MM::VOID stepNodeAny(MM::Transition * transition,
    //                     MM::Instance * instance,
    //                     MM::Node * node,
    //                     MM::Vector<Edge *> * work);
    
    //phase 3
    MM::VOID finalize(MM::Instance * instance, MM::Transition * tr);
    
  public:
    MM::FlowEdge * synthesizeFlowEdge(MM::Instance * i,
                                      MM::Node * src,
                                      MM::UINT32 flow,
                                      MM::Node * tgt);
  private:
    MM::VOID clearActiveNodes(MM::Instance * i);
    
    MM::VOID setActiveNodes(MM::Instance * i,
                            MM::Transition * tr);
    
    //MM::VOID activateTriggerTargets(MM::Instance * i,
    //                        MM::Node * n);

    //MM::BOOLEAN isDisabled(MM::Node * node,
    //                       MM::Instance * i);

    //MM::BOOLEAN isSatisfied(MM::Instance * i,
    //                        MM::Node *,
    //                        MM::Transition * tr);
    
    //MM::VOID propagateGates(MM::Instance * i,
    //                        MM::Transition * tr);
    
    //------------------------------------------------------------
    //Visitor
    //------------------------------------------------------------
  public:
    MM::ValExp * eval(MM::Instance * i, MM::Edge * e);
    
 
  private:
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
    
    MM::ValExp * eval(MM::AllExp exp,
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
