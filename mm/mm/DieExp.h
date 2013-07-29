//
//  DieExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/20/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__DieExp__
#define __mm__DieExp__

namespace MM
{
  class DieExp : public MM::Exp
  {
  private:
    static const MM::CHAR * DIE_STR;
    static const MM::UINT32 DIE_LEN;
    MM::UINT32 max;
    MM::Location * maxLoc;
    MM::Location * dieLoc;
  public:
    DieExp(MM::UINT32 max);
    DieExp(MM::UINT32     max,
           MM::Location * maxLoc,
           MM::Location * dieLoc);
    ~DieExp();
    MM::ValExp * eval();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__DieExp__) */
