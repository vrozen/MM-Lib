//
//  Machine.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/16/13.
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

const MM::UINT32 MM::Machine::LOG_SIZE = 1024 * 32 * 8;

MM::Machine::Machine() : MM::Recycler()
{
  reflector = new MM::Reflector(this);
  evaluator = new MM::Evaluator(this);
  log = createString(MM::Machine::LOG_SIZE);
  
  MM::Vector<MM::Element*> * elements = createElementVector();
  type = createDefinition(MM_NULL, elements);
  
  //create the initial state
  inst = createInstance(MM_NULL, type, MM_NULL);

  //let the state observe the global scope type
  type->addObserver(inst);
  
  //initialize the global scope type
  reflector->init(type);
  
  delegates = new MM::Vector<MM::Machine::InstanceObserver *>();
  
  //initialize the start state (set active nodes)
  //evaluator->initStartState(inst);
}

MM::Machine::~Machine()
{
  delete reflector;
  delete delegates;
  evaluator->recycle(this);
  inst->recycle(this);
  log->recycle(this);
  type->recycle(this);
}

MM::TID MM::Machine::getTypeId()
{
  return MM::T_Machine;
}

MM::BOOLEAN MM::Machine::instanceof(MM::TID tid)
{
  if(tid == MM::T_Machine)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recycler::instanceof(tid);
  }
}

extern MM::Program * MM_parse(const MM::CHAR * input);
extern MM::Program * MM_parseFile(const MM::CHAR * input);

MM::Reflector * MM::Machine::getReflector()
{
  return reflector;
}

MM::Evaluator * MM::Machine::getEvaluator()
{
  return evaluator;
}

MM::Definition * MM::Machine::getDefinition()
{
  return type;
}

MM::Instance * MM::Machine::getInstance()
{
  return inst;
}

MM::UINT32 MM::Machine::getDefinition(MM::UINT32 definition, //0-> global scope
                                      MM::CHAR * name)
{
  MM::Element * element = MM_NULL;
  MM::Definition * def = (MM::Definition *) definition;
  
  if(def == MM_NULL)
  {
    def = type;
  }
  
  MM::Name * n = createName(name);
  element = def->getElement(n);
  n->recycle(this);
  
  return (MM::UINT32) element;
}


MM::UINT32 MM::Machine::getInstance(MM::UINT32 instance, //0 -> global scope
                                    MM::CHAR  * name)
{
  MM::Instance * r = 0;
  
  if(instance == 0)
  {
    r = this->inst;
  }
  else
  {
    MM::Instance * i = (MM::Instance *) instance;
    MM::Definition * def = i->getDefinition();
    
    MM::Name * n = createName(name);
    MM::Element * e = def->getElement(n);
    n->recycle(this);
    
    if(e->instanceof(MM::T_Declaration) == MM_TRUE)
    {
      MM::Declaration * decl = (MM::Declaration *) e;
      r = i->getInstance(decl);
    }
  }
  return (MM::UINT32) r;
}

MM::VOID MM::Machine::getName (MM::UINT32   element,
                               MM::CHAR *   buffer,
                               MM::UINT32   bufferSize)
{
  MM::Element * e = (MM::Element *) element;
  MM::Name * n = e->getName();  
  MM::CHAR * buf = n->getBuffer();
  MM::UINT32 len = n->getLength();
  
  if(len <= bufferSize)
  {
    snprintf(buffer, bufferSize, "%s", buf);
  }
}

MM::VOID MM::Machine::activate(MM::UINT32 node,
                               MM::UINT32 instance)
{
  MM::Node * n = (MM::Node *) node;
  MM::Instance * i = (MM::Instance *) instance;
  i->setActive(n);
}

MM::VOID MM::Machine::step()
{
  MM::Transition * tr = createTransition();
  evaluator->step(tr);
  tr->recycle(this);
}

