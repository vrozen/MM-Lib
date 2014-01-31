//
//  Instance.h
//  mm
//
//  Created by Riemer van Rozen on 9/11/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Instance__
#define __mm__Instance__

namespace MM
{
  //class Definition;
  //class Declaration;
  class Instance : public MM::Recyclable, //managed
                   public MM::Observer,   //observes its definition
                   public MM::Observable  //observed by the outside world
  {
  public:
    static const MM::CHAR * ACTIVE_STR;   /**> active string */
    static const MM::CHAR * DISABLED_STR; /**> disabled string */
    static const MM::UINT32 INDENT;       /**> serialization indentation amount*/
  private:
    MM::Instance * parent; /**> parent instance. @note: bad design? */
    MM::Definition * def;  /**> declared type. */
    //MM::Name * name;     /**> declared name. @note: necessary? */
    MM::Element * decl;    /**> declared element */
    
    MM::BOOLEAN marked;    /**> marked for deletion or not */

    //NOTE: these maps can become arrays
    //      when nodes and declarations in types have unique sequential labels
    //      pool values: pool --> value
    MM::Map<MM::Node *, MM::UINT32> * values;
    MM::Map<MM::Node *, MM::Vector<Edge *>::Iterator *> * gates;
    MM::Map<MM::Node *, MM::UINT32> * curGateValues;
    
    //temporary values
    MM::Map<MM::Node *, MM::UINT32> * oldValues;  /**> old temporary pool values*/
    MM::Map<MM::Node *, MM::UINT32> * newValues;  /**> new temporary pool values*/
    MM::Map<MM::Node *, MM::UINT32> * gateValues; /**> new temporary gate values*/
    
    //temporary try values for all
    MM::Map<MM::Node *, MM::UINT32> * oldTryValues; /**> old try values for 'all' */
    MM::Map<MM::Node *, MM::UINT32> * newTryValues; /**> new try values for 'all' */
    
    //declaration instances: declaration --> instance
    //MM::Map<MM::Declaration *, MM::Instance *> * instances; /**> sub-instances*/
    
    MM::Map<MM::Element *, MM::Vector<MM::Instance *> *> * instances;
    
    MM::Vector<MM::Node *> * activeNodes;   /**> active nodes */
    MM::Vector<MM::Node *> * disabledNodes; /**> disabled nodes are
                                                 nodes that are not active
                                                 because a conditions is false*/
    
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
    MM::UINT32 getValue(MM::Node * node);
    MM::UINT32 getNewValue(MM::Node * node);
    MM::UINT32 getOldValue(MM::Node * node);
    MM::UINT32 getGateValue(MM::Node * node);
    
    //only used during definition modficiations
    MM::VOID deleteValue(MM::Node * node);
    MM::VOID setValue(MM::Node * node, MM::UINT32 value);
    
    MM::VOID setNewValue(MM::Node * node, MM::UINT32 value);
    MM::VOID setOldValue(MM::Node * node, MM::UINT32 value);
    MM::VOID setGateValue(MM::Node * node, MM::UINT32 value);
    
    //Edge expression evaluation
    MM::BOOLEAN isEvaluatedExp(MM::Exp * exp);
    MM::VOID setEvaluatedExp(MM::Exp * exp, MM::INT32 val);
    MM::INT32 getEvaluatedExp(MM::Exp * exp);
    
    //Activity:
    MM::BOOLEAN isActive(MM::Node * node);
    MM::VOID setActive(MM::Node * node);

    //Disabed:
    MM::BOOLEAN isDisabled(MM::Node * node);
    MM::VOID setDisabled(MM::Node * node);
    
    //Type updates that require dynamic fixes
    MM::VOID update(MM::Observable * observable,
                    MM::VOID * aux,
                    MM::UINT32 message,
                    MM::VOID * object);
    
  private:
    MM::VOID createNode(MM::Node * node);
    
    MM::VOID createInstance(MM::Declaration * decl, MM::Machine * m);
    MM::VOID createPool(MM::Node * pool, MM::Machine * m);
    MM::VOID createGate(MM::Node * gate);
    MM::VOID createSource(MM::Node * source);
    MM::VOID createDrain(MM::Node * drain);
    MM::VOID createConverter(MM::Node * converter);
    MM::VOID createReference(MM::Node * ref);
    
    MM::VOID removeInstance(MM::Declaration * decl, MM::Recycler * r);
    MM::VOID removePool(MM::Node * pool);
    
    MM::VOID createInstancePool(MM::Node         * node,
                                MM::UINT32         at,
                                MM::Machine      * m,
                                MM::Definition   * unitDef);
    
    MM::VOID removeGate(MM::Node * gate);
    MM::VOID removeSource(MM::Node * source);
    MM::VOID removeDrain(MM::Node * drain);
    MM::VOID removeConverter(MM::Node * converter);
    MM::VOID removeReference(MM::Node * ref);
    
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
    
    MM::VOID begin();
    MM::VOID finalize();

    MM::VOID clearActive();
    MM::VOID clearDisabled();
    
    MM::UINT32 getCapacity(MM::Node * node);
    MM::UINT32 getResources(MM::Node * node);
    MM::BOOLEAN hasResources(MM::Node * node, MM::UINT32 amount);
    MM::BOOLEAN hasCapacity(MM::Node * node, MM::UINT32 amount);
    MM::VOID sub(MM::Node * node, MM::Machine * m, MM::UINT32 amount);
    MM::VOID add(MM::Node * node, MM::Machine * m, MM::UINT32 amount);
    
  public:
    MM::VOID nameToString(MM::Element * element, MM::String * buf);
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}

#endif /* defined(__mm__Instance__) */
