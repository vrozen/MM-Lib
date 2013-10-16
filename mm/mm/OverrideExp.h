/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The OverrideExp abstraction expresses an overriden expression.
 * @package MM
 * @file    OverrideExp.h
 * @author  Riemer van Rozen
 * @date    July 20th 2013
 */
/******************************************************************************/
#ifndef __mm__OverrideExp__
#define __mm__OverrideExp__

namespace MM
{
  /**
   * @class OverrideExp
   * @brief Defines the OverrideExp class
   */
  class OverrideExp : public MM::Exp
  {
  private:
    MM::Exp * exp;            /**> expression */
    MM::Location * lparenLoc; /**> left parenthesis location */
    MM::Location * rparenLoc; /**> right parenthesis location */
  public:
    static const MM::CHAR LPAREN_CHAR; /**> left parenthesis character */
    static const MM::CHAR RPAREN_CHAR; /**> right parenthesis character */
    OverrideExp(MM::Exp * exp);
    OverrideExp(MM::Exp      * exp,
                MM::Location * lparenLoc,
                MM::Location * rparenLoc);
    ~OverrideExp();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::Exp * getExp();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__OverrideExp__) */
