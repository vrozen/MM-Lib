/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The OneExp abstraction expresses shorthand on edges
 *  -->    : OneExp has a flow of one: NumberValueExp(1)
 *  . * .> : BinExp has lhs OneExp and rhs OneExp: isTrigger() = MM_TRUE
 *  . == .>: BinExp has lhs OneExp and rhs OneExp:
 *           lhs OneExp refers to source and rhs OneExp refers to target
 * @package MM
 * @file    AliasExp.h
 * @author  Riemer van Rozen
 * @date    July 20th 2013
 */
/******************************************************************************/
#ifndef __mm__OneExp__
#define __mm__OneExp__

namespace MM
{
  /**
   * @class OneExp
   * @brief Defines the OneExp class
   */
  class OneExp : public MM::Exp
  {
  private:
    MM::Location * loc; /**> source locations */
  public:
    OneExp();
    OneExp(MM::Location * loc);
    ~OneExp();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__OneExp__) */
