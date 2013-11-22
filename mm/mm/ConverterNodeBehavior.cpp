//
//  ConverterNodeBehavior.cpp
//  mm
//
//  Created by Riemer van Rozen on 11/21/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//
/*
#include <stdio.h>
#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Map.h"
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Exp.h"
#include "Observer.h"
#include "Observable.h"
#include "Node.h"
#include "Edge.h"
#include "NodeBehavior.h"
#include "ConverterNodeBehavior.h"
#include "Declaration.h"
#include "Definition.h"
#include "Instance.h"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Map.h"
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "Assertion.h"
#include "Deletion.h"
#include "Activation.h"
#include "Signal.h"
#include "Edge.h"
#include "StateEdge.h"
#include "FlowEdge.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "Transformation.h"
#include "Modification.h"
#include "Transition.h"
#include "Program.h"
#include "PoolNodeBehavior.h"
#include "SourceNodeBehavior.h"
#include "DrainNodeBehavior.h"
#include "RefNodeBehavior.h"
#include "GateNodeBehavior.h"
#include "ConverterNodeBehavior.h"
#include "Observer.h"
#include "Observable.h"
#include "Declaration.h"
#include "InterfaceNode.h"
#include "Definition.h"
#include "Instance.h"
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
#include "DieExp.h"
#include "AliasExp.h"
#include "OneExp.h"
#include "VarExp.h"
#include "Reflector.h"
#include "Evaluator.h"
#include "Machine.h"

const MM::CHAR * MM::ConverterNodeBehavior::CONVERTER_STR = "converter";
const MM::CHAR * MM::ConverterNodeBehavior::FROM_STR = "from";
const MM::CHAR * MM::ConverterNodeBehavior::TO_STR  = "to";
const MM::UINT32 MM::ConverterNodeBehavior::CONVERTER_LEN =
  strlen(MM::ConverterNodeBehavior::CONVERTER_STR);
const MM::UINT32 MM::ConverterNodeBehavior::FROM_LEN =
  strlen(MM::ConverterNodeBehavior::FROM_STR);
const MM::UINT32 MM::ConverterNodeBehavior::TO_LEN  =
  strlen(MM::ConverterNodeBehavior::TO_STR);

MM::ConverterNodeBehavior::ConverterNodeBehavior(MM::NodeBehavior::IO    io,
                                                 MM::NodeBehavior::When  when,
                                                 MM::Name * from,
                                                 MM::Name * to,
                                                 MM::Node * sourceNode,
                                                 MM::Node * drainNode,
                                                 MM::Edge * triggerEdge) :
  MM::NodeBehavior(io,
                   when,
                   MM::NodeBehavior::ACT_PULL,
                   MM::NodeBehavior::HOW_ALL)
{
  this->from = from;
  this->to = to;
  this->sourceNode = sourceNode;
  this->drainNode = drainNode;
  this->triggerEdge = triggerEdge;
}

MM::ConverterNodeBehavior::~ConverterNodeBehavior()
{
  this->from = MM_NULL;
  this->to = MM_NULL;
}

MM::VOID MM::ConverterNodeBehavior::recycle(MM::Recycler *r)
{
  if(from != MM_NULL)
  {
    from->recycle(r);
  }
  if(to != MM_NULL)
  {
    to->recycle(r);
  }
  
  sourceNode->recycle(r);
  drainNode->recycle(r);
  triggerEdge->recycle(r);
  
  MM::NodeBehavior::recycle(r);
}

MM::TID MM::ConverterNodeBehavior::getTypeId()
{
  return MM::T_ConverterNodeBehavior;
}

MM::BOOLEAN MM::ConverterNodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_ConverterNodeBehavior)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::NodeBehavior::instanceof(tid);
  }
}

MM::Name * MM::ConverterNodeBehavior::getFrom()
{
  return from;
}

MM::Name * MM::ConverterNodeBehavior::getTo()
{
  return to;
}

MM::Edge * MM::ConverterNodeBehavior::getTriggerEdge()
{
  return triggerEdge;
}

MM::Node * MM::ConverterNodeBehavior::getSourceNode()
{
  return sourceNode;
}

MM::Node * MM::ConverterNodeBehavior::getDrainNode()
{
  return drainNode;
}

MM::VOID MM::ConverterNodeBehavior::setFrom(MM::Name * from)
{
  this->from = from;
}

MM::VOID MM::ConverterNodeBehavior::setTo(MM::Name * to)
{
  this->to = to;
}

MM::UINT32 MM::ConverterNodeBehavior::getCreateMessage()
{
  return MM::MSG_NEW_CONVERTER;
}

MM::UINT32 MM::ConverterNodeBehavior::getUpdateMessage()
{
  return MM::MSG_UPD_CONVERTER;
}

MM::UINT32 MM::ConverterNodeBehavior::getDeleteMessage()
{
  return MM::MSG_DEL_CONVERTER;
}

MM::VOID MM::ConverterNodeBehavior::step(MM::Node * node,
                                         MM::Instance * i,
                                         MM::Machine * m,
                                         MM::Transition * tr)
{
  MM::Name * name = node->getName();
  MM::CHAR * buf = name->getBuffer();
  printf("STEP NODE %s\n", buf);
  
  if(i->isActive(sourceNode) == MM_TRUE)
  {
    MM::Vector<MM::Edge *> * work = node->getOutput();
    NodeBehavior::stepAll(sourceNode, i, work, m, tr);
  }

  MM::Vector<MM::Edge *> * work = node->getInput();
  NodeBehavior::stepAll(node, i, work, m, tr);
}

MM::UINT32 MM::ConverterNodeBehavior::getCapacity(MM::Instance * i,
                                                  MM::Node * n)
{
  return drainNode->getCapacity(i);
}

MM::UINT32 MM::ConverterNodeBehavior::getResources(MM::Instance * i,
                                                   MM::Node * n)
{
  return sourceNode->getResources(i);
}

MM::VOID MM::ConverterNodeBehavior::add(MM::Instance * i,
                                        MM::Node * n,
                                        MM::UINT32 amount)
{
  return drainNode->add(i, amount);
}

MM::VOID MM::ConverterNodeBehavior::sub(MM::Instance * i,
                                        MM::Node * n,
                                        MM::UINT32 amount)
{
  return sourceNode->sub(i, amount);
}

MM::BOOLEAN MM::ConverterNodeBehavior::hasCapacity(MM::Instance * i,
                                                   MM::Node * n,
                                                   MM::UINT32 amount)
{
  return drainNode->hasCapacity(i, amount);
}

MM::BOOLEAN MM::ConverterNodeBehavior::hasResources(MM::Instance * i,
                                                    MM::Node * n,
                                                    MM::UINT32 amount)
{
  return sourceNode->hasResources(i, amount);
}


MM::VOID MM::ConverterNodeBehavior::activateTriggerTargets(MM::Node * node,
                                                           MM::Instance * i,
                                                           MM::Machine * m)
{
  //trigger the source node
  i->setActive(sourceNode);
  MM::NodeBehavior::activateTriggerTargets(node, i, m);
}

MM::VOID MM::ConverterNodeBehavior::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::ConverterNodeBehavior::CONVERTER_STR,
              MM::ConverterNodeBehavior::CONVERTER_LEN);
}

MM::VOID MM::ConverterNodeBehavior::toString(MM::String * buf,
                                             MM::Name * name)
{
  MM::NodeBehavior::toString(buf, name);
  toString(buf);
  buf->space();
  name->toString(buf);
  buf->space();
  if(from != MM_NULL)
  {
    buf->append((MM::CHAR*)MM::ConverterNodeBehavior::FROM_STR,
                MM::ConverterNodeBehavior::FROM_LEN);
    buf->space();
    from->toString(buf);
    buf->space();
  }
  if(to != MM_NULL)
  {
    buf->append((MM::CHAR*)MM::ConverterNodeBehavior::TO_STR,
                MM::ConverterNodeBehavior::TO_LEN);
    buf->space();
    to->toString(buf);
    buf->space();
  }
}