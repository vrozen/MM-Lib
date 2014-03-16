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
 * \class     BooleanValExp
 * \brief     The BooleanValExp abstraction defines boolean value expressions.
 * \file      BooleanValExp.h
 * \author    Riemer van Rozen
 * \date      July 19th 2013
 */
/******************************************************************************/

#ifndef __mm__BooleanValExp__
#define __mm__BooleanValExp__

namespace MM
{
  class BooleanValExp : public MM::ValExp
  {
  private:
    static const MM::CHAR * TRUE_STR;  /**> true literal string */
    static const MM::CHAR * FALSE_STR; /**> false literal string */
    static const MM::UINT32 TRUE_LEN;  /**> true literal string length */
    static const MM::UINT32 FALSE_LEN; /**> false literal string length */
    MM::BOOLEAN val;                   /**> bolean value */
    MM::Location * loc;                /**> source location */
  public:
    BooleanValExp(MM::BOOLEAN val);
    BooleanValExp(MM::BOOLEAN val, MM::Location * loc);
    ~BooleanValExp();
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID recycle(MM::Recycler * r);
    MM::BOOLEAN getValue();
    MM::Location * getLocation();
    MM::BOOLEAN greaterEquals(MM::UINT32 val);
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__BooleanValExp__) */
