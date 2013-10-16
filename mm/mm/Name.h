/******************************************************************************
 * Copyright (c) 2013 Riemer van Rozen. All rights reserved.
 ******************************************************************************/
/*!
 * The Name abstraction is used to compose identifiers.
 * @package MM
 * @file    Name.h
 * @author  Riemer van Rozen
 * @date    July 27th 2013
 */
/******************************************************************************/
#ifndef __mm__Name__
#define __mm__Name__

namespace MM
{
  /**
   * @class Name
   * @brief Defines the Name class.
   */
  class Name : public MM::Recyclable
  {
  private:
    MM::CHAR     * str;  /**< string buffer */
    MM::UINT32     len;  /**< string length */
    MM::Location * loc;  /**< location */
    MM::Name     * name; /**< child name */
    MM::Name     * pre;  /**< preffix name (used for edges) */
  protected:
    ~Name();
  public:
    static const MM::CHAR DOT_CHAR;      /**< dot character */
    Name(MM::CHAR * str, MM::UINT32 len);
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);

    friend MM::BOOLEAN operator < (const Name & n1, const Name & n2)
    {
      MM::BOOLEAN lt = MM_FALSE;
      if(n1.len < n2.len)
      {
        return MM_TRUE;
      }
      else if(n1.len == n2.len)
      {
        if(strncmp(n1.str, n2.str, n1.len) < 0)
        {
          lt = MM_TRUE;
        }
      }
      return lt;
    }
    
    /**
     * @class Compare
     * @brief The Compare class defines comparison between names
     */
    class Compare
    {
    public:
      bool operator()(MM::Name const * n1, MM::Name const * n2) const
      {
        MM::BOOLEAN lt = *n1 < *n2;
        return lt;
      }
    };
    
    MM::UINT32 getLength();
    MM::VOID setName(MM::Name * name);
    MM::Name * getName();
    MM::VOID setPreName(MM::Name * name);
    MM::Name * getPreName();
    
    MM::VOID print(); //debug
    MM::CHAR * getBuffer();
    MM::Location * getLocation();
    MM::VOID setLocation(MM::Location * loc);
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__Name__) */
