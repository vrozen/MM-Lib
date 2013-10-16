//
//  Delete.h
//  mm
//
//  Created by Riemer van Rozen on 9/29/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Delete__
#define __mm__Delete__

namespace MM
{
  class Delete : public MM::Element
  {
  public:
    static const MM::CHAR * DELETE_STR;
    static const MM::UINT32 DELETE_LEN;
    //private:
    //MM::Name     * name;
    //MM::Location * loc;
  public:
    Delete(MM::Name * name);
    ~Delete();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    //MM::Location * getLocation();
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}

#endif /* defined(__mm__Delete__) */
