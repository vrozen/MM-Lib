//
//  NumberValExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/19/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__NumberValExp__
#define __mm__NumberValExp__

namespace MM
{
  class RangeValExp;
  class NumberValExp : public MM::ValExp
  {
  private:
    static const MM::CHAR * DOT_STR;
    static const MM::UINT32 DOT_LEN;
    MM::INT32 val;
    MM::Location * loc;
  public:
    NumberValExp(MM::INT32 val);
    NumberValExp(MM::INT32 val, MM::Location * loc);
    NumberValExp(MM::INT32 val, MM::UINT8 fraction);
    NumberValExp(MM::INT32 val, MM::UINT8 fraction, MM::Location * loc);
    ~NumberValExp();
    MM::ValExp::TYPE getType();
    MM::INT32 getValue();
    MM::INT32 getIntValue();
    MM::ValExp * eval();
    MM::ValExp * eval(MM::Operator::OP op);
    MM::ValExp * eval(MM::Operator::OP op, MM::ValExp * val);
    MM::Location * getLocation();
    MM::VOID toString(MM::String * buf);
  private:
    MM::ValExp * evalNumber(MM::Operator::OP op, MM::NumberValExp * v);
    MM::ValExp * evalRange(MM::Operator::OP op, MM::RangeValExp * v);
  };
}

#endif /* defined(__mm__NumberValExp__) */
