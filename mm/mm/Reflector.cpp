//
//  reflector.cpp
//  mm
//
//  Created by Riemer van Rozen on 9/29/13.
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
#include "Instance.h"
#include "Reflector.h"
#include "Evaluator.h"
#include "Machine.h"

MM::Reflector::Reflector(MM::Machine * m)
{
  this->m = m;
}

MM::Reflector::~Reflector()
{
  this->m = MM_NULL;
}

MM::TID MM::Reflector::getTypeId()
{
  return MM::T_Reflector;
}

MM::BOOLEAN MM::Reflector::instanceof(MM::TID tid)
{
  if(tid == MM::T_Reflector)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::Definition * MM::Reflector::getDefinition()
{
  return m->getDefinition();
}

MM::Instance * MM::Reflector::getInstance()
{
  return m->getInstance();
}

//Merge a delta with the global type
MM::VOID MM::Reflector::merge(MM::Modification * modification)
{

  //merge the global scope type with the delta
  
  MM::Vector<Element *> * elements = modification->getElements();
  MM::Vector<Element *>::Iterator i = elements->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Element * e = i.getNext();
    
    printf("Merge: merging ");
    if(e->getName() != MM_NULL)
    {
      e->getName()->print();
    }
    printf(".\n");
    merge(m->getDefinition(), e);
  }
  
  modification->clearElements();
  
}

MM::VOID MM::Reflector::addElement(MM::Definition * def,
                                   MM::Element * element)
{
  MM::Name * name = element->getName();
  MM::Element * e1 = MM_NULL;

  if(name != MM_NULL)
  {
    e1 = def->getElement(name);
  }
  
  //if element exists in the definition
  if(e1 != MM_NULL)
  {
    //replace the existing element
    replace(def, e1, element);
  }
  else
  {
    //otherwise add the new element and  initialize
    def->addElement(element);
    init(def, element);
  }
}

//deinitialize an element and remove it
MM::VOID MM::Reflector::removeElement(MM::Definition * def,
                                      MM::Element * element)
{
  deinit(def, element);
}

//------------------------------------------------------------------------------
//Merge visitor
//Merges an element into an existing type
//Traverses the name space searching for the correct definition
//------------------------------------------------------------------------------
//merge element into root
MM::VOID MM::Reflector::merge(MM::Definition * root,
                              MM::Element * element)
{
  MM::Definition * def = MM_NULL;
  MM::Element * found = MM_NULL;
  
  MM::CHAR * buf = MM_NULL;
  MM::Name * name = element->getName();
  if(name != MM_NULL)
  {
    buf = name->getBuffer();
  }
  
  if(element->getTypeId() == MM::T_Definition)
  {    
    printf("Merge: Merge definition %s into parent type definition\n", buf);
    merge(root, (MM::Definition *) element);
  }
  else
  {
    printf("Merge: Merge element %s into parent type definition\n", buf);
    if(navigate(root, element, &def, &found) == MM_TRUE)
    {
      if(found == MM_NULL)
      {
        printf("Merge: Element %s is new in type: add and initialize\n", buf);
        
        def->addElement(element);
        init(def, element);
      }
      else
      {
        printf("Merge: Element %s exists in type: replace it\n", buf);
        replace(def, found, element);
      }
    }
  }
}

//merge type definition into root
MM::VOID MM::Reflector::merge(MM::Definition * root,
                              MM::Definition * type)
{
  MM::Definition * def = MM_NULL;
  MM::Element * found = MM_NULL;
  
  if(navigate(root, type, &def, &found) == MM_TRUE)
  {
    printf("Merge: Navigated to type definition.\n");
    if(found == MM_NULL)
    {
      printf("Merge: Adding new type definition %s to parent definition.\n",
             type->getName()->getBuffer());
      def->addElement(type);
      init(root,type);
    }
    else
    {
      printf("Merge: Merging type definitions %s\n",
             found->getName()->getBuffer());
      
      //2b. definition is not new update elements and add elements
      MM::Vector<Element *> * elements = type->getElements();
      MM::Vector<Element *>::Iterator i = elements->getIterator();
      while(i.hasNext() == MM_TRUE)
      {
        MM::Element * e = i.getNext();
        merge(def, e);
      }
      type->clearElements();
      type->recycle(m);
    }
  }
}

