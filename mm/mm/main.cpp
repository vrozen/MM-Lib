//
//  main.cpp
//  mm
//
//  Created by Riemer van Rozen on 3/6/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
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
#include "Operator.h"
#include "ValExp.h"
#include "UnExp.h"
#include "BinExp.h"
#include "RangeValExp.h"
#include "BooleanValExp.h"
#include "NumberValExp.h"

/*
int main(int argc, const char * argv[])
{
  MM::String * str1 = new MM::String(128);
  str1->append((MM::CHAR*)"P",1);
  MM::String * str2 = new MM::String(128);
  str2->append((MM::CHAR*)"Q",1);
  
  MM::String* s = new MM::String(512);
  
  MM::Exp * exp1 = new MM::NumberValExp(4,22);
  MM::Exp * exp2 = new MM::NumberValExp(2);
  MM::Exp * exp3 = new MM::BinExp(exp1, MM::Operator::OP_DIV, exp2);
  
  exp1->toString(s);
  s->linebreak();
  
  exp2->toString(s);
  s->linebreak();
  
  exp3->toString(s);
  s->linebreak();
  
  //MM::Exp * exp4 = new MM::BooleanValExp(MM_TRUE);
  //MM::Exp * exp5 = new MM::BooleanValExp(MM_FALSE);
  //MM::Exp * exp6 = new MM::BinExp(exp4, MM::Exp::OP_AND, exp5);
  
  MM::ValExp * v1 = exp3->eval();
  //MM::ValExp * v2 = exp6->eval();
  
  v1->toString(s);
  s->linebreak();
  s->print();
  
  //MM::PoolNode p(MM::Node::WHEN_AUTO, MM::Node::ACT_PULL, MM::Node::HOW_ALL, str1, 5, 10, NULL);
  //MM::PoolNode q(MM::Node::WHEN_AUTO, MM::Node::ACT_PULL, MM::Node::HOW_ALL, str2, 0, 4, NULL);
  //MM::FlowEdge f(&p, exp3, &q);
  //p.toString(s);
  //q.toString(s);
  //f.toString(s);
  //s->print();
  
  return 0;
}
*/
