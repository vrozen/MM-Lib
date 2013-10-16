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
  class Definition;
  class Declaration;
  class Instance : public MM::Recyclable, public MM::Observer
  {
  private:
    //type definition
    MM::Definition * type;

    //pool values: pool id --> value
    MM::Map<MM::UINT32 /*id*/, MM::UINT32 /*value*/ > * values;
    
    //declaration instances: declaration id --> instance
    MM::Map<MM::UINT32 /*id*/, MM::Instance * /*instance*/> * instances;
    
    //node id --> boolean
    MM::Vector<MM::UINT32 /*id*/> * activeNodes;
    
  public:
    Instance(MM::Definition * type);
    ~Instance();
    MM::VOID recycle(MM::Recycler * r);

    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::Definition * getDefinition();
    
    //Pool:
    MM::VOID store(MM::UINT32 pool, MM::UINT32 val); //stores a value of a pool
    MM::INT32 retrieve(MM::UINT32 pool);             //retrieves value of a pool

    MM::VOID commit();
    
    //Instances:
    MM::Instance * retrieveInstance(MM::UINT32 decl);
    
    //Activity:
    MM::BOOLEAN isActive(MM::UINT32 node);
    MM::VOID setActive(MM::UINT32 node, MM::BOOLEAN active);

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
    
    //MM::VOID toString(MM::String * buf);
  };
}

#endif /* defined(__mm__Instance__) */