MM::BOOLEAN MM::Reflector::navigate(MM::Definition  * root,  //type to search in
                                    MM::Element     * element,
                                    MM::Definition ** def,   //found def
                                    MM::Element    ** found) //found element
{
  MM::Definition * type = root;       //start searching for types here
  MM::Name * rootName = MM_NULL;      //store name root
  MM::Name * curName = MM_NULL;       //name cursor for navigation
  MM::Name * lastName = MM_NULL;      //previous name
  MM::Element * curElement = MM_NULL; //element cursor for navigation
  MM::BOOLEAN success = MM_FALSE;     //return value
    
  if(element != MM_NULL)
  {
    rootName = element->getName();
    curName = element->getName();
    
    //HACK
    if(curName == MM_NULL)
    {
      success = MM_TRUE;
    }
    //END HACK
    
    while(curName != MM_NULL)
    {
      printf("Navigate: Navigating to %s\n", curName->getBuffer());      
      curElement = type->getElement(curName);
      
      if(curElement != MM_NULL && curElement->getTypeId() == MM::T_Definition)
      {
        printf("Navigate: Navigating into type %s\n",
               curElement->getName()->getBuffer());
        
        //parent is a definition, keep searching
        type = (MM::Definition *) curElement;
        
        if(curName->getName() == MM_NULL)
        {
          //we found a definitions
          printf("Navigate: Found definition %s\n", curName->getBuffer());
          success = MM_TRUE;
          break;
        }
      }
      else
      {
        //element is not a definition
        if(curName->getName() == MM_NULL)
        {
          printf("Navigate: Found element %s\n", curName->getBuffer());
          
          //e1 == MM_NULL --> name denotes a new element
          //e1 != MM_NULL --> element will be replaced
          success = MM_TRUE;
        }
        break;
      }
    
      lastName = curName;
      curName = curName->getName();
    }
  }

  if(success == MM_TRUE)
  {
    //clean unused name part
    if(lastName != MM_NULL)
    {
      lastName->setName(MM_NULL);
      rootName->recycle(m);
    }
    printf("Navigate: Success\n");
    element->setName(curName);
    * def = type;
    * found = curElement;
    success = MM_TRUE;
  }
  else
  {
    //TODO: error
    printf("Navigate: Error\n");
  }
  
  return success;
}

//------------------------------------------------------------------------------
//Init visitor
//initialize an element inside a definition
//------------------------------------------------------------------------------
//initialize a complete definition
MM::VOID MM::Reflector::init(MM::Definition * def)
{
  MM::Vector<MM::Node *> * pullAllNodes = m->createNodeVector();
  MM::Vector<MM::Node *> * pullAnyNodes = m->createNodeVector();
  MM::Vector<MM::Node *> * pushAllNodes = m->createNodeVector();
  MM::Vector<MM::Node *> * pushAnyNodes = m->createNodeVector();
  
  MM::Map<MM::Name *, MM::Element *, MM::Name::Compare> * n2e =
    m->createName2ElementMap();
  
  MM::Vector<Element *> * elements = def->getElements();
  MM::Vector<MM::Element *>::Iterator i = elements->getIterator();
  
  def->setPullAllNodes(pullAllNodes);
  def->setPullAnyNodes(pullAnyNodes);
  def->setPushAllNodes(pushAllNodes);
  def->setPushAnyNodes(pushAnyNodes);
  def->setNameToElementMap(n2e);
  
  //init types
  for(i.reset(); i.hasNext() == MM_TRUE; )
  {
    MM::Element * e = i.getNext();
    if(e->getTypeId() == MM::T_Definition)
    {
      init(def, (MM::Definition *) e);
    }
  }
  
  //init nodes
  for(i.reset(); i.hasNext() == MM_TRUE; )
  {
    MM::Element * e = i.getNext();
    if(e->instanceof(MM::T_Node) == MM_TRUE)
    {
      init(def, (MM::Node *) e);
    }
  }
  
  //init edges
  for(i.reset(); i.hasNext() == MM_TRUE; )
  {
    MM::Element * e = i.getNext();
    if(e->instanceof(MM::T_Edge) == MM_TRUE)
    {
      init(def, (MM::Edge *) e);
    }
  }
  
  //init declarations
  for(i.reset(); i.hasNext() == MM_TRUE; )
  {
    MM::Element * e = i.getNext();
    if(e->getTypeId() == MM::T_Declaration)
    {
      init(def, (MM::Declaration *) e);
    }
  }
  
  //init assertions
  for(i.reset(); i.hasNext() == MM_TRUE; )
  {
    MM::Element * e = i.getNext();
    if(e->getTypeId() == MM::T_Assertion)
    {
      init(def, (MM::Assertion *) e);
    }
  }
  
  //init deletions (does not make sense but okay let's be thorough)
  for(i.reset(); i.hasNext() == MM_TRUE; )
  {
    MM::Element * e = i.getNext();
    if(e->getTypeId() == MM::T_Deletion)
    {
      init(def, (MM::Deletion *) e);
    }
  }
}

MM::VOID MM::Reflector::init(MM::Definition * def, MM::Element * element)
{
  if(element->instanceof(MM::T_Node) == MM_TRUE)
  {
    return init(def, (MM::Node *) element);
  }
  else if(element->instanceof(MM::T_Edge) == MM_TRUE)
  {
    return init(def, (MM::Edge *) element);
  }
  else
  {
    switch(element->getTypeId())
    {
      case MM::T_Assertion:
        init(def, (MM::Assertion *) element);
        break;
      case MM::T_Deletion:
        init(def, (MM::Deletion *) element);
        break;
      case MM::T_Declaration:
        init(def, (MM::Declaration *) element);
        break;
      case MM::T_Definition:
        init(def, (MM::Definition *) element);
        break;
      default:
        //TODO: error
        break;
    }
  }
}

MM::VOID MM::Reflector::init(MM::Definition * def, MM::Node * node)
{
  //store node by name
  MM::Name * name = node->getName();
  def->putElement(name, node);
  
  if(name->getName() != MM_NULL)
  {
    //TODO: error
    printf("Error: required simple name, found query\n");
  }
  
  init(node);
  
  def->prioritize(node);
  
  MM::NodeBehavior * behavior = node->getBehavior();
  
  //initialize node specifically
  switch(behavior->getTypeId())
  {
    case MM::T_PoolNodeBehavior:
      init(def, node, (PoolNodeBehavior *) behavior);
      break;
    case MM::T_DrainNodeBehavior:
      init(def, node, (MM::DrainNodeBehavior *) behavior);
      break;
    case MM::T_SourceNodeBehavior:
      init(def, node, (MM::SourceNodeBehavior *) behavior);
      break;
    case MM::T_RefNodeBehavior:
      init(def, node, (MM::RefNodeBehavior *) behavior);
      break;
    case MM::T_GateNodeBehavior:
      init(def, node, (MM::GateNodeBehavior *) behavior);
      break;
    case MM::T_ConverterNodeBehavior:
      init(def, node, (MM::ConverterNodeBehavior *) behavior);
      break;
    default:
      break;
  }
}

