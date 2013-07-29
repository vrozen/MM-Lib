//
//  VarValExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/19/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__VarValExp__
#define __mm__VarValExp__

namespace MM
{
  class VarExp : public MM::Exp
  {
  private:
    MM::Name * name;
    MM::PoolNode * ref;
  public:
    VarExp(MM::Name * name);
    ~VarExp();
    MM::ValExp * eval();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__VarValExp__) */
