//
//  Assertion.h
//  mm
//
//  Created by Riemer van Rozen on 7/29/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Assert__
#define __mm__Assert__

namespace MM
{
  class Assertion : public MM::Element
  {
  public:
    static const MM::CHAR * ASSERT_STR;
    static const MM::UINT32 ASSERT_LEN;
    static const MM::CHAR COLON_CHAR;
  private:
    MM::Exp      * exp; /**> assertion expression */
    MM::CHAR     * msg; /**> assertion message */
    MM::Location * loc; /**> assert source location */
  public:
    Assertion(MM::Name * name,
              MM::Exp * exp,
              MM::CHAR * msg,
              MM::Location * loc);
    Assertion(MM::Name * name,
              MM::Exp * exp,
              MM::CHAR * msg);
    ~Assertion();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::Exp * getExp();
    MM::CHAR * getMessage();
    MM::UINT32 getMessageLength();
    MM::Location * getLocation();
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}

#endif /* defined(__mm__Assertion__) */
