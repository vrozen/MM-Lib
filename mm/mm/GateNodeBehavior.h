//
//  GateNodeBehavior.h
//  mm
//
//  Created by Riemer van Rozen on 10/16/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__GateNodeBehavior__
#define __mm__GateNodeBehavior__
namespace MM
{
  class GateNodeBehavior : public MM::NodeBehavior
  {
  private:
    static const MM::CHAR * GATE_STR;
    static const MM::UINT32 GATE_LEN;
  public:
    GateNodeBehavior(MM::NodeBehavior::IO   io,
                     MM::NodeBehavior::When when,
                     MM::NodeBehavior::Act  act,
                     MM::NodeBehavior::How  how);
    ~GateNodeBehavior();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::UINT32 getCreateMessage();
    MM::UINT32 getUpdateMessage();
    MM::UINT32 getDeleteMessage();    
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::Name * name);    
  };
}
#endif /* defined(__mm__GateNodeBehavior__) */
