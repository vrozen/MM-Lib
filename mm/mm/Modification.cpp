//
//  Modification.cpp
//  mm
//
//  Created by Riemer van Rozen on 10/16/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "String.h"
#include "Vector.h"
#include "Recycler.h"
#include "Location.h"
#include "Name.h"
#include "Element.h"
#include "Transformation.h"
#include "Modification.h"

const MM::CHAR * MM::Modification::MODIFY_STR = "modify";
const MM::UINT32 MM::Modification::MODIFY_LEN =
  strlen(MM::Modification::MODIFY_STR);

MM::Modification::Modification(MM::Vector<MM::Element *> * elements) :
  MM::Transformation::Transformation(elements)
{
  this->loc = MM_NULL;
}

MM::Modification::Modification(MM::Vector<MM::Element *> * elements,
                               MM::Location * loc) :
  MM::Transformation::Transformation(elements)
{
  this->loc = loc;
}

MM::Modification::~Modification()
{
  this->loc = MM_NULL;
}

MM::VOID MM::Modification::recycle(MM::Recycler * r)
{
  if(loc != MM_NULL)
  {
    loc->recycle(r);
  }
  MM::Transformation::recycle(r);
}

MM::TID MM::Modification::getTypeId()
{
  return MM::T_Modification;
}

MM::BOOLEAN MM::Modification::instanceof(MM::TID tid)
{
  if(tid == MM::T_Modification)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Transformation::instanceof(tid);
  }
}

MM::VOID MM::Modification::toString(MM::String * buf)
{
  MM::Transformation::toString(buf);
  buf->append((MM::CHAR*)MM::Modification::MODIFY_STR,
              MM::Modification::MODIFY_LEN);
  buf->linebreak();
}
