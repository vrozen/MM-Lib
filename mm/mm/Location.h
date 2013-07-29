//
//  Location.h
//  mm
//
//  Created by Riemer van Rozen on 7/27/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Location__
#define __mm__Location__

namespace MM
{
  class Location
  {
  private:
    MM::UINT32 line;
    MM::UINT32 col;
    MM::UINT32 endLine;
    MM::UINT32 endCol;
  public:
    Location(MM::UINT32 beginLine,
             MM::UINT32 beginCol,
             MM::UINT32 endLine,
             MM::UINT32 endCol);
    ~Location();
    MM::UINT32 getLine();
    MM::UINT32 getColumn();
    MM::UINT32 getLength();
  };
}

#endif /* defined(__mm__Location__) */
