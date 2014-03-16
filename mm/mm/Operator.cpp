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
 * The Operator abstraction defines operator lexicals and codes.
 * @package MM
 * @file    Operator.cpp
 * @author  Riemer van Rozen
 * @date    July 27th 2013
 */
/******************************************************************************/
#include <string.h>
#include "Types.h"
#include "Operator.h"

const MM::CHAR * MM::Operator::OP_STR[] =
{
  "error",
  "+",
  "-",
  "*",
  "/",
  "&&",
  "||",
  ">",
  "<",
  "<=",
  ">=",
  "==",
  "!=",
  "~",
  "!",
  "%",
  "|"
};

const MM::UINT32 MM::Operator::OP_LEN[] =
{
  strlen(OP_STR[0]), /**> error */
  strlen(OP_STR[1]), /**> +     */
  strlen(OP_STR[2]), /**> -     */
  strlen(OP_STR[3]), /**> *     */
  strlen(OP_STR[4]), /**> /     */
  strlen(OP_STR[5]), /**> &&    */
  strlen(OP_STR[6]), /**> ||    */
  strlen(OP_STR[7]), /**> >     */
  strlen(OP_STR[8]), /**> <     */
  strlen(OP_STR[9]), /**> <=    */
  strlen(OP_STR[10]), /**> >=    */
  strlen(OP_STR[11]), /**> ==    */
  strlen(OP_STR[12]), /**> !=    */
  strlen(OP_STR[13]), /**> ~     */
  strlen(OP_STR[14]), /**> !     */
  strlen(OP_STR[15]), /**> %     */
  strlen(OP_STR[16])  /**> |     */
};
