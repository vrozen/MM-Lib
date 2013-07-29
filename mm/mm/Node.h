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
  class Transition;
  
  class Node : public MM::Element
  {
  public:
    typedef enum __IO
    {
      IO_ERROR,
      IO_PRIVATE,
      IO_IN,
      IO_OUT,
      IO_INOUT
    } IO;
    
    typedef enum __When
    {
      WHEN_ERROR,
      WHEN_PASSIVE,
      WHEN_AUTO,
      WHEN_USER,
      WHEN_START
    } When;
    
    typedef enum __Act
    {
      ACT_ERROR,
      ACT_PULL,
      ACT_PUSH
    } Act;
    
    typedef enum __How
    {
      HOW_ERROR,
      HOW_ANY,
      HOW_ALL
    } How;
    
    static const MM::CHAR * IO_STR[];
    static const MM::CHAR * WHEN_STR[];
    static const MM::CHAR * ACT_STR[];
    static const MM::CHAR * HOW_STR[];
    
    static const MM::UINT32 IO_LEN[];
    static const MM::UINT32 WHEN_LEN[];
    static const MM::UINT32 ACT_LEN[];
    static const MM::UINT32 HOW_LEN[];
    
  private:
    std::vector<MM::Edge*> * input;
    std::vector<MM::Edge*> * output;
    std::vector<MM::Edge*> * cond;
    MM::Name * name;
    MM::Node::IO io;
    MM::Node::When when;
    MM::Node::Act act;
    MM::Node::How how;
    //MM::BOOLEAN active;
  protected:
    Node(MM::Node::IO io,
         MM::Node::When when,
         MM::Node::Act act,
         MM::Node::How how,
         MM::Name * name);
  public:
    virtual ~Node();
    MM::Name * getName();
    MM::VOID addInput(MM::Edge * edge);
    MM::VOID addOutput(MM::Edge * edge);
    MM::VOID addCondition(MM::Edge * edge);
    MM::VOID removeInput(MM::Edge * edge);
    MM::VOID removeOutput(MM::Edge * edge);
    MM::VOID removeCondition(MM::Edge * edge);
    MM::Node::When getWhen();
    MM::Node::Act getAct();
    MM::Node::How getHow();
    std::vector<Edge*> * getInput();
    std::vector<Edge*> * getOutput();
    std::vector<Edge*> * getCond();
    MM::VOID setWhen(MM::Node::When when);
    MM::VOID setAct(MM::Node::Act act);
    MM::VOID setHow(MM::Node::How how);
    MM::BOOLEAN isActive();
    virtual MM::BOOLEAN hasCapacity() = 0;
    virtual MM::BOOLEAN hasResources() = 0;
    virtual MM::BOOLEAN hasCapacity(MM::UINT32 amount) = 0;
    virtual MM::BOOLEAN hasResources(MM::UINT32 amount) = 0;
    virtual MM::VOID sub(MM::UINT32 amount) = 0;
    virtual MM::VOID add(MM::UINT32 amount) = 0;
    MM::Transition * step();
  private:
    MM::Transition * stepAll(std::vector<Edge*> * work);
    MM::Transition * stepAny(std::vector<Edge*> * work);
  public:
    MM::VOID toString(MM::String * buf);
  };
}
#endif /* defined(__mm__Node__) */