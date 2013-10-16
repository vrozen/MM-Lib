/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The Exp abstraction is the abstract super class of all expessions.
 * @package MM
 * @file    Exp.h
 * @author  Riemer van Rozen
 * @date    July 11th 2013
 */
/******************************************************************************/
#ifndef __mm__Exp__
#define __mm__Exp__

namespace MM
{
  class ValExp;
  class Machine;
  class Edge;
  
  /**
   * @class Name
   * @brief Defines the Name class
   */
  class Exp : public MM::Recyclable
  {
  protected:
    Exp();
  public:
    virtual ~Exp() = 0;
    virtual MM::VOID recycle(MM::Recycler * r) = 0;
    virtual MM::TID getTypeId();
    virtual MM::BOOLEAN instanceof(MM::TID tid);
    virtual MM::VOID toString(MM::String * buf) = 0;
     
    //NOTE: state edges that are not triggers are conditions
    
    //TODO: transformation: one() * one() --> TriggerExp()
    
    //NOTE: all (dynamic) evals should refer to Machine for allocating objects
    
  };
}
#endif /* defined(__mm__Exp__) */
