//
//  FlowEvent.h
//  mm
//
//  Created by Riemer van Rozen on 1/30/14.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

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
    MM::Node     * actNode;
    MM::Instance * actInstance;
    
    //on which edge did the node act?
    MM::Edge     * actEdge;
    
    //resolved node instances
    MM::Node     * srcNode;
    MM::Node     * tgtNode;
    MM::Instance * srcInstance;
    MM::Instance * tgtInstance;
    
    //amount of resources that flowed from source to target
    MM::UINT32 amount;
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
