//
//  Operator.h
//  mm
//
//  Created by Riemer van Rozen on 7/27/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Operator__
#define __mm__Operator__

namespace MM
{
  class Operator
  {
  public:
    typedef enum __OP
    {
      OP_ERROR,
      OP_ADD,  // +
      OP_SUB,  // -
      OP_MUL,  // *
      OP_DIV,  // /
      OP_AND,  // &&
      OP_OR,   // ||
      OP_GT,   // >
      OP_LT,   // <
      OP_LE,   // <=
      OP_GE,   // >=
      OP_EQ,   // ==
      OP_NEQ,  // !=
      OP_UNM,  // -
      OP_NOT,   // !
      OP_PERCENT, // %
      OP_PER    
    } OP;
    static const MM::CHAR * OP_STR[];
    static const MM::UINT32 OP_LEN[];
  };
}

#endif /* defined(__mm__Operator__) */
