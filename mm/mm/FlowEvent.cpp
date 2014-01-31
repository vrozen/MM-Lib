//
//  FlowEvent.cpp
//  mm
//
//  Created by Riemer van Rozen on 1/30/14.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Map.h"
#include "Recycler.h"
#include "Observer.h"
#include "Observable.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Transformation.h"
#include "Program.h"
#include "Modification.h"
#include "Transition.h"
#include "FlowEvent.h"
#include "Operator.h"
#include "Exp.h"
#include "Assertion.h"
#include "Deletion.h"
#include "Activation.h"
#include "Signal.h"
#include "Edge.h"
#include "StateEdge.h"
#include "FlowEdge.h"
#include "NodeWorkItem.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "PoolNodeBehavior.h"
#include "SourceNodeBehavior.h"
#include "DrainNodeBehavior.h"
#include "GateNodeBehavior.h"
#include "RefNodeBehavior.h"
#include "ConverterNodeBehavior.h"
#include "Declaration.h"
#include "InterfaceNode.h"
#include "Definition.h"
#include "Instance.h"
#include "Operator.h"
#include "ValExp.h"
#include "UnExp.h"
#include "BinExp.h"
#include "DieExp.h"
#include "RangeValExp.h"
#include "BooleanValExp.h"
#include "NumberValExp.h"
#include "OverrideExp.h"
#include "ActiveExp.h"
#include "AllExp.h"
#include "AliasExp.h"
#include "OneExp.h"
#include "VarExp.h"
#include "Reflector.h"
#include "Evaluator.h"
#include "Machine.h"

MM::FlowEvent::FlowEvent(MM::Instance * actInstance,
                         MM::Node     * actNode,
                         MM::Edge     * actEdge,
                         MM::Instance * srcInstance,
                         MM::Node     * srcNode,
                         MM::UINT32     amount,
                         MM::Instance * tgtInstance,
                         MM::Node     * tgtNode) : MM::Element(MM_NULL)
{
  this->actInstance = actInstance;
  this->actNode = actNode,
  this->actEdge = actEdge,
  this->srcInstance = srcInstance;
  this->srcNode = srcNode;
  this->amount = amount;
  this->tgtInstance = tgtInstance;
  this->tgtNode = tgtNode;
}

MM::FlowEvent::~FlowEvent()
{
  this->actInstance = MM_NULL;
  this->actNode = MM_NULL,
  this->actEdge = MM_NULL,
  this->srcInstance = MM_NULL;
  this->srcNode = MM_NULL;
  this->amount = MM_NULL;
  this->tgtInstance = MM_NULL;
  this->tgtNode = MM_NULL;
}

MM::VOID MM::FlowEvent::recycle(MM::Recycler *r)
{
  this->MM::Element::recycle(r);
}

MM::TID MM::FlowEvent::getTypeId()
{
  return MM::T_FlowEvent;
}

MM::BOOLEAN MM::FlowEvent::instanceof(MM::TID tid)
{
  if(tid == MM::T_FlowEvent)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}

MM::Node * MM::FlowEvent::getSourceNode()
{
  return srcNode;
}

MM::UINT32 MM::FlowEvent::getAmount()
{
  return amount;
}

MM::Node * MM::FlowEvent::getTargetNode()
{
  return tgtNode;
}

MM::Instance * MM::FlowEvent::getActInstance()
{
  return actInstance;
}

MM::Edge * MM::FlowEvent::getActEdge()
{
  return actEdge;
}

MM::Node * MM::FlowEvent::getActNode()
{
  return actNode;
}

MM::Instance * MM::FlowEvent::getSourceInstance()
{
  return srcInstance;
}

MM::Instance * MM::FlowEvent::getTargetInstance()
{
  return tgtInstance;
}

MM::VOID MM::FlowEvent::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::FlowEvent::toString(MM::String * buf, MM::UINT32 indent)
{
  srcInstance->nameToString(srcNode, buf);
  buf->space();
  buf->append('-');
  buf->appendInt(amount);
  buf->append('-');
  buf->append('>');
  buf->space();
  tgtInstance->nameToString(tgtNode, buf);
}