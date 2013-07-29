//
//  ValueExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/19/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__ValExp__
#define __mm__ValExp__

namespace MM
{
  class ValExp : public MM::Exp
  {
  public:
    typedef enum __TYPE
    {
      T_ERROR,
      T_NUMBER,
      T_BOOLEAN,
      T_RANGE
    } TYPE;
  protected:
    ValExp();
  public:
    virtual ~ValExp();
    virtual MM::ValExp::TYPE getType() = 0;
    virtual MM::INT32 getIntValue() = 0;
    virtual MM::ValExp * eval() = 0;
    virtual MM::ValExp * eval(MM::Operator::OP op) = 0;
    virtual MM::ValExp * eval(MM::Operator::OP op, MM::ValExp * val) = 0;
    virtual MM::VOID toString(MM::String * buf) = 0;
  };
}

#endif /* defined(__mm__ValExp__) */
