//
//  Recycler.h
//  mm
//
//  Created by Riemer van Rozen on 8/1/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Recycler__
#define __mm__Recycler__

namespace MM
{
  class Recycler
  {
  private:
    static MM::INT32 bufferCount;
    static const MM::CHAR * ORPHAN_MESSAGE;
    static const MM::CHAR * OBJECT_MESSAGE;
    static const MM::CHAR * BUFFER_MESSAGE;
    static const MM::UINT32 ORPHAN_MESSAGE_SIZE;
    static const MM::UINT32 OBJECT_MESSAGE_SIZE;
    static const MM::UINT32 BUFFER_MESSAGE_SIZE;

    MM::Vector<MM::Recyclable *> * objects;
  protected:
    Recycler();
    ~Recycler();
  public:
    virtual MM::TID getTypeId();
    virtual MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID create(MM::Recyclable * r);
    MM::VOID recycle(MM::Recyclable * r);
    MM::VOID uncreate(MM::Recyclable * r);
    static MM::VOID uncreate(MM::CHAR * str);
    static MM::CHAR * createBuffer(MM::UINT32 size);
  };
}

#endif /* defined(__mm__Recycler__) */
