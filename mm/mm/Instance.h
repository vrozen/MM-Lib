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
  class Instance : public MM::Recyclable, public MM::Observer
  {
  public:
    static const MM::UINT32 INDENT;
  private:
    MM::Instance * parent; /**> parent instance. @note: bad design? */
    MM::Definition * type; /**> declared type. */
    MM::Name * name;       /**> declared name. @note: necessary? */

    //NOTE: these maps can become arrays
    //      when nodes and declarations in types have unique sequential labels
    //      pool values: pool --> value
    MM::Map<MM::Node *, MM::UINT32> * values;
    MM::Map<MM::Node *, MM::UINT32> * oldValues;
    MM::Map<MM::Node *, MM::UINT32> * newValues;
    
    //declaration instances: declaration --> instance
    MM::Map<MM::Declaration *, MM::Instance *> * instances;
    
    //node --> boolean
    MM::Vector<MM::Node *> * activeNodes; /**> TODO: bitvector */
    
    //node --> boolean
    MM::Vector<MM::Node *> * disabledNodes; /**> TODO: bitvector */
    
  public:
    Instance(MM::Instance * parent,
             MM::Definition * def,
             MM::Name * name);
    ~Instance();
    MM::VOID recycle(MM::Recycler * r);

    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::Map<MM::Declaration *, MM::Instance *> * getInstances();
    
    MM::Definition * getDefinition();
    MM::Instance * getParent();
    MM::Name * getName();
    
    //Pool:
    MM::VOID store(MM::Node * pool, MM::UINT32 val); //stores a value of a pool
    MM::INT32 retrieve(MM::Node * pool);             //retrieves value of a pool
    
    //Instances:
    MM::Instance * retrieveInstance(MM::Declaration * decl);
    
    MM::UINT32 getValue(MM::Node * node);
    
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
    MM::VOID createInstance(MM::Declaration * decl, MM::Machine * m);
    MM::VOID createPool(MM::Node * pool);

    MM::VOID removeInstance(MM::Declaration * decl, MM::Recycler * r);
    MM::VOID removePool(MM::Node * pool);
    
  public:
    MM::VOID begin();
    MM::UINT32 getCapacity(MM::Node * node);
    MM::UINT32 getResources(MM::Node * node);
    MM::BOOLEAN hasResources(MM::Node * node, MM::UINT32 amount);
    MM::BOOLEAN hasCapacity(MM::Node * node, MM::UINT32 amount);
    MM::VOID sub(MM::Node * node, MM::UINT32 amount);
    MM::VOID add(MM::Node * node, MM::UINT32 amount);
    MM::VOID commit();
    MM::VOID rollback();
  public:
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::UINT32 indent);
  };
}

#endif /* defined(__mm__Instance__) */
