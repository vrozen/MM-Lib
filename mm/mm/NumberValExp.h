/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The NumberValExp abstraction defines number value expressions.
 * @package MM
 * @file    NumberValExp.h
 * @author  Riemer van Rozen
 * @date    July 19th 2013
 */
/******************************************************************************/
#ifndef __mm__NumberValExp__
#define __mm__NumberValExp__

namespace MM
{
  class RangeValExp;
 
  /**
   * @class NumberValExp
   * @brief Defines the NumberValExp class
   */
  class NumberValExp : public MM::ValExp
  {
  private:
    static const MM::CHAR DOT_CHAR; /**> dot character */
    MM::INT32 val;                  /**> value */
    MM::Location * loc;             /**> value source location */
  public:
    NumberValExp(MM::INT32 val);
    NumberValExp(MM::INT32 val, MM::Location * loc);
    NumberValExp(MM::INT32 val, MM::UINT8 fraction);
    NumberValExp(MM::INT32 val, MM::UINT8 fraction, MM::Location * loc);
    ~NumberValExp();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::INT32 getValue();
    MM::INT32 getIntValue();
    MM::Location * getLocation();
    MM::BOOLEAN greaterEquals(MM::UINT32 val);
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__NumberValExp__) */
