/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The Location abstraction defines textual source locations.
 * @package MM
 * @file    Location.h
 * @author  Riemer van Rozen
 * @date    July 27th 2013
 */
/******************************************************************************/
#ifndef __mm__Location__
#define __mm__Location__

namespace MM
{
  /**
   * @class Location
   * @brief   Defines the Location class.
   */
  class Location : public MM::Recyclable
  {
  private:
    static const MM::CHAR * LOCATION_STR; /**< location string */
    static const MM::UINT32 LOCATION_LEN; /**< location string length */
    static const MM::CHAR * LINE_STR;     /**< line string */
    static const MM::UINT32 LINE_LEN;     /**< line string length */
    static const MM::CHAR * COLUMN_STR;   /**< column string */
    static const MM::UINT32 COLUMN_LEN;   /**< column string length */
    static const MM::CHAR * LENGTH_STR;   /**< length string */
    static const MM::UINT32 LENGTH_LEN;   /**< length string length */
    
    MM::UINT32 line;    /**< begin line number */
    MM::UINT32 col;     /**< begin column number */
    MM::UINT32 endLine; /**< end line number */
    MM::UINT32 endCol;  /**< end column number */
  public:
    Location(MM::UINT32 beginLine,
             MM::UINT32 beginCol,
             MM::UINT32 endLine,
             MM::UINT32 endCol);
    ~Location();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);

    MM::UINT32 getLine();
    MM::UINT32 getColumn();
    MM::UINT32 getLength();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__Location__) */
