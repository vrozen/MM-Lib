//
//  ConverterNodeBehavior.h
//  mm
//
//  Created by Riemer van Rozen on 11/21/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__ConverterNodeBehavior__
#define __mm__ConverterNodeBehavior__

namespace MM
{
  class ConverterNodeBehavior : public MM::NodeBehavior
  {
  private:
    static const MM::CHAR * CONVERTER_STR;
    static const MM::CHAR * FROM_STR;
    static const MM::CHAR * TO_STR;

    static const MM::UINT32 CONVERTER_LEN;
    static const MM::UINT32 FROM_LEN;
    static const MM::UINT32 TO_LEN;
    
    MM::Name * from;
    MM::Name * to;
    
    MM::Node * sourceNode;
    MM::Node * drainNode;
    MM::Edge * triggerEdge;
    
  public:
    ConverterNodeBehavior(MM::NodeBehavior::IO   io,
                          MM::NodeBehavior::When when,
                          MM::Name * from,
                          MM::Name * to,
                          MM::Node * sourceNode,
                          MM::Node * drainNode,
                          MM::Edge * triggerEdge);
    
    ~ConverterNodeBehavior();
    MM::VOID recycle(MM::Recycler *r);
    
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::Name * getFrom();
    MM::Name * getTo();

    MM::Edge * getTriggerEdge();
    MM::Node * getSourceNode();
    MM::Node * getDrainNode();
    
    MM::VOID setFrom(MM::Name * from);
    MM::VOID setTo(MM::Name * to);
    
    MM::UINT32 getCreateMessage();
    MM::UINT32 getUpdateMessage();
    MM::UINT32 getDeleteMessage();
    
    
    MM::VOID step(MM::Node * n,
                  MM::Instance * i,
                  MM::Machine * m,
                  MM::Transition * t);
    
    //instance manipulation during transitions
    MM::VOID add(MM::Instance * i, MM::Node * n, MM::UINT32 amount);
    MM::VOID sub(MM::Instance * i, MM::Node * n, MM::UINT32 amount);
    MM::UINT32 getCapacity(MM::Instance * i, MM::Node * n);
    MM::UINT32 getResources(MM::Instance * i, MM::Node * n);
    MM::BOOLEAN hasCapacity(MM::Instance * i, MM::Node * n, MM::UINT32 amount);
    MM::BOOLEAN hasResources(MM::Instance * i, MM::Node * n, MM::UINT32 amount);
    
    MM::VOID activateTriggerTargets(MM::Node * node,
                                    MM::Instance * i,
                                    MM::Machine * m);
    
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::Name * name);
    
  };
}

#endif /* defined(__mm__ConverterNodeBehavior__) */
