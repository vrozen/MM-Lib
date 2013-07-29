//
//  Machine.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/16/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "Assert.h"
#include "Edge.h"
#include "StateEdge.h"
#include "FlowEdge.h"
#include <vector>
#include "Node.h"
#include "Event.h"
#include "FlowEvent.h"
#include "Transition.h"
#include "PoolNode.h"
#include "SourceNode.h"
#include "DrainNode.h"
#include "RefNode.h"
#include "Declaration.h"
#include "Definition.h"
#include "Operator.h"
#include "ValExp.h"
#include "UnExp.h"
#include "BinExp.h"
#include "RangeValExp.h"
#include "BooleanValExp.h"
#include "NumberValExp.h"
#include "OverrideExp.h"
#include "ActiveExp.h"
#include "AllExp.h"
#include "AliasExp.h"
#include "OneExp.h"
#include "VarExp.h"
#include "Machine.h"

MM::Machine::Machine()
{
  for(int i = 0; i < MAX_DEFS; i++)
  {
    defs[i] = NULL;
  }
  for(int i = 0; i< MAX_INSTS; i++)
  {
    insts[i] = NULL;
  }
  curDef = 0;
  curInst = 0;
}

MM::Machine::~Machine()
{
}

/*
MM::UINT32 MM::Machine::addInstance (MM::UINT32   inst, //0 -> global scope
                                     MM::UINT32   type,
                                     MM::CHAR   * name)
{
  MM::UINT32 pools = 0; //defs[def]->getPoolCount();
  MM::UINT32 gates = 0; //defs[def]->getGateCount();
  MM::UINT32 insts = 0; //defs[def]->getInstanceCount();

  MM::UINT32 size
    = sizeof(Instance)
    + pools * sizeof(MM::INT32)
    + gates * 2 * sizeof(MM::INT32)
    + insts * sizeof(MM::UINT32);
  
  MM::Instance * i = (MM::Instance*) malloc(size);
  MM::UINT32 pos = curInst;
  i->pools = pools;
  i->gates = gates;
  i->insts = insts;
  
  curInst++;
  
  this->insts[pos] = i;
  return pos;
}
*/

MM::VOID recycleInstance(MM::Instance * instance)
{
}

MM::Transition * MM::Machine::step()
{  
  //A. prepare
  //1. set temporary values (new, old) to val
  //   for each node -> reset()
  
  
  //B. activity
  //1. pull all nodes
  //2. pull any nodes
  //3. push all nodes
  //4. push any nodes
  
  //C. finalize
  //1. set temporary values (new, old) to zero
  //2. redistribute gates
  //3. set active nodes in next state
  //4. process trigger to activate nodes in next state
  
  return NULL;
}




std::vector<MM::Element*> * MM::Machine::createList()
{
  return new std::vector<MM::Element*> ();
}

std::vector<MM::Element*> * MM::Machine::createList(std::vector<MM::Element*> * elements,
                                                    MM::Element * element)
{
  elements->push_back(element);
  return elements;
}

MM::Location * MM::Machine::createLocation(YYLTYPE * loc)
{
  return new MM::Location(loc->first_line,
                          loc->first_column,
                          loc->last_line,
                          loc->last_column);
}

MM::Name * MM::Machine::createName(MM::Name * n1,
                                   MM::CHAR * str,
                                   YYLTYPE  * strLoc)
{
  MM::Location * loc = MM::Machine::createLocation(strLoc);
  MM::Name * n2 = new MM::Name(str,loc);
  n1->setSubName(n2);
  return n1;
}

MM::Name * MM::Machine::createName(MM::CHAR * str,
                                   YYLTYPE  * strLoc)
{
  MM::Location * loc = MM::Machine::createLocation(strLoc);
  return new MM::Name(str,loc);
}

MM::SourceNode * MM::Machine::createSourceNode(MM::Node::IO    io,
                                               MM::Node::When  when,
                                               MM::Node::Act   act,
                                               MM::Node::How   how,
                                               MM::Name      * name)
{
  return new MM::SourceNode(io,when,act,how,name);
}

MM::DrainNode * MM::Machine::createDrainNode(MM::Node::IO    io,
                                             MM::Node::When  when,
                                             MM::Node::Act   act,
                                             MM::Node::How   how,
                                             MM::Name      * name)
{
  return new MM::DrainNode(io,when,act,how,name);
}

MM::PoolNode * MM::Machine::createPoolNode(MM::Node::IO    io,
                                           MM::Node::When  when,
                                           MM::Node::Act   act,
                                           MM::Node::How   how,
                                           MM::Name      * name,
                                           MM::UINT32      at,
                                           MM::UINT32      max,
                                           MM::Exp       * exp)
{
  return new MM::PoolNode(io,when,act,how,name,at,max,exp);
}

