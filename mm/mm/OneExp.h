//
//  OneExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/20/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__OneExp__
#define __mm__OneExp__

namespace MM
{
  class OneExp : public MM::Exp
  {
  private:
    MM::Location * loc;
  public:
    OneExp();
    OneExp(MM::Location * loc);
    ~OneExp();
    MM::ValExp * eval();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__OneExp__) */
