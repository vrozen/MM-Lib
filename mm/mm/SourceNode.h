//
//  SourceNode.h
//  mm
//
//  Created by Riemer van Rozen on 7/11/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__SourceNode__
#define __mm__SourceNode__
namespace MM
{
  class SourceNode : public Node
  {
  public:
    SourceNode(MM::When when, MM::Act act, MM::How how, MM::String * name);
    ~SourceNode();
    MM::Transition * step();
    
    MM::BOOLEAN hasCapacity();
    MM::BOOLEAN hasResources();
    MM::BOOLEAN hasCapacity(MM::UINT32 amount);
    MM::BOOLEAN hasResources(MM::UINT32 amount);
    MM::VOID sub(MM::UINT32 amount);
    MM::VOID add(MM::UINT32 amount);
    MM::VOID toString(MM::String * buf);
  };
}
#endif /* defined(__mm__SourceNode__) */