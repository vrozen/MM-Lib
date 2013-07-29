//
//  String.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <iostream>
#include "Types.h"
#include "String.h"

const MM::CHAR * MM::String::SPACE_STR      = " ";
const MM::CHAR * MM::String::LINEBREAK_STR  = "\n";
const MM::UINT32 MM::String::SPACE_LEN      = 1;
const MM::UINT32 MM::String::LINEBREAK_LEN  = 1;
const MM::UINT32 MM::String::RESIZE_FACTOR  = 2;

MM::String::String(MM::UINT32 size)
{
  this->size = size;
  this->used = 0;
  this->buf = new MM::CHAR[size];
  memset(this->buf, 0, size);
}

MM::String::~String()
{
  delete buf;
}

MM::String * MM::String::clone()
{
  MM::String * r = new MM::String(size);
  r->append(this);
  return r;
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
  char* pcNew = new char[size];
  memset(this->buf, 0, size);
  snprintf(pcNew, size-1, "%s", buf);
  delete buf;
  buf = pcNew;
}

MM::VOID MM::String::append(MM::INT32 val)
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
    append(val);
  }
}

MM::VOID MM::String::space()
{
  append((MM::CHAR*)MM::String::SPACE_STR, MM::String::SPACE_LEN);
}

MM::VOID MM::String::linebreak()
{
  append((MM::CHAR*)MM::String::LINEBREAK_STR, MM::String::LINEBREAK_LEN);
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