MM::VOID MM::Reflector::init(MM::Node * node)
{
  MM::Vector<MM::Edge *> * input = m->createEdgeVector();
  MM::Vector<MM::Edge *> * output = m->createEdgeVector();
  MM::Vector<MM::Edge *> * conditions = m->createEdgeVector();
  MM::Vector<MM::Edge *> * triggers = m->createEdgeVector();
  MM::Vector<MM::Edge *> * aliases = m->createEdgeVector();
  
  node->setInput(input);
  node->setOutput(output);
  node->setConditions(conditions);
  node->setTriggers(triggers);
  node->setAliases(aliases);
}

MM::VOID MM::Reflector::init(MM::Definition * def,
                             MM::Node * node,
                             MM::PoolNodeBehavior * behavior)
{
  def->notifyObservers(def, m, MSG_NEW_POOL, node);
}

MM::VOID MM::Reflector::init(MM::Definition * def,
                             MM::Node * node,
                             MM::SourceNodeBehavior * behavior)
{
  def->notifyObservers(def, m, MSG_NEW_SOURCE, node);
}

MM::VOID MM::Reflector::init(MM::Definition * def,
                             MM::Node * node,
                             MM::DrainNodeBehavior * behavior)
{
  def->notifyObservers(def, m, MSG_NEW_DRAIN, node);
}

MM::VOID MM::Reflector::init(MM::Definition * def,
                             MM::Node * node,
                             MM::GateNodeBehavior * behavior)
{
  def->notifyObservers(def, m, MSG_NEW_GATE, node);
}


MM::VOID MM::Reflector::init(MM::Definition * def,
                             MM::Node * node,
                             MM::RefNodeBehavior * behavior)
{
  def->notifyObservers(def, m, MSG_NEW_REF, node);
}

MM::VOID MM::Reflector::init(MM::Definition * def,
                             MM::Node * node,
                             MM::ConverterNodeBehavior * behavior)
{
  def->notifyObservers(def, m, MSG_NEW_CONVERTER, node);
}


MM::VOID MM::Reflector::init(MM::Definition * def, MM::Edge * edge)
{
  //FIXME: interfaces on declarations  //FIXED?
  
  //resolve src and tgt to nodes
  MM::Name * srcName = edge->getSourceName();
  MM::Name * tgtName = edge->getTargetName();

  MM::Node * srcNode = def->findNode(srcName, MM::NodeBehavior::IO_OUT);
  MM::Node * tgtNode = def->findNode(tgtName, MM::NodeBehavior::IO_IN);
  
  if(srcNode != MM_NULL)
  {
    edge->setSource(srcNode);
  }
  else
  {
    //TODO: error
    printf("Error: source node of edge not found\n");
  }
  
  if(tgtNode != MM_NULL)
  {
    edge->setTarget(tgtNode);
  }
  else
  {
    //TODO: error
    printf("Error: target node of edge not found\n");
  }
  
  switch(edge->getTypeId())
  {
    case MM::T_FlowEdge:
      init(def, (MM::FlowEdge *) edge);
      break;
    case MM::T_StateEdge:
      init(def, (MM::StateEdge *) edge);
      break;
    default:
      break;
  }
}

MM::VOID MM::Reflector::init(MM::Definition * def, MM::StateEdge * edge)
{
  MM::Name * name = edge->getName();
  if(name != MM_NULL)
  {
    def->putElement(name, edge);
  }
  
  if(edge->isTrigger() == MM_TRUE)
  {
    //store trigger in src node
    MM::Node * src = edge->getSource();
    src->addTrigger(edge);
  }
  else if(edge->isAlias() == MM_TRUE)
  {
    MM::Node * src = edge->getSource();
    MM::Node * tgt = edge->getTarget();
    
    MM::NodeBehavior * behavior = tgt->getBehavior();
    
    if(behavior->getTypeId() == MM::T_RefNodeBehavior)
    {
      MM::RefNodeBehavior * ref = (MM::RefNodeBehavior *) behavior;

      MM::Edge * alias = ref->getAlias();
      
      //deinit and remove existing alias
      if(alias != MM_NULL)
      {
        removeElement(def, alias);
      }
      
      //store alias in tgt node
      ref->setAlias(edge);
      
      //store alias in src node
      src->addAlias(edge);
    }
    else
    {
      //TODO: error
      printf("Error: attempt to alias a node that is not a reference\n");
    }
  }
  else
  {
    //store condition in tgt node
    MM::Node * tgt = edge->getTarget();
    if(tgt != MM_NULL)
    {
      tgt->addCondition(edge);
    }
  }
}

