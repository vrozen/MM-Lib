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
 * \class     Declaration
 * \brief     The Declaration abstraction defines that a single named instance
 *            of a specified definition exists in each instance
 *            of the definition that contains the declaration.
 * \note      Declarations are observable such that elements internal to
 *            its type definition become exposed through interface nodes.
 * \file      Declaration.h
 * \author    Riemer van Rozen
 * \date      July 23rd 2013
 */
/******************************************************************************/

#ifndef __mm__Declaration__
#define __mm__Declaration__

namespace MM
{
  class Definition;
  class Declaration : public MM::Element, public MM::Observer
  {
  private:
    MM::Name       * type;  /**> type name */
    MM::Definition * def;   /**> type definition */
    MM::UINT32       label; /**> declaration identifier */

    //declarations observe definitions to spawn and delete interfaces
    //for observable nodes
    MM::Map<MM::Name *, //interface name
            MM::Node *, //interface node
            MM::Name::Compare> * interfaces;
    
  public:
    Declaration(MM::Name * type,
                MM::Name * name,
                MM::Map<MM::Name *, MM::Node *, MM::Name::Compare> * interfaces);
    ~Declaration();
    MM::VOID recycle(MM::Recycler * r);
    
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::VOID update(MM::Observable * observable,
                    MM::VOID * aux,
                    MM::UINT32 message,
                    MM::VOID * object);
    
    MM::Name * getTypeName();
    
    MM::VOID setDefinition(MM::Definition * def);
    MM::Definition * getDefinition();

    MM::Node * getInterface(MM::Name * name);
    MM::VOID addInterface(MM::Machine * m, MM::Node * node);
    MM::VOID removeInterface(MM::Machine * m, MM::Node * node);

    //instance manipulation during transitions
    MM::VOID begin(MM::Instance * i, MM::Machine * m);
    MM::VOID end(MM::Instance * i, MM::Machine * m);
    MM::VOID change(MM::Instance * i, MM::Machine * m);
    
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}

#endif /* defined(__mm__Instance__) */
