//
//  Instance.h
//  mm
//
//  Created by Riemer van Rozen on 7/23/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Instance__
#define __mm__Instance__

namespace MM
{
  class Definition;
  class Declaration : public MM::Element
  {
  private:
    MM::Name * type;
    MM::Name * name;
    MM::Definition * def;
  public:
    Declaration(MM::Name * type, MM::Name * name);
    ~Declaration();
    MM::Definition * getDefinition();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__Instance__) */
