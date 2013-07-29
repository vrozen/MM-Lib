//
//  BinExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/18/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__BinExp__
#define __mm__BinExp__

namespace MM
{
  class BinExp : public MM::Exp
  {
  private:
    MM::Exp          * e1;
    MM::Exp          * e2;
    MM::Operator::OP   op;
    MM::Location     * loc;    
  public:
    BinExp(MM::Exp          * e1,
           MM::Operator::OP   op,
           MM::Exp          * e2);
    BinExp(MM::Exp          * e1,
           MM::Operator::OP   op,
           MM::Exp          * e2,
           MM::Location     * loc);
    ~BinExp();
    MM::ValExp * eval();
    MM::VOID toString(MM::String * buf);
  };
}


#endif /* defined(__mm__BinExp__) */
