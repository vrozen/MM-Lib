//
//  Exp.h
//  mm
//
//  Created by Riemer van Rozen on 7/11/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Exp__
#define __mm__Exp__

namespace MM
{
  class ValExp;
  class Exp
  {
  protected:
    Exp();
  public:
    virtual ~Exp() = 0;
    virtual MM::ValExp * eval() = 0;
    virtual MM::VOID toString(MM::String * buf) = 0;
  };
}
#endif /* defined(__mm__Exp__) */
