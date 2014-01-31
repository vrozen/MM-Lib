//
//  Pool.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
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

const MM::CHAR * MM::PoolNodeBehavior::POOL_STR = "pool";
const MM::CHAR * MM::PoolNodeBehavior::OF_STR   = "of";
const MM::CHAR * MM::PoolNodeBehavior::AT_STR   = "at";
const MM::CHAR * MM::PoolNodeBehavior::MAX_STR  = "max";
const MM::CHAR * MM::PoolNodeBehavior::ADD_STR  = "add";
const MM::CHAR * MM::PoolNodeBehavior::SELF_STR = "self";

const MM::UINT32 MM::PoolNodeBehavior::POOL_LEN =
  strlen(MM::PoolNodeBehavior::POOL_STR);
const MM::UINT32 MM::PoolNodeBehavior::OF_LEN =
  strlen(MM::PoolNodeBehavior::OF_STR);
const MM::UINT32 MM::PoolNodeBehavior::AT_LEN   =
  strlen(MM::PoolNodeBehavior::AT_STR);
const MM::UINT32 MM::PoolNodeBehavior::MAX_LEN  =
  strlen(MM::PoolNodeBehavior::MAX_STR);
const MM::UINT32 MM::PoolNodeBehavior::ADD_LEN  =
  strlen(MM::PoolNodeBehavior::ADD_STR);
const MM::UINT32 MM::PoolNodeBehavior::SELF_LEN =
  strlen(MM::PoolNodeBehavior::SELF_STR);

MM::PoolNodeBehavior::PoolNodeBehavior(MM::NodeBehavior::IO    io,
                                       MM::NodeBehavior::When  when,
                                       MM::NodeBehavior::Act   act,
                                       MM::NodeBehavior::How   how,
                                       MM::Name              * of,
                                       MM::UINT32              at,
                                       MM::UINT32              max,
                                       MM::Exp               * exp,
                                       MM::Map<MM::Name *, Node *, MM::Name::Compare> * interfaces):
  MM::NodeBehavior(io, when, act, how),
  MM::Observer()
{
  this->of = of;
  this->def = MM_NULL;
  this->at = at;
  this->max = max;
  this->exp = exp;
  this->interfaces = interfaces;
}

MM::PoolNodeBehavior::~PoolNodeBehavior()
{
  this->of = MM_NULL;
  this->def = MM_NULL;
  this->at = 0;
  this->max = 0;
  this->exp = MM_NULL;
  this->def = MM_NULL;
  this->interfaces = MM_NULL;
}

MM::VOID MM::PoolNodeBehavior::recycle(MM::Recycler *r)
{
  if(exp != MM_NULL)
  {
    exp->recycle(r);
  }
  if(of != MM_NULL)
  {
    of->recycle(r);
  }
  
  MM::Map<MM::Name *, MM::Node *, MM::Name::Compare>::Iterator i =
  interfaces->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Node * n = i.getNext();
    n->recycle(r);
  }
  delete interfaces; //TODO recycle

  MM::NodeBehavior::recycle(r);
}

MM::TID MM::PoolNodeBehavior::getTypeId()
{
  return MM::T_PoolNodeBehavior;
}

MM::BOOLEAN MM::PoolNodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_PoolNodeBehavior)
  {
    return MM_TRUE;
  }
  else if(MM::NodeBehavior::instanceof(tid) == MM_TRUE ||
          MM::Observer::instanceof(tid) == MM_TRUE)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::VOID MM::PoolNodeBehavior::update(MM::Observable * observable,
                                      MM::VOID * aux,
                                      MM::UINT32 message,
                                      MM::VOID * object)
{
  switch(message)
  {
    case MM::MSG_NEW_DRAIN:
    case MM::MSG_NEW_POOL:
    case MM::MSG_NEW_SOURCE:
    case MM::MSG_NEW_REF:
    case MM::MSG_NEW_GATE:
      addInterface((MM::Machine *) aux, (MM::Node *) object);
      break;
    case MM::MSG_DEL_DRAIN:
    case MM::MSG_DEL_POOL:
    case MM::MSG_DEL_SOURCE:
    case MM::MSG_DEL_REF:
    case MM::MSG_DEL_GATE:
      removeInterface((MM::Machine *) aux, (MM::Node *) object);
      break;
    default:
      //message not understood
      break;
  }
}

MM::Name * MM::PoolNodeBehavior::getTypeName()
{
  return of;
}

