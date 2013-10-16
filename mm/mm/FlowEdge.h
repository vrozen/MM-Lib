//
//  FlowEdge.h
//  mm
//
//  Created by Riemer van Rozen on 7/11/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__FlowEdge__
#define __mm__FlowEdge__

namespace MM
{
  class FlowEdge : public MM::Edge
  {
  private:
    static const MM::CHAR * MIN_STR;
    static const MM::CHAR * MINGT_STR;
    static const MM::UINT32 MIN_LEN;
    static const MM::UINT32 MINGT_LEN;
  protected:
    ~FlowEdge();
  public:
    FlowEdge(MM::Name * name, MM::Name * src, MM::Exp * exp, MM::Name * tgt);
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}

#endif /* defined(__mm__FlowEdge__) */
