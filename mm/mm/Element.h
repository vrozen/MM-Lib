//
//  Element.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Element__
#define __mm__Element__

namespace MM
{
  class Element
  {
  protected:
    Element();
    virtual ~Element() = 0;
  public:
    virtual MM::VOID toString(MM::String * buf) = 0;
  };
}
#endif /* defined(__mm__Element__) */
