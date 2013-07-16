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
  class StateEdge : Edge
  {
  public:
    StateEdge(MM::Node * src, MM::Exp * exp, MM::Node * tgt);
    ~StateEdge();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__StateEdge__) */
