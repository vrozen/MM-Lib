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
  class FlowEdge : Edge
  {
  public:
    FlowEdge(MM::Node * src, MM::Exp * exp, MM::Node * tgt);
    ~FlowEdge();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__FlowEdge__) */
