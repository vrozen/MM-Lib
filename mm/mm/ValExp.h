/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The ValExp abstraction defines the abstract superclass of value expressions.
 * @package MM
 * @file    ValExp.h
 * @author  Riemer van Rozen
 * @date    July 19th 2013
 */
/******************************************************************************/
#ifndef __mm__ValExp__
#define __mm__ValExp__

namespace MM
{
  /**
   * @class ValExp
   * @brief Defines the ValExp class
   */
  class ValExp : public MM::Exp
  {
  protected:
    ValExp();
  public:
    virtual ~ValExp();
    MM::VOID recycle(MM::Recycler * r);
    virtual MM::TID getTypeId();
    virtual MM::BOOLEAN instanceof(MM::TID tid);
    virtual MM::VOID toString(MM::String * buf) = 0;
  };
}

#endif /* defined(__mm__ValExp__) */
