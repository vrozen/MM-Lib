//
//  YYLTYPE.h
//  mm
//
//  Created by Riemer van Rozen on 7/29/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef mm_YYLTYPE_h
#define mm_YYLTYPE_h

typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1

#endif