/*
MM::VOID MM::Machine::step (MM::CHAR * buf,
                            MM::UINT32 size)
{
  MM::Transition * tr = createTransition();
  evaluator->step(tr);
  MM::String * str = new MM::String(buf, size);
  tr->toString(str);  
  delete str;
  tr->recycle(this);
}

MM::VOID MM::Machine::step (MM::UINT32 instance,
                            MM::CHAR * buf,
                            MM::UINT32 size)
{
  MM::Instance * i = (MM::Instance *) instance;  
  MM::Transition * tr = createTransition();
  MM::String * str = new MM::String(buf, size);
  evaluator->step(i, tr);
  tr->toString(str);
  delete str;
  tr->recycle(this);
}
*/

MM::UINT32 MM::Machine::addObserver(MM::UINT32 instance,
                       //MM::VOID * caller,
                       MM::CALLBACK callback)
{
  MM::Machine::InstanceObserver * io =
    new MM::Machine::InstanceObserver((MM::Instance*)instance, callback);
  
  delegates->add(io);
  
  return 0;
}

MM::VOID MM::Machine::removeObserver (MM::UINT32 observer)
{
  MM::Machine::InstanceObserver * io =
    (MM::Machine::InstanceObserver *) observer;
  delegates->remove(io);
  delete io;
}

MM::String * MM::Machine::getLog()
{
  return log;
}

MM::VOID MM::Machine::eval (const MM::CHAR * input)
{
  MM::Program * program = MM_parseFile(input);
  MM::String * buf = createString(1024 * 100 * 32);
  program->toString(log); //store history
  
  MM::Vector<Transformation *> * ts = program->getTransformations();
  MM::Vector<Transformation *>::Iterator i = ts->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    Transformation * t = i.getNext();
    if(t->instanceof(MM::T_Modification) == MM_TRUE)
    {
      reflector->merge((MM::Modification *) t);
      MM::Definition * def = reflector->getDefinition();
      buf->clear();
      def->toString(buf);
      buf->print();
    }
  }
  
  /*
   MM::Instance * inst = reflector->getInstance();

  buf->clear();
  inst->toString(buf);
  buf->print();

  for(int i = 0; i < 10; i ++)
  {
    MM::Transition * tr = createTransition();
    evaluator->step(tr);
    tr->toString(log);
    
    inst->toString(log); //debug
    
    tr->recycle(this);
  }
  
  printf("\n\nHistory\n\n");
  log->print();
  */
  buf->recycle(this);
  program->recycle(this);
}

//MM::VOID MM::Machine::setTree (MM::Definition * def)
//{
  //this->def = def;
  //}

//MM::Element * MM::Machine::getTree()
//{
  //return def;
  //}

//MM::Definition * MM::Machine::getDefinition(MM::Name * name)
//{
//  return types->get(name);
//}

//MM::VOID MM::Machine::putDefinition(MM::Name * name, MM::Definition * def)
//{
  //types->put(name, def);
  //}

MM::Vector<MM::Transformation *> * MM::Machine::createTransformationVector()
{
  MM::Vector<MM::Transformation *> * v = new Vector<MM::Transformation *> ();
  //TODO: process vectors in recycler
  return v;
}

MM::Vector<MM::Element *> * MM::Machine::createElementVector()
{
  MM::Vector<MM::Element *> * v = new MM::Vector<MM::Element*> ();
  //TODO: process vectors in recycler
  return v;
}

MM::Vector<MM::Node *> * MM::Machine::createNodeVector()
{
  MM::Vector<MM::Node *> * v = new MM::Vector<MM::Node *> (); 
  //TODO: process vectors in recycler
  return v;
}

MM::Vector<MM::Edge *> * MM::Machine::createEdgeVector()
{
  MM::Vector<MM::Edge *> * v = new MM::Vector<MM::Edge *> ();
  //TODO: process vectors in recycler
  return v;  
}

MM::Map<MM::Name *, MM::Element *, MM::Name::Compare> * MM::Machine::createName2ElementMap()
{
  MM::Map<MM::Name *, MM::Element *, MM::Name::Compare> * n2e =
    new MM::Map<MM::Name *, MM::Element *, MM::Name::Compare>();
  //TODO: process maps in recylcer
  return n2e;
}

