//
//  Recycler.cpp
//  mm
//
//  Created by Riemer van Rozen on 8/1/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "YYLTYPE.h"
#include "Types.h"
#include "Recyclable.h"
#include "String.h"
#include "Vector.h"
#include "Recycler.h"

const MM::CHAR * MM::Recycler::ORPHAN_MESSAGE = "orphan: ";
const MM::CHAR * MM::Recycler::OBJECT_MESSAGE = "object count: ";
const MM::CHAR * MM::Recycler::BUFFER_MESSAGE = "buffer count: ";

const MM::UINT32 MM::Recycler::ORPHAN_MESSAGE_SIZE = strlen(MM::Recycler::ORPHAN_MESSAGE);
const MM::UINT32 MM::Recycler::OBJECT_MESSAGE_SIZE = strlen(MM::Recycler::OBJECT_MESSAGE);
const MM::UINT32 MM::Recycler::BUFFER_MESSAGE_SIZE = strlen(MM::Recycler::BUFFER_MESSAGE);

MM::INT32 MM::Recycler::bufferCount = 0;

MM::Recycler::Recycler()
{
  objects = new MM::Vector<Recyclable*>();
}

MM::Recycler::~Recycler()
{
  MM::INT32 curObjects = objects->size();
  MM::INT32 curBuffers = bufferCount;
  
  MM::CHAR * buffer = createBuffer(1024 * 16 * 8);
  MM::String * str = new MM::String(buffer, 1024 * 16 * 8);
  
  str->append((MM::CHAR*)MM::Recycler::OBJECT_MESSAGE, MM::Recycler::OBJECT_MESSAGE_SIZE);
  str->appendInt(curObjects);
  str->linebreak();
  str->append((MM::CHAR*)MM::Recycler::BUFFER_MESSAGE, MM::Recycler::BUFFER_MESSAGE_SIZE);
  str->appendInt(curBuffers);
  str->linebreak();
  
  MM::Vector<Recyclable *>::Iterator i = objects->getIterator();
  
  while(i.hasNext() == MM_TRUE)
  {
    MM::Recyclable * r = i.getNext();
    str->append((MM::CHAR *) MM::Recycler::ORPHAN_MESSAGE,
                MM::Recycler::ORPHAN_MESSAGE_SIZE);
    MM::CHAR * bla = (MM::CHAR*)typeid(*r).name();
    str->append(bla, strlen(bla));
    str->linebreak();
    r->toString(str);
  }

  str->print();
  MM::Recycler::uncreate(str->getBuffer());
  delete str;
  delete objects;
}

MM::TID MM::Recycler::getTypeId()
{
  return MM::T_Recycler;
}

MM::BOOLEAN MM::Recycler::instanceof(MM::TID tid)
{
  if(tid == MM::T_Recycler)
  {
    return MM_TRUE;
  }
  else
  {
    return MM_FALSE;
  }
}

MM::VOID MM::Recycler::recycle(Recyclable * r)
{
  r->recycle(this);
}

//must be called by Machine when it creates an object
MM::VOID MM::Recycler::create(MM::Recyclable * r)
{
  objects->add(r);
}

//is called only by recyclable
MM::VOID MM::Recycler::uncreate(MM::Recyclable * r)
{
  if(objects->contains(r) == MM_TRUE)
  {
    objects->remove(r);
    delete r;
  }
  else
  {
    printf("attempt to uncreate an unknown object\n");
  }
}

MM::CHAR * MM::Recycler::createBuffer(MM::UINT32 size)
{
  //printf("CREATE %d\n", size);
  bufferCount++;
  MM::CHAR * buf = (MM::CHAR *) malloc(size);
  memset(buf, 0, size);
  return buf;
}

MM::VOID MM::Recycler::uncreate(MM::CHAR * str)
{
  bufferCount--;
  //printf("%p: [%s]  \n", str, str);
  free(str);
}
