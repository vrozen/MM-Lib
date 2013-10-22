//
//  Program.h
//  mm
//
//  Created by Riemer van Rozen on 10/16/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Program__
#define __mm__Program__

namespace MM
{
  class Program : public MM::Recyclable
  {
  private:
    MM::Vector<Transformation *> * transformations;
  public:
    Program(MM::Vector<Transformation *> * transformations);
    ~Program();
    MM::VOID recycle(MM::Recycler *r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID addTransformation(MM::Transformation * tr);
    MM::Vector<MM::Transformation *> * getTransformations();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__Program__) */
