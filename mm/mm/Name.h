//
//  Name.h
//  mm
//
//  Created by Riemer van Rozen on 7/27/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Name__
#define __mm__Name__

namespace MM
{
  class Name
  {
  private:
    MM::CHAR     * str;
    MM::Location * loc;
    MM::Name     * sub;
  public:
    static const MM::CHAR * DOT_STR;
    static const MM::UINT32 DOT_LEN;
    Name(MM::CHAR * str);
    Name(MM::CHAR * str, MM::Location * loc);
    ~Name();
    MM::VOID setSubName(Name * sub);
    MM::CHAR* getBuffer();
    MM::UINT32 getLength();
    MM::Location * getLocation();
    MM::VOID toString(String * buf);
  };
}

#endif /* defined(__mm__Name__) */
