/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The AliasExp abstraction expresses that a source of a state edge
 * with an AliasExp is an alias of the target of that edge.
 * @package MM
 * @file    AliasExp.h
 * @author  Riemer van Rozen
 * @date    July 20th 2013
 */
/******************************************************************************/
#ifndef __mm__AliasExp__
#define __mm__AliasExp__

namespace MM
{
  /**
   * @class AliasExp
   * @brief Defines the AliasExp class
   */
  class AliasExp : public MM::Exp
  {
  private:
    MM::Location * loc;               /**> source location */
  public:
    static const MM::CHAR ALIAS_CHAR; /**> alias character */
    AliasExp();
    AliasExp(MM::Location * loc);
    ~AliasExp();
    MM::VOID recycle(MM::Recycler * r);    
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__AliasExp__) */