MM::VOID MM::PoolNodeBehavior::setDefinition(MM::Definition * def)
{
  this->def = def;
}

MM::Definition * MM::PoolNodeBehavior::getDefinition()
{
  return def;
}

MM::Node * MM::PoolNodeBehavior::getInterface(MM::Name * name)
{
  return interfaces->get(name);
}


MM::VOID MM::PoolNodeBehavior::addInterface(MM::Machine * m, MM::Node * node)
{
  if(node->getBehavior()->getIO() != MM::NodeBehavior::IO_PRIVATE)
  {
    MM::Name * name = node->getName();
    MM::CHAR * str = name->getBuffer();
    printf("Pool: Sees interface %s begin\n", str);
    
    MM::Name * clone = m->createName(name);
    
    //NOTE: declaration is MM_NULL
    //reasoning: we cannot resolve aliases to a specific instance
    //when an interfacenode is on a pool node
    MM::InterfaceNode * iNode = m->createInterfaceNode(clone, MM_NULL, node);
    
    interfaces->put(name, iNode);
    
    MM::Reflector * reflector = m->getReflector();
    reflector->init(iNode);
  }
}

MM::VOID MM::PoolNodeBehavior::removeInterface(MM::Machine * m, MM::Node * node)
{
  MM::Name * name = node->getName();
  if(interfaces->contains(name) == MM_TRUE)
  {
    printf("Pool: Sees interface end\n");
    MM::InterfaceNode * iNode = (MM::InterfaceNode *) interfaces->get(name);
    
    MM::Reflector * reflector = m->getReflector();
    
    //deinit input edges
    MM::Vector<MM::Edge *> * input = iNode->getInput();
    MM::Vector<MM::Edge *>::Iterator inputIter = input->getIterator();
    while(inputIter.hasNext() == MM_TRUE)
    {
      MM::Edge * edge = inputIter.getNext();
      reflector->deinit(def, edge);
    }
    
    //deinit output edges
    MM::Vector<MM::Edge *> * output = iNode->getOutput();
    MM::Vector<MM::Edge *>::Iterator outputIter = output->getIterator();
    while(outputIter.hasNext() == MM_TRUE)
    {
      MM::Edge * edge = outputIter.getNext();
      reflector->deinit(def, edge);
    }
    
    //deinit condition edges
    MM::Vector<MM::Edge *> * conditions = iNode->getConditions();
    MM::Vector<MM::Edge *>::Iterator conditionsIter = conditions->getIterator();
    while(conditionsIter.hasNext() == MM_TRUE)
    {
      MM::Edge * edge = conditionsIter.getNext();
      reflector->deinit(def, edge);
    }
    
    //deinit trigger edges
    MM::Vector<MM::Edge *> * triggers = iNode->getTriggers();
    MM::Vector<MM::Edge *>::Iterator triggersIter = triggers->getIterator();
    while(triggersIter.hasNext() == MM_TRUE)
    {
      MM::Edge * edge = triggersIter.getNext();
      reflector->deinit(def, edge);
    }
    
    //deinit alias edges
    MM::Vector<MM::Edge *> * aliases = iNode->getAliases();
    MM::Vector<MM::Edge *>::Iterator aliasesIter = aliases->getIterator();
    while(aliasesIter.hasNext() == MM_TRUE)
    {
      MM::Edge * edge = aliasesIter.getNext();
      reflector->deinit(def, edge);
    }
    
    iNode->recycle(m);
    interfaces->remove(name);
  }
}

MM::Name * MM::PoolNodeBehavior::getOf()
{
  return of;
}

MM::UINT32 MM::PoolNodeBehavior::getAt()
{
  return at;
}

MM::UINT32 MM::PoolNodeBehavior::getMax()
{
  return max;
}

MM::Exp * MM::PoolNodeBehavior::getAdd()
{
  return exp;
}

MM::VOID MM::PoolNodeBehavior::setAt(MM::UINT32 at)
{
  this->at = at;
}

MM::VOID MM::PoolNodeBehavior::setMax(MM::UINT32 max)
{
  this->max = max;
}

MM::VOID MM::PoolNodeBehavior::setAdd(MM::Exp * exp)
{
  this->exp = exp;
}

MM::UINT32 MM::PoolNodeBehavior::getCreateMessage()
{
  return MM::MSG_NEW_POOL;
}

