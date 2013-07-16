//
//  Pool.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Pool__
#define __mm__Pool__

namespace MM
{
  class PoolNode : public Node
  {
  private:
    MM::INT32 val;
    MM::INT32 val_new;
    MM::INT32 val_old;
    MM::UINT32 at;
    MM::UINT32 max;
    MM::Exp * exp;
    MM::Transition * stepAll(std::vector<Edge*> * work);
    MM::Transition * stepAny(std::vector<Edge*> * work);
  public:
    PoolNode(MM::When when, MM::Act act, MM::How how,
             MM::String * name, MM::INT32 at, MM::UINT32 max,
             MM::Exp * exp);
    ~PoolNode();
    MM::INT32 getResources();
    MM::INT32 getCapacity();
    MM::Transition * step();
    
    MM::BOOLEAN hasCapacity();
    MM::BOOLEAN hasResources();
    MM::BOOLEAN hasCapacity(MM::UINT32 amount);
    MM::BOOLEAN hasResources(MM::UINT32 amount);
    MM::VOID sub(MM::UINT32 amount);
    MM::VOID add(MM::UINT32 amount);
    MM::VOID toString(MM::String * buf);
  private:

  };
}
#endif /* defined(__mm__Pool__) */
