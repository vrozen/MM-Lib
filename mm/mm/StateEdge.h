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
  public:
    StateEdge(MM::Name * src, MM::Exp * exp, MM::Name * tgt);
    ~StateEdge();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__StateEdge__) */