MM::VOID MM::Reflector::init(MM::Definition * def, MM::FlowEdge * edge)
{
  //add flow edges to nodes
  MM::Node * src = edge->getSource();
  MM::Node * tgt = edge->getTarget();
  if(src != MM_NULL)
  {
    src->addOutput(edge);    
  }
  else
  {
    printf("Error: edge has unresolved source\n");
  }
  
  if(tgt != MM_NULL)
  {
    tgt->addInput(edge);
  }
  else
  {
    printf("Error: edge has unresolved target\n");
  }
}

MM::VOID MM::Reflector::init(MM::Definition * def, MM::Definition * def2)
{
  //store type (locally scoped)
  MM::Name * name = def2->getName();
  def->putElement(name, def2);
  init(def2);
  def2->setParent(def);
}

MM::VOID MM::Reflector::init(MM::Definition * def, MM::Declaration * decl)
{
  //resolve type of declaration
  MM::Name * typeName = decl->getTypeName();
  MM::Name * name = decl->getName();
  def->putElement(name, decl);
  
  MM::Definition * def2 = def->findDeclaredDefinition(typeName);
  if(def != MM_NULL)
  {
    decl->setDefinition(def2);
    
    
    MM::Vector<MM::Element *> * elements = def2->getElements();
    MM::Vector<MM::Element *>::Iterator eIter = elements->getIterator();
    while(eIter.hasNext() == MM_TRUE)
    {
      MM::Element * element = eIter.getNext();
      if(element->instanceof(MM::T_Node) == MM_TRUE)
      {
        MM::Node * node = (MM::Node *) element;
        MM::NodeBehavior * behavior = node->getBehavior();
        MM::UINT32 msg = behavior->getCreateMessage();
        decl->update(def2, m, msg, node);
      }
    }
    
    
    def2->addObserver(decl);
  }
  else
  {
    //TODO: error
    printf("Error: Declared type not found\n");
  }
  //inform instances of declaration
  def->notifyObservers(def, m, MSG_NEW_DECL, decl);
}

MM::VOID MM::Reflector::init(MM::Definition * def, MM::Assertion * assert)
{
  //TODO
}

MM::VOID MM::Reflector::init(MM::Definition * def, MM::Deletion * del)
{
  //name is a simple name (name->getName() == MM_NULL)
  MM::Name * name = del->getName();
  
  //retrieve the element by name
  MM::Element * element = def->getElement(name);
  
  removeElement(def, element);
}

//------------------------------------------------------------------------------
//Deinit visitor
//deinitialize an element inside a definition
//------------------------------------------------------------------------------

MM::VOID MM::Reflector::deinit(MM::Definition * def, MM::Element * element)
{
  if(element->instanceof(MM::T_Node) == MM_TRUE)
  {
    deinit(def, (MM::Node *) element);
  }
  else if(element->instanceof(MM::T_Edge) == MM_TRUE)
  {
    deinit(def, (MM::Edge *) element);
  }
  else
  {
    switch(element->getTypeId())
    {
      case MM::T_Assertion:
        deinit(def, (MM::Assertion *) element);
        break;
      case MM::T_Deletion:
        deinit(def, (MM::Deletion *) element);
        break;
      case MM::T_Declaration:
        deinit(def, (MM::Declaration *) element);
        break;
      case MM::T_Definition:
        deinit(def, (MM::Definition *) element);
        break;
      default:
        //TODO: error
        break;
    }
  }
  
  //all elements that are deinitialized are
  //1. also removed from their type
  def->removeElement(element);
  //2. recycled
  element->recycle(m);
}

