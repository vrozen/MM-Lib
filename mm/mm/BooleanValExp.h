/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The BooleanValExp abstraction defines boolean value expressions.
 * @package MM
 * @file    BooleanValExp.h
 * @author  Riemer van Rozen
 * @date    July 19th 2013
 */
/******************************************************************************/
#ifndef __mm__BooleanValExp__
#define __mm__BooleanValExp__

namespace MM
{
  /**
   * @class BooleanValExp
   * @brief Defines the BooleanValExp class
   */
  class BooleanValExp : public MM::ValExp
  {
  private:
    static const MM::CHAR * TRUE_STR;  /**> true literal string */
    static const MM::CHAR * FALSE_STR; /**> false literal string */
    static const MM::UINT32 TRUE_LEN;  /**> true literal string length */
    static const MM::UINT32 FALSE_LEN; /**> false literal string length */
    MM::BOOLEAN val;                   /**> value */
    MM::Location * loc;                /**> source location */
  public:
    BooleanValExp(MM::BOOLEAN val);
    BooleanValExp(MM::BOOLEAN val, MM::Location * loc);
    ~BooleanValExp();
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID recycle(MM::Recycler * r);
    MM::BOOLEAN getValue();
    MM::Location * getLocation();
    MM::BOOLEAN greaterEquals(MM::UINT32 val);
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__BooleanValExp__) */
