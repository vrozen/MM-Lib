//
//  String.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__String__
#define __mm__String__

namespace MM
{
  class String
  {
  private:
    static const MM::CHAR * SPACE_STR;
    static const MM::CHAR * LINEBREAK_STR;
    static const MM::UINT32 SPACE_LEN;
    static const MM::UINT32 LINEBREAK_LEN;
    static const MM::UINT32 RESIZE_FACTOR;
    MM::UINT32 size;
    MM::UINT32 used;
    MM::CHAR * buf;
    MM::UINT32 digits(MM::INT32 val);
    MM::VOID resize(MM::UINT32 size);
  public:
    String(MM::UINT32 size);
    ~String();
    MM::String * clone();
    MM::UINT32 getSize();
    MM::UINT32 getUsed();
    MM::CHAR * getBuffer();
    MM::VOID append(MM::String * str);
    MM::VOID append(MM::CHAR * buf, MM::UINT32 len);
    MM::VOID append(MM::INT32 val);
    MM::VOID space();
    MM::VOID linebreak();
    MM::VOID clear();
    MM::VOID print();
  };
}
#endif /* defined(__mm__String__) */
