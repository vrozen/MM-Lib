/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The ActiveExp abstraction expresses that a target of a state edge
 * with an ActiveExp is only active if the source is active.
 * @package MM
 * @file    ActiveExp.h
 * @author  Riemer van Rozen
 * @date    July 21th 2013
 */
/******************************************************************************/
#ifndef __mm__ActiveExp__
#define __mm__ActiveExp__

namespace MM
{
  /**
   * @class ActiveExp
   * @brief Defines the ActiveExp class
   */
  class ActiveExp : public MM::Exp
  {
  private:
    MM::Name     * name; /**> name */
    MM::Location * loc;  /**> source location */
  public:
    static const MM::CHAR * ACTIVE_STR;
    static const MM::UINT32 ACTIVE_LEN;
    ActiveExp(MM::Name * name);
    ActiveExp(MM::Name     * name,
              MM::Location * loc);
    ~ActiveExp();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);    
    MM::Name * getName();    
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__ActiveExp__) */
