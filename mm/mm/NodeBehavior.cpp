//
//  NodeBehavior.cpp
//  mm
//
//  Created by Riemer van Rozen on 10/9/13.
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
#include "Edge.h"
#include "Observer.h"
#include "Observable.h"
#include "Node.h"
#include "NodeBehavior.h"
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

const MM::CHAR * MM::NodeBehavior::IO_STR[] =
{
  "error",
  "", //epsilon = private
  "in",
  "out",
  "inout"
};

const MM::CHAR * MM::NodeBehavior::WHEN_STR[] =
{
  "error",
  "", //epsilon = passive
  "auto",
  "user",
  "start"
};

const MM::CHAR * MM::NodeBehavior::ACT_STR[] =
{
  "error",
  "", //epsilon = pull
  "push"
};

const MM::CHAR * MM::NodeBehavior::HOW_STR[] =
{
  "error",
  "", //epsilon = any
  "all"
};

const MM::UINT32 MM::NodeBehavior::IO_LEN[] =
{
  strlen(MM::NodeBehavior::IO_STR[0]), //error
  strlen(MM::NodeBehavior::IO_STR[1]), //epsilon (private)
  strlen(MM::NodeBehavior::IO_STR[2]), //in
  strlen(MM::NodeBehavior::IO_STR[3]), //out
  strlen(MM::NodeBehavior::IO_STR[4])  //inout
};

const MM::UINT32 MM::NodeBehavior::WHEN_LEN[] =
{
  strlen(MM::NodeBehavior::WHEN_STR[0]), //error
  strlen(MM::NodeBehavior::WHEN_STR[1]), //epsilon (passive)
  strlen(MM::NodeBehavior::WHEN_STR[2]), //auto
  strlen(MM::NodeBehavior::WHEN_STR[3]), //user
  strlen(MM::NodeBehavior::WHEN_STR[4])  //start
};

const MM::UINT32 MM::NodeBehavior::ACT_LEN[] =
{
  strlen(MM::NodeBehavior::ACT_STR[0]), //error
  strlen(MM::NodeBehavior::ACT_STR[1]), //epsilon (pull)
  strlen(MM::NodeBehavior::ACT_STR[2])  //push
};

const MM::UINT32 MM::NodeBehavior::HOW_LEN[] =
{
  strlen(MM::NodeBehavior::HOW_STR[0]), //error
  strlen(MM::NodeBehavior::HOW_STR[1]), //any
  strlen(MM::NodeBehavior::HOW_STR[2])  //all
};

MM::NodeBehavior::NodeBehavior(MM::NodeBehavior::IO io,
                               MM::NodeBehavior::When when,
                               MM::NodeBehavior::Act act,
                               MM::NodeBehavior::How how) : MM::Recyclable()
{
  this->io = io;
  this->when = when;
  this->act = act;
  this->how = how;
}

MM::NodeBehavior::~NodeBehavior()
{
  this->io = MM::NodeBehavior::IO_ERROR;
  this->when = MM::NodeBehavior::WHEN_ERROR;
  this->act = MM::NodeBehavior::ACT_ERROR;
  this->how = MM::NodeBehavior::HOW_ERROR;
}

MM::VOID MM::NodeBehavior::recycle(MM::Recycler * r)
{
  MM::Recyclable::recycle(r);
}

MM::TID MM::NodeBehavior::getTypeId()
{
  return MM::T_NodeBehavior;
}

MM::BOOLEAN MM::NodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_NodeBehavior)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

MM::NodeBehavior::IO MM::NodeBehavior::getIO()
{
  return io;
}

MM::NodeBehavior::When MM::NodeBehavior::getWhen()
{
  return when;
}

MM::NodeBehavior::Act MM::NodeBehavior::getAct()
{
  return act;
}

MM::NodeBehavior::How MM::NodeBehavior::getHow()
{
  return how;
}

MM::VOID  MM::NodeBehavior::setIO(MM::NodeBehavior::IO io)
{
  this->io = io;
}

MM::VOID MM::NodeBehavior::setWhen(MM::NodeBehavior::When when)
{
  this->when = when;
}

MM::VOID MM::NodeBehavior::setAct(MM::NodeBehavior::Act act)
{
  this->act = act;
}

MM::VOID MM::NodeBehavior::setHow(MM::NodeBehavior::How how)
{
  this->how = how;
}

MM::BOOLEAN MM::NodeBehavior::conformsTo(MM::NodeBehavior::IO direction)
{
  MM::BOOLEAN r = MM_FALSE;
  if(direction == MM::NodeBehavior::IO_IN)
  {
    if(io == MM::NodeBehavior::IO_INOUT || io == MM::NodeBehavior::IO_IN)
    {
      r = MM_TRUE;
    }
  }
  else if(direction == MM::NodeBehavior::IO_OUT)
  {
    if(io == MM::NodeBehavior::IO_INOUT || io == MM::NodeBehavior::IO_OUT)
    {
      r = MM_TRUE;
    }
  }  
  return r;
}

MM::VOID MM::NodeBehavior::step(MM::Node * node,
                                MM::Instance * i,
                                MM::Machine * m,
                                MM::Transition *tr)
{
  MM::Name * name = node->getName();
  MM::CHAR * buf = name->getBuffer();
  printf("STEP NODE %s\n", buf);
  
  MM::Vector<MM::Edge *> * work = MM_NULL;
  if(act == MM::NodeBehavior::ACT_PULL)
  {
    work = node->getInput();
  }
  else
  {
    work = node->getOutput();
  }
  
  if(how == MM::NodeBehavior::HOW_ANY)
  {
    stepAny(node, i, work, m, tr);
  }
  else
  {
    stepAll(node, i, work, m, tr);
  }
}



//process an all instance node
MM::VOID MM::NodeBehavior::stepAll(MM::Node * node,
                                   MM::Instance * i,
                                   MM::Vector<MM::Edge *> * work,
                                   MM::Machine * m,
                                   MM::Transition * tr)
{
  MM::Evaluator * evaluator = m->getEvaluator();
  
  MM::Vector<MM::Element *> es;
  MM::Vector<MM::Edge *>::Iterator edgeIter = work->getIterator();
  MM::BOOLEAN success = MM_TRUE;
  
  printf("STEP ALL NODE %s (%ld edges)\n",
         node->getName()->getBuffer(),
         work->size());
  
  while(edgeIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = edgeIter.getNext();
    MM::ValExp * valExp = evaluator->eval(i, edge); //chance plays into this!
    MM::INT32 flow = 0;
    
    if(valExp->getTypeId() == MM::T_NumberValExp)
    {
      flow = ((NumberValExp *) valExp)->getIntValue();
    }
    else if(valExp->getTypeId() == MM::T_RangeValExp)
    {
      flow = ((RangeValExp *) valExp)->getIntValue();
    }
    
    valExp->recycle(m);
    
    MM::Node * src = edge->getSource();
    MM::Node * tgt = edge->getTarget();
    
    if(flow > 0 &&
       i->hasResources(src, flow) == MM_TRUE &&
       i->hasCapacity(tgt, flow) == MM_TRUE)
    {
      MM::FlowEdge * edge = evaluator->synthesizeFlowEdge(i, src, flow, tgt);
      es.add(edge);
    }
    else
    {
      success = MM_FALSE;
      break;
    }
  }
  
  if(success == MM_TRUE)  //if we have computed a succesfull transition
  {
    MM::Vector<MM::Element *>::Iterator eIter = es.getIterator();
    while(eIter.hasNext() == MM_TRUE)
    {
      //store the transition
      MM::FlowEdge * edge = (MM::FlowEdge *) eIter.getNext();
      tr->addElement((MM::Element*)edge);
      
      //and apply the flow
      MM::Instance * i = edge->getInstance();
      MM::Node * src = edge->getSource();
      MM::Node * tgt = edge->getTarget();
      MM::NumberValExp * exp = (MM::NumberValExp *) edge->getExp();
      MM::UINT32 flow = exp->getIntValue();
      
      i->sub(src, flow);
      i->add(tgt, flow);
    }
  }
  else
  {
    MM::Vector<MM::Element *>::Iterator eIter = es.getIterator();
    while(eIter.hasNext() == MM_TRUE)
    {
      MM::Element * element = eIter.getNext();
      element->recycle(m);
    }
  }
}


//process an any instance node
MM::VOID MM::NodeBehavior::stepAny(MM::Node * node,
                                   MM::Instance * i,
                                   MM::Vector<MM::Edge *> * edges,
                                   MM::Machine * m,
                                   MM::Transition * tr)
{
  MM::Evaluator * evaluator = m->getEvaluator();

  //collect work
  MM::Vector<MM::Edge *> work;
  MM::Vector<MM::Edge *>::Iterator edgeIter = edges->getIterator();
  while(edgeIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = edgeIter.getNext();
    work.add(edge);
  }
  MM::UINT32 size = work.size();
  
  printf("STEP ANY NODE (%ld edges)\n", size);
  
  //process work
  while(size != 0)
  {
    MM::UINT32 randomPos = rand() % size;
    MM::Edge * edge = work.elementAt(randomPos);
    work.remove(edge);
    size = work.size();
    
    MM::ValExp * valExp = evaluator->eval(i, edge);    
    MM::INT32 flow = 0;
    
    if(valExp->getTypeId() == MM::T_NumberValExp)
    {
      flow = ((NumberValExp *) valExp)->getIntValue();
    }
    else if(valExp->getTypeId() == MM::T_RangeValExp)
    {
      flow = ((RangeValExp *) valExp)->getIntValue();
    }
    else
    {
      //TODO runtime exception
    }
    
    valExp->recycle(m);
    
    MM::Node * src = edge->getSource();
    MM::Node * tgt = edge->getTarget();
    
    if(flow > 0 &&
       i->hasResources(src, 1) == MM_TRUE &&
       i->hasCapacity(tgt, 1) == MM_TRUE)
    {
      if(i->hasResources(src, flow) == MM_TRUE)
      {
        if(i->hasCapacity(tgt, flow) == MM_TRUE)
        {
          printf("Full flow %ld\n", flow);
          i->sub(src, flow);
          i->add(tgt, flow);
          MM::FlowEdge * edge = evaluator->synthesizeFlowEdge(i, src, flow, tgt);
          tr->addElement(edge);
          
        }
        else
        {
          flow = i->getCapacity(tgt);
          printf("Flow up to capacity %ld\n", flow);
          i->sub(src, flow);
          i->add(tgt, flow);
          MM::FlowEdge * edge = evaluator->synthesizeFlowEdge(i, src, flow, tgt);
          tr->addElement(edge);
        }
      }
      else
      {
        flow = i->getResources(src);
        if(i->hasCapacity(tgt,flow) == MM_TRUE)
        {
          printf("Flow up to availability %ld\n", flow);
          i->sub(src, flow);
          i->add(tgt, flow);
          MM::FlowEdge * edge = evaluator->synthesizeFlowEdge(i, src, flow, tgt);
          tr->addElement(edge);
        }
        else
        {
          flow = i->getCapacity(tgt);
          printf("Flow up to capacity %ld\n", flow);
          i->sub(src, flow);
          i->add(tgt, flow);
          MM::FlowEdge * edge = evaluator->synthesizeFlowEdge(i, src, flow, tgt);
          tr->addElement(edge);
        }
      }
    }
  }
  
  /*
  MM::Vector<MM::Edge *> * aliases = node->getAliases();
  MM::Vector<MM::Edge *>::Iterator aliasIter = aliases->getIterator();
  while(aliasIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = aliasIter.getNext();
    MM::Node * aliasNode = edge->getTarget();
    aliasNode->activateTriggerTargets(i, e, r);
  }
   */
}

MM::VOID MM::NodeBehavior::activateTriggerTargets(MM::Node * node,
                                                  MM::Instance * i,
                                                  MM::Machine * m)
{
  MM::Evaluator * e = m->getEvaluator();
  MM::Vector<MM::Edge *> * triggers = node->getTriggers();
  MM::Vector<MM::Edge *>::Iterator tIter = triggers->getIterator();
  while(tIter.hasNext() == MM_TRUE)
  {
    MM::Edge * trigger = tIter.getNext();
    MM::Node * tgtNode = trigger->getTarget();
    
    //notify observers a trigger happened
    i->notifyObservers(i, MM_NULL, MM::MSG_TRIGGER, trigger);
    
    if(tgtNode->isDisabled(i, e, m) == MM_FALSE)
    {
      i->setActive(tgtNode);
    }
    else
    {
      i->setDisabled(tgtNode);
    }
  }
  
  MM::Vector<MM::Edge *> * aliases = node->getAliases();
  MM::Vector<MM::Edge *>::Iterator aIter = aliases->getIterator();
  while(aIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = aIter.getNext();
    MM::Node * aliasNode = edge->getTarget();
    aliasNode->activateTriggerTargets(i, m);
  }
}

MM::VOID MM::NodeBehavior::toString(MM::String * buf, MM::Name * name)
{
  if(io != MM::NodeBehavior::IO_PRIVATE)
  {
    buf->append((MM::CHAR*)MM::NodeBehavior::IO_STR[io],
                MM::NodeBehavior::IO_LEN[io]);
    buf->space();
  }
  if(when != MM::NodeBehavior::WHEN_PASSIVE)
  {
    buf->append((MM::CHAR*)MM::NodeBehavior::WHEN_STR[when],
              MM::NodeBehavior::WHEN_LEN[when]);
    buf->space();
  }
  if(act != MM::NodeBehavior::ACT_PULL)
  {
    buf->append((MM::CHAR*)MM::NodeBehavior::ACT_STR[act],
                MM::NodeBehavior::ACT_LEN[act]);
    buf->space();
  }
  if(how != MM::NodeBehavior::HOW_ANY)
  {
    buf->append((MM::CHAR*)MM::NodeBehavior::HOW_STR[how],
              MM::NodeBehavior::HOW_LEN[how]);
    buf->space();
  }
}