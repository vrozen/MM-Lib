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
  class SourceNodeBehavior : public MM::NodeBehavior
  {
  private:
    static const MM::CHAR * SOURCE_STR;
    static const MM::UINT32 SOURCE_LEN;
  public:
    SourceNodeBehavior(MM::NodeBehavior::IO   io,
               MM::NodeBehavior::When when,
               MM::NodeBehavior::Act  act,
               MM::NodeBehavior::How  how);
    ~SourceNodeBehavior();
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
#endif /* defined(__mm__SourceNode__) */