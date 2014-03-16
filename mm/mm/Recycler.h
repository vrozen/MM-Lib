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
 * \class     Recycler
 * \brief     The Recycler abstraction is used to recycle recyclable objects.
 * \file      Recycler.h
 * \author    Riemer van Rozen
 * \date      August 1st 2013
 */
/******************************************************************************/

#ifndef __mm__Recycler__
#define __mm__Recycler__

namespace MM
{
  class Recycler
  {
  private:
    static MM::INT32 bufferCount;
    static const MM::CHAR * ORPHAN_MESSAGE;
    static const MM::CHAR * OBJECT_MESSAGE;
    static const MM::CHAR * BUFFER_MESSAGE;
    static const MM::UINT32 ORPHAN_MESSAGE_SIZE;
    static const MM::UINT32 OBJECT_MESSAGE_SIZE;
    static const MM::UINT32 BUFFER_MESSAGE_SIZE;

    MM::Vector<MM::Recyclable *> * objects;
  protected:
    Recycler();
    ~Recycler();
  public:
    virtual MM::TID getTypeId();
    virtual MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID create(MM::Recyclable * r);
    MM::VOID recycle(MM::Recyclable * r);
    MM::VOID uncreate(MM::Recyclable * r);
    static MM::VOID uncreate(MM::CHAR * str);
    static MM::CHAR * createBuffer(MM::UINT32 size);

  	static const MM::CHAR * TYPE_STR[];
  };
}

#endif /* defined(__mm__Recycler__) */
