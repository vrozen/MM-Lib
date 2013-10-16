//
//  DieExp.h
//  mm
//
//  Created by Riemer van Rozen on 7/20/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__DieExp__
#define __mm__DieExp__

namespace MM
{
  /**
   * @class DieExp
   * @brief Defines the DieExp class
   */
  class DieExp : public MM::Exp
  {
  private:
    static const MM::CHAR * DIE_STR; /**> die string */
    static const MM::UINT32 DIE_LEN; /**> die string length */
    MM::UINT32 max;                  /**> maximum */
    MM::Location * maxLoc;           /**> max location */
    MM::Location * dieLoc;           /**> die location */
  public:
    DieExp(MM::UINT32 max);
    DieExp(MM::UINT32     max,
           MM::Location * maxLoc,
           MM::Location * dieLoc);
    ~DieExp();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    MM::UINT32 getMax();
    MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__DieExp__) */
