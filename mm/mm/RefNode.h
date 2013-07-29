//
//  RefNode.h
//  mm
//
//  Created by Riemer van Rozen on 7/28/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__RefNode__
#define __mm__RefNode__

namespace MM
{
  class RefNode : public MM::Node
  {
  private:
    static const MM::CHAR * REF_STR;
    static const MM::UINT32 REF_LEN;
    MM::Node * ref;
  public:
    RefNode(MM::Name * name);
    ~RefNode();
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
#endif /* defined(__mm__RefNode__) */
