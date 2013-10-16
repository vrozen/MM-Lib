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
  
  behavior->recycle(r);
  
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

MM::VOID MM::Node::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::Node::toString(MM::String * buf, MM::UINT32 indent)
{
  buf->space(indent);
  behavior->toString(buf, name);
}

/*
MM::BOOLEAN MM::Node::isActive(MM::Instance * i)
{
  //return active;
  //note this should be calculated based on instantiations,
  //not on the static types
  return MM_TRUE;
}

MM::BOOLEAN MM::Node::isSatisfied(MM::Machine * m,
                                  MM::Instance * i,
                                  MM::Transition * t)
{
  //calculate which node's inputs are 'satisfied'
  //this set is the set of node labels for which all flow edges they operate on are satisfied at the same time
  //this semantics is a bit strange since we also have the 'all' and 'any' modifiers
  //therefore we might expect any nodes to trigger when any flow is satisfied, but this is not true!

  //satisfied nodes are
  //1. pulling nodes
  //either each inflow is satisfied and it has inflow
  //or the node has no inflow and it is active (auto or activated)
  //2. pushing nodes
  //either each outflow is satisfied and it has outflow
  //or the node has no outflow and it is active (auto or activated)
  
  MM::BOOLEAN satisfied = MM_TRUE;
  
  if(act == MM::Node::ACT_PULL)
  {
    if(input->isEmpty() == MM_TRUE)
    {
      satisfied = this->isActive(i);
    }
    else
    {
      MM::Vector<Edge *>::Iterator fIter = input->getIterator();
      while(fIter.hasNext())
      {
        Edge * edge = fIter.getNext();
        Node * src = edge->getSource();
        Node * tgt = edge->getTarget();
        ValExp * val = 0; //FIXME: edge->getExp()->eval(m, i, edge);
        //FlowEvent * flow = t->getFlow(i, src, tgt);
        //UINT32 amount = flow->getAmount();
        
        //if(flow != MM_NULL)
        //{
          //satisfied = val->greaterEquals(amount);
          //}
          //else
          //{
          // satisfied = MM_FALSE;
          // }
      }
    }
  }
  else if(act == ACT_PUSH)
  {
    MM::Vector<Edge *>::Iterator iter = input->getIterator();
    
    while(iter.hasNext())
    {
      Edge * edge = iter.getNext();
      
      //if(!edge->isSatisfied(instance, transition))
      //{
      // satisified = MM_FALSE;
      //}
    }
  }
  else
  {
    //error
  }
  
  return satisfied;
}



MM::Transition * MM::Node::step()
{
  MM::Transition * tr = NULL;
  MM::Vector<Edge *> * work = NULL;
  
  if(this->getAct() == ACT_PULL)
  {
    work = this->getInput();
  }
  else //act must must be push
  {
    work = this->getOutput();
  }
  
  if(this->getHow() == HOW_ANY)
  {
    tr = stepAny(work);
  }
  else //how must be all
  {
    tr = stepAll(work);
  }
  
  return tr;
}

MM::Transition * MM::Node::stepAll(MM::Vector<Edge *> * work)
{
  MM::Vector<Edge *>::Iterator i = work->getIterator();
  bool success = true;
  Transition * tr = new Transition();
  
  while(i.hasNext() == MM_TRUE)
  {
    Edge* edge = i.getNext();
    MM::INT32 flow = 0;
    Node * src = edge->getSource();
    Node * tgt = edge->getTarget();
    
    //TODO: evaluate flow amount
    
    if(flow > 0 && src->hasResources(flow) && tgt->hasCapacity(flow))
    {
      src->sub(flow);
      tgt->add(flow);
      tr->add(new FlowEvent(src,flow,tgt));
    }
    else
    {
      success = false;
      break;
    }
  }
  
  if(!success)
  {
    //FIXME
    //tr->back();
    //tr->clear();
  }
  
  return tr;
}

MM::Transition * MM::Node::stepAny(MM::Vector<Edge *> * work)
{
  //MM::Vector<Edge *>::Iterator * i = work->getIterator();
  //MM::Vector<Edge *> rnd(work->size());
  //rnd = *work;
  
  //FIXME random

  Transition * tr = MM_NULL;
  while(i->hasNext() == MM_TRUE)
  {
    Edge * edge = i->getNext();s
    MM::INT32 flow = 0;
    Node * src = edge->getSource();
    Node * tgt = edge->getTarget();
    
    //TODO: evaluate flow amount
    
    if(flow > 0 && src->hasResources() && tgt->hasCapacity())
    {
      if(src->hasResources(flow))
      {
        if(tgt->hasCapacity(flow))
        {
          src->sub(flow);
          tgt->add(flow);
          tr->add(new FlowEvent(src,flow,tgt));
        }
        else
        {
          flow = ((PoolNode*)tgt)->getCapacity();
          src->sub(flow);
          tgt->add(flow);
          tr->add(new FlowEvent(src,flow,tgt));
        }
      }
      else
      {
        flow = ((PoolNode*)src)->getResources();
        if(tgt->hasCapacity(flow))
        {
          src->sub(flow);
          tgt->add(flow);
          tr->add(new FlowEvent(src,flow,tgt));
        }
        else
        {
          flow = ((PoolNode*)tgt)->getCapacity();
          src->sub(flow);
          tgt->add(flow);
          tr->add(new FlowEvent(src,flow,tgt));
        }
      }
    }
  }
  return tr;
}
*/


