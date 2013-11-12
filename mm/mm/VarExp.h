/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The VarExp abstraction defines expressions referencing pools.
 * @package MM
 * @file    VarExp.h
 * @author  Riemer van Rozen
 * @date    July 19th 2013
 */
/******************************************************************************/
#ifndef __mm__VarExp__
#define __mm__VarExp__

namespace MM
{
  /**
   * @class VarExp
   * @brief Defines the VarExp class
   */
  class VarExp : public MM::Exp
  {
  private:
    MM::Name * name; /**> variable name */
    //MM::Node * ref;
  public:
    VarExp(MM::Name * name);
    ~VarExp();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::Name * getName();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__VarExp__) */
