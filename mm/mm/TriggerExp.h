/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The TriggerExp abstraction expresses that a source of a state edge
 * activates the target of that edge if all of the edge the source operates
 * on are satisfied (meaning a flow of one or more exists for that edge).
 * @note The notion of satisfied does not respect all or any modifiers of nodes.
 * @package MM
 * @file    TriggerExp.h
 * @author  Riemer van Rozen
 * @date    July 20th 2013
 */
/******************************************************************************/

#ifndef __mm__TriggerExp__
#define __mm__TriggerExp__

namespace MM
{
  /**
   * @class TriggerExp
   * @brief Defines the TriggerExp class
   */
  class TriggerExp : public MM::Exp
  {
  private:
    MM::Location * loc;                  /**< trigger source location */
  public:
    static const MM::CHAR TRIGGER_CHAR;  /**< trigger string */
    TriggerExp();
    TriggerExp(MM::Location * loc);
    ~TriggerExp();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__TriggerExp__) */
