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
  class Instance;
  class Edge : public MM::Element
  {
  private:
  private:
    static const MM::CHAR COLON_CHAR;
    MM::Name * srcName; //source node name (parsed)
    MM::Name * tgtName; //target node name (parsed)
    MM::Node * srcNode; //source node (resolved)
    MM::Node * tgtNode; //target node (resolved)
    MM::Exp  * exp;     //expression (parsed)
  protected:
    Edge(MM::Name * name, MM::Name * src, MM::Exp * exp, MM::Name * tgt);
    virtual ~Edge();
  public:
    MM::VOID recycle(MM::Recycler * r);
    virtual MM::TID getTypeId();
    virtual MM::BOOLEAN instanceof(MM::TID tid);
    MM::Node * getSource();
    MM::Node * getTarget();
    MM::Exp * getExp();    
    MM::VOID setExp(MM::Exp * exp);
    MM::VOID setSource(MM::Node * src);
    MM::VOID setTarget(MM::Node * tgt);
    MM::Name * getSourceName();
    MM::Name * getTargetName();
    virtual MM::VOID toString(MM::String * buf) = 0;
    virtual MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}
#endif /* defined(__mm__Edge__) */

