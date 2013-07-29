//
//  AllValExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/19/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__AllValExp__
#define __mm__AllValExp__

namespace MM
{
  class AllExp : public MM::Exp
  {
  private:
    static const MM::CHAR * ALL_STR;
    static const MM::UINT32 ALL_LEN;
    MM::Location * loc;
  public:
    AllExp();
    AllExp(MM::Location * loc);
    ~AllExp();
    MM::ValExp * eval();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__AllValExp__) */