MM::Map<MM::Name *, MM::Node *, MM::Name::Compare> * MM::Machine::createName2NodeMap()
{
  MM::Map<MM::Name *, MM::Node *, MM::Name::Compare> * n2n =
  new MM::Map<MM::Name *, MM::Node *, MM::Name::Compare>();
  //TODO: process maps in recylcer
  return n2n;
}

MM::String * MM::Machine::createString(MM::UINT32 size)
{
  MM::CHAR * buffer = createBuffer(size+1);
  MM::String * str = new MM::String(buffer,size);
  MM::Recycler::create(str);
  return str;
}

MM::Location * MM::Machine::createLocation(YYLTYPE * loc)
{
  MM::Location * r = new MM::Location(loc->first_line,
                                      loc->first_column,
                                      loc->last_line,
                                      loc->last_column);
  MM::Recycler::create(r);
  return r;
}

MM::Name * MM::Machine::createName(MM::CHAR   * str,
                                   MM::UINT32 * len,
                                   MM::UINT32 * start,
                                   MM::UINT32 * end)
{
  MM::CHAR * buf = createBuffer(*len+1);
  strncpy(buf, str + *start, *len);
  MM::Name * n = new MM::Name(buf, *len);
  MM::Recycler::create(n);  
   *start += *len + 1;
  return n;
}

MM::VOID MM::Machine::eatWhiteSpace(MM::CHAR   * str,
                                    MM::UINT32 * start,
                                    MM::UINT32 * end)
{
  MM::BOOLEAN whitespace = MM_TRUE;
  while(whitespace == MM_TRUE)
  {
    switch(str[*start])
    {
      case ' ':
      case '\t':
      case '\f':
      case '\r':
        (*start)++;
        break;
      default:
        whitespace = MM_FALSE;
        break;
    }
    if(*start >= *end)
    {
      break;
    }
  }
}

MM::Name * MM::Machine::createName(MM::CHAR * str, YYLTYPE  * strLoc)
{
  MM::Name * name = MM_NULL;
  MM::Name * dotRoot = MM_NULL;
  MM::Name * colonRoot = MM_NULL;
  MM::Name * curName = MM_NULL;
  
  MM::UINT32 start = 0;
  MM::UINT32 end = strlen(str);

  do
  {
    MM::UINT32 len1 = strcspn(str + start, ".");
    MM::UINT32 len2 = strcspn(str + start, ":");
    if(len1 <= len2)
    {
      name = createName(str, &len1, &start, &end);
      if(curName != MM_NULL)
      {
        curName->setName(name);
      }
      if(dotRoot == MM_NULL)
      {
        dotRoot = name;
      }
      
      curName = name;
    }
    else
    {
      name = createName(str, &len2, &start, &end);
      if(curName != MM_NULL)
      {
        curName->setName(name);
      }
      if(dotRoot != MM_NULL)
      {
        colonRoot = dotRoot; 
      }
      else
      {
        colonRoot = name;
      }
      dotRoot = MM_NULL;
      curName = MM_NULL;
      eatWhiteSpace(str, &start, &end);
    }
    
  } while(start < end);

  MM::Location * loc = MM::Machine::createLocation(strLoc);
  dotRoot->setLocation(loc);
  dotRoot->setPreName(colonRoot);
  
  return dotRoot;
}

MM::Name * MM::Machine::createName(MM::Name * name)
{
  MM::CHAR * buf = name->getBuffer();
  MM::UINT32 len = name->getLength();
  
  MM::CHAR * buf2 = createBuffer(len+1);
  strncpy(buf2, buf, len);
  
  MM::Name * r = new MM::Name(buf2, len);
  
  MM::Recycler::create(r);
  
  return r;
}

MM::Name * MM::Machine::createName(MM::CHAR * buf)
{
  MM::UINT32 len = strlen(buf);
  MM::CHAR * buf2 = createBuffer(len+1);
  strncpy(buf2, buf, len);
  
  MM::Name * r = new MM::Name(buf2, len);
  
  MM::Recycler::create(r);
  
  return r;
}


MM::Program * MM::Machine::createProgram()
{
  MM::Vector<MM::Transformation *> *
  transformations = createTransformationVector();
  MM::Program * r = new MM::Program(transformations);
  MM::Recycler::create(r);
  return r;  
}

