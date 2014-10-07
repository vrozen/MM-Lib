/******************************************************************************
 * Copyright (c) 2013-2014, Amsterdam University of Applied Sciences (HvA) and
 *                          Centrum Wiskunde & Informatica (CWI)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contributors:
 *   * Riemer van Rozen - rozen@cwi.nl - HvA / CWI
 ******************************************************************************/
//
//  reflector.cpp
//  mm
//
//  Created by Riemer van Rozen on 9/29/13.
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
#include "Operator.h"
#include "Exp.h"
#include "VarExp.h"
#include "Assertion.h"
#include "Deletion.h"
#include "Edge.h"
#include "StateEdge.h"
#include "FlowEdge.h"
#include "NodeWorkItem.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "Transformation.h"
#include "Modification.h"
#include "Transition.h"
#include "Event.h"
#include "FlowEvent.h"
#include "TriggerEvent.h"
#include "Failure.h"
#include "Enablement.h"
#include "Disablement.h"
#include "Violation.h"
#include "Prevention.h"
#include "Activation.h"
#include "Program.h"
#include "PoolNodeBehavior.h"
#include "SourceNodeBehavior.h"
#include "DrainNodeBehavior.h"
#include "RefNodeBehavior.h"
#include "GateNodeBehavior.h"
#include "ConverterNodeBehavior.h"
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
    
    MM_printf("Merge: merging ");
    if(e->getName() != MM_NULL)
    {
      e->getName()->print();
    }
    MM_printf("\n");
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
    MM_printf("Merge: Merge definition %s into parent type definition\n", buf);
    merge(root, (MM::Definition *) element);
  }
  else
  {
    MM_printf("Merge: Merge element %s into parent type definition\n", buf);
    if(navigate(root, element, &def, &found) == MM_TRUE)
    {
      if(found == MM_NULL)
      {
        MM_printf("Merge: Element %s is new in type: add and initialize\n", buf);
        
        def->addElement(element);
        init(def, element);
      }
      else
      {
        MM_printf("Merge: Element %s exists in type: replace it\n", buf);
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
    MM_printf("Merge: Navigated to type definition.\n");
    if(found == MM_NULL)
    {
      MM_printf("Merge: Adding new type definition %s to parent definition.\n",
                type->getName()->getBuffer());
      def->addElement(type);
      init(root,type);
    }
    else
    {
      MM_printf("Merge: Merging type definitions %s\n",
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
      MM_printf("Navigate: Navigating to %s\n", curName->getBuffer());      
      curElement = type->getElement(curName);
      
      if(curElement != MM_NULL && curElement->getTypeId() == MM::T_Definition)
      {
        MM_printf("Navigate: Navigating into type %s\n",
                  curElement->getName()->getBuffer());
        
        //parent is a definition, keep searching
        type = (MM::Definition *) curElement;
        
        if(curName->getName() == MM_NULL)
        {
          //we found a definitions
          MM_printf("Navigate: Found definition %s\n", curName->getBuffer());
          success = MM_TRUE;
          break;
        }
      }
      else
      {
        //element is not a definition
        if(curName->getName() == MM_NULL)
        {
          MM_printf("Navigate: Found element %s\n", curName->getBuffer());
          
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
    MM_printf("Navigate: Success\n");
    element->setName(curName);
    * def = type;
    * found = curElement;
    success = MM_TRUE;
  }
  else
  {
    //TODO: error
    MM_printf("Navigate: Error\n");
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
  
  def->setPullAllNodes(pullAllNodes);
  def->setPullAnyNodes(pullAnyNodes);
  def->setPushAllNodes(pushAllNodes);
  def->setPushAnyNodes(pushAnyNodes);
  def->setNameToElementMap(n2e);
  
  MM::UINT32 size = elements->size();
  
  //NOTE: don't use iterator because the number of nodes and edges may increase
  //      during the initialization... :-S :-)
  //      however, the new nodes are initialized already (converter sugar)
  //NOTE: decision: we may never decrease the amount of elements.
  //NOTE: decision: all initializations initialize extra generated elements
  
  //init types
  for(MM::UINT32 i = 0; i < size; i++)
  {
    MM::Element * e = elements->elementAt(i);
    if(e->getTypeId() == MM::T_Definition)
    {
      init(def, (MM::Definition *) e);
    }
  }
 
  //init nodes
  for(MM::UINT32 i = 0; i < size; i++)
  {
    MM::Element * e = elements->elementAt(i);
    if(e->instanceof(MM::T_Node) == MM_TRUE)
    {
      init(def, (MM::Node *) e);
    }
  }
  
  //init declarations
  for(MM::UINT32 i = 0; i < size; i++)
  {
    MM::Element * e = elements->elementAt(i);

    if(e->getTypeId() == MM::T_Declaration)
    {
      init(def, (MM::Declaration *) e);
    }
  }
  
  //init edges
  for(MM::UINT32 i = 0; i < size; i++)
  {
    MM::Element * e = elements->elementAt(i);
    if(e->instanceof(MM::T_Edge) == MM_TRUE)
    {
      init(def, (MM::Edge *) e);
    }
  }
  
  //init assertions
  for(MM::UINT32 i = 0; i < size; i++)
  {
    MM::Element * e = elements->elementAt(i);
    if(e->getTypeId() == MM::T_Assertion)
    {
      init(def, (MM::Assertion *) e);
    }
  }
  
  //init deletions (does not make sense but okay let's be thorough)
  for(MM::UINT32 i = 0; i < size; i++)
  {
    MM::Element * e = elements->elementAt(i);
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
    MM_printf("Error: required simple name, found query\n");
  }
  
  def->prioritize(node);
  
  MM::NodeBehavior * behavior = node->getBehavior();
  
  //initialize node specifically
  switch(behavior->getTypeId())
  {
    case MM::T_PoolNodeBehavior:
      init(node);
      init(def, node, (PoolNodeBehavior *) behavior);
      break;
    case MM::T_DrainNodeBehavior:
      init(node);
      init(def, node, (MM::DrainNodeBehavior *) behavior);
      break;
    case MM::T_SourceNodeBehavior:
      init(node);
      init(def, node, (MM::SourceNodeBehavior *) behavior);
      break;
    case MM::T_RefNodeBehavior:
      init(node);
      init(def, node, (MM::RefNodeBehavior *) behavior);
      break;
    case MM::T_GateNodeBehavior:
      init(node);
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
  MM::Vector<MM::Edge *> * input      = m->createEdgeVector();
  MM::Vector<MM::Edge *> * output     = m->createEdgeVector();
  MM::Vector<MM::Edge *> * conditions = m->createEdgeVector();
  MM::Vector<MM::Edge *> * triggers   = m->createEdgeVector();
  MM::Vector<MM::Edge *> * aliases    = m->createEdgeVector();
  
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
  MM::Name * of = behavior->getOf();
  if(of != MM_NULL)
  {
    MM::Element * element = def->findDeclaredDefinition(of);
    if(element != MM_NULL &&
       element->instanceof(MM::T_Definition) == MM_TRUE)
    {
      //initialize interfaces
      MM::Definition * unitDef = (MM::Definition *) element;
      MM::Vector<MM::Element *> * elements = unitDef->getElements();
      MM::Vector<MM::Element *>::Iterator eIter = elements->getIterator();
      while(eIter.hasNext() == MM_TRUE)
      {
        MM::Element * element = eIter.getNext();
        if(element->instanceof(MM::T_Node) == MM_TRUE)
        {
          MM::Node * node = (MM::Node *) element;
          MM::NodeBehavior * behavior2 = node->getBehavior();
          MM::UINT32 msg = behavior2->getCreateMessage();
          behavior->update(unitDef, m, msg, node);
        }
      }
      
      //add observer
      ((MM::Definition*)unitDef)->addObserver(behavior);
    }
  }
  
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
  //1. create an anonymous node that behaves like a drain
  //   that shares with the node that has converter node behavior
  //   a. inputs with node
  //   b. conditions
  //   c. triggers
  //   d. aliases
  MM::Node * drainNode = m->createDrainNode(behavior->getIO(),
                                            behavior->getWhen(),
                                            MM::NodeBehavior::HOW_ALL,
                                            MM_NULL);
  
  
  //2. create an anonymous node that behaves like a source
  //   that shares with thenode that has converter node behavior
  //   a. outputs  
  MM::Node * sourceNode = m->createSourceNode(behavior->getIO(),
                                              MM::NodeBehavior::WHEN_PASSIVE,
                                              MM_NULL);
  
  //create names for drain and source nodes
  MM::Name * name = node->getName();
  MM::CHAR * buf = name->getBuffer();
  //MM::UINT32 len = name->getLength();
  
  MM::CHAR sourceName[128] = {0};
  MM::CHAR drainName[128] = {0};
  
  snprintf(sourceName, 128, buf);
  snprintf(drainName, 128, buf);
  
  //drain and converter need the same name
  
  //snprintf(drainName+len,128-len, "_drain");
  //snprintf(sourceName+len, 128-len, "_source");
  
  MM::Name * drainNodeName = m->createName(drainName);
  MM::Name * sourceNodeName = m->createName(sourceName);
  
  drainNode->setName(drainNodeName);
  sourceNode->setName(sourceNodeName);
  
  //initialize nodes
  init(drainNode);
  init(sourceNode);
  
  //3. create a trigger from source to drain
  MM::StateEdge * triggerEdge = m->createAnonymousTriggerEdge(drainNode, sourceNode);
  //Node: trigger edge is already created initialized
    
  def->addElement(drainNode);
  def->addElement(sourceNode);
  def->addElement(triggerEdge);

  def->prioritize(drainNode);
  def->prioritize(sourceNode);
  
  //store source, drain and trigger for deinit and merge/update
  behavior->setSourceNode(sourceNode);
  behavior->setDrainNode(drainNode);
  behavior->setTriggerEdge(triggerEdge);

  //converters share edges with the source and drain nodes they consist of
  MM::Vector<MM::Edge *> * input      = drainNode->getInput();
  MM::Vector<MM::Edge *> * conditions = drainNode->getConditions();
  
  MM::Vector<MM::Edge *> * output     = sourceNode->getOutput();
  MM::Vector<MM::Edge *> * triggers   = sourceNode->getTriggers();
  MM::Vector<MM::Edge *> * aliases    = sourceNode->getAliases();
  
  if(node->hasEdgeOwnership() == MM_TRUE)
  {
    MM::Vector<MM::Edge *> * oldInput      = node->getInput();
    MM::Vector<MM::Edge *> * oldConditions = node->getConditions();
    MM::Vector<MM::Edge *> * oldOutput     = node->getOutput();
    MM::Vector<MM::Edge *> * oldTriggers   = node->getTriggers();
    MM::Vector<MM::Edge *> * oldAliases    = node->getAliases();
    
    input->addAll(oldInput);
    output->addAll(oldOutput);
    conditions->addAll(oldConditions);
    triggers->addAll(oldTriggers);
    aliases->addAll(oldAliases);
    
    delete oldInput;
    delete oldOutput;
    delete oldAliases;
    delete oldTriggers;
    delete oldConditions;
  }
  
  node->setInput(input);
  node->setConditions(conditions);
  node->setAliases(aliases);
  node->setTriggers(triggers);
  node->setOutput(output);
  
  //add trigger edge
  drainNode->addTrigger(triggerEdge);
  

  
  //desugaring remains invisible
  sourceNode->setVisible(MM_FALSE);
  drainNode->setVisible(MM_FALSE);
  triggerEdge->setVisible(MM_FALSE);
  
  def->notifyObservers(def, m, behavior->getCreateMessage(), node);
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
    MM_printf("Error: source node %s of edge not found\n", srcName->getBuffer());
  }
  
  if(tgtNode != MM_NULL)
  {
    edge->setTarget(tgtNode);
  }
  else
  {
    //TODO: error
    MM_printf("Error: target node %s of edge not found\n", tgtName->getBuffer());
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

    //Note: because getBehavior returns the behavior of the referenced node on interfaces
    //      it can happen that we resolve an alias acros instance borders
    //      in the NodeBehavior class we rely on that
    //      we just check if the node is in the definition of the current instance
    //      and if not, then we resolve it to the parent instead 
    if(src == MM_NULL)
    {
      MM_printf("Error: unresolved source name %s\n",edge->getSourceName()->getBuffer());
    }
    else if(tgt == MM_NULL)
    {
      MM_printf("Error: unresolved target name %s\n",edge->getTargetName()->getBuffer());
    }
    else
    {
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
        MM_printf("Error: attempt to alias a node that is not a reference\n");
      }
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
  
  MM::Name * name = edge->getName();
  if(name != MM_NULL)
  {
    def->putElement(name, edge);
  }
  
  if(src != MM_NULL)
  {
    src->addOutput(edge);    
  }
  else
  {
    MM_printf("Error: edge has unresolved source\n");
  }
  
  if(tgt != MM_NULL)
  {
    tgt->addInput(edge);
  }
  else
  {
    MM_printf("Error: edge has unresolved target\n");
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
    MM_printf("Error: Declared type not found\n");
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
  removeElement(def, del);
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
    MM_printf("Error: expected simple name, found query\n");
  }
  
  def->removeElement(name);
  def->deprioritize(node);
  def->removeElement(node);
  
  //deinit input edges
  MM::Vector<MM::Edge *> * input = node->getInput();

  /*big fix*/
  if(input != MM_NULL)
  {
    while(input->size() != 0)
	{
      MM::Edge * edge = input->pop();
      removeElement(def, edge);
    }
  }
  
  //deinit output edges
  MM::Vector<MM::Edge *> * output = node->getOutput();
  if(output != MM_NULL)
  {
    MM::Vector<MM::Edge *>::Iterator outputIter = output->getIterator();
    while(outputIter.hasNext() == MM_TRUE)
    {
      MM::Edge * edge = outputIter.getNext();
      //deinit(def, edge);
      removeElement(def, edge);
    }
  }
  
  //deinit condition edges
  MM::Vector<MM::Edge *> * conditions = node->getConditions();
  if(conditions != MM_NULL)
  {
    MM::Vector<MM::Edge *>::Iterator conditionsIter = conditions->getIterator();
    while(conditionsIter.hasNext() == MM_TRUE)
    {
      MM::Edge * edge = conditionsIter.getNext();
      //deinit(def, edge);
      removeElement(def, edge);
    }
  }
  
  //deinit trigger edges
  MM::Vector<MM::Edge *> * triggers = node->getTriggers();
  if(triggers != MM_NULL)
  {
    MM::Vector<MM::Edge *>::Iterator triggersIter = triggers->getIterator();
    while(triggersIter.hasNext() == MM_TRUE)
    {
      MM::Edge * edge = triggersIter.getNext();
      //deinit(def, edge);
      removeElement(def, edge);
    }
  }
  
  //deinit alias edges
  MM::Vector<MM::Edge *> * aliases = node->getAliases();
  if(aliases != MM_NULL)
  {
    MM::Vector<MM::Edge *>::Iterator aliasesIter = aliases->getIterator();
    while(aliasesIter.hasNext() == MM_TRUE)
    {
      MM::Edge * edge = aliasesIter.getNext();
      //deinit(def, edge);
      removeElement(def, edge);
    }
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
    case MM::T_ConverterNodeBehavior:
      deinit(def, node, (MM::ConverterNodeBehavior *) behavior);
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

MM::VOID MM::Reflector::deinit(MM::Definition * def,
                               MM::Node * node,
                               MM::ConverterNodeBehavior * behavior)
{
  MM::Node * drainNode = behavior->getDrainNode();
  MM::Node * sourceNode = behavior->getSourceNode();
  MM::Edge * triggerEdge = behavior->getTriggerEdge();
 
  //remove ownership of edges from drain and source
  drainNode->setInput(MM_NULL);
  drainNode->setConditions(MM_NULL);
  sourceNode->setTriggers(MM_NULL);
  sourceNode->setAliases(MM_NULL);
  sourceNode->setOutput(MM_NULL);
  
  removeElement(def, triggerEdge);
  removeElement(def, drainNode);
  removeElement(def, sourceNode);
  
  node->setEdgeOwnership(MM_TRUE);
  
  MM::Vector<MM::Edge *> * input = node->getInput();
  MM::Vector<MM::Edge *>::Iterator inputIter = input->getIterator();
  while(inputIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = inputIter.getNext();
    edge->setTarget(node);
  }
  
  MM::Vector<MM::Edge *> * conditions = node->getConditions();
  MM::Vector<MM::Edge *>::Iterator conditionsIter = conditions->getIterator();
  while(conditionsIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = conditionsIter.getNext();
    edge->setTarget(node);
  }
  
  MM::Vector<MM::Edge *> * triggers = node->getOutput();
  MM::Vector<MM::Edge *>::Iterator triggerIter = triggers->getIterator();
  while(triggerIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = triggerIter.getNext();
    edge->setSource(node);
  }

  MM::Vector<MM::Edge *> * output = node->getOutput();
  MM::Vector<MM::Edge *>::Iterator outputIter = output->getIterator();
  while(outputIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = outputIter.getNext();
    edge->setSource(node);
  }
  
  MM::Vector<MM::Edge *> * aliases = node->getAliases();
  MM::Vector<MM::Edge *>::Iterator aliasIter = aliases->getIterator();
  while(aliasIter.hasNext() == MM_TRUE)
  {
    MM::Edge * edge = aliasIter.getNext();
    edge->setSource(node);
  }
  
  def->notifyObservers(def, m, behavior->getDeleteMessage(), node);
}

MM::VOID MM::Reflector::deinit(MM::Definition * def, MM::Edge * edge)
{
  MM::Name * name = edge->getName();
  if(name != MM_NULL)
  {
    def->removeElement(name);
  }
  
  //def->removeElement(edge);

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
                                MM::Node       * node,
                                MM::Element    * element)
{
  //common code for replacing nodes goes here...
  def->deprioritize(node);
  
  if(element->getTypeId() == MM::T_Node)
  {
    MM::Node * node2 = (MM::Node *) element;
    MM::NodeBehavior * behavior = node->getBehavior();
    MM::NodeBehavior * behavior2 = node2->getBehavior();
    
    //swap behaviors
    node->setBehavior(behavior2);
    node2->setBehavior(behavior);
    
    //always deinitialize an old converter
    if(behavior->getTypeId() == MM::T_ConverterNodeBehavior)
    {
      deinit(def, node, (MM::ConverterNodeBehavior*) behavior);
      
      //it got removed from n2e... side effect of source and drain with same name
      
      def->putElement(node->getName(), node);
    }
    
    //always initialize a new converter
    if(behavior2->getTypeId() == MM::T_ConverterNodeBehavior)
    {
      init(def, node, (MM::ConverterNodeBehavior*) behavior2);
      node->setEdgeOwnership(MM_TRUE);
    }
    
    //reprioritize
	  //def->deprioritize(node);
    def->prioritize(node);

    //notify observers
    if(behavior->getTypeId() == behavior2->getTypeId())
    {
      MM::UINT32 updateMessage = behavior->getUpdateMessage();
      def->notifyObservers(def, m, updateMessage, node);

	    if(behavior->instanceof(MM::T_RefNodeBehavior) == MM_TRUE)
	    {
        MM::RefNodeBehavior * refBehavior = (RefNodeBehavior *) behavior; 
		    MM::Edge * alias = refBehavior->getAlias();

		    MM::RefNodeBehavior * refBehavior2 = (RefNodeBehavior *) behavior2;
		    refBehavior2->setAlias(alias);
	    }
    }
    else
    {
      MM::UINT32 deleteMessage = behavior->getDeleteMessage();
      MM::UINT32 createMessage = behavior2->getCreateMessage();
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
  /*if(element->getTypeId() == MM::T_FlowEdge)
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
  {*/
    removeElement(def, edge);
    addElement(def, element);
  //}
}

MM::VOID MM::Reflector::replace(MM::Definition * def,
                                MM::StateEdge * edge,
                                MM::Element * element)
{
    removeElement(def, edge);
    addElement(def, element);

		/* 
  if(element->getTypeId() == MM::T_StateEdge)
  {


	MM::StateEdge * edge2 = (MM::StateEdge *) element;
    if(edge->isAlias() == MM_TRUE && edge2->isAlias() == MM_TRUE)
    {
      //cleanup identical element
      //element->recycle(m);
      
      //do nothing
    }
    else if(edge->isTrigger() == MM_TRUE && edge2->isTrigger() == MM_TRUE)
    {
      //cleanup identical element
      //element->recycle(m);
      
      //do nothing
    }
    else if(edge->isCondition() == MM_TRUE && edge2->isCondition() == MM_TRUE)
    {
      MM::Exp * exp = edge->getExp();
      MM::Exp * exp2 = edge2->getExp();
      edge->setExp(exp2);
      edge2->setExp(exp);
      //edge2->recycle(m);
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
  }*/
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