MM::RefNode * MM::Machine::createRefNode(MM::Name * name)
{
  return new MM::RefNode(name);
}

MM::StateEdge * MM::Machine::createStateEdge(MM::Name * src,
                                             MM::Exp  * exp,
                                             MM::Name * tgt)
{
  return new MM::StateEdge(src,exp,tgt);
}

MM::FlowEdge * MM::Machine::createFlowEdge(MM::Name * src,
                                           MM::Exp  * exp,
                                           MM::Name * tgt)
{
  return new MM::FlowEdge(src,exp,tgt);
}

MM::Definition * MM::Machine::createDefinition(MM::Name * name,
                                               std::vector<Element*> * es)
{
  return new MM::Definition(name,es);
}


MM::Declaration * MM::Machine::createDeclaration(MM::Name * type,
                                                  MM::Name * name)
{
  return new MM::Declaration(type,name);
}


MM::Assert * MM::Machine::createAssert(MM::Name * name,
                                       MM::Exp  * exp,
                                       MM::CHAR * msg,
                                       YYLTYPE  * msgLoc)
{
  MM::Location * loc = MM::Machine::createLocation(msgLoc);
  return new MM::Assert(name,exp,msg,loc);
}

MM::UnExp * MM::Machine::createUnExp(MM::Operator::OP  op,
                                     YYLTYPE         * opLoc,
                                     MM::Exp         * exp)
{
  MM::Location * loc = MM::Machine::createLocation(opLoc);
  
  return new MM::UnExp(op, exp, loc);
}

MM::BinExp * MM::Machine::createBinExp(MM::Exp          * e1,
                                       MM::Operator::OP   op,
                                       YYLTYPE          * opLoc,
                                       MM::Exp          * e2)
{
  MM::Location * loc = MM::Machine::createLocation(opLoc);
  
  return new MM::BinExp(e1,op,e2,loc);
}

MM::OverrideExp * MM::Machine::createOverrideExp(YYLTYPE * lparenLoc,
                                                 MM::Exp * e,
                                                 YYLTYPE * rparenLoc)
{
  MM::Location * lparen_loc = MM::Machine::createLocation(lparenLoc);
  MM::Location * rparen_loc = MM::Machine::createLocation(rparenLoc);
  
  return new MM::OverrideExp(e, lparen_loc, rparen_loc);
}

MM::RangeValExp * MM::Machine::createRangeValExp(MM::INT32   v1,
                                                 YYLTYPE   * v1Loc,
                                                 YYLTYPE   * rangeLoc,
                                                 MM::INT32   v2,
                                                 YYLTYPE   * v2Loc)
{
  MM::Location * v1_loc = MM::Machine::createLocation(v1Loc);
  MM::Location * v2_loc = MM::Machine::createLocation(v2Loc);
  MM::Location * range_loc = MM::Machine::createLocation(rangeLoc);
  
  return new MM::RangeValExp(v1, v2, v1_loc, range_loc, v2_loc);
}

MM::NumberValExp * MM::Machine::createNumberValExp(MM::INT32  val,
                                                   YYLTYPE  * valLoc)
{
  MM::Location * loc = MM::Machine::createLocation(valLoc);
  
  return new MM::NumberValExp(val/100, val%100, loc);
}

MM::BooleanValExp * MM::Machine::createBooleanValExp(MM::BOOLEAN val,
                                                     YYLTYPE * valLoc)
{
  MM::Location * loc = MM::Machine::createLocation(valLoc);
  
  return new MM::BooleanValExp(val, loc);
};

MM::AllExp * MM::Machine::createAllExp(YYLTYPE * allLoc)
{
  MM::Location * loc = MM::Machine::createLocation(allLoc);
  
  return new MM::AllExp(loc);
};

MM::ActiveExp * MM::Machine::createActiveExp(YYLTYPE  * activeLoc,
                                             MM::Name * name)
{
  MM::Location * loc = MM::Machine::createLocation(activeLoc);
  
  return new MM::ActiveExp(name,loc);
}

MM::AliasExp * MM::Machine::createAliasExp(YYLTYPE * aliasLoc)
{
  MM::Location * loc = createLocation(aliasLoc);
  
  return new MM::AliasExp(loc);
}

MM::OneExp * MM::Machine::createOneExp(YYLTYPE * epsilonLoc)
{
  MM::Location * loc = createLocation(epsilonLoc);
  
  return new MM::OneExp(loc);
}

MM::VarExp * MM::Machine::createVarExp(MM::Name * name)
{
  return new MM::VarExp(name);
}
