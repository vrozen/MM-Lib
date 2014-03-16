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
 * \class     Operator
 * \brief     The Operator abstraction defines operator lexicals and codes.
 * \file      Operator.h
 * \author    Riemer van Rozen
 * \date      July 27th 2013
 */
/******************************************************************************/

#ifndef __mm__Operator__
#define __mm__Operator__

namespace MM
{
  class Operator
  {
  public:
    typedef enum __OP
    {
      OP_ERROR,   /**> error */
      OP_ADD,     /**> +     */
      OP_SUB,     /**> -     */
      OP_MUL,     /**> *     */
      OP_DIV,     /**> /     */
      OP_AND,     /**> &&    */
      OP_OR,      /**> ||    */
      OP_GT,      /**> >     */
      OP_LT,      /**> <     */
      OP_LE,      /**> <=    */
      OP_GE,      /**> >=    */
      OP_EQ,      /**> ==    */
      OP_NEQ,     /**> !=    */
      OP_UNM,     /**> ~     */
      OP_NOT,     /**> !     */
      OP_PERCENT, /**> %     */
      OP_PER      /**> |     */
    } OP;
    static const MM::CHAR * OP_STR[]; /**> Operator strings*/
    static const MM::UINT32 OP_LEN[]; /**> Operator string lengths*/
  };
}

#endif /* defined(__mm__Operator__) */
