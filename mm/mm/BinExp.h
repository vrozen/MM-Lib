/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The BinExp abstraction defines binary expressions.
 * @package MM
 * @file    BinExp.h
 * @author  Riemer van Rozen
 * @date    July 18th 2013
 */
/******************************************************************************/
#ifndef __mm__BinExp__
#define __mm__BinExp__

namespace MM
{
  /**
   * @class BinExp
   * @brief Defines the BinExp class
   */
  class BinExp : public MM::Exp
  {
  private:
    MM::Exp          * e1;  /**> left hand side expression */
    MM::Exp          * e2;  /**> right hand side expression */
    MM::Operator::OP   op;  /**> binary operator */
    MM::Location     * loc; /**> operator source location */
  public:
    BinExp(MM::Exp          * e1,
           MM::Operator::OP   op,
           MM::Exp          * e2);
    BinExp(MM::Exp          * e1,
           MM::Operator::OP   op,
           MM::Exp          * e2,
           MM::Location     * loc);
    ~BinExp();
    
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
 
    MM::Exp * getLhsExp();
    MM::Exp * getRhsExp();
    MM::Operator::OP getOperator();
    
    MM::BOOLEAN isTriggerExp();
    MM::BOOLEAN isAlaiasExp();    
    
    MM::VOID toString(MM::String * buf);
  };
}


#endif /* defined(__mm__BinExp__) */
