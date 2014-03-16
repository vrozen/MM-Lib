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
 * \class     Location
 * \brief     The Location abstraction defines textual source locations.
 * \file      Location.h
 * \author    Riemer van Rozen
 * \date      July 27th 2013
 */
/******************************************************************************/

#ifndef __mm__Location__
#define __mm__Location__

namespace MM
{
  class Location : public MM::Recyclable
  {
  private:
    static const MM::CHAR * LOCATION_STR; /**> location string */
    static const MM::UINT32 LOCATION_LEN; /**> location string length */
    static const MM::CHAR * LINE_STR;     /**> line string */
    static const MM::UINT32 LINE_LEN;     /**> line string length */
    static const MM::CHAR * COLUMN_STR;   /**> column string */
    static const MM::UINT32 COLUMN_LEN;   /**> column string length */
    static const MM::CHAR * LENGTH_STR;   /**> length string */
    static const MM::UINT32 LENGTH_LEN;   /**> length string length */
    
    MM::UINT32 line;    /**> begin line number */
    MM::UINT32 col;     /**> begin column number */
    MM::UINT32 endLine; /**> end line number */
    MM::UINT32 endCol;  /**> end column number */
  public:
    Location(MM::UINT32 beginLine,
             MM::UINT32 beginCol,
             MM::UINT32 endLine,
             MM::UINT32 endCol);
    ~Location();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);

    MM::UINT32 getLine();
    MM::UINT32 getColumn();
    MM::UINT32 getLength();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__Location__) */
