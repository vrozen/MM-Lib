//
//  NodeWorkItem.h
//  mm
//
//  Created by Riemer van Rozen on 1/27/14.
//  Copyright (c) 2014 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__NodeWorkItem__
#define __mm__NodeWorkItem__

namespace  MM
{
  class Instance;
  class Node;
  class Edge;
  class NodeWorkItem
  {
  private:
    MM::Node     * node;
    MM::Instance * instance;
    MM::Edge     * edge;
  public:
    NodeWorkItem(MM::Instance * instance, MM::Node * node, MM::Edge * edge);
    ~NodeWorkItem();
    MM::Instance * getInstance();
    MM::Node * getNode();
    MM::Edge * getEdge();
  };
}

#endif /* defined(__mm__NodeWorkItem__) */
