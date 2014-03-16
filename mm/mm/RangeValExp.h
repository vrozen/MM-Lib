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
 * \class     RangeValExp
 * \brief     The RangeValExp abstraction defines range value expressions.
 * \file      RangeValExp.h
 * \author    Riemer van Rozen
 * \date      July 19th 2013
 */
/******************************************************************************/

#ifndef __mm__RangeValExp__
#define __mm__RangeValExp__

namespace MM
{
  class RangeValExp : public MM::ValExp
  {
  private:
    static const MM::CHAR * DOTDOT_STR; /**> dotdot literal string */
    static const MM::UINT32 DOTDOT_LEN; /**> dotdot literal string length */
    MM::UINT32 min;                     /**> minimum value */
    MM::UINT32 max;                     /**> maximum value */
    MM::Location * minLoc;              /**> minimum value source location */
    MM::Location * maxLoc;              /**> maximum value source location */
    MM::Location * rangeLoc;            /**> range (dotdot) source location */
  public:
    RangeValExp(MM::UINT32     min,
                MM::UINT32     max);
    RangeValExp(MM::UINT32     min,
                MM::UINT32     max,
                MM::Location * minLoc,
                MM::Location * maxLoc,
                MM::Location * rangeLoc);
    ~RangeValExp();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::UINT32 getMin();
    MM::UINT32 getMax();
    MM::INT32 getIntValue();
    MM::BOOLEAN greaterEquals(MM::UINT32 val);
    
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__RangeValExp__) */
