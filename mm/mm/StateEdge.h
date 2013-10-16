//
//  StateEdge.h
//  mm
//
//  Created by Riemer van Rozen on 7/11/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__StateEdge__
#define __mm__StateEdge__

namespace MM
{
  class StateEdge : public MM::Edge
  {
  private:
    static const MM::CHAR * DOT_STR;
    static const MM::CHAR * DOTGT_STR;
    static const MM::UINT32 DOT_LEN;
    static const MM::UINT32 DOTGT_LEN;
  protected:
    ~StateEdge();
  public:
    StateEdge(MM::Name * name, MM::Name * src, MM::Exp * exp, MM::Name * tgt);
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::BOOLEAN isTrigger();
    MM::BOOLEAN isAlias();
    MM::BOOLEAN isCondition();
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}

#endif /* defined(__mm__StateEdge__) */
