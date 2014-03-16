/******************************************************************************
 * Copyright (c) 2013-2014, Amsterdam University of Applied Sciences (HvA) and
 *                          Centrum Wiskunde & Informatica (CWI)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contributors:
 *   * Riemer van Rozen - rozen@cwi.nl - HvA / CWI
 ******************************************************************************/
//
//  Recycler.cpp
//  mm
//
//  Created by Riemer van Rozen on 8/1/13.
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

const MM::CHAR * MM::Recycler::TYPE_STR[] =
{
  //base
  "NULL",
  "T_Recycler",
  "T_Recyclable",
  "T_Observer",
  "T_Observable",
  "T_String",
  "T_Map",
  "T_Vector",
  //type transformation
  "T_Reflector",
  "T_Machine",
  "T_InstanceObserver", //API
                      //data transformation
  "T_Program",
  "T_Evaluator",
  "T_Instance",
  "T_Transformation",
  "T_Transition",
  "T_Modification",
  "T_FlowEvent",
  //ast / type
  "T_Location",
  "T_Name",
  "T_Element",
  "T_Definition",
  "T_Declaration",
  "T_Assertion",
  "T_Signal",
  "T_Deletion",
  "T_Activation",
  "T_Edge",
  "T_FlowEdge",
  "T_StateEdge",
  "T_Node",
  "T_InterfaceNode",
  "T_NodeBehavior",
  "T_PoolNodeBehavior",
  "T_DrainNodeBehavior",
  "T_GateNodeBehavior",
  "T_SourceNodeBehavior",
  "T_RefNodeBehavior",
  "T_ConverterNodeBehavior",
  //expressions
  "T_Exp",
  "T_TriggerExp",
  "T_AliasExp",
  "T_OneExp",
  "T_ActiveExp",
  "T_DieExp",
  "T_OverrideExp",
  "T_VarExp",
  "T_AllExp",
  "T_BinExp",
  "T_UnExp",
  "T_ValExp",
  "T_BooleanValExp",
  "T_NumberValExp",
  "T_RangeValExp"
};

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
  MM::Vector<Recyclable *>::Iterator i = objects->getIterator();
  
  while(i.hasNext() == MM_TRUE)
  {
    MM::Recyclable * r = i.getNext();
    str->append((MM::CHAR *) MM::Recycler::ORPHAN_MESSAGE,
                MM::Recycler::ORPHAN_MESSAGE_SIZE);
    str->space();
    MM::CHAR * description = (MM::CHAR*)typeid(*r).name();
    str->append(description, strlen(description));
    str->linebreak();
    //r->toString(str);
    //str->linebreak();
  }

  str->append((MM::CHAR*)MM::Recycler::OBJECT_MESSAGE, MM::Recycler::OBJECT_MESSAGE_SIZE);
  str->appendInt(curObjects);
  str->linebreak();
  str->append((MM::CHAR*)MM::Recycler::BUFFER_MESSAGE, MM::Recycler::BUFFER_MESSAGE_SIZE);
  str->appendInt(curBuffers);
  str->linebreak();
  
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
  if(r == MM_NULL)
  {
    printf("Recycler: Attempt to recycle null\n");
  }
  else if(objects->contains(r) == MM_TRUE)
  {
    objects->remove(r);
    //printf("Recycler: Deleting %s\n",
	//	(MM::CHAR*)typeid(*r).name());

    delete r;
  }
  else
  {
    printf("Recycler: Attempt to uncreate an unknown object %s\n",
		(MM::CHAR*)typeid(*r).name());

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
