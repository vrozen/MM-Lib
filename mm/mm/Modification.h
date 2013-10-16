//
//  Modification.h
//  mm
//
//  Created by Riemer van Rozen on 10/16/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Modification__
#define __mm__Modification__

namespace MM
{
  class Modification : public MM::Transformation
  {
  public:
    const static MM::CHAR * MODIFY_STR;
    const static MM::UINT32 MODIFY_LEN;
  private:
    MM::Location * loc; /**> modify source location*/
  public:
    Modification(MM::Vector<MM::Element *> * elements);
    Modification(MM::Vector<MM::Element *> * elements, MM::Location * loc);
    ~Modification();
    MM::VOID recycle(MM::Recycler *r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__Modification__) */
