//
//  Node.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Node__
#define __mm__Node__

namespace MM
{
  typedef enum __When
  {
    WHEN_PASSIVE,
    WHEN_AUTO,
    WHEN_USER,
    WHEN_START
  } When;
  
  typedef enum __Act
  {
    ACT_PULL,
    ACT_PUSH
  } Act;
  
  typedef enum __How
  {
    HOW_ANY,
    HOW_ALL
  } How;
  
  class Node : public Element
  {
  private:
    std::vector<MM::Edge*> * input;
    std::vector<MM::Edge*> * output;
    std::vector<MM::Edge*> * cond;
    MM::String * name;
    MM::When when;
    MM::Act act;
    MM::How how;
  protected:
    Node(MM::When when, MM::Act act, MM::How how, MM::String * name);
    virtual ~Node();
  public:
    //virtual Transition * step();
    MM::String * getName();
    MM::VOID addInput(MM::Edge * edge);
    MM::VOID addOutput(MM::Edge * edge);
    MM::VOID addCondition(MM::Edge * edge);
    MM::VOID removeInput(MM::Edge * edge);
    MM::VOID removeOutput(MM::Edge * edge);
    MM::VOID removeCondition(MM::Edge * edge);
    MM::When getWhen();
    MM::Act getAct();
    MM::How getHow();
    std::vector<Edge*> * getInput();
    std::vector<Edge*> * getOutput();
    std::vector<Edge*> * getCond();
    MM::VOID setWhen(MM::When when);
    MM::VOID setAct(MM::Act act);
    MM::VOID setHow(MM::How how);
    virtual MM::BOOLEAN hasCapacity() = 0;
    virtual MM::BOOLEAN hasResources() = 0;
    virtual MM::BOOLEAN hasCapacity(MM::UINT32 amount) = 0;
    virtual MM::BOOLEAN hasResources(MM::UINT32 amount) = 0;
    virtual MM::VOID sub(MM::UINT32 amount) = 0;
    virtual MM::VOID add(MM::UINT32 amount) = 0;
    MM::VOID toString(MM::String * buf);
  };
}
#endif /* defined(__mm__Node__) */