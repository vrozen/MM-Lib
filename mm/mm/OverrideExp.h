//
//  OverrideExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/20/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__OverrideExp__
#define __mm__OverrideExp__

namespace MM
{
  class OverrideExp : public MM::Exp
  {
  private:
    MM::Exp * exp;
    MM::Location * lparenLoc;
    MM::Location * rparenLoc;
  public:
    static const MM::CHAR * LPAREN_STR;
    static const MM::CHAR * RPAREN_STR;
    static const MM::UINT32 LPAREN_LEN;
    static const MM::UINT32 RPAREN_LEN;
    OverrideExp(MM::Exp * exp);
    OverrideExp(MM::Exp      * exp,
                MM::Location * lparenLoc,
                MM::Location * rparenLoc);
    ~OverrideExp();
    MM::ValExp * eval();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__OverrideExp__) */
