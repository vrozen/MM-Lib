//
//  NodeBehavior.cpp
//  mm
//
//  Created by Riemer van Rozen on 10/9/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "Vector.h"
#include "Map.h"
#include "Recycler.h"
#include "Location.h"
#include "String.h"
#include "Name.h"
#include "NodeBehavior.h"

const MM::CHAR * MM::NodeBehavior::IO_STR[] =
{
  "error",
  "", //epsilon = private
  "in",
  "out",
  "inout"
};

const MM::CHAR * MM::NodeBehavior::WHEN_STR[] =
{
  "error",
  "", //epsilon = passive
  "auto",
  "user",
  "start"
};

const MM::CHAR * MM::NodeBehavior::ACT_STR[] =
{
  "error",
  "", //epsilon = pull
  "push"
};

const MM::CHAR * MM::NodeBehavior::HOW_STR[] =
{
  "error",
  "", //epsilon = any
  "all"
};

const MM::UINT32 MM::NodeBehavior::IO_LEN[] =
{
  strlen(MM::NodeBehavior::IO_STR[0]), //error
  strlen(MM::NodeBehavior::IO_STR[1]), //epsilon (private)
  strlen(MM::NodeBehavior::IO_STR[2]), //in
  strlen(MM::NodeBehavior::IO_STR[3]), //out
  strlen(MM::NodeBehavior::IO_STR[4])  //inout
};

const MM::UINT32 MM::NodeBehavior::WHEN_LEN[] =
{
  strlen(MM::NodeBehavior::WHEN_STR[0]), //error
  strlen(MM::NodeBehavior::WHEN_STR[1]), //epsilon (passive)
  strlen(MM::NodeBehavior::WHEN_STR[2]), //auto
  strlen(MM::NodeBehavior::WHEN_STR[3]), //user
  strlen(MM::NodeBehavior::WHEN_STR[4])  //start
};

const MM::UINT32 MM::NodeBehavior::ACT_LEN[] =
{
  strlen(MM::NodeBehavior::ACT_STR[0]), //error
  strlen(MM::NodeBehavior::ACT_STR[1]), //epsilon (pull)
  strlen(MM::NodeBehavior::ACT_STR[2])  //push
};

const MM::UINT32 MM::NodeBehavior::HOW_LEN[] =
{
  strlen(MM::NodeBehavior::HOW_STR[0]), //error
  strlen(MM::NodeBehavior::HOW_STR[1]), //any
  strlen(MM::NodeBehavior::HOW_STR[2])  //all
};

MM::NodeBehavior::NodeBehavior(MM::NodeBehavior::IO io,
                               MM::NodeBehavior::When when,
                               MM::NodeBehavior::Act act,
                               MM::NodeBehavior::How how) : MM::Recyclable()
{
  this->io = io;
  this->when = when;
  this->act = act;
  this->how = how;
}

MM::NodeBehavior::~NodeBehavior()
{
  this->io = MM::NodeBehavior::IO_ERROR;
  this->when = MM::NodeBehavior::WHEN_ERROR;
  this->act = MM::NodeBehavior::ACT_ERROR;
  this->how = MM::NodeBehavior::HOW_ERROR;
}

MM::VOID MM::NodeBehavior::recycle(MM::Recycler * r)
{
  MM::Recyclable::recycle(r);
}

MM::TID MM::NodeBehavior::getTypeId()
{
  return MM::T_NodeBehavior;
}

MM::BOOLEAN MM::NodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_NodeBehavior)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::Recyclable::instanceof(tid);
  }
}

MM::NodeBehavior::IO MM::NodeBehavior::getIO()
{
  return io;
}

MM::NodeBehavior::When MM::NodeBehavior::getWhen()
{
  return when;
}

MM::NodeBehavior::Act MM::NodeBehavior::getAct()
{
  return act;
}

MM::NodeBehavior::How MM::NodeBehavior::getHow()
{
  return how;
}

MM::VOID  MM::NodeBehavior::setIO(MM::NodeBehavior::IO io)
{
  this->io = io;
}

MM::VOID MM::NodeBehavior::setWhen(MM::NodeBehavior::When when)
{
  this->when = when;
}

MM::VOID MM::NodeBehavior::setAct(MM::NodeBehavior::Act act)
{
  this->act = act;
}

MM::VOID MM::NodeBehavior::setHow(MM::NodeBehavior::How how)
{
  this->how = how;
}

MM::BOOLEAN MM::NodeBehavior::conformsTo(MM::NodeBehavior::IO direction)
{
  MM::BOOLEAN r = MM_FALSE;
  if(direction == MM::NodeBehavior::IO_IN)
  {
    if(io == MM::NodeBehavior::IO_INOUT || io == MM::NodeBehavior::IO_IN)
    {
      r = MM_TRUE;
    }
  }
  else if(direction == MM::NodeBehavior::IO_OUT)
  {
    if(io == MM::NodeBehavior::IO_INOUT || io == MM::NodeBehavior::IO_OUT)
    {
      r = MM_TRUE;
    }
  }  
  return r;
}

MM::VOID MM::NodeBehavior::toString(MM::String * buf, MM::Name * name)
{
  if(io != MM::NodeBehavior::IO_PRIVATE)
  {
    buf->append((MM::CHAR*)MM::NodeBehavior::IO_STR[io],
                MM::NodeBehavior::IO_LEN[io]);
    buf->space();
  }
  if(when != MM::NodeBehavior::WHEN_PASSIVE)
  {
    buf->append((MM::CHAR*)MM::NodeBehavior::WHEN_STR[when],
              MM::NodeBehavior::WHEN_LEN[when]);
    buf->space();
  }
  if(act != MM::NodeBehavior::ACT_PULL)
  {
    buf->append((MM::CHAR*)MM::NodeBehavior::ACT_STR[act],
                MM::NodeBehavior::ACT_LEN[act]);
    buf->space();
  }
  if(how != MM::NodeBehavior::HOW_ANY)
  {
    buf->append((MM::CHAR*)MM::NodeBehavior::HOW_STR[how],
              MM::NodeBehavior::HOW_LEN[how]);
    buf->space();
  }
}