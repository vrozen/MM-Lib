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
  class RefNodeBehavior : public MM::NodeBehavior
  {
  private:
    static const MM::CHAR * REF_STR;
    static const MM::UINT32 REF_LEN;
    MM::Edge * alias; //a RefNode must have exactly one alias edge
  public:
    RefNodeBehavior();
    ~RefNodeBehavior();
    MM::VOID recycle(MM::Recycler *r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::Edge * getAlias();
    MM::VOID setAlias(MM::Edge * edge);
    MM::Node * getReference();
    MM::UINT32 getCreateMessage();
    MM::UINT32 getUpdateMessage();
    MM::UINT32 getDeleteMessage();    
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::Name * name);
  };
}
#endif /* defined(__mm__RefNode__) */