MM::Program * MM::Machine::createProgram(MM::Vector<MM::Transformation *> *
                                         transformations)
{
  MM::Program * r = new MM::Program(transformations);
  MM::Recycler::create(r);
  return r;
}

MM::Modification * MM::Machine::createModification()
{
  MM::Vector<MM::Element *> * elements = createElementVector();
  MM::Modification * r = new MM::Modification(elements);
  MM::Recycler::create(r);
  return r;
}

MM::Modification * MM::Machine::createModification(MM::Vector<MM::Element *> *
                                                   elements)
{
  MM::Modification * r = new MM::Modification(elements);
  MM::Recycler::create(r);
  return r;
}

MM::Modification * MM::Machine::createModification(MM::Vector<MM::Element *> *
                                                   elements,
                                                   YYLTYPE * modifyLoc)
{
  MM::Location * loc = createLocation(modifyLoc);
  MM::Modification * r = new MM::Modification(elements, loc);
  MM::Recycler::create(r);
  return r;
}

MM::Transition * MM::Machine::createTransition()
{
  MM::Vector<MM::Element *> * elements = createElementVector();
  
  MM::Transition * r = new MM::Transition(elements);
  MM::Recycler::create(r);
  return r;
}

MM::Transition * MM::Machine::createTransition(MM::Vector<MM::Element *> *
                                               elements)
{
  MM::Transition * r = new MM::Transition(elements);
  MM::Recycler::create(r);
  return r;
}

MM::Transition * MM::Machine::createTransition(MM::Vector<MM::Element *> *
                                               elements,
                                               YYLTYPE * stepLoc)
{
  MM::Location * loc = createLocation(stepLoc);
  MM::Transition * r = new MM::Transition(elements, loc);
  MM::Recycler::create(r);
  return r;
}

MM::FlowEvent * MM::Machine::createFlowEvent(MM::Instance * actInstance,
                                             MM::Node     * actNode,
                                             MM::Edge     * actEdge,
                                             MM::Instance * srcInstance,
                                             MM::Node     * srcNode,
                                             MM::UINT32     amount,
                                             MM::Instance * tgtInstance,
                                             MM::Node     * tgtNode)
{
  MM::FlowEvent * r = new MM::FlowEvent(actInstance, actNode, actEdge,
                                        srcInstance, srcNode,
                                        amount,
                                        tgtInstance, tgtNode);
  MM::Recycler::create(r);
  return r;
}

MM::Node * MM::Machine::createSourceNode(MM::NodeBehavior::IO   io,
                                         MM::NodeBehavior::When when,
                                         MM::Name             * name)
{
  MM::SourceNodeBehavior * behavior =
    new MM::SourceNodeBehavior(io,when);
  MM::Recycler::create(behavior);
  MM::Node * r = new MM::Node(name, behavior);
  MM::Recycler::create(r);
  return r;
}

MM::Node * MM::Machine::createDrainNode(MM::NodeBehavior::IO    io,
                                        MM::NodeBehavior::When  when,
                                        MM::NodeBehavior::How   how,
                                        MM::Name      * name)
{
  MM::DrainNodeBehavior * behavior =
    new MM::DrainNodeBehavior(io,when,how);
  MM::Recycler::create(behavior);
  MM::Node * r = new MM::Node(name,behavior);
  MM::Recycler::create(r);
  return r;
}

MM::Node * MM::Machine::createGateNode(MM::NodeBehavior::IO    io,
                                       MM::NodeBehavior::When  when,
                                       MM::NodeBehavior::Act   act,
                                       MM::NodeBehavior::How   how,
                                       MM::Name      * name)
{
  MM::GateNodeBehavior * behavior =
    new MM::GateNodeBehavior(io,when,act,how);
  MM::Recycler::create(behavior);
  
  MM::Node * r = new MM::Node(name, behavior);
  MM::Recycler::create(r);
  return r;
}

