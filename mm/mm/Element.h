/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The Element abstraction is the abstract superclass of all program elements.
 * @package MM
 * @file    Element.h
 * @author  Riemer van Rozen
 * @date    July 10th 2013
 */
/******************************************************************************/
#ifndef __mm__Element__
#define __mm__Element__

namespace MM
{
  class Machine;
  class Element : public MM::Recyclable
  {
  protected:
    Element(MM::Name * name);
    MM::Name * name;
  public:
    virtual ~Element();
    MM::VOID recycle(MM::Recycler * r);
    virtual MM::TID getTypeId();
    virtual MM::BOOLEAN instanceof(MM::TID tid);
    MM::Name * getName();
    MM::VOID setName(MM::Name * name);
    virtual MM::VOID toString(MM::String * buf) = 0;
    virtual MM::VOID toString(MM::String * buf, MM::UINT32 indent) = 0;
  };
}
#endif /* defined(__mm__Element__) */
