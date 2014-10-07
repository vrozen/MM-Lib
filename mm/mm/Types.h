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
 * \namespace MM
 * \file      Types.h
 * \author    Riemer van Rozen
 * \date      July 10th 2013
 */
/******************************************************************************/

#ifndef mm_Types_h
#define mm_Types_h

//Dirty trick where C# and C++ share the definition of messages
#include "Message.cs"

//FIXME: HACK
#if _MSC_VER
#define snprintf _snprintf
#endif

#if MM_DEBUG
  #define MM_printf printf
#else
  #define MM_printf
#endif

namespace MM
{
  typedef unsigned char UINT8;   /**> unsigned byte type */
  typedef long          INT32;   /**> signed 32 bits integer type */
  typedef unsigned long UINT32;  /**> unsigned 32 bits integer type */
  typedef char          CHAR;    /**> character type */
  typedef void          VOID;    /**> void type */
  typedef bool          BOOLEAN; /**> boolean type */

  #define MM_MAX_RESOURCES INT_MAX
  #define MM_MIN_RESOURCES INT_MIN
  
  #define MM_TRUE  true  /**> true value */
  #define MM_FALSE false /**> false value */
  #define MM_NULL  0     /**> null value */
  
  //callback type definitions
  typedef MM::VOID (* CALLBACK)
  (
    MM::UINT32 caller,     //caller: Who're you gonna call?
    MM::UINT32 message,    //what happened?
    MM::UINT32 instance,   //instance in which it happened
                           //MM::UINT32 definition, //definition of the instance
    MM::UINT32 element,    //element (node or assertion) which caused the event
    MM::UINT32 val         //new value in case of MSG_VALUE
  );
  
  //The following enum is not OOP
  //Its reason is avoiding doublde dispatch
  //and matching object type in switch statements
  typedef enum TID
  {
    //base
    T_NULL,
    T_Recycler,
    T_Recyclable,
    T_Observer,
    T_Observable,
    T_String,
    T_Map,
    T_Vector,
    //type transformation
    T_Reflector,
    T_Machine,
    T_Delegate,
    T_InstanceObserver, //API
    //data transformation
    T_Program,
    T_Evaluator,
    T_Instance,
    T_Transformation,
    T_Transition,
    T_Modification,
	T_Event,
    T_FlowEvent,
	T_TriggerEvent,
	T_Failure,
    T_Activation,
	T_Violation,
	T_Prevention,
	T_Enablement,
	T_Disablement,
    //ast / type
    T_Location,
    T_Name,
    T_Element,
    T_Definition,
    T_Declaration,
    T_Assertion,
    T_Deletion,
    T_Edge,
    T_FlowEdge,
    T_StateEdge,
    T_Node,
    T_InterfaceNode,
    T_NodeBehavior,
    T_PoolNodeBehavior,
    T_DrainNodeBehavior,
    T_GateNodeBehavior,
    T_SourceNodeBehavior,
    T_RefNodeBehavior,
    T_ConverterNodeBehavior,
    //expressions
    T_Exp,
    T_TriggerExp,
    T_AliasExp,
    T_OneExp,
    T_ActiveExp,
    T_DieExp,
    T_OverrideExp,
    T_VarExp,
    T_AllExp,
    T_BinExp,
    T_UnExp,
    T_ValExp,
    T_BooleanValExp,
    T_NumberValExp,
    T_RangeValExp
  } TID;
  //static const MM::CHAR * TYPE_STR[100];
}

#endif

