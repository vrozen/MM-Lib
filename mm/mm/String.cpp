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
//
//  String.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Recycler.h"
#include "String.h"

const MM::CHAR MM::String::SPACE_CHAR      = ' ';
const MM::CHAR MM::String::LINEBREAK_CHAR  = '\n';
const MM::UINT32 MM::String::RESIZE_FACTOR = 2;

MM::String::String(MM::CHAR * buf, MM::UINT32 size) : MM::Recyclable()
{
  this->size = size;
  this->used = 0;
  this->buf = buf;
}

MM::String::~String()
{
  size = 0;
  used = 0;
  buf = MM_NULL;
}

MM::VOID MM::String::recycle(MM::Recycler * r)
{
  r->uncreate(buf);
  this->MM::Recyclable::recycle(r);
}

MM::TID MM::String::getTypeId()
{
  return MM::T_String;
}

MM::BOOLEAN MM::String::instanceof(TID tid)
{
  if(tid == MM::T_String)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

MM::UINT32 MM::String::getSize()
{
  return this->size;
}

MM::UINT32 MM::String::getUsed()
{
  return this->used;
}

MM::CHAR * MM::String::getBuffer()
{
  return this->buf;
}

MM::VOID MM::String::append(MM::String * str)
{
  append(str->getBuffer(), str->getSize());
}

MM::VOID MM::String::append(MM::CHAR * buf, MM::UINT32 len)
{
  if(this->used + len < this->size)
  {
    strncat(this->buf + this->used, buf, len);
    this->used += len;
  }
  else
  {
    resize(this->size * MM::String::RESIZE_FACTOR);
    append(buf, len);
  }
}

MM::VOID MM::String::resize(MM::UINT32 size)
{
  this->size = size;
  //MM::CHAR * newBuf = new char[size];
  MM::CHAR * newBuf = MM::Recycler::createBuffer(size);
  //memset(newBuf, 0, size);
  snprintf(newBuf, size-1, "%s", buf);
  MM::Recycler::uncreate(buf);
  //delete buf;
  //r->uncreate(buf);
  buf = newBuf;
}

MM::VOID MM::String::appendInt(MM::INT32 val)
{
  MM::UINT32 ulDigits = digits(val);
  
  if(this->used + ulDigits < this->size)
  {
    snprintf(this->buf + this->used, this->size - this->used, "%ld", val);
    this->used += ulDigits;
  }
  else
  {
    resize(this->size * MM::String::RESIZE_FACTOR);
    appendInt(val);
  }
}

MM::VOID MM::String::append(MM::CHAR c)
{
  if(this->used < this->size)
  {
    snprintf(this->buf + this->used, this->size - this->used, "%c", c);
    this->used++;
  }
}

MM::VOID MM::String::space()
{
  append(MM::String::SPACE_CHAR);
}

MM::VOID MM::String::space(MM::UINT32 amount)
{
  for(MM::UINT32 i = 0; i < amount; i++)
  {
    space();
  }
}

MM::VOID MM::String::linebreak()
{
  append(MM::String::LINEBREAK_CHAR);
}

MM::VOID MM::String::clear()
{
  this->used = 0;
  memset(this->buf, 0, this->size);
}

MM::VOID MM::String::print()
{
  fprintf(stdout, "%s", buf);
  fflush(stdout);
}

MM::UINT32 MM::String::digits(MM::INT32 val)
{
  MM::UINT32 digits = 0;
  if (val <= 0)
  {
    digits = 1;
  }
  while (val)
  {
    val /= 10;
    digits++;
  }
  return digits;
}

MM::VOID MM::String::toString(MM::String * buf)
{ 
  buf->append(this);
}