MM::Node * MM::Machine::createPoolNode(MM::NodeBehavior::IO    io,
                                       MM::NodeBehavior::When  when,
                                       MM::NodeBehavior::Act   act,
                                       MM::NodeBehavior::How   how,
                                       MM::Name      * name,
                                       MM::Name      * of,
                                       MM::UINT32      at,
                                       MM::UINT32      max,
                                       MM::Exp       * exp)
{
  MM::Map<MM::Name *, MM::Node *, MM::Name::Compare> * interfaces =
  createName2NodeMap();
  
  MM::PoolNodeBehavior * behavior =
    new MM::PoolNodeBehavior(io,when,act,how,of,at,max,exp,interfaces);
  MM::Recycler::create(behavior);
  
  MM::Node * r = new MM::Node(name, behavior);
  MM::Recycler::create(r);
  return r;
}

MM::Node * MM::Machine::createConverterNode(MM::NodeBehavior::IO    io,
                                            MM::NodeBehavior::When  when,
                                            MM::Name      * name,
                                            MM::Name      * from,
                                            MM::Name      * to)
{
  MM::ConverterNodeBehavior * behavior =
    new MM::ConverterNodeBehavior(io, when, from, to);
  MM::Recycler::create(behavior);
  
  MM::Node * r = new MM::Node(name, behavior);
  //converter does not own edges
  r->setEdgeOwnership(MM_FALSE);
  MM::Recycler::create(r);
  return r;
}

MM::Node * MM::Machine::createRefNode(MM::NodeBehavior::IO io, MM::Name * name)
{
  MM::RefNodeBehavior * behavior = new MM::RefNodeBehavior(io);
  MM::Recycler::create(behavior);
  MM::Node * r = new MM::Node(name, behavior);
  MM::Recycler::create(r);
  return r;
}


MM::InterfaceNode * MM::Machine::createInterfaceNode(MM::Name * name,
                                                     MM::Element * parent,
                                                     MM::Node * ref)
{
  MM::InterfaceNode * r = new MM::InterfaceNode(name, parent, ref);
  MM::Recycler::create(r);
  return r;
}

MM::StateEdge * MM::Machine::createStateEdge(MM::Name * name,
                                             MM::Name * src,
                                             MM::Exp  * exp,
                                             MM::Name * tgt)
{
  MM::StateEdge * r = new MM::StateEdge(name,src,exp,tgt);
  MM::Recycler::create(r);
  return r;
}

MM::StateEdge * MM::Machine::createAnonymousTriggerEdge(MM::Node * src,
                                                        MM::Node * tgt)
{
  MM::Exp * e1 = createOneExp();
  MM::Exp * e2 = createOneExp();
  MM::Exp * exp = createBinExp(e1, MM::Operator::OP_MUL, e2);
  
  MM::Name * srcName = src->getName();
  MM::Name * tgtName = tgt->getName();
  
  MM::Name * triggerSrcName = createName(srcName);
  MM::Name * triggerTgtName = createName(tgtName);
  
  MM::StateEdge * triggerEdge = createStateEdge(MM_NULL, triggerSrcName, exp, triggerTgtName);
  triggerEdge->setSource(src);
  triggerEdge->setTarget(tgt);
  return triggerEdge;
}

MM::FlowEdge * MM::Machine::createFlowEdge(MM::Name * name,
                                           MM::Name * src,
                                           MM::Exp  * exp,
                                           MM::Name * tgt)
{
  MM::FlowEdge * r = new MM::FlowEdge(name,src,exp,tgt);
  MM::Recycler::create(r);
  return r;
}

MM::Definition * MM::Machine::createDefinition()
{
  MM::Vector<Element*> * elements = createElementVector();  
  MM::Definition * r = new MM::Definition(MM_NULL, elements);
  MM::Recycler::create(r);
  return r;
}

MM::Definition * MM::Machine::createDefinition(MM::Name * name,
                                               MM::Vector<Element*> * elements)
{
  MM::Definition * r = new MM::Definition(name, elements);
  MM::Recycler::create(r);
  return r;
}


