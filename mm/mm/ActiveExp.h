//
//  ActiveExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/21/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__ActiveExp__
#define __mm__ActiveExp__

namespace MM
{
  class ActiveExp : public MM::Exp
  {
  private:
    MM::Name     * name;
    MM::Node     * ref;
    MM::Location * loc;
  public:
    static const MM::CHAR * ACTIVE_STR;
    static const MM::UINT32 ACTIVE_LEN;
    ActiveExp(MM::Name * name);
    ActiveExp(MM::Name     * name,
              MM::Location * loc);
    ~ActiveExp();
    MM::ValExp * eval();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__ActiveExp__) */
