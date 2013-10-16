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
  /**
   * @class String
   * @brief Defines the String class.
   */
  class String : public MM::Recyclable
  {
  private:
    static const MM::CHAR SPACE_CHAR;      /**> space character */
    static const MM::CHAR LINEBREAK_CHAR;  /**> linebreak character */
    static const MM::UINT32 RESIZE_FACTOR; /**> reallocation resize factor */
    MM::UINT32 size;                       /**> allocated buffer size */
    MM::UINT32 used;                       /**> used buffer size */
    MM::CHAR * buf;                        /**> character buffer */
    MM::UINT32 digits(MM::INT32 val);
    MM::VOID resize(MM::UINT32 size);
    static MM::UINT32 getId();
  public:
    String(MM::CHAR * buf, MM::UINT32 size);
    ~String();
    MM::VOID recycle(MM::Recycler * r);    
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(TID tid);
    MM::UINT32 getSize();
    MM::UINT32 getUsed();
    MM::CHAR * getBuffer();
    MM::VOID append(MM::String * str);
    MM::VOID append(MM::CHAR * buf, MM::UINT32 len);
    MM::VOID append(MM::CHAR c);
    MM::VOID appendInt(MM::INT32 val);
    MM::VOID space();
    MM::VOID space(MM::UINT32 amount);
    MM::VOID linebreak();
    MM::VOID clear();
    MM::VOID print();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__String__) */