MM::Declaration * MM::Machine::createDeclaration(MM::Name * type,
                                                 MM::Name * name)
{
  MM::Map<MM::Name *, MM::Node *, MM::Name::Compare> * interfaces =
    createName2NodeMap();
  MM::Declaration * r = new MM::Declaration(type, name, interfaces);
  MM::Recycler::create(r);
  return r;
}

MM::Assertion * MM::Machine::createAssertion(YYLTYPE  * assertLoc,
                                             MM::Name * name,
                                             MM::Exp  * exp,
                                             MM::CHAR * msg)
{
  MM::Location * loc = MM::Machine::createLocation(assertLoc);
  MM::UINT32 len = strlen(msg);

  MM::CHAR * buf = MM::Recycler::createBuffer(len+1);
  strncpy(buf, msg, len);
  MM::Assertion * r = new MM::Assertion(name,exp,buf,loc);
  
  MM::Recycler::create(r);
  return r;
}

MM::Assertion * MM::Machine::createAssertion(MM::Name * name,
                                             MM::Exp  * exp,
                                             MM::CHAR * msg)
{
  MM::UINT32 len = strlen(msg);
  MM::CHAR * buf = MM::Recycler::createBuffer(len+1);
  strncpy(buf, msg, len);
  MM::Assertion * r = new MM::Assertion(name,exp,buf);
  
  MM::Recycler::create(r);
  return r;
}

MM::Deletion * MM::Machine::createDeletion(YYLTYPE * deleteLoc,
                                           MM::Name * name)
{
  MM::Location * loc = MM::Machine::createLocation(deleteLoc);
  MM::Deletion * r = new MM::Deletion(loc, name);
  MM::Recycler::create(r);
  return r;
}

MM::Activation * MM::Machine::createActivation(YYLTYPE * deleteLoc,
                                             MM::Name * name)
{
  MM::Location * loc = MM::Machine::createLocation(deleteLoc);
  MM::Activation * r = new MM::Activation(loc, name);
  MM::Recycler::create(r);
  return r;
}

MM::Activation * MM::Machine::createActivation(MM::Name * name)
{
  MM::Activation * r = new MM::Activation(name);
  MM::Recycler::create(r);
  return r;
}

MM::Deletion * MM::Machine::createDeletion(MM::Name * name)
{
  MM::Deletion * r = new MM::Deletion(name);
  MM::Recycler::create(r);
  return r;
}


MM::Signal * MM::Machine::createSignal(MM::Name * name)
{
  MM::Signal * r = new MM::Signal(name);
  MM::Recycler::create(r);
  return r;
}

MM::Signal * MM::Machine::createSignal(YYLTYPE * signalLoc,
                                       MM::Name * name)
{
  MM::Location * loc = MM::Machine::createLocation(signalLoc);
  MM::Signal * r = new MM::Signal(loc, name);
  MM::Recycler::create(r);
  return r;  
}

MM::UnExp * MM::Machine::createUnExp(MM::Operator::OP  op,
                                     YYLTYPE         * opLoc,
                                     MM::Exp         * exp)
{
  MM::Location * loc = MM::Machine::createLocation(opLoc);
  MM::UnExp * r = new MM::UnExp(op, exp, loc);
  MM::Recycler::create(r);
  return r;
}

MM::UnExp * MM::Machine::createUnExp(MM::Operator::OP  op,
                                     MM::Exp         * exp)
{
  MM::UnExp * r = new MM::UnExp(op, exp);
  MM::Recycler::create(r);
  return r;
}

MM::BinExp * MM::Machine::createBinExp(MM::Exp          * e1,
                                       MM::Operator::OP   op,
                                       YYLTYPE          * opLoc,
                                       MM::Exp          * e2)
{
  MM::Location * loc = MM::Machine::createLocation(opLoc);
  MM::BinExp * r = new MM::BinExp(e1,op,e2,loc);
  MM::Recycler::create(r);
  return r;
}


MM::BinExp * MM::Machine::createBinExp(MM::Exp          * e1,
                                       MM::Operator::OP   op,
                                       MM::Exp          * e2)
{
  MM::BinExp * r = new MM::BinExp(e1,op,e2);
  MM::Recycler::create(r);
  return r;
}

