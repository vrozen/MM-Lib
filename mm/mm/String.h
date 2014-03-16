/******************************************************************************
 * Copyright (c) 2013-2014, Amsterdam University of Applied Sciences (HvA) and
 *                          Centrum Wiskunde & Informatica (CWI)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contributors:
 *   * Riemer van Rozen - rozen@cwi.nl - HvA / CWI
 ******************************************************************************/
/*!
 * \namespace MM
 * \class     String
 * \brief     The String abstraction defines bounded String buffers.
 * \file      String.h
 * \author    Riemer van Rozen
 * \date      October 7th 2013
 */
/******************************************************************************/

#ifndef __mm__String__
#define __mm__String__

namespace MM
{
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
