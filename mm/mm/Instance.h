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
 * \class     Instance
 * \brief     The instance abstraction defines instance data
 *            that is defined by its definition,
 *            and is manipulated by the evaluator during steps.
 * \note      Observable by components external to MM Lib. 
 * \file      Instance.h
 * \author    Riemer van Rozen
 * \date      September 11th 2013
 */
/******************************************************************************/

#ifndef __mm__Instance__
#define __mm__Instance__

namespace MM
{
  class PoolNodeInstance;

  class Instance : public MM::Recyclable, //managed
                   public MM::Observer,   //observes its definition
                   public MM::Observable  //observed by the outside world
  {
  private:
    static const MM::CHAR * ACTIVE_STR;   /**> active keyword */
    static const MM::CHAR * DISABLED_STR; /**> disabled keyword */
    static const MM::UINT32 INDENT;       /**> serialization indentation amount*/

    MM::Instance * parent; /**> parent instance. /note bad design? */
    MM::Definition * def;  /**> declared type. */
    //MM::Name * name;     /**> declared name. /note necessary? */
    MM::Element * decl;    /**> declared element */
    
    MM::BOOLEAN marked;    /**> marked for deletion or not */

    /* /note : these maps can become arrays
               when nodes and declarations in types have unique sequential labels
               pool values: pool --> value */
    //MM::Map<MM::Node *, MM::INT32> * values;
    //MM::Map<MM::Node *, MM::Vector<Edge *>::Iterator *> * gates;
    //MM::Map<MM::Node *, MM::INT32> * curGateValues;
    
    //temporary values
    //MM::Map<MM::Node *, MM::INT32> * oldValues;  /**> old temporary pool values*/
    //MM::Map<MM::Node *, MM::INT32> * newValues;  /**> new temporary pool values*/
    //MM::Map<MM::Node *, MM::INT32> * gateValues; /**> new temporary gate values*/
    
    //temporary try values for all (no longer used...)
    //MM::Map<MM::Node *, MM::INT32> * oldTryValues; /**> old try values for 'all' */
    //MM::Map<MM::Node *, MM::INT32> * newTryValues; /**> new try values for 'all' */
    
    //declaration instances: declaration --> instance
    //MM::Map<MM::Declaration *, MM::Instance *> * instances; /**> sub-instances*/

    MM::Map<MM::Node *, MM::PoolNodeInstance *> * poolNodeInstances;
    
    MM::Map<MM::Element *, MM::Vector<MM::Instance *> *> * instances;
    
    MM::Vector<MM::Node *> * activeNodes;   /**> active nodes */
    MM::Vector<MM::Node *> * disabledNodes; /**> disabled nodes are
                                                 nodes that are not active
                                                 because a conditions is false*/

    MM::Vector<MM::Node *> * newActiveNodes;   /**> active nodes */
    MM::Vector<MM::Node *> * newDisabledNodes; /**> disabled nodes are
                                                    nodes that are not active
                                                    because a conditions is false*/
    //FIXME: dirty expressions
    MM::Map<MM::Exp *, MM::INT32> * evaluatedExps;
    
  public:
    Instance(MM::Instance * parent,
             MM::Definition * def,
             MM::Element * decl);
    ~Instance();
    MM::VOID recycle(MM::Recycler * r);

    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::Definition * getDefinition();
    MM::Instance * getParent();
    MM::Element * getDeclaration();
    
    //mark and sweep instance deletion
    MM::VOID mark();
    MM::BOOLEAN isMarked();
    MM::VOID sweep(MM::Machine * m);
    
    //Pool:
    //MM::VOID store(MM::Node * pool, MM::UINT32 val); //stores a value of a pool
    //MM::INT32 retrieve(MM::Node * pool);             //retrieves value of a pool
    
    //Instances:
    MM::Map<MM::Element *, MM::Vector<MM::Instance *> *> * getInstances();
    MM::Vector<MM::Instance *> * getInstances(MM::Element * element);
    MM::Instance * getInstance(MM::Declaration * decl);
    
    MM::INT32 getIndex(MM::Element * element, MM::Instance * i);
    
    //pool and gate values:
    MM::INT32 getValue(MM::Node * node);
    MM::INT32 getNewValue(MM::Node * node);
    MM::INT32 getOldValue(MM::Node * node);
    //MM::INT32 getGateValue(MM::Node * node);
    
    //only used during definition modficiations
    MM::VOID deleteValue(MM::Node * node);
    MM::VOID setValue(MM::Node * node, MM::INT32 value);
    
    MM::VOID setNewValue(MM::Node * node, MM::INT32 value);
    MM::VOID setOldValue(MM::Node * node, MM::INT32 value);
    //MM::VOID setGateValue(MM::Node * node, MM::INT32 value);
    
    //Edge expression evaluation
    MM::BOOLEAN isEvaluatedExp(MM::Exp * exp);
    MM::VOID setEvaluatedExp(MM::Exp * exp, MM::INT32 val);
    MM::INT32 getEvaluatedExp(MM::Exp * exp);
    
    //Activity:
    MM::BOOLEAN isActive(MM::Node * node);
    MM::VOID setActive(MM::Node * node);
	  MM::VOID setNextActive(MM::Node * node);

    //Disabed:
    MM::BOOLEAN isDisabled(MM::Node * node);
    MM::VOID setDisabled(MM::Node * node);
    
    //Type updates that require dynamic fixes
    MM::VOID update(MM::Observable * observable,
                    MM::VOID * aux,
                    MM::UINT32 message,
                    MM::VOID * object);
    
  //private:
    //MM::VOID createNode(MM::Node * node);
    
    //MM::VOID createInstance(MM::Declaration * decl, MM::Machine * m);
    //MM::VOID createPool(MM::Node * pool, MM::Machine * m);
    //MM::VOID createGate(MM::Node * gate);
    //MM::VOID createSource(MM::Node * source);
    //MM::VOID createDrain(MM::Node * drain);
    //MM::VOID createConverter(MM::Node * converter);
    //MM::VOID createReference(MM::Node * ref);
    
    //MM::VOID removeInstance(MM::Declaration * decl, MM::Recycler * r);
    //MM::VOID removePool(MM::Node * pool);
    
    //MM::VOID createInstancePool(MM::Node         * node,
    //                            MM::UINT32         at,
    //                            MM::Machine      * m,
    //                            MM::Definition   * unitDef);
    
    //MM::VOID removeGate(MM::Node * gate);
    //MM::VOID removeSource(MM::Node * source);
    //MM::VOID removeDrain(MM::Node * drain);
    //MM::VOID removeConverter(MM::Node * converter);
    //MM::VOID removeReference(MM::Node * ref);
    
  public:
    MM::VOID createInstances(MM::Element    * element,
                             MM::Machine    * m,
                             MM::Definition * unitDef,
                             MM::UINT32       amount);
    
    MM::VOID destroyInstances(MM::Element    * element,
                              MM::Machine    * m,
                              MM::UINT32       amount);

    MM::VOID destroyAllInstances(MM::Element    * element,
                                 MM::Machine    * m);

    MM::VOID destroyInstance(MM::Element  * element,
                             MM::Machine  * m,
                             MM::Instance * i);    

    MM::PoolNodeInstance * getPoolNodeInstance(MM::Node * node);
    MM::VOID addPoolNodeInstance(MM::PoolNodeInstance * poolNodeInstance);
    MM::VOID removePoolNodeInstance(MM::PoolNodeInstance * poolNodeInstance);

    MM::VOID begin();
    MM::VOID finalize();

    MM::VOID clearActive();
    MM::VOID clearDisabled();
    
    MM::INT32 getCapacity(MM::Node * node, MM::Machine * m);
    MM::INT32 getResources(MM::Node * node, MM::Machine * m);
    MM::BOOLEAN hasResources(MM::Node * node, MM::UINT32 amount, MM::Machine * m);
    MM::BOOLEAN hasCapacity(MM::Node * node, MM::UINT32 amount, MM::Machine * m);
    MM::VOID sub(MM::Node * node, MM::Machine * m, MM::UINT32 amount);
    MM::VOID add(MM::Node * node, MM::Machine * m, MM::UINT32 amount);
        
    MM::VOID MM::Instance::notifyValues(MM::Machine * m);

    MM::VOID findNodeInstance(MM::Node * node,
                              MM::Node ** rNode,
                              MM::Instance ** rInstance);

    MM::VOID findNodeInstance(MM::VarExp * exp,
                              MM::Node ** rNode,
                              MM::Instance ** rInstance);

    MM::PoolNodeInstance * findPoolNodeInstance(MM::VarExp * varExp);

    MM::VOID nameToString(MM::String * buf);
    MM::VOID nameToString(MM::Element * element, MM::String * buf);
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}

#endif /* defined(__mm__Instance__) */