MM::OverrideExp * MM::Machine::createOverrideExp(MM::Exp * e)
{
  MM::OverrideExp * r = new MM::OverrideExp(e);
  MM::Recycler::create(r);
  return r;
}

MM::OverrideExp * MM::Machine::createOverrideExp(YYLTYPE * lparenLoc,
                                                 MM::Exp * e,
                                                 YYLTYPE * rparenLoc)
{
  MM::Location * loc1 = createLocation(lparenLoc);
  MM::Location * loc2 = createLocation(rparenLoc);
  MM::OverrideExp * r = new MM::OverrideExp(loc1, e, loc2);
  MM::Recycler::create(r);
  return r;
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
  MM::RangeValExp * r = new MM::RangeValExp(v1, v2, v1_loc, range_loc, v2_loc);
  MM::Recycler::create(r);
  return r;
}

MM::RangeValExp * MM::Machine::createRangeValExp(MM::INT32   v1,
                                                 MM::INT32   v2)
{
  MM::RangeValExp * r = new MM::RangeValExp(v1, v2);
  MM::Recycler::create(r);
  return r;
}

MM::NumberValExp * MM::Machine::createNumberValExp(MM::INT32  val,
                                                   YYLTYPE  * valLoc)
{
  MM::Location * loc = MM::Machine::createLocation(valLoc);  
  MM::NumberValExp * r = new MM::NumberValExp(val/100, val%100, loc);
  MM::Recycler::create(r);
  return r;
}

MM::NumberValExp * MM::Machine::createNumberValExp(MM::INT32 val)
{
  MM::NumberValExp * r = new MM::NumberValExp(val/100, val%100);
  MM::Recycler::create(r);
  return r;
}


MM::BooleanValExp * MM::Machine::createBooleanValExp(MM::BOOLEAN val,
                                                     YYLTYPE * valLoc)
{
  MM::Location * loc = MM::Machine::createLocation(valLoc);
  MM::BooleanValExp * r = new MM::BooleanValExp(val, loc);
  MM::Recycler::create(r);
  return r;
};

MM::BooleanValExp * MM::Machine::createBooleanValExp(MM::BOOLEAN val)
{
  MM::BooleanValExp * r = new MM::BooleanValExp(val, MM_NULL);
  MM::Recycler::create(r);
  return r;
};

MM::AllExp * MM::Machine::createAllExp(YYLTYPE * allLoc)
{
  MM::Location * loc = MM::Machine::createLocation(allLoc);
  MM::AllExp * r = new MM::AllExp(loc);
  MM::Recycler::create(r);
  return r;
};

MM::ActiveExp * MM::Machine::createActiveExp(YYLTYPE  * activeLoc,
                                             MM::Name * name)
{
  MM::Location * loc = MM::Machine::createLocation(activeLoc);
  MM::ActiveExp * r = new MM::ActiveExp(name,loc);
  MM::Recycler::create(r);
  return r;
}

MM::AliasExp * MM::Machine::createAliasExp(YYLTYPE * aliasLoc)
{
  MM::Location * loc = createLocation(aliasLoc);
  MM::AliasExp * r = new MM::AliasExp(loc);
  MM::Recycler::create(r);
  return r;
}

MM::OneExp * MM::Machine::createOneExp()
{
  MM::OneExp * r = new MM::OneExp(MM_NULL);
  MM::Recycler::create(r);
  return r;
}

MM::OneExp * MM::Machine::createOneExp(YYLTYPE * epsilonLoc)
{
  MM::Location * loc = createLocation(epsilonLoc);
  MM::OneExp * r = new MM::OneExp(loc);
  MM::Recycler::create(r);
  return r;
}

MM::VarExp * MM::Machine::createVarExp(MM::Name * name)
{
  MM::VarExp * r = new MM::VarExp(name);
  MM::Recycler::create(r);
  return r;
}

MM::Instance * MM::Machine::createInstance(MM::Instance * parent,
                                           MM::Definition * def,
                                           MM::Element * decl)
{
  MM::Instance * instance = new MM::Instance(parent, def, decl);
  MM::Recycler::create(instance);
  return instance;
}