MM::VOID MM::Reflector::deinit(MM::Definition * def, MM::Node * node)
{
  //store node by name
  MM::Name * name = node->getName();
  
  if(name->getName() != MM_NULL)
  {
    //TODO: error
    printf("Error: expected simple name, found query\n");
  }
  
  def->removeElement(name);
  def->deprioritize(node);
  
  MM::Vector<MM::Edge *> * input = node->getInput();
  MM::Vector<MM::Edge *> * output = node->getOutput();
  MM::Vector<MM::Edge *> * conditions = node->getConditions();
  MM::Vector<MM::Edge *> * triggers = node->getTriggers();
  MM::Vector<MM::Edge *> * aliases = node->getAliases();
  
  //deinit input edges
  MM::Vector<MM::Edge *>::Iterator inputIter = input->getIterator();
  while(inputIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = inputIter.getNext();
    deinit(def, edge);
  }
  
  //deinit output edges
  MM::Vector<MM::Edge *>::Iterator outputIter = output->getIterator();
  while(outputIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = outputIter.getNext();
    deinit(def, edge);
  }
  
  //deinit condition edges
  MM::Vector<MM::Edge *>::Iterator conditionsIter = conditions->getIterator();
  while(conditionsIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = conditionsIter.getNext();
    deinit(def, edge);
  }
  
  //deinit trigger edges
  MM::Vector<MM::Edge *>::Iterator triggersIter = triggers->getIterator();
  while(triggersIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = triggersIter.getNext();
    deinit(def, edge);
  }
  
  MM::Vector<MM::Edge *>::Iterator aliasesIter = aliases->getIterator();
  while(aliasesIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = aliasesIter.getNext();
    deinit(def, edge);
  }
  
  MM::NodeBehavior * behavior = node->getBehavior();
  
  //deinitialize node specifically
  switch(behavior->getTypeId())
  {
    case MM::T_PoolNodeBehavior:
      deinit(def, node, (MM::PoolNodeBehavior *) behavior);
      break;
    case MM::T_DrainNodeBehavior:
      deinit(def, node, (MM::DrainNodeBehavior *) behavior);
      break;
    case MM::T_SourceNodeBehavior:
      deinit(def, node, (MM::SourceNodeBehavior *) behavior);
      break;
    case MM::T_RefNodeBehavior:
      deinit(def, node, (MM::RefNodeBehavior *) behavior);
      break;
    default:
      break;
  }
}

MM::VOID MM::Reflector::deinit(MM::Definition * def,
                               MM::Node * node,
                               MM::PoolNodeBehavior * behavior)
{
  def->notifyObservers(def, m, MM::MSG_DEL_POOL, node);
}

MM::VOID MM::Reflector::deinit(MM::Definition * def,
                               MM::Node * node,
                               MM::SourceNodeBehavior * behavior)
{
  def->notifyObservers(def, m, MM::MSG_DEL_SOURCE, node);
}

MM::VOID MM::Reflector::deinit(MM::Definition * def,
                               MM::Node * node,
                               MM::DrainNodeBehavior * behavior)
{
  def->notifyObservers(def, m, MM::MSG_DEL_DRAIN, node);
}

MM::VOID MM::Reflector::deinit(MM::Definition * def,
                               MM::Node * node,
                               MM::RefNodeBehavior * behavior)
{
  def->notifyObservers(def, m, MM::MSG_DEL_REF, node);
}

MM::VOID MM::Reflector::deinit(MM::Definition * def, MM::Edge * edge)
{
  MM::Name * name = edge->getName();
  if(name != MM_NULL)
  {
    def->removeElement(name);
  }
  
  switch(edge->getTypeId())
  {
    case MM::T_FlowEdge:
      deinit(def, (MM::FlowEdge *) edge);
      break;
    case MM::T_StateEdge:
      deinit(def, (MM::StateEdge *) edge);
      break;
    default:
      break;
  }
}

