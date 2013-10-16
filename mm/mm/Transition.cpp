//
//  Transition.cpp
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
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "Element.h"
#include "Operator.h"
#include "Exp.h"
#include "Edge.h"
#include "NodeBehavior.h"
#include "Node.h"
#include "Event.h"
#include "FlowEvent.h"
#include "Transition.h"
#include "Observer.h"
#include "Observable.h"
#include "Map.h"
//#include "Instance.h"

MM::Transition::Transition() : MM::Recyclable()
{
  this->steps = new std::vector<MM::Event*>(); //FIXME
}

MM::Transition::~Transition()
{
  steps = MM_NULL;
}

MM::VOID MM::Transition::recycle(MM::Recycler * r)
{
  this->clear(r);
  delete this->steps; //FIXME
  this->MM::Recyclable::recycle(r);
}

MM::TID MM::Transition::getTypeId()
{
  return MM::T_Transition;
}

MM::BOOLEAN MM::Transition::instanceof(MM::TID tid)
{
  if(tid == MM::T_Transition)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

MM::VOID MM::Transition::add(MM::Event * event)
{
  steps->push_back(event);
}

MM::VOID MM::Transition::clear(MM::Recycler * r)
{
  while (!steps->empty()) //FIXME
  {
    Event * e = steps->back();
    e->recycle(r);
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

/*
MM::FlowEvent * getFlow(MM::Instance * i, MM::Node * src, MM::Node * tgt)
{
  MM::FlowEvent * flow = MM_NULL;
  
  //resolve the Name of the Node src and Node tgt in Instance i
  
  //search through the transition to find if there is a flow between those names
  
  return flow;
}*/

MM::VOID MM::Transition::toString(MM::String * str)
{
  std::vector<MM::Event*>::iterator i;
  
  for(i = steps->begin(); i != steps->end(); i++)
  {
    (*i)->toString(str);
  }
}