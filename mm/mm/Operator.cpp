//
//  Operator.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/27/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

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
  "-",
  "!",
  "%",
  "|"
};

const MM::UINT32 MM::Operator::OP_LEN[] =
{
  5, // error
  1, // +
  1, // -
  1, // *
  1, // /
  2, // &&
  2, // ||
  1, // >
  1, // <
  2, // <=
  2, // >=
  2, // ==
  2, // !=
  1, // -
  1, // !
  1, // %
  1  // |
};
