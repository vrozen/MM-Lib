//
//  Definition.h
//  mm
//
//  Created by Riemer van Rozen on 7/21/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Definition__
#define __mm__Definition__

namespace MM
{
  class Definition : public MM::Element
  {
  public:
    static const MM::CHAR * LPAREN_STR;
    static const MM::CHAR * RPAREN_STR;
    static const MM::CHAR * LBRACE_STR;
    static const MM::CHAR * RBRACE_STR;
    static const MM::CHAR * COMMA_STR;

    static const MM::UINT32 LPAREN_LEN;
    static const MM::UINT32 RPAREN_LEN;
    static const MM::UINT32 LBRACE_LEN;
    static const MM::UINT32 RBRACE_LEN;
    static const MM::UINT32 COMMA_LEN;
    
  private:
    MM::Name * name;
    std::vector<MM::Element *> * elements;
  public:
    Definition(MM::Name * name, std::vector<MM::Element *> * elements);
    Definition(std::vector<MM::Element *> * elements);
    ~Definition();
    
    MM::VOID addElement(MM::Element * element);
    MM::VOID removeElement(MM::Element * element);
    
    MM::UINT32 getPoolCount();
    MM::UINT32 getDeclCount();

    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__Definition__) */
