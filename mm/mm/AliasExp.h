//
//  RefExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/20/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__AliasExp__
#define __mm__AliasExp__

namespace MM
{
  class AliasExp : public MM::Exp
  {
  private:
    MM::Location * loc;
  public:
    static const MM::CHAR * ALIAS_STR;
    static const MM::UINT32 ALIAS_LEN;
    AliasExp();
    AliasExp(MM::Location * loc);
    ~AliasExp();
    MM::ValExp * eval();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__AliasExp__) */
