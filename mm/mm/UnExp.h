//
//  UnExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/19/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__UnExp__
#define __mm__UnExp__

namespace MM
{
  class UnExp : public MM::Exp
  {
  private:
    MM::Exp * exp;
    MM::Operator::OP op;
    MM::Location * loc;
  public:
    UnExp(MM::Operator::OP op,
          MM::Exp * exp);
    UnExp(MM::Operator::OP op,
          MM::Exp * exp,          
          MM::Location * loc);
    ~UnExp();
    MM::ValExp * eval();
    MM::VOID toString(MM::String * buf);
  };
}


#endif /* defined(__mm__UnExp__) */
