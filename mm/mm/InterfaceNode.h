//
//  Interface.h
//  mm
//
//  Created by Riemer van Rozen on 10/8/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Interface__
#define __mm__Interface__

namespace MM
{
  class InterfaceNode : public MM::Node
  {
  private:
    MM::Declaration * decl;
    MM::Node * ref;
  public:
    InterfaceNode(MM::Name        * name,
                  MM::Declaration * decl,
                  MM::Node        * ref);
    ~InterfaceNode();
    MM::VOID recycle(MM::Recycler *r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::NodeBehavior * getBehavior();
    MM::Declaration * getDeclaration();
    MM::Node * getNode();

    MM::VOID add(MM::Instance * i, MM::UINT32 amount);
    MM::VOID sub(MM::Instance * i, MM::UINT32 amount);
    MM::UINT32 getCapacity(MM::Instance * i);
    MM::UINT32 getResources(MM::Instance * i);
    MM::BOOLEAN hasCapacity(MM::Instance * i, MM::UINT32 amount);
    MM::BOOLEAN hasResources(MM::Instance * i, MM::UINT32 amount);
    
    MM::VOID activateTriggerTargets(MM::Instance * i, MM::Machine * m);
    MM::VOID toString(MM::String * buf);
  };
}
#endif /* defined(__mm__Interface__) */
