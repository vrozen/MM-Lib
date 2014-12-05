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
 * \class     Name
 * \brief     The Name abstraction is used to compose identifiers into
 *            qualified names used to lookup named language elements.
 * \file      Name.h
 * \author    Riemer van Rozen
 * \date      July 27th 2013
 */
/******************************************************************************/

#ifndef __mm__Name__
#define __mm__Name__

namespace MM
{
  class Name : public MM::Recyclable
  {
  private:
	static const MM::CHAR DOT_CHAR; /**> dot character */
	  MM::CHAR     * str;             /**> string buffer */
    MM::UINT32     len;             /**> string length */
    MM::Location * loc;             /**> location */
    MM::Name     * name;            /**> child name */
    MM::Name     * pre;             /**> prefix name (used only for edges) */
  protected:
    ~Name();
  public:
    Name(MM::CHAR * str, MM::UINT32 len);
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);    
    MM::BOOLEAN equals(MM::Name * name);
    MM::BOOLEAN equals(MM::CHAR * str, MM::UINT32 len);
    
    friend MM::BOOLEAN operator < (const Name & n1, const Name & n2)
    {
      MM::BOOLEAN lt = MM_FALSE;
      if(n1.len < n2.len)
      {
        return MM_TRUE;
      }
      else if(n1.len == n2.len)
      {
        if(strncmp(n1.str, n2.str, n1.len) < 0)
        {
          lt = MM_TRUE;
        }
      }
      return lt;
    }
    
    /**
     * /brief The Compare class defines comparison between names
     */
    class Compare
    {
    public:
      bool operator()(MM::Name const * n1, MM::Name const * n2) const
      {
        MM::BOOLEAN lt = *n1 < *n2;
        return lt;
      }
    };
    
    MM::UINT32 getLength();
    MM::VOID setName(MM::Name * name);
    MM::Name * getName();
    MM::VOID setPreName(MM::Name * name);
    MM::Name * getPreName();
    
    MM::VOID append(MM::Name * name);
    MM::VOID print(); //debug
    MM::CHAR * getBuffer();
    MM::Location * getLocation();
    MM::VOID setLocation(MM::Location * loc);
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__Name__) */
