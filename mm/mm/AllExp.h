/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The AllExp abstraction expresses a that the full available amount will
 * flow along a FlowEdge from a source node to target node.
 * @note A - all -> B equals A - A -> B
 * @package MM
 * @file    AllExp.h
 * @author  Riemer van Rozen
 * @date    July 19th 2013
 */
/******************************************************************************/
#ifndef __mm__AllExp__
#define __mm__AllExp__

namespace MM
{
  /**
   * @class AllExp
   * @brief Defines the AllExp class
   */
  class AllExp : public MM::Exp
  {
  private:
    static const MM::CHAR * ALL_STR; /**> all string */
    static const MM::UINT32 ALL_LEN; /**> all string length */
    MM::Location * loc;              /**> source location */
  public:
    AllExp();
    AllExp(MM::Location * loc);
    ~AllExp();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__AllExp__) */
