/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The RangeValExp abstraction defines range value expressions.
 * @package MM
 * @file    RangeValExp.cpp
 * @author  Riemer van Rozen
 * @date    July 19th 2013
 */
/******************************************************************************/
#ifndef __mm__RangeValExp__
#define __mm__RangeValExp__

namespace MM
{
  class RangeValExp : public MM::ValExp
  {
  private:
    static const MM::CHAR * DOTDOT_STR; /**> dotdot literal string */
    static const MM::UINT32 DOTDOT_LEN; /**> dotdot literal string length */
    MM::UINT32 min;                     /**> minimum value */
    MM::UINT32 max;                     /**> maximum value */
    MM::Location * minLoc;              /**> minimum value source location */
    MM::Location * maxLoc;              /**> maximum value source location */
    MM::Location * rangeLoc;            /**> range (dotdot) source location */
  public:
    RangeValExp(MM::UINT32     min,
                MM::UINT32     max);
    RangeValExp(MM::UINT32     min,
                MM::UINT32     max,
                MM::Location * minLoc,
                MM::Location * maxLoc,
                MM::Location * rangeLoc);
    ~RangeValExp();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::UINT32 getMin();
    MM::UINT32 getMax();
    MM::INT32 getIntValue();
    MM::BOOLEAN greaterEquals(MM::UINT32 val);
    
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__RangeValExp__) */
