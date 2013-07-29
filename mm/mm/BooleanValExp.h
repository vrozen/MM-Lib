//
//  BooleanValExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/19/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__BooleanValExp__
#define __mm__BooleanValExp__

namespace MM
{
  class BooleanValExp : public MM::ValExp
  {
  private:
    static const MM::CHAR * TRUE_STR;
    static const MM::CHAR * FALSE_STR;
    static const MM::UINT32 TRUE_LEN;
    static const MM::UINT32 FALSE_LEN;
    MM::BOOLEAN val;
    MM::Location * loc;
  public:
    BooleanValExp(MM::BOOLEAN val);
    BooleanValExp(MM::BOOLEAN val, MM::Location * loc);
    ~BooleanValExp();
    MM::ValExp::TYPE getType();
    MM::BOOLEAN getValue();
    MM::INT32 getIntValue();
    MM::ValExp * eval();
    MM::ValExp * eval(MM::Operator::OP op);
    MM::ValExp * eval(MM::Operator::OP op, MM::ValExp * val);
    MM::Location * getLocation();
    MM::VOID toString(MM::String * buf);
  };
}


#endif /* defined(__mm__BooleanValExp__) */
