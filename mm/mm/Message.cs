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
 * \enum      MESSAGE
 * \brief     MESSAGE enumeration defines messages sent to observers.
 * \note      Using define hackery for single file maintenance this file is C++
 * \namespace LibMM
 * \enum      MESSAGE
 * \brief     MESSAGE enumeration defines messages sent to observers
 * \note      Using define hackery for single file maintenance this file is C#
 * \file      Message.cs
 * \author    Riemer van Rozen
 * \date      September 13th 2013
 */
/******************************************************************************/

#if __cplusplus
namespace MM
{

#else
namespace LibMM
{
  public
#endif

  enum MESSAGE
  {
    MSG_ERROR,    //error message
    
    //type creation messages
    MSG_NEW_TYPE,   //a new type definition was created
    MSG_NEW_DECL,   //a declaration of a certain type was made in a definition
    MSG_NEW_POOL,   //a pool was added to a definiton
    MSG_NEW_SOURCE, //a source was added to a definition
    MSG_NEW_DRAIN,  //a drain was added to a definition
    MSG_NEW_GATE,   //a gate was added to a definition
    MSG_NEW_REF,    //a reference (alias) was added to a definition
    MSG_NEW_CONVERTER,
 
    MSG_NEW_CONDITION,
    MSG_NEW_TRIGGER,
    MSG_NEW_FLOW,

    
    //type deletion messages
    MSG_DEL_TYPE,   //a type definition was deleted
    MSG_DEL_DECL,   //a declaration was undeclared from a definition
    MSG_DEL_POOL,   //a pool was removed from a definition
    MSG_DEL_SOURCE, //a source was removed from a definition
    MSG_DEL_DRAIN,  //a drain was removed from a definition
    MSG_DEL_GATE,   //a gate was removed from a definition
    MSG_DEL_REF,    //a reference (alias) was removed from a definition
    MSG_DEL_CONVERTER,

    MSG_DEL_CONDITION,
    MSG_DEL_TRIGGER,
    MSG_DEL_FLOW,
    
    //type update messages
    MSG_UPD_TYPE,   //a type definition was updated
    MSG_UPD_DECL,   //a declaration was updated (it changed type!)
    MSG_UPD_POOL,   //a pool was updated (changed modifiers)
    MSG_UPD_SOURCE, //a source was updated (changed modifiers)
    MSG_UPD_DRAIN,  //a drain was updated (changed modifiers)
    MSG_UPD_GATE,   //a gate was updated (changed modifiers)
    MSG_UPD_REF,    //a reference was updated (can this happen?)
    MSG_UPD_CONVERTER,
    
    MSG_UPD_CONDITION,
    MSG_UPD_TRIGGER,
    MSG_UPD_FLOW,
    
    //instance messages
    MSG_NEW_INST,   //a new instance was created inside another instance
    MSG_DEL_INST,   //an instance was deleted from another instance
    
    //instance flow messages needed?
    
    //instance value messages
    MSG_ADD_VALUE,
    MSG_SUB_VALUE,
	  MSG_HAS_VALUE,
    
    //instance trigger message
    MSG_TRIGGER,   //a trigger inside an instance happened

    //instance activated message
    MSG_ACTIVATED, //a node inside an instance was activated
    
    //instance disabled message
    MSG_DISABLED,  //a node inside an instance was not activated
                   //because at least one of its conditions was false
    
    //instance signal condition message
    MSG_SIGNAL     //an invariant inside an instance was violated
  };

#if __cplusplus
  typedef enum MESSAGE MSG;
};

#else
}
#endif