MM::VOID MM::Reflector::deinit(MM::Definition * def, MM::StateEdge * edge)
{
  if(edge->isTrigger() == MM_TRUE)
  {
    MM::Node * src = edge->getSource();
    src->removeTrigger(edge);
  }
  else if(edge->isAlias() == MM_TRUE)
  {
    MM::Node * src = edge->getSource();
    MM::Node * tgt = edge->getTarget();
    //remove alias from src
    src->removeAlias(edge);
    
    MM::NodeBehavior * behavior = tgt->getBehavior();
    
    if(behavior->getTypeId() == MM::T_RefNodeBehavior)
    {
      //remove alias from tgt
      MM::RefNodeBehavior * refNode = (MM::RefNodeBehavior *) behavior;
      refNode->setAlias(MM_NULL);
    }
  }
  else
  {
    MM::Node * tgt = edge->getTarget();
    tgt->removeCondition(edge);
  }
}

MM::VOID MM::Reflector::deinit(MM::Definition * def, MM::FlowEdge * edge)
{
  MM::Node * src = edge->getSource();
  MM::Node * tgt = edge->getTarget();
  src->removeOutput(edge);
  tgt->removeInput(edge);
}

MM::VOID MM::Reflector::deinit(MM::Definition * def, MM::Definition * def2)
{
  MM::Name * name = def2->getName();
  def->removeElement(name);

  //deinit all elements in this type
  MM::Vector<Element *> * elements = def2->getElements();
  MM::Vector<MM::Element *>::Iterator i = elements->getIterator();
  while(i.hasNext() == MM_TRUE)
  {
    MM::Element * element = i.getNext();
    deinit(def2, element);
  }
  
  //inform instances of removed type
  def2->notifyObservers(def2, m, MSG_DEL_TYPE, def2);
}

MM::VOID MM::Reflector::deinit(MM::Definition * def, MM::Declaration * decl)
{
  //inform instances of removed declaration
  def->notifyObservers(def, m, MSG_DEL_DECL, decl);
}

MM::VOID MM::Reflector::deinit(MM::Definition * def, MM::Assertion * assert)
{
  //TODO: tell the evaluator that this assertion does not apply anymore
}

MM::VOID MM::Reflector::deinit(MM::Definition * def, MM::Deletion * del)
{
  //do nothing
}

//------------------------------------------------------------------------------
//Replace visitor
//replace an element with a new element inside a definition
//------------------------------------------------------------------------------

//replace e1 by e2 in def
MM::VOID MM::Reflector::replace(MM::Definition * def,
                                MM::Element * e1,
                                MM::Element * e2)
{

  if(e1->instanceof(MM::T_Node) == MM_TRUE)
  {
    replace(def, (MM::Node *) e1, e2);
  }
  else if(e1->instanceof(MM::T_Edge) == MM_TRUE)
  {
    replace(def, (MM::Edge *) e1, e2);
  }
  else
  {
    switch(e1->getTypeId())
    {
      case MM::T_Assertion:
        replace(def, (MM::Assertion *) e1, e2);
        break;
      case MM::T_Deletion:
        replace(def, (MM::Deletion *) e1, e2);
        break;
      case MM::T_Declaration:
        replace(def, (MM::Declaration *) e1,  e2);
        break;
      case MM::T_Definition:
        replace(def,  (MM::Definition *) e1, e2);
        break;
      default:
        //TODO: error
        break;
    }
  }
  //common code for replacing elements goes here...
}

