//
//  Edge.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Edge__
#define __mm__Edge__

namespace MM
{
  class Node;
  class Edge
  {
  private:
    MM::Node * src;
    MM::Exp  * exp;
    MM::Node * tgt;
  protected:
    Edge(MM::Node * src, MM::Exp * exp, MM::Node * tgt);
    virtual ~Edge();
  public:
    MM::Node * getSource();
    MM::Node * getTarget();
    virtual MM::VOID toString(MM::String * buf) = 0;
  };
}
#endif /* defined(__mm__Edge__) */

