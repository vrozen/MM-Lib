//
//  Assert.h
//  mm
//
//  Created by Riemer van Rozen on 7/29/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Assert__
#define __mm__Assert__

namespace MM
{
  class Assert : public MM::Element
  {
  public:
    static const MM::CHAR * ASSERT_STR;
    static const MM::UINT32 ASSERT_LEN;
    static const MM::CHAR * COLON_STR;
    static const MM::UINT32 COLON_LEN;
  private:
    MM::Name     * name;
    MM::Exp      * exp;
    MM::CHAR     * msg;
    MM::Location * loc;
  public:
    Assert(MM::Name * name, MM::Exp * exp, MM::CHAR * msg, MM::Location * loc);
    ~Assert();
    MM::Name * getName();
    MM::Exp * getExp();
    MM::CHAR * getMessage();
    MM::UINT32 getMessageLength();
    MM::Location * getLocation();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__Assert__) */
