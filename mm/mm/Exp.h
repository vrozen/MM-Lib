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
  class Exp
  {
  private:
    MM::UINT32 val;
  public: //protected
    Exp(MM::UINT32 val);
    virtual ~Exp();
  };
}
#endif /* defined(__mm__Exp__) */
