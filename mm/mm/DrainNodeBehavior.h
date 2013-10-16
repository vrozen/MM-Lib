//
//  DrainNode.h
//  mm
//
//  Created by Riemer van Rozen on 7/11/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__DrainNode__
#define __mm__DrainNode__
namespace MM
{
  class DrainNodeBehavior : public MM::NodeBehavior
  {
  private:
    static const MM::CHAR * DRAIN_STR;
    static const MM::UINT32 DRAIN_LEN;
  public:
    DrainNodeBehavior(MM::NodeBehavior::IO    io,
                      MM::NodeBehavior::When  when,
                      MM::NodeBehavior::Act   act,
                      MM::NodeBehavior::How   how);
    ~DrainNodeBehavior();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::Name * name);

  };
}
#endif /* defined(__mm__DrainNode__) */
