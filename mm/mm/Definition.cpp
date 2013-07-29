//
//  Definition.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/21/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "Edge.h"
#include "FlowEdge.h"
#include <vector>
#include "Node.h"
#include "Event.h"
#include "FlowEvent.h"
#include "Transition.h"
#include "PoolNode.h"
#include "Declaration.h"
#include "Definition.h"

const MM::CHAR * MM::Definition::LPAREN_STR = "(";
const MM::CHAR * MM::Definition::RPAREN_STR = ")";
const MM::CHAR * MM::Definition::LBRACE_STR = "{";
const MM::CHAR * MM::Definition::RBRACE_STR = "}";
const MM::CHAR * MM::Definition::COMMA_STR  = ",";

const MM::UINT32 MM::Definition::LPAREN_LEN = 1;
const MM::UINT32 MM::Definition::RPAREN_LEN = 1;
const MM::UINT32 MM::Definition::LBRACE_LEN = 1;
const MM::UINT32 MM::Definition::RBRACE_LEN = 1;
const MM::UINT32 MM::Definition::COMMA_LEN  = 1;

MM::Definition::Definition(MM::Name * name,
                           std::vector<MM::Element *> * elements) : MM::Element()
{
  this->name = name;
  this->elements = elements;
}

MM::Definition::Definition(std::vector<MM::Element *> * elements) : MM::Element()
{
  this->name = MM_NULL;
  this->elements = elements;
}

MM::Definition::~Definition()
{
  while (!elements->empty())
  {
    delete elements->back();
    elements->pop_back();
  }
  delete elements;
}

MM::VOID MM::Definition::addElement(MM::Element * element)
{
  elements->push_back(element);
}

MM::VOID MM::Definition::removeElement(MM::Element * element)
{
  std::vector<Element*>::iterator i = elements->begin();
  std::vector<Element*>::iterator end = elements->end();
  
  for(; i != end; i++)
  {
    if(*i == element)
    {
      elements->erase(i);
      delete *i;
    }
  }
}

MM::UINT32 MM::Definition::getPoolCount()
{
  MM::UINT32 count = 0;
  std::vector<Element*>::iterator i = elements->begin();
  std::vector<Element*>::iterator end = elements->end();
  
  for(; i != end; i++)
  {
    if(typeid(*i) == typeid(MM::PoolNode *))
    {
      count++;
    }
  }

  return count;
}

MM::UINT32 MM::Definition::getDeclCount()
{
  int count = 0;
  std::vector<Element*>::iterator i = elements->begin();
  std::vector<Element*>::iterator end = elements->end();
  
  for(; i != end; i++)
  {
    if(typeid(*i) == typeid(MM::Declaration *))
    {
      count++;
    }
  }
    
  return count;
}

MM::VOID MM::Definition::toString(MM::String * buf)
{
  if(name != MM_NULL)
  {
    name->toString(buf);
    buf->linebreak();
    buf->append((MM::CHAR*)MM::Definition::LBRACE_STR, MM::Definition::LBRACE_LEN);
    buf->linebreak();
  }
  std::vector<Element*>::iterator e_i = elements->begin();
  std::vector<Element*>::iterator e_end = elements->end();
  for( ; e_i != e_end; e_i++)
  {
    Element * e = *e_i;
    e->toString(buf);
    buf->linebreak();
  }
  if(name != MM_NULL)
  {
    buf->append((MM::CHAR*)MM::Definition::RBRACE_STR, MM::Definition::RBRACE_LEN);
  }
}
