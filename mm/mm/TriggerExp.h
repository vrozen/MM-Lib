//
//  TriggerExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/20/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__TriggerExp__
#define __mm__TriggerExp__

namespace MM
{
  class TriggerExp : public MM::Exp
  {
  private:
    MM::Location * loc;
  public:
    static const MM::CHAR* TRIGGER_STR;
    static const MM::UINT32 TRIGGER_LEN;
    TriggerExp();
    TriggerExp(MM::Location * loc);
    ~TriggerExp();
    MM::ValExp * eval();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__TriggerExp__) */
