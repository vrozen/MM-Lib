/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The UnExp abstraction defines unary expressions.
 * @package MM
 * @file    UnExp.h
 * @author  Riemer van Rozen
 * @date    July 19th 2013
 */
/******************************************************************************/
#ifndef __mm__UnExp__
#define __mm__UnExp__

namespace MM
{
  /**
   * @class UnExp
   * @brief Defines the UnExp class
   */
  class UnExp : public MM::Exp
  {
  private:
    MM::Exp * exp;       /**> expression / operand */
    MM::Operator::OP op; /**> unary operator */
    MM::Location * loc;  /**> operator source location */
  public:
    UnExp(MM::Operator::OP op,
          MM::Exp * exp);
    UnExp(MM::Operator::OP op,
          MM::Exp * exp,          
          MM::Location * loc);
    ~UnExp();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);

    MM::Exp * getExp();
    
    MM::Operator::OP getOperator();
        
    MM::VOID toString(MM::String * buf);
  };
}


#endif /* defined(__mm__UnExp__) */