MM::VOID MM::Reflector::replace(MM::Definition * def,
                                MM::Node * node,
                                MM::Element * element)
{
  //common code for replacing nodes goes here...
  def->deprioritize(node);
  
  if(element->getTypeId() == MM::T_Node)
  {
    MM::Node * node2 = (MM::Node *) element;
    MM::NodeBehavior * b1 = node->getBehavior();
    MM::NodeBehavior * b2 = node2->getBehavior();
    
    //swap behaviors
    node->setBehavior(b2);
    node2->setBehavior(b1);

    //reprioritize
    def->prioritize(node);
    
    //notify observers
    if(b1->getTypeId() == b2->getTypeId())
    {
      MM::UINT32 updateMessage = b1->getUpdateMessage();
      def->notifyObservers(def, m, updateMessage, node);
    }
    else
    {
      MM::UINT32 deleteMessage = b1->getDeleteMessage();
      MM::UINT32 createMessage = b2->getCreateMessage();
      def->notifyObservers(def, m, deleteMessage, node);
      def->notifyObservers(def, m, createMessage, node);
    }
    
    //clean up
    node2->recycle(m);
  }
  else
  {
    //replace a node by a not node
    removeElement(def, node);
    addElement(def, element);
  }
}

MM::VOID MM::Reflector::replace(MM::Definition * def,
                                MM::Edge * edge,
                                MM::Element * element)
{
  //common code for replacing edges goes here...  
  switch(edge->getTypeId())
  {
    case MM::T_FlowEdge:
      replace(def, (MM::FlowEdge *) edge, element);
      break;
    case MM::T_StateEdge:
      replace(def, (MM::StateEdge *) edge, element);
      break;
    default:
      break;
  }
}

MM::VOID MM::Reflector::replace(MM::Definition * def,
                                MM::Definition * def2,
                                MM::Element * element)
{
  removeElement(def, def2);
  addElement(def, element);
}

MM::VOID MM::Reflector::replace(MM::Definition * def,
                                MM::Declaration * decl,
                                MM::Element * element)
{
  removeElement(def, decl);
  addElement(def, element); //might be redeclare: effect is reset
}

MM::VOID MM::Reflector::replace(MM::Definition * def,
                                MM::FlowEdge * edge,
                                MM::Element * element)
{
  if(element->getTypeId() == MM::T_FlowEdge)
  {
    MM::FlowEdge * edge2 = (MM::FlowEdge *) element;
    
    MM::Exp * exp = edge->getExp();
    
    MM::Exp * exp2 = edge2->getExp();
    edge->setExp(exp2);
    
    edge2->setExp(exp);
    //cleanup edge2    
    edge2->recycle(m);
  }
  else
  {
    removeElement(def, edge);
    addElement(def, element);
  }
}

MM::VOID MM::Reflector::replace(MM::Definition * def,
                                MM::StateEdge * edge,
                                MM::Element * element)
{
  if(element->getTypeId() == MM::T_StateEdge)
  {
    MM::StateEdge * edge2 = (MM::StateEdge *) element;
    if(edge->isAlias() == MM_TRUE && edge2->isAlias() == MM_TRUE)
    {
      //cleanup identical element
      element->recycle(m);
    }
    else if(edge->isTrigger() == MM_TRUE && edge2->isTrigger() == MM_TRUE)
    {
      //cleanup identical element
      element->recycle(m);
    }
    else if(edge->isCondition() == MM_TRUE && edge2->isCondition() == MM_TRUE)
    {
      MM::Exp * exp = edge->getExp();
      MM::Exp * exp2 = edge2->getExp();
      edge->setExp(exp2);
      edge2->setExp(exp);
      edge2->recycle(m);
    }
    else
    {
      removeElement(def, edge);
      addElement(def, element);      
    }
  }
  else
  {
    removeElement(def, edge);
    addElement(def, element);
  }
}

MM::VOID MM::Reflector::replace(MM::Definition * def,
                                MM::Assertion * assert,
                                MM::Element * element)
{
  removeElement(def, assert);
  addElement(def, element);
}

MM::VOID MM::Reflector::replace(MM::Definition * def,
                                MM::Deletion * del,
                                MM::Element * element)
{
  removeElement(def, del);
  addElement(def, element);
}
