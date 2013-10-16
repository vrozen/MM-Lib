//
//  Node.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Node__
#define __mm__Node__

namespace MM
{
  class Transition;
  
  class Node : public MM::Element
  {
  private:
    MM::Vector<MM::Edge *> * input;      //tgt = this node
    MM::Vector<MM::Edge *> * output;     //src = this node
    MM::Vector<MM::Edge *> * conditions; //tgt = this node
    MM::Vector<MM::Edge *> * triggers;   //src = this node
    MM::Vector<MM::Edge *> * aliases;    //tgt = this node
    
    MM::NodeBehavior * behavior;

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

    MM::NodeBehavior * getBehavior();
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
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}
#endif /* defined(__mm__Node__) */