MM::UINT32 MM::PoolNodeBehavior::getUpdateMessage()
{
  return MM::MSG_UPD_POOL;
}

MM::UINT32 MM::PoolNodeBehavior::getDeleteMessage()
{
  return MM::MSG_DEL_POOL;
}

MM::VOID MM::PoolNodeBehavior::stepPullAll(MM::Node * tgtNode,
                                           MM::Instance * tgtInstance,
                                           MM::Vector<MM::NodeWorkItem *> * work,
                                           MM::Machine * m,
                                           MM::Transition * tr)
{
  MM::Evaluator * evaluator = m->getEvaluator();
  
  MM::Vector<MM::Element *> es;
  MM::Vector<MM::NodeWorkItem *>::Iterator workIter = work->getIterator();
  MM::BOOLEAN success = MM_TRUE;
  
  MM::INT32 tempTgtCapacity = tgtInstance->getCapacity(tgtNode);
  
  printf("STEP PULL ALL NODE %s (%ld edges)\n",
         tgtNode->getName()->getBuffer(),
         work->size());
  
  while(workIter.hasNext() == MM_TRUE)
  {
    MM::NodeWorkItem * workItem = workIter.getNext();
    MM::Edge * edge = workItem->getEdge();
    MM::Exp * exp = edge->getExp();
    MM::Node * srcNode = workItem->getNode();
    MM::Instance * srcInstance = workItem->getInstance();
    MM::INT32 val = 0; //evaluated expression
    
    if(tgtInstance->isEvaluatedExp(exp) == MM_TRUE) //check if expression is pre-evaluated
    {
      val = tgtInstance->getEvaluatedExp(exp);
    }
    else
    {
      //NOTE: whatever is evaluated here will hold during this step
      //      since it is stored in evaluated expressions
      //      and chance plays into this!
      MM::ValExp * valExp = evaluator->eval(tgtInstance, edge);
      
      if(valExp->getTypeId() == MM::T_NumberValExp)
      {
        val = ((NumberValExp *) valExp)->getIntValue();
        tgtInstance->setEvaluatedExp(exp, val);
      }
      else if(valExp->getTypeId() == MM::T_RangeValExp)
      {
        val = ((RangeValExp *) valExp)->getIntValue();
        tgtInstance->setEvaluatedExp(exp, val);
      }
      else
      {
        //TODO runtime exception
      }
      
      valExp->recycle(m);
    }
    
    if(val > 0 &&
       srcInstance->hasResources(srcNode, val) == MM_TRUE &&
       (tempTgtCapacity - val) >= 0)
    {
      tempTgtCapacity -= val;
      MM::FlowEvent * event =
        m->createFlowEvent(srcInstance, srcNode, edge,
                           srcInstance, srcNode, val, tgtInstance, tgtNode);
      es.add(event);
    }
    else
    {
      success = MM_FALSE;
      break;
    }
  }
  
  //if we have computed a succesfull transition, then apply it
  if(success == MM_TRUE)
  {
    MM::Vector<MM::Element *>::Iterator eIter = es.getIterator();
    while(eIter.hasNext() == MM_TRUE)
    {
      //store the transition
      MM::FlowEvent * event = (MM::FlowEvent *) eIter.getNext();
      tr->addElement((MM::Element*)event);
      
      //and apply the flow
      MM::Instance * srcInstance = event->getSourceInstance();
      MM::Instance * tgtInstance = event->getTargetInstance();
      MM::Node * srcNode = event->getSourceNode();
      MM::Node * tgtNode = event->getTargetNode();
      MM::UINT32 flow = event->getAmount();
      printf("Full flow %ld\n", flow);
      
      srcInstance->sub(srcNode, m, flow);
      tgtInstance->add(tgtNode, m, flow);
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

MM::VOID MM::PoolNodeBehavior::stepPushAll(MM::Node * srcNode,
                                           MM::Instance * srcInstance,
                                           MM::Vector<MM::NodeWorkItem *> * work,
                                           MM::Machine * m,
                                           MM::Transition * tr)
{
  MM::Evaluator * evaluator = m->getEvaluator();
  
  MM::Vector<MM::Element *> es;
  MM::Vector<MM::NodeWorkItem *>::Iterator workIter = work->getIterator();
  MM::BOOLEAN success = MM_TRUE;
  
  MM::INT32 tempSrcAmount = srcInstance->getValue(srcNode);
  
  printf("STEP PUSH ALL NODE %s (%ld edges)\n",
         srcNode->getName()->getBuffer(),
         work->size());
  
  while(workIter.hasNext() == MM_TRUE)
  {
    MM::NodeWorkItem * workItem = workIter.getNext();
    MM::Edge * edge = workItem->getEdge();
    MM::Exp * exp = edge->getExp();
    MM::Node * tgtNode = workItem->getNode();
    MM::Instance * tgtInstance = workItem->getInstance();
    MM::INT32 val = 0; //evaluated expression
    
    if(srcInstance->isEvaluatedExp(exp) == MM_TRUE) //check if expression is pre-evaluated
    {
      val = srcInstance->getEvaluatedExp(exp);
    }
    else
    {
      //NOTE: whatever is evaluated here will hold during this step
      //      since it is stored in evaluated expressions
      //      and chance plays into this!
      MM::ValExp * valExp = evaluator->eval(srcInstance, edge);
      
      if(valExp->getTypeId() == MM::T_NumberValExp)
      {
        val = ((NumberValExp *) valExp)->getIntValue();
        srcInstance->setEvaluatedExp(exp, val);
      }
      else if(valExp->getTypeId() == MM::T_RangeValExp)
      {
        val = ((RangeValExp *) valExp)->getIntValue();
        srcInstance->setEvaluatedExp(exp, val);
      }
      else
      {
        //TODO runtime exception
      }
      
      valExp->recycle(m);
    }
    
    if(val > 0 &&
       tempSrcAmount - val >= 0 &&
       tgtInstance->hasCapacity(tgtNode,val) == MM_TRUE)
    {
      tempSrcAmount -= val;
      MM::FlowEvent * event =
      m->createFlowEvent(srcInstance, srcNode, edge,
                         srcInstance, srcNode, val, tgtInstance, tgtNode);
      es.add(event);
    }
    else
    {
      success = MM_FALSE;
      break;
    }
  }
  
  //if we have computed a succesfull transition, then apply it
  if(success == MM_TRUE)
  {
    MM::Vector<MM::Element *>::Iterator eIter = es.getIterator();
    while(eIter.hasNext() == MM_TRUE)
    {
      //store the transition
      MM::FlowEvent * event = (MM::FlowEvent *) eIter.getNext();
      tr->addElement((MM::Element*)event);
      
      //and apply the flow
      MM::Instance * srcInstance = event->getSourceInstance();
      MM::Instance * tgtInstance = event->getTargetInstance();
      MM::Node * srcNode = event->getSourceNode();
      MM::Node * tgtNode = event->getTargetNode();
      MM::UINT32 flow = event->getAmount();
      printf("Full flow %ld\n", flow);
      
      srcInstance->sub(srcNode, m, flow);
      tgtInstance->add(tgtNode, m, flow);
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

//what happens to an instance when a pool node is created
MM::VOID MM::PoolNodeBehavior::begin(MM::Instance * i,
                                     MM::Machine * m,
                                     MM::Node * n)
{
  if(of != MM_NULL && at != 0)
  {
    MM::Definition * def = i->getDefinition();
    MM::Element * unitDef = def->findDeclaredDefinition(of);
    if(unitDef != MM_NULL &&
       unitDef->instanceof(MM::T_Definition) == MM_TRUE)
    {
      i->createInstances(n, m, (MM::Definition *) unitDef, at);
    }
  }
  
  //hack:
  i->setValue(n, at);     //Begin before step
  i->setNewValue(n, at);  //Befin during step
}

MM::VOID MM::PoolNodeBehavior::end(MM::Instance * i,
                                   MM::Machine * m,
                                   MM::Node * n)
{
  //remove value
  i->deleteValue(n);
  
  //detroy instances
  i->destroyAllInstances(n, m);
}

MM::VOID MM::PoolNodeBehavior::change(MM::Instance * i,
                                      MM::Machine * m,
                                      MM::Node * n)
{
  //todo
  
  //add or remove instances
}

MM::VOID MM::PoolNodeBehavior::add(MM::Instance * i,
                                   MM::Machine  * m,
                                   MM::Node     * n,
                                   MM::UINT32     amount)
{
  //in case of instance pool: create instances
  if(of != MM_NULL)
  {
    MM::Definition * def = i->getDefinition();
    MM::Element * unitDef = def->findDeclaredDefinition(of);
    if(unitDef != MM_NULL &&
       unitDef->instanceof(MM::T_Definition) == MM_TRUE)
    {
      i->createInstances(n, m, (MM::Definition *) unitDef, amount);
    }
  }
  
  //add to new value
  MM::UINT32 newValue = i->getNewValue(n);
  newValue = newValue + amount;
  i->setNewValue(n, newValue);
}

MM::VOID MM::PoolNodeBehavior::sub(MM::Instance * i,
                                   MM::Machine  * m,
                                   MM::Node     * n,
                                   MM::UINT32     amount)
{
  //in case of instance pool: delete instances
  if(of != MM_NULL)
  {
    MM::Definition * def = i->getDefinition();
    MM::Element * unitDef = def->findDeclaredDefinition(of);
    if(unitDef != MM_NULL &&
       unitDef->instanceof(MM::T_Definition) == MM_TRUE)
    {
      i->destroyInstances(n, m, amount);
    }
  }
    
  //subtract from old value
  MM::UINT32 oldValue = i->getOldValue(n);
  oldValue = oldValue - amount;
  i->setOldValue(n, oldValue);
  
  //subtract from new value
  MM::UINT32 newValue = i->getNewValue(n);
  newValue = newValue - amount;
  i->setNewValue(n, newValue);

  //check if self is empty, which kills this instance
  /*MM::Name * poolName = n->getName();
  if(newValue == 0)
  {
    if(poolName->equals((MM::CHAR*)MM::PoolNodeBehavior::SELF_STR,
                      MM::PoolNodeBehavior::SELF_LEN) == MM_TRUE)
    {
      //inform parent instance of the demise of instance
      MM::Instance * parentInstance = i->getParent();
      parentInstance->destroyInstance(n, m, i);
    }
  }*/
}

MM::UINT32 MM::PoolNodeBehavior::getCapacity(MM::Instance * i,
                                             MM::Node     * n)
{
  return max - i->getNewValue(n);
}

MM::UINT32 MM::PoolNodeBehavior::getResources(MM::Instance * i,
                                              MM::Node     * n)
{
  return i->getOldValue(n);
}

MM::BOOLEAN MM::PoolNodeBehavior::hasCapacity(MM::Instance * i,
                                              MM::Node     * n,
                                              MM::UINT32     amount)
{
  MM::BOOLEAN r = MM_FALSE;
  if(max == 0)
  {
    r = MM_TRUE;
  }
  else
  {
    MM::UINT32 newValue = i->getNewValue(n);
    if(max - newValue >= amount)
    {
      r = MM_TRUE;
    }
  }
  return r;
}

MM::BOOLEAN MM::PoolNodeBehavior::hasResources(MM::Instance * i,
                                               MM::Node     * n,
                                               MM::UINT32     amount)
{
  MM::BOOLEAN r = MM_FALSE;
  MM::UINT32 oldValue = i->getOldValue(n);
  if(oldValue >= amount)
  {
    r = MM_TRUE;
  }
  return r;
}

MM::VOID MM::PoolNodeBehavior::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::PoolNodeBehavior::POOL_STR,
              MM::PoolNodeBehavior::POOL_LEN);
}

MM::VOID MM::PoolNodeBehavior::toString(MM::String * buf,
                                        MM::Name * name)
{
  MM::NodeBehavior::toString(buf, name);
  toString(buf);
  buf->space();
  name->toString(buf);
  if(of != MM_NULL)
  {
    buf->space();
    buf->append((MM::CHAR*)MM::PoolNodeBehavior::OF_STR,
                MM::PoolNodeBehavior::OF_LEN);
    buf->space();
    of->toString(buf);
  }  
  if(at!= 0)
  {
    buf->space();
    buf->append((MM::CHAR*)MM::PoolNodeBehavior::AT_STR,
                MM::PoolNodeBehavior::AT_LEN);
    buf->space();
    buf->appendInt(at);
  }
  if(max != 0)
  {
    buf->space();
    buf->append((MM::CHAR*)MM::PoolNodeBehavior::MAX_STR,
                MM::PoolNodeBehavior::MAX_LEN);
    buf->space();
    buf->appendInt(max);
  }
  if(exp != MM_NULL)
  {
    buf->space();
    buf->append((MM::CHAR*)MM::PoolNodeBehavior::ADD_STR,
                MM::PoolNodeBehavior::ADD_LEN);
    buf->space();
    exp->toString(buf);
  }
}
