//
//  Transformation.h
//  mm
//
//  Created by Riemer van Rozen on 10/16/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Transformation__
#define __mm__Transformation__

namespace MM
{
  class Transformation : public MM::Recyclable
  {
  private:
    MM::Vector<MM::Element *> * elements;
  protected:
    Transformation(MM::Vector<MM::Element *> * elements);
  public:
    ~Transformation();
    MM::VOID recycle(MM::Recycler *r);
    MM::TID getTypeId() = 0;
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID addElement(MM::Element * element);
    MM::Vector<MM::Element *> * getElements();
    MM::VOID clearElements();
    MM::VOID toString(MM::String * buf);
  };
}


#endif /* defined(__mm__Transformation__) */
