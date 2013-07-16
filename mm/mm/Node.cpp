//
//  Node.cpp
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

const MM::CHAR * WHEN_STR[] =
{
  "passive",
  "auto",
  "user",
  "start"
};

const MM::CHAR * ACT_STR[] =
{
  "pull",
  "push"
};

const MM::CHAR * HOW_STR[] =
{
  "any",
  "all"
};

MM::Node::Node(MM::When when, MM::Act act, MM::How how, MM::String * name): MM::Element()
{
  this->when = when;
  this->act = act;
  this->how = how;
  this->name = name;
  this->input = new std::vector<Edge*>();
  this->output = new std::vector<Edge*>();
  this->cond = new std::vector<Edge*>();
}

MM::Node::~Node()
{
  delete name;
  delete input;
  delete output;
  delete cond;
}

MM::String * MM::Node::getName()
{
  return name;
}

MM::VOID MM::Node::addInput(MM::Edge * edge)
{
  this->input->push_back(edge);
}

MM::VOID MM::Node::addOutput(MM::Edge * edge)
{
  this->output->push_back(edge);
}

MM::VOID MM::Node::addCondition(MM::Edge * edge)
{
  this->cond->push_back(edge);
}

MM::VOID MM::Node::removeInput(MM::Edge * edge)
{
  //todo
}

MM::VOID MM::Node::removeOutput(MM::Edge * edge)
{
  //todo
}


MM::VOID MM::Node::removeCondition(MM::Edge * edge)
{
  //todo
}

MM::When MM::Node::getWhen()
{
  return when;
}

MM::Act MM::Node::getAct()
{
  return act;
}

MM::How MM::Node::getHow()
{
  return how;
}

std::vector<MM::Edge*> * MM::Node::getInput()
{
  return input;
}

std::vector<MM::Edge*> * MM::Node::getOutput()
{
  return output;
}

std::vector<MM::Edge*> * MM::Node::getCond()
{
  return cond;
}

MM::VOID MM::Node::setWhen(MM::When when)
{
  this->when = when;
}

MM::VOID MM::Node::setAct(MM::Act act)
{
  this->act = act;
}

MM::VOID MM::Node::setHow(MM::How how)
{
  this->how = how;
}

MM::VOID MM::Node::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)WHEN_STR[when], strlen(WHEN_STR[when]));
  buf->space();
  buf->append((MM::CHAR*)ACT_STR[act], strlen(ACT_STR[act]));
  buf->space();
  buf->append((MM::CHAR*)HOW_STR[how], strlen(HOW_STR[how]));
  buf->space();
}
