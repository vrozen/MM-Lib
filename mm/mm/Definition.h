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
 * \class     Definition
 * \brief     The definition abstraction and the elements contained within it
 *            define the structure and behavior of instances created
 *            for the global scope, instance pools or declarations.
 * \note      Definitions are observable, such that notifications about
 *            structural changes are sent to observers,
 *            enabling structural reflection.
 * \file      Definition.h
 * \author    Riemer van Rozen
 * \date      July 21rd 2013
 */
/******************************************************************************/

#ifndef __mm__Definition__
#define __mm__Definition__

namespace MM
{
  class Declaration;
  class Definition : public MM::Element,
                     public MM::Observable /* observed by Declarations */
  {
  public:
    //static const MM::CHAR LPAREN_CHAR;     /**> left parenthesis character */
    //static const MM::CHAR RPAREN_CHAR;     /**> right parenthesis character */
    static const MM::CHAR LBRACE_CHAR;     /**> left brace character */
    static const MM::CHAR RBRACE_CHAR;     /**> right brace character */
    static const MM::CHAR COMMA_CHAR;      /**> comma character */
  private:
    MM::Vector<MM::Element *> * elements;  /**> elements in this definition */
    
    MM::Definition * parent; /**> definition one level up in lexical scoping */
    
    MM::Vector<MM::Node *> * pullAllNodes; /**> nodes with pull all modifiers */
    MM::Vector<MM::Node *> * pullAnyNodes; /**> nodes with pull any modifiers */
    MM::Vector<MM::Node *> * pushAllNodes; /**> nodes with push all modifiers */
    MM::Vector<MM::Node *> * pushAnyNodes; /**> nodes with push any modifiers */
    
    
    //tell declarations nodes were added / removed to update their interfaces
    //MM::Vector<MM::Declaration *> * declarations;
    
    MM::Map<MM::Name *, MM::Element *, MM::Name::Compare> * n2e; /**> name --> element */
    
    //maps contains nodes and type defs for searching the name space
    //reason for adding id: quick lookups and indirection on changing nodes
    //name --> id
    //MM::Map<MM::Name * /*name*/, MM::UINT32 /*id*/, MM::Name::Compare> * n2i;
    //id --> element
    //MM::Map<MM::UINT32 /*id*/, MM::Element * /*element*/> i2e;
    
  public:
    Definition(MM::Name * name, MM::Vector<MM::Element *> * elements);
    Definition(MM::Vector<MM::Element *> * elements);
    ~Definition();
    MM::VOID recycle(MM::Recycler * r);
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);

    MM::Vector<MM::Node *> * getPullAllNodes();
    MM::Vector<MM::Node *> * getPullAnyNodes();
    MM::Vector<MM::Node *> * getPushAllNodes();
    MM::Vector<MM::Node *> * getPushAnyNodes();
    
    MM::VOID prioritize(MM::Node * node);
    MM::VOID deprioritize(MM::Node * node);
    
    MM::VOID addPullAllNode(MM::Node * node);
    MM::VOID addPullAnyNode(MM::Node * node);
    MM::VOID addPushAllNode(MM::Node * node);
    MM::VOID addPushAnyNode(MM::Node * node);
    
    MM::VOID removePullAllNode(MM::Node * node);
    MM::VOID removePullAnyNode(MM::Node * node);
    MM::VOID removePushAllNode(MM::Node * node);
    MM::VOID removePushAnyNode(MM::Node * node);
        
    MM::VOID setPullAllNodes(MM::Vector<MM::Node *> * pullAllNodes);
    MM::VOID setPullAnyNodes(MM::Vector<MM::Node *> * pullAnyNodes);
    MM::VOID setPushAllNodes(MM::Vector<MM::Node *> * pushAllNodes);
    MM::VOID setPushAnyNodes(MM::Vector<MM::Node *> * pullAnyNodes);
    
    //MM::VOID setNameToIdMap(MM::Map<MM::Name *, MM::UINT32, MM::Name::Compare> * n2i);
    //MM::VOID setIdToElementMap(MM::Map<MM::UINT32, MM::Element *> i2e);
    
    MM::VOID setNameToElementMap(MM::Map<MM::Name *, MM::Element *, MM::Name::Compare> * n2e);
    
    MM::VOID setParent(MM::Definition * parent);

    MM::Node * findNode(MM::Name * name, MM::NodeBehavior::IO direction);
    
    MM::Definition * findDeclaredDefinition(MM::Name * name);
    MM::Definition * findQueriedDefinition(MM::Name * name);
    
    MM::Element * getElement(MM::Name * name);
    MM::VOID putElement(MM::Name * name, MM::Element * element);
    MM::VOID removeElement(MM::Name * name);
    MM::VOID addElement(MM::Element * element);
    MM::VOID removeElement(MM::Element * element);
    MM::BOOLEAN containsElement(MM::Element * element);
    MM::VOID clearElements();
    MM::Vector<MM::Element *> * getElements();
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}

#endif /* defined(__mm__Definition__) */
