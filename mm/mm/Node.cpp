//
//  Node.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

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
#include "Observer.h"
#include "Observable.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "Edge.h"
#include "NodeBehavior.h"
#include "Node.h"

MM::Node::Node(MM::Name * name,
               MM::NodeBehavior * behavior): MM::Element(name)
{
  this->behavior = behavior;
  input = MM_NULL;
  output = MM_NULL;
  conditions = MM_NULL;
  triggers = MM_NULL;
  aliases = MM_NULL;
}

MM::Node::~Node()
{
  behavior = MM_NULL;
  input = MM_NULL;
  output = MM_NULL;
  conditions = MM_NULL;
  triggers = MM_NULL;
  aliases = MM_NULL;
}

MM::VOID MM::Node::recycle(MM::Recycler * r)
{
  if(input != MM_NULL)
  {
    delete input;  //FIXME
  }
  if(output != MM_NULL)
  {
    delete output; //FIXME
  }
  if(conditions != MM_NULL)
  {
    delete conditions;   //FIXME
  }
  if(triggers != MM_NULL)
  {
    delete triggers; //FIXME
  }
  if(aliases != MM_NULL)
  {
    delete aliases;
  }
  if(behavior != MM_NULL)
  {
    behavior->recycle(r);
  }
  MM::Element::recycle(r);
}

MM::TID MM::Node::getTypeId()
{
  return MM::T_Node;
}

MM::BOOLEAN MM::Node::instanceof(MM::TID tid)
{
  if(tid == MM::T_Node)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}

MM::NodeBehavior * MM::Node::getBehavior()
{
  return behavior;
}

MM::VOID MM::Node::setBehavior(MM::NodeBehavior * behavior)
{
  this->behavior = behavior;
}

MM::VOID MM::Node::addInput(MM::Edge * edge)
{
  input->add(edge);
}

MM::VOID MM::Node::addOutput(MM::Edge * edge)
{
  output->add(edge);
}

MM::VOID MM::Node::addCondition(MM::Edge * edge)
{
  conditions->add(edge);
}

MM::VOID MM::Node::addTrigger(MM::Edge * edge)
{
  triggers->add(edge);
}

MM::VOID MM::Node::addAlias(MM::Edge * edge)
{
  aliases->add(edge);
}

MM::VOID MM::Node::removeInput(MM::Edge * edge)
{
  input->remove(edge);
}

MM::VOID MM::Node::removeOutput(MM::Edge * edge)
{
  output->remove(edge);
}

MM::VOID MM::Node::removeCondition(MM::Edge * edge)
{
  conditions->remove(edge);
}

MM::VOID MM::Node::removeTrigger(MM::Edge * edge)
{
  triggers->remove(edge);
}

MM::VOID MM::Node::removeAlias(MM::Edge * edge)
{
  aliases->remove(edge);
}

MM::Vector<MM::Edge *> * MM::Node::getInput()
{
  return input;
}

MM::Vector<MM::Edge *> * MM::Node::getOutput()
{
  return output;
}

MM::Vector<MM::Edge *> * MM::Node::getConditions()
{
  return conditions;
}

MM::Vector<MM::Edge *> * MM::Node::getTriggers()
{
  return triggers;
}

MM::Vector<MM::Edge *> * MM::Node::getAliases()
{
  return aliases;
}

MM::VOID MM::Node::setInput(MM::Vector<MM::Edge *> * input)
{
  this->input = input;
}

MM::VOID MM::Node::setOutput(MM::Vector<MM::Edge *> * output)
{
  this->output = output;
}

MM::VOID MM::Node::setConditions(MM::Vector<MM::Edge *> * conditions)
{
  this->conditions = conditions;
}

MM::VOID MM::Node::setTriggers(MM::Vector<MM::Edge *> * triggers)
{
  this->triggers = triggers;
}

MM::VOID MM::Node::setAliases(MM::Vector<MM::Edge *> * aliases)
{
  this->aliases = aliases;
}

MM::VOID MM::Node::add(MM::Instance * i, MM::UINT32 amount)
{
  behavior->add(i, this, amount);
}

MM::VOID MM::Node::sub(MM::Instance * i, MM::UINT32 amount)
{
  behavior->sub(i, this, amount);
}

MM::UINT32 MM::Node::getCapacity(MM::Instance * i)
{
  return behavior->getCapacity(i, this);
}

MM::UINT32 MM::Node::getResources(MM::Instance * i)
{
  return behavior->getResources(i, this);
}

MM::BOOLEAN MM::Node::hasCapacity(MM::Instance * i,
                                  MM::UINT32 amount)
{
  return behavior->hasCapacity(i, this, amount);
}

MM::BOOLEAN MM::Node::hasResources(MM::Instance * i,
                                   MM::UINT32 amount)
{
  return behavior->hasResources(i, this, amount);
}

MM::VOID MM::Node::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::Node::toString(MM::String * buf, MM::UINT32 indent)
{
  buf->space(indent);
  behavior->toString(buf, name);
}


