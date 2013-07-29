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
  class PoolNode : public MM::Node
  {
  private:
    static const MM::CHAR * POOL_STR;
    static const MM::CHAR * AT_STR;
    static const MM::CHAR * MAX_STR;
    static const MM::CHAR * ADD_STR;
    static const MM::UINT32 POOL_LEN;
    static const MM::UINT32 AT_LEN;
    static const MM::UINT32 MAX_LEN;
    static const MM::UINT32 ADD_LEN;
    MM::INT32 val;
    MM::INT32 val_new;
    MM::INT32 val_old;
    MM::UINT32 at;
    MM::UINT32 max;
    MM::Exp * exp;
  public:
    PoolNode(MM::Node::IO    io,
             MM::Node::When  when,
             MM::Node::Act   act,
             MM::Node::How   how,
             MM::Name      * name,
             MM::INT32       at,
             MM::UINT32      max,
             MM::Exp       * exp);
    ~PoolNode();
    MM::INT32 getResources();
    MM::INT32 getCapacity();
    MM::BOOLEAN hasCapacity();
    MM::BOOLEAN hasResources();
    MM::BOOLEAN hasCapacity(MM::UINT32 amount);
    MM::BOOLEAN hasResources(MM::UINT32 amount);
    MM::VOID sub(MM::UINT32 amount);
    MM::VOID add(MM::UINT32 amount);
    MM::VOID toString(MM::String * buf);
  };
}
#endif /* defined(__mm__Pool__) */
