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
/*!
 * \namespace LibMM
 * \class     Machine
 * \brief     The Machine class wraps MM Lib in a MS .NET implementation.
 * \file      LibMM.h
 * \author    Riemer van Rozen
 * \date      March 14th 2014
 */
/******************************************************************************/

#pragma once

#include "..\mm\YYLTYPE.h"
#include "..\mm\mm.h"

using namespace System;
using namespace System::Runtime::InteropServices;

//#include <msclr/marshal.h>
//using namespace msclr::interop;

  /*
namespace MM
{
  typedef void (__stdcall * CALLBACK)(unsigned long,
	                                  unsigned long,
									  unsigned long,
									  unsigned long);
  public class Machine
  {
  private:
    char * message;
	unsigned long uldValue;
    signed long sldValue;
	CALLBACK callback;

  public:
    Machine()
	{
      this->message = 0;
	  this->uldValue = 0;
	  this->sldValue = 0;
	  this->callback = 0;
	}

	~Machine()
    {
	}


	void setMessage(char * message)
	{
	  this->message = message;
	}

	void setSignedLong(signed long sldValue)
	{
	  this->sldValue = sldValue;
	}

    void setUnsignedLong(unsigned long uldValue)
	{
	  this->uldValue = uldValue;
	}
	
	__declspec(dllexport) void setCallback(CALLBACK callback)
	{
	  this->callback = callback;
	}

	char * getMessage()
	{
	  return message;
	}

	signed long getSignedLong()
	{
	  return sldValue;
	}

	unsigned long getUnsignedLong()
	{
	  return uldValue;
	}

    CALLBACK getCallback()
	{
	  return callback;
	}

	void call(int n1, int n2, int n3, int n4)
	{
	  callback(n1,n2,n3,n4);
	}

  };
}
*/

namespace LibMM
{
  using namespace MM;

  public ref class Machine
  {

  private:
    MM::Machine * m;

  public:
	  Machine()
	  {
        m = new MM::Machine();	    
	  }

	  ~Machine()
	  {
		delete m;
	  }

  protected:
	  !Machine()
	  {
		delete m;
	  }

  public:
      
	  void reset()
	  {
		  delete m;
		  m = new MM::Machine();
	  }
	  
	  
	  delegate void CallbackDelegate(unsigned long self,
		                             unsigned long message,
		                             unsigned long instance,
									 unsigned long element,
									 long value);

	  

	  /*void setMessage(System::String^ message)
	  {
		char* str = (char*)(void*)Marshal::StringToHGlobalAnsi(message);
	    m->setMessage(str);
	  }

	  void setSignedLong(signed long sldValue)
	  {
	    m->setSignedLong(sldValue);
	  }

      void setUnsignedLong(unsigned long uldValue)
	  {
		m->setUnsignedLong(uldValue);
      }*/
	
	  /*
	  unsigned long long setCallback(unsigned long long observable,
		                             CallbackDelegate^ fp)
	  {
        GCHandle gch = GCHandle::Alloc(fp);
        IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);
        CALLBACK cb = static_cast<CALLBACK>(ip.ToPointer());
		unsigned long long r =  m->addObserver(observable, cb);
		return r;
	  }*/

	  unsigned long addInstanceObserver(unsigned long instance, unsigned long caller, CallbackDelegate^ fp)
	  {
        GCHandle gch = GCHandle::Alloc(fp);
        IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);
        CALLBACK cb = static_cast<CALLBACK>(ip.ToPointer());
		unsigned long r =  m->addInstanceObserver(instance, caller, cb);
		return r;
	  }

	  unsigned long addDefinitionObserver(unsigned long definition, unsigned long caller, CallbackDelegate^ fp)
	  {
        GCHandle gch = GCHandle::Alloc(fp);
        IntPtr ip = Marshal::GetFunctionPointerForDelegate(fp);
        CALLBACK cb = static_cast<CALLBACK>(ip.ToPointer());
		unsigned long r =  m->addDefinitionObserver(definition, caller, cb);
		return r;
	  }

	  unsigned long getGlobalInstance()
	  {
		MM::Instance * i = m->getInstance();
		unsigned long r = (unsigned long) i;
	    return r;
	  }

	  unsigned long getGlobalDefinition()
	  {
	    MM::Definition * def = m->getDefinition();
		unsigned long r = (unsigned long) def;
	    return r;
	  }

	  //FIXME: not yet working correctly
	  unsigned long getInstance(unsigned long instance, //0 -> global scope
                                System::String ^ name)
      {
	    char* n = (char*)(void*)Marshal::StringToHGlobalAnsi(name);
		unsigned long r =  m->getInstance(instance, n);
		Marshal::FreeHGlobal(IntPtr(n));
		return r;
	  }

	  unsigned long getDefinition(unsigned long instance)
	  {
	    MM::Instance * i = (MM::Instance *) instance;
		return (unsigned long) i->getDefinition();
	  }

	  unsigned long getElement(unsigned long definition,
		                       System::String ^ name)
	  {
		MM::Definition * def = (MM::Definition *) definition;
		MM::Element * element = MM_NULL;

		if(def != MM_NULL)
		{
		  char* str = (char*)(void*)Marshal::StringToHGlobalAnsi(name);
		  MM::Name * n = m->createName(str);
		  element = def->getElement(n);
		  n->recycle(m);
		  Marshal::FreeHGlobal(IntPtr(str));
		}
		 
		return (unsigned long) element;
	  }

	  bool isInteractive(unsigned long node)
	  {
		  MM::Node * n = (MM::Node *) node;

		  MM::NodeBehavior * behavior = n->getBehavior();

		  bool isInteractive = false;

		  if(behavior->getWhen() == MM::NodeBehavior::WHEN_USER)
		  {
			  isInteractive = true;
		  }
		  return isInteractive;
	  }


	  signed long getValue(unsigned long instance,
		                     unsigned long poolNode)
	  {
		  MM::Instance * i = (MM::Instance *) instance;
		  MM::Node * n = (MM::Node *) poolNode;
		  MM::INT32 val = n->getAmount(i, m);
		  return (signed long) val;
	  }

	  System::String ^ getName(unsigned long element)
	  {
		  unsigned long size = 1024 * 256 *  8;
		  char * buf = (char *) malloc(size);
		  memset(buf, 0, size);
		
          m->getName(element, buf, size);

    		System::String ^ str = gcnew System::String(buf);

 	  	  free(buf);
        return str;
	  }

	  System::String ^ getInstanceName(unsigned long instance)
	  {
	    unsigned long size = 1024 * 256 * 8;
	    char * buf = (char *) malloc(size);
	    memset(buf, 0, size);
		
	    m->getInstanceName(instance, buf, size);
	
	    System::String ^ str = gcnew System::String(buf);

	  	free(buf);
	  	return str;
	  }

	  System::String ^ getModel()
	  {
	    unsigned long size = 1024 * 256 * 8;
	    char * buf = (char *) malloc(size);
	    memset(buf, 0, size);

	    MM::String * str = new MM::String(buf, size);

	    MM::Definition * def = m->getDefinition();

	    def->toString(str);

	    System::String ^ ret = gcnew System::String(buf);
 
	    delete str;
	    free(buf);

	    return ret;
	  }

	  System::String ^ getState()
	  {
		  unsigned long size = 1024 * 256 * 8;
	    char * buf = (char *) malloc(size);
		  memset(buf, 0, size);

		  MM::String * str = new MM::String(buf, size);

		  MM::Instance * instance = m->getInstance();

		  instance->toString(str);

		  System::String ^ ret = gcnew System::String(buf);

		  delete str;
		  free(buf);

		  return ret;
	  }



	  void activate(unsigned long node,
		            unsigned long instance)
	  {
		  m->activate(node, instance);
	  }

	  void step()
	  {
      //unsigned long long size = 1024 * 256 * 8;
		  //char * buf = (char *) malloc(size);
		  m->step();
      //return gcnew System::String(buf);
	  }

	  /*System::String ^*/ void step(unsigned long instance)
	  {
      //unsigned long long size = 1024 * 256 * 8;
		  //char * buf = (char *) malloc(size);
		  //m->step(instance, buf, size);
		  m->step();
      //return gcnew System::String(buf);
	  }

	  void removeObserver(unsigned long observer)
	  {
		  m->removeObserver(observer);
	  }


	  /*void setMessage(System::String^ message)
	  {
		char* str = (char*)(void*)Marshal::StringToHGlobalAnsi(message);
	    m->setMessage(str);
	  }
	  */

	  void eval(System::String^ message)
	  {
		  char* str = (char*)(void*)Marshal::StringToHGlobalAnsi(message);
	    m->eval(str);
		  Marshal::FreeHGlobal(IntPtr(str));

		  //marshal_context ^ context = gcnew marshal_context();
	    //const char* chars = context->marshal_as<const char*>(str);
		  //m->eval(chars);
     	//delete context;
	  }

	  void evalFile(System::String^ file)
	  {
		  char* str = (char*)(void*)Marshal::StringToHGlobalAnsi(file);
	    m->evalFile(str);
		  Marshal::FreeHGlobal(IntPtr(str));

	    //marshal_context ^ context = gcnew marshal_context();
	    //const char* chars = context->marshal_as<const char*>(str);
	   	//m->evalFile(chars);
     	//delete context;
	  }

	  /*
	  System::String^ getMessage()
	  {
		char * message = m->getMessage();
		return gcnew String(message);
	  }

	  signed long getSignedLong()
	  {
	    return m->getSignedLong();
	  }

	  unsigned long getUnsignedLong()
	  {
	    return m->getUnsignedLong();
	  }

	  void call(int n1, int n2, int n3, int n4)
	  {
		m->call(n1,n2,n3,n4);
	  }
	  */
  };
}
