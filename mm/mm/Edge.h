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
  class Edge : public Element
  {
  private:
    MM::Name * srcName;
    MM::Name * tgtName;
    MM::Node * srcNode;
    MM::Exp  * exp;
    MM::Node * tgtNode;    
  protected:
    Edge(MM::Name * src, MM::Exp * exp, MM::Name * tgt);
    virtual ~Edge();
  public:
    MM::Node * getSource();
    MM::Node * getTarget();
    MM::Exp * getExp();
    MM::VOID setSource(MM::Node * src);
    MM::VOID setTarget(MM::Node * tgt);
    virtual MM::VOID toString(MM::String * buf) = 0;
  };
}
#endif /* defined(__mm__Edge__) */

