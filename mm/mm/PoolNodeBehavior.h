//
//  Pool.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Pool__
#define __mm__Pool__

namespace MM
{
  class PoolNodeBehavior : public MM::NodeBehavior
  {
  private:
    static const MM::CHAR * POOL_STR;
    static const MM::CHAR * AT_STR;
    static const MM::CHAR * MAX_STR;
    static const MM::CHAR * ADD_STR;
    static const MM::UINT32 POOL_LEN;
    static const MM::UINT32 AT_LEN;
    static const MM::UINT32 MAX_LEN;
    static const MM::UINT32 ADD_LEN;

    MM::UINT32 at;
    MM::UINT32 max;
    MM::Exp * exp;
  public:
    PoolNodeBehavior(MM::NodeBehavior::IO   io,
                     MM::NodeBehavior::When when,
                     MM::NodeBehavior::Act  act,
                     MM::NodeBehavior::How  how,
                     MM::UINT32             at,
                     MM::UINT32             max,
                     MM::Exp              * exp);
    ~PoolNodeBehavior();
    MM::VOID recycle(MM::Recycler *r);

    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
        
    MM::UINT32 getAt();
    MM::UINT32 getMax();
    MM::Exp * getAdd();
    
    MM::VOID setAt(MM::UINT32 at);
    MM::VOID setMax(MM::UINT32 max);
    MM::VOID setAdd(MM::Exp * exp);
    
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::Name * name);

  };
}
#endif /* defined(__mm__Pool__) */
