//
//  Transition.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include "Types.h"
#include "String.h"
#include "Element.h"
#include "Exp.h"
#include "Edge.h"
#include <vector>
#include "Node.h"
#include "Event.h"
#include "FlowEvent.h"
#include "Transition.h"

MM::Transition::Transition()
{
  this->steps = new std::vector<MM::Event*>();
}

MM::Transition::~Transition()
{
  this->clear();
  delete this->steps;
}

MM::VOID MM::Transition::add(MM::Event * event)
{
  steps->push_back(event);
}

MM::VOID MM::Transition::toString(MM::String * str)
{
  std::vector<MM::Event*>::iterator i;
  
  for(i = steps->begin(); i != steps->end(); i++)
  {
    (*i)->toString(str);
  }
}

MM::VOID MM::Transition::clear()
{
  while (!steps->empty())
  {
    delete steps->back();
    steps->pop_back();
  }
}

MM::VOID MM::Transition::step()
{
  
}

MM::VOID MM::Transition::back()
{
  std::vector<MM::Event*>::iterator i;
  for(i = steps->begin(); i != steps->end(); i++)
  {
    Event* event = *i;
    event->back();
  }
}
