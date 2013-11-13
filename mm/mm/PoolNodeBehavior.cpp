//
//  Pool.cpp
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
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
#include "Exp.h"
#include "NodeBehavior.h"
#include "PoolNodeBehavior.h"

const MM::CHAR * MM::PoolNodeBehavior::POOL_STR = "pool";
const MM::CHAR * MM::PoolNodeBehavior::AT_STR   = "at";
const MM::CHAR * MM::PoolNodeBehavior::MAX_STR  = "max";
const MM::CHAR * MM::PoolNodeBehavior::ADD_STR  = "add";
const MM::UINT32 MM::PoolNodeBehavior::POOL_LEN =
  strlen(MM::PoolNodeBehavior::POOL_STR);
const MM::UINT32 MM::PoolNodeBehavior::AT_LEN   =
  strlen(MM::PoolNodeBehavior::AT_STR);
const MM::UINT32 MM::PoolNodeBehavior::MAX_LEN  =
  strlen(MM::PoolNodeBehavior::MAX_STR);
const MM::UINT32 MM::PoolNodeBehavior::ADD_LEN  =
  strlen(MM::PoolNodeBehavior::ADD_STR);

MM::PoolNodeBehavior::PoolNodeBehavior(MM::NodeBehavior::IO    io,
                                       MM::NodeBehavior::When  when,
                                       MM::NodeBehavior::Act   act,
                                       MM::NodeBehavior::How   how,
                                       MM::UINT32      at,
                                       MM::UINT32      max,
                                       MM::Exp       * exp):
  MM::NodeBehavior(io, when, act, how)
{
  this->at = at;
  this->max = max;
  this->exp = exp;
}

MM::PoolNodeBehavior::~PoolNodeBehavior()
{
  this->at = 0;
  this->max = 0;
  this->exp = MM_NULL;
}

MM::VOID MM::PoolNodeBehavior::recycle(MM::Recycler *r)
{
  if(exp != MM_NULL)
  {
    exp->recycle(r);
  }
  MM::NodeBehavior::recycle(r);
}

MM::TID MM::PoolNodeBehavior::getTypeId()
{
  return MM::T_PoolNodeBehavior;
}

MM::BOOLEAN MM::PoolNodeBehavior::instanceof(MM::TID tid)
{
  if(tid == MM::T_PoolNodeBehavior)
  {
    return MM_TRUE;
  }
  else
  {
    return MM::NodeBehavior::instanceof(tid);
  }
}

MM::UINT32 MM::PoolNodeBehavior::getAt()
{
  return at;
}

MM::UINT32 MM::PoolNodeBehavior::getMax()
{
  return max;
}

MM::Exp * MM::PoolNodeBehavior::getAdd()
{
  return exp;
}

MM::VOID MM::PoolNodeBehavior::setAt(MM::UINT32 at)
{
  this->at = at;
}

MM::VOID MM::PoolNodeBehavior::setMax(MM::UINT32 max)
{
  this->max = max;
}

MM::VOID MM::PoolNodeBehavior::setAdd(MM::Exp * exp)
{
  this->exp = exp;
}

MM::UINT32 MM::PoolNodeBehavior::getCreateMessage()
{
  return MM::MSG_NEW_POOL;
}

MM::UINT32 MM::PoolNodeBehavior::getUpdateMessage()
{
  return MM::MSG_UPD_POOL;
}

MM::UINT32 MM::PoolNodeBehavior::getDeleteMessage()
{
  return MM::MSG_DEL_POOL;
}

MM::VOID MM::PoolNodeBehavior::toString(MM::String * buf)
{
  buf->append((MM::CHAR*)MM::PoolNodeBehavior::POOL_STR,
              MM::PoolNodeBehavior::POOL_LEN);
}

MM::VOID MM::PoolNodeBehavior::toString(MM::String * buf, MM::Name * name)
{
  MM::NodeBehavior::toString(buf, name);
  toString(buf);
  buf->space();
  name->toString(buf);
  buf->space();
  if(at!= 0)
  {
    buf->append((MM::CHAR*)MM::PoolNodeBehavior::AT_STR,
                MM::PoolNodeBehavior::AT_LEN);
    buf->space();
    buf->appendInt(at);
    buf->space();
  }
  if(max != 0)
  {
    buf->append((MM::CHAR*)MM::PoolNodeBehavior::MAX_STR,
                MM::PoolNodeBehavior::MAX_LEN);
    buf->space();
    buf->appendInt(max);
    buf->space();
  }
  if(exp != MM_NULL)
  {
    buf->append((MM::CHAR*)MM::PoolNodeBehavior::ADD_STR,
                MM::PoolNodeBehavior::ADD_LEN);
    buf->space();
    exp->toString(buf);
  }
}
