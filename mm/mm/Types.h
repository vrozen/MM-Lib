//
//  Types.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef mm_Types_h
#define mm_Types_h

namespace MM
{
  typedef unsigned char   UINT8;
  typedef long            INT32;
  typedef unsigned long   UINT32;
  typedef char            CHAR;
  typedef void            VOID;
  typedef bool            BOOLEAN;
  typedef struct __NUMBER
  {
    MM::UINT32 v;
    MM::UINT8  m;
  }                       NUMBER;
}

#define MM_TRUE  true
#define MM_FALSE false

#endif
