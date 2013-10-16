//
//  Definition.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/21/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Map.h"
#include "Vector.h"
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Exp.h"
#include "Edge.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "Observer.h"
#include "Observable.h"
#include "Declaration.h"
#include "Definition.h"

const MM::CHAR MM::Definition::LPAREN_CHAR = '(';
const MM::CHAR MM::Definition::RPAREN_CHAR = ')';
const MM::CHAR MM::Definition::LBRACE_CHAR = '{';
const MM::CHAR MM::Definition::RBRACE_CHAR = '}';
const MM::CHAR MM::Definition::COMMA_CHAR  = ',';

//required functionality
//   NOTE: the following is needed to determine which node may act next
//1. retrieve its pull all nodes
//2. retrieve its push all nodes
//3. retrieve its pull any nodes
//4. retrieve its push any nodes

//calculated functionality
//   NOTE: in each of these aliases must be taken into account
//A. calculate conditions of each of its nodes and store them in the node
//   NOTE: necessary to know when a node may activate
//B. calculate target triggers of each of its nodes and store them in the node
//   NOTE: so that when a node's conditions are met it can activate the target nodes
//C. calculate a node's inflow and store these flow edges in the node
//   NOTE: necessary for when a pull node acts
//D. calculate a node's outflow and store these flow edges in the node
//   NOTE: necessary for when a push node acts

MM::Definition::Definition(MM::Name * name,
                           MM::Vector<MM::Element *> * elements):
  MM::Element(name), MM::Observable()
{
  this->parent = MM_NULL;
  this->elements = elements;
  this->pullAllNodes = MM_NULL;
  this->pullAnyNodes = MM_NULL;
  this->pushAllNodes = MM_NULL;
  this->pushAnyNodes = MM_NULL;
  this->n2e = MM_NULL;
}

MM::Definition::Definition(MM::Vector<MM::Element *> * elements):
  MM::Element(MM_NULL), MM::Observable()
{
  this->parent = MM_NULL;
  this->elements = elements;
  this->pullAllNodes = MM_NULL;
  this->pullAnyNodes = MM_NULL;
  this->pushAllNodes = MM_NULL;
  this->pushAnyNodes = MM_NULL;
  this->n2e = MM_NULL;
}

MM::Definition::~Definition()
{
  this->name = MM_NULL;
  this->parent = MM_NULL;  
  this->elements = MM_NULL;
  this->pullAllNodes = MM_NULL;
  this->pullAnyNodes = MM_NULL;
  this->pushAllNodes = MM_NULL;
  this->pushAnyNodes = MM_NULL;
  this->n2e = MM_NULL;
}

MM::VOID MM::Definition::recycle(MM::Recycler * r)
{
  //deinitialize everything in this type
  //deinit(this);
  
  //TODO: go through recycler instead of delete
  if(pullAllNodes != MM_NULL)
  {
    delete pullAllNodes;
  }
  if(pullAnyNodes != MM_NULL)
  {
    delete pullAnyNodes;
  }
  if(pushAllNodes != MM_NULL)
  {
    delete pushAllNodes;
  }
  if(pushAnyNodes != MM_NULL)
  {
    delete pushAnyNodes;
  }
  if(n2e != MM_NULL)
  {
    delete n2e;
  }
  
  while (!elements->isEmpty())
  {
    Element * e = elements->pop();
    e->recycle(r);
  }
  delete elements; //FIXME
  
  this->Element::recycle(r);
  //this->Observable::recycle(r);
}

MM::TID MM::Definition::getTypeId()
{
  return MM::T_Definition;
}

MM::BOOLEAN MM::Definition::instanceof(MM::TID tid)
{
  if(tid == MM::T_Definition)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Element::instanceof(tid);
  }
}


//------------------------------------------------------------------------------
//Locate nodes in definitions
//NOTE: the method searches through declarations and types
//NOTE: normally we only allow a search to go one deep
//      because graphically we cannot depict edges between 2-nested types
//NOTE: the method does not respect visibility yet
//------------------------------------------------------------------------------
MM::Node * MM::Definition::findNode(MM::Name * name,
                                    MM::NodeBehavior::IO direction)
{
  MM::Node * node = MM_NULL;
  
  if(name != MM_NULL)
  {
    MM::Element * e1 = this->getElement(name);
    if(e1 != MM_NULL)
    {
      if(e1->getTypeId() == MM::T_Declaration)
      {
        //element is a declaration --> edge is to an interface
        MM::Declaration * decl = (MM::Declaration *) e1;
        MM::Definition * def = decl->getDefinition();
        MM::Name * nodeName = name->getName();
        if(nodeName != MM_NULL && def != MM_NULL)
        {
          MM::Element * e2 = def->getElement(nodeName);
          if(e2 != MM_NULL &&
             e2->instanceof(MM::T_InterfaceNode) == MM_TRUE &&
             nodeName->getName() == MM_NULL)
          {
            //FIXME: check edge end is connected to an interface that is input or output
            MM::Node * n = (MM::Node *) e2;            
            if(n->getBehavior()->conformsTo(direction) == MM_TRUE)
            {
              node = (MM::Node *) e2;
              //* ref = (MM::Declaration *) e1;
            }
            else
            {
              //TODO: error
              printf("Definition Error: interface does not accept input");
            }
          }
        }
      }
      else if(e1->getTypeId() == MM::T_Node && name->getName() == MM_NULL)
      {
        node = (MM::Node *) e1;
        //* ref = MM_NULL;
      }
      else
      {
        //TODO: error
        printf("Definition Error: incorrectly defined name, prefix is not a type\n");
      }
    }
  } 
  return node;
}


//Traverse lexical scoping of declared types to find a the type of a declaration
MM::Definition * MM::Definition::findDeclaredDefinition(MM::Name * name)
{
  if(name == MM_NULL)
  {
    printf("Definition Error: cannot retrieve nameless type\n");
    return MM_NULL;
  }
  
  MM::Element * element = getElement(name);
 
  if(name->getName() != MM_NULL)
  {
    printf("Definition Error: expected simple name, found query %s.\n",
           name->getBuffer());
  }
  
  if(element == MM_NULL)
  {
    if(parent != MM_NULL)
    {
      return parent->findDeclaredDefinition(name);
    }
    else
    {
      //TODO: error
      printf("Definition Error: type %s not found\n", name->getBuffer());
      return MM_NULL;
    }
  }
  else if(element->instanceof(MM::T_Definition) == MM_TRUE)
  {
    return (MM::Definition *) element;
  }
  else
  {
    //TODO: error
    printf("Definition Error: name %s does not denote a definition\n",
           name->getBuffer());
    return MM_NULL;
  }
}

MM::VOID MM::Definition::prioritize(MM::Node * node)
{
  MM::NodeBehavior * behavior = node->getBehavior();
  
  //store node in priority queue
  MM::NodeBehavior::Act act = behavior->getAct();
  MM::NodeBehavior::How how = behavior->getHow();
  if(act == MM::NodeBehavior::ACT_PULL)
  {
    if(how == MM::NodeBehavior::HOW_ALL)
    {
      pullAllNodes->add(node);
    }
    else if(how == MM::NodeBehavior::HOW_ANY)
    {
      pullAnyNodes->add(node);
    }
  }
  else if(act == MM::NodeBehavior::ACT_PUSH)
  {
    if(how == MM::NodeBehavior::HOW_ALL)
    {
      pushAllNodes->add(node);
    }
    else
    {
      pushAnyNodes->add(node);
    }
  }
}

MM::VOID MM::Definition::deprioritize(MM::Node * node)
{
  //store node in priority queue
  MM::NodeBehavior * behavior = node->getBehavior();
  
  MM::NodeBehavior::Act act = behavior->getAct();
  MM::NodeBehavior::How how = behavior->getHow();
  
  if(act == MM::NodeBehavior::ACT_PULL)
  {
    if(how == MM::NodeBehavior::HOW_ALL)
    {
      pullAllNodes->remove(node);
    }
    else if(how == MM::NodeBehavior::HOW_ANY)
    {
      pullAllNodes->remove(node);
    }
  }
  else if(act == MM::NodeBehavior::ACT_PUSH)
  {
    if(how == MM::NodeBehavior::HOW_ALL)
    {
      pushAllNodes->remove(node);
    }
    else
    {
      pushAnyNodes->remove(node);
    }
  }
}

MM::Vector<MM::Node *> * MM::Definition::getPullAllNodes()
{
  return pullAllNodes;
}

MM::Vector<MM::Node *> * MM::Definition::getPullAnyNodes()
{
  return pullAnyNodes;
}

MM::Vector<MM::Node *> * MM::Definition::getPushAllNodes()
{
  return pushAllNodes;
}

MM::Vector<MM::Node *> * MM::Definition::getPushAnyNodes()
{
  return pushAnyNodes;
}

/*
MM::VOID MM::Definition::addPullAllNode(MM::Node * node)
{
  pullAllNodes->add(node);
}

MM::VOID MM::Definition::addPullAnyNode(MM::Node * node)
{
  pullAnyNodes->add(node);
}

MM::VOID MM::Definition::addPushAllNode(MM::Node * node)
{
  pushAllNodes->add(node);
}

MM::VOID MM::Definition::addPushAnyNode(MM::Node * node)
{
  pushAnyNodes->add(node);
}

MM::VOID MM::Definition::removePullAllNode(MM::Node * node)
{
  pullAllNodes->remove(node);
}

MM::VOID MM::Definition::removePullAnyNode(MM::Node * node)
{
  pullAnyNodes->remove(node);
}

MM::VOID MM::Definition::removePushAllNode(MM::Node * node)
{
  pushAllNodes->remove(node);
}

MM::VOID MM::Definition::removePushAnyNode(MM::Node * node)
{
  pushAnyNodes->remove(node);
}
*/

MM::VOID MM::Definition::setPullAllNodes(MM::Vector<MM::Node *> * pullAllNodes)
{
  this->pullAllNodes = pullAllNodes;
}

MM::VOID MM::Definition::setPullAnyNodes(MM::Vector<MM::Node *> * pullAnyNodes)
{
  this->pullAnyNodes = pullAnyNodes;
}

MM::VOID MM::Definition::setPushAllNodes(MM::Vector<MM::Node *> * pushAllNodes)
{
  this->pushAllNodes = pushAllNodes;
}

MM::VOID MM::Definition::setPushAnyNodes(MM::Vector<MM::Node *> * pushAnyNodes)
{
  this->pushAnyNodes = pushAnyNodes;
}

MM::VOID MM::Definition::setNameToElementMap(MM::Map<MM::Name *, MM::Element *, MM::Name::Compare> * n2e)
{
  this->n2e = n2e;
}

MM::VOID MM::Definition::setParent(MM::Definition * parent)
{
  this->parent = parent;
}

MM::Element * MM::Definition::getElement(MM::Name * name)
{
  MM::Element * r = MM_NULL;
  if(n2e != MM_NULL)
  {
    r = n2e->get(name);
  }
  return r;
}

//called during initialization
MM::VOID MM::Definition::putElement(MM::Name * name, MM::Element * element)
{
  n2e->put(name, element);
}

//called when element is added
MM::VOID MM::Definition::addElement(MM::Element * element)
{
  elements->add(element);
}

//called when element is removed
MM::VOID MM::Definition::removeElement(MM::Element * element)
{
  elements->remove(element);
}

MM::VOID MM::Definition::clearElements()
{
  elements->clear();
}

//called during deinitialization
MM::VOID MM::Definition::removeElement(MM::Name * name)
{
  n2e->remove(name);
}

MM::Vector<MM::Element *> * MM::Definition::getElements()
{
  return elements;
}

MM::VOID MM::Definition::toString(MM::String * buf)
{
  toString(buf, 0);
}

MM::VOID MM::Definition::toString(MM::String * buf, MM::UINT32 indent)
{
  if(name != MM_NULL)
  {
    buf->space(indent);
    name->toString(buf);
    buf->linebreak();
    buf->space(indent);
    buf->append(MM::Definition::LBRACE_CHAR);
    buf->linebreak();
  }
  MM::Vector<Element*>::Iterator iter = elements->getIterator();
  Element * element = MM_NULL;
  while(iter.hasNext())
  {
    element = iter.getNext();
    if(name != MM_NULL)
    {
      element->toString(buf, indent+2);
    }
    else
    {
      element->toString(buf, 0);
    }
    buf->linebreak();
  }
  if(name != MM_NULL)
  {
    buf->space(indent);
    buf->append(MM::Definition::RBRACE_CHAR);
  }
}
