//
//  main.cpp
//  mm
//
//  Created by Riemer van Rozen on 3/6/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "String.h"
#include "Element.h"
#include "Exp.h"
#include "Edge.h"
#include "FlowEdge.h"
#include <vector>
#include "Node.h"
#include "Event.h"
#include "FlowEvent.h"
#include "Transition.h"
#include "PoolNode.h"

int main(int argc, const char * argv[])
{
  MM::String * str1 = new MM::String(128);
  str1->append((MM::CHAR*)"P",1);
  MM::String * str2 = new MM::String(128);
  str2->append((MM::CHAR*)"Q",1);
  
  MM::Exp * exp = new MM::Exp(1);
  
  MM::PoolNode p(MM::WHEN_AUTO, MM::ACT_PULL, MM::HOW_ALL, str1, 5, 10, exp);
  MM::PoolNode q(MM::WHEN_AUTO, MM::ACT_PULL, MM::HOW_ALL, str2, 0, 4, exp);
  MM::FlowEdge f(&p, exp, &q);
  
  MM::String* s = new MM::String(512);
  p.toString(s);
  q.toString(s);
  f.toString(s);
  s->print();
  
  return 0;
}

