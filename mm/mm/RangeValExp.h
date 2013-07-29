//
//  RangeValExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/19/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__RangeValExp__
#define __mm__RangeValExp__

namespace MM
{
  class RangeValExp : public MM::ValExp
  {
  private:
    static const MM::CHAR * DOTDOT_STR;
    static const MM::UINT32 DOTDOT_LEN;
    MM::UINT32 min;
    MM::UINT32 max;
    MM::Location * minLoc;
    MM::Location * maxLoc;
    MM::Location * rangeLoc;
  public:
    RangeValExp(MM::UINT32     min,
                MM::UINT32     max);
    RangeValExp(MM::UINT32     min,
                MM::UINT32     max,
                MM::Location * minLoc,
                MM::Location * maxLoc,
                MM::Location * rangeLoc);
    ~RangeValExp();
    MM::ValExp::TYPE getType();
    MM::UINT32 getMin();
    MM::UINT32 getMax();
    MM::INT32 getIntValue();
    MM::ValExp * eval();
    MM::ValExp * eval(MM::Operator::OP op);
    MM::ValExp * eval(MM::Operator::OP op, MM::ValExp * val);
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__RangeValExp__) */