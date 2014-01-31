//
//  Pool.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Pool__
#define __mm__Pool__

namespace MM
{
  class Definition;
  class PoolNodeBehavior : public MM::NodeBehavior, public MM::Observer
  {
  private:
    static const MM::CHAR * POOL_STR;
    static const MM::CHAR * OF_STR;
    static const MM::CHAR * AT_STR;
    static const MM::CHAR * MAX_STR;
    static const MM::CHAR * ADD_STR;
    static const MM::CHAR * SELF_STR;

    static const MM::UINT32 POOL_LEN;
    static const MM::UINT32 OF_LEN;
    static const MM::UINT32 AT_LEN;
    static const MM::UINT32 MAX_LEN;
    static const MM::UINT32 ADD_LEN;
    static const MM::UINT32 SELF_LEN;
    
    
    MM::Name * of;
    MM::UINT32 at;
    MM::UINT32 max;
    MM::Exp * exp;
    
    //MM::Name       * type;  /**> type name */
    MM::Definition * def;   /**> type definition */
    
    //declarations observe definitions to spawn and delete interfaces
    //for observable nodes
    MM::Map<MM::Name *, //interface name
    MM::Node *, //interface node
    MM::Name::Compare> * interfaces;
    
  public:
    PoolNodeBehavior(MM::NodeBehavior::IO   io,
                     MM::NodeBehavior::When when,
                     MM::NodeBehavior::Act  act,
                     MM::NodeBehavior::How  how,
                     MM::Name             * of,
                     MM::UINT32             at,
                     MM::UINT32             max,
                     MM::Exp              * exp,
                     MM::Map<MM::Name *, Node *, MM::Name::Compare> * interfaces);
    ~PoolNodeBehavior();
    MM::VOID recycle(MM::Recycler *r);

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
    
    MM::Name * getOf();
    MM::UINT32 getAt();
    MM::UINT32 getMax();
    MM::Exp * getAdd();
    
    MM::VOID setAt(MM::UINT32 at);
    MM::VOID setMax(MM::UINT32 max);
    MM::VOID setAdd(MM::Exp * exp);
    
    MM::UINT32 getCreateMessage();
    MM::UINT32 getUpdateMessage();
    MM::UINT32 getDeleteMessage();
    
    //pull has inherited behavior
    
    MM::VOID stepPullAll(MM::Node * tgtNode,
                         MM::Instance * tgtInstance,
                         MM::Vector<MM::NodeWorkItem *> * work,
                         MM::Machine * m,
                         MM::Transition * tr);

    MM::VOID stepPushAll(MM::Node * srcNode,
                         MM::Instance * srcInstance,
                         MM::Vector<MM::NodeWorkItem *> * work,
                         MM::Machine * m,
                         MM::Transition * tr);

    //instance manipulation during modifications
    MM::VOID begin(MM::Instance * i,
                   MM::Machine  * m,
                   MM::Node     * n);
    MM::VOID end(MM::Instance * i,
                 MM::Machine  * m,
                 MM::Node     * n);
    MM::VOID change(MM::Instance * i,
                    MM::Machine  * m,
                    MM::Node     * n);
    
    //instance manipulation during transitions
    MM::VOID add(MM::Instance * i,
                 MM::Machine  * m,
                 MM::Node     * n,
                 MM::UINT32     amount);
    MM::VOID sub(MM::Instance * i,
                 MM::Machine  * m,
                 MM::Node     * n,
                 MM::UINT32     amount);
    MM::UINT32 getCapacity(MM::Instance * i, MM::Node * n);
    MM::UINT32 getResources(MM::Instance * i, MM::Node * n);
    MM::BOOLEAN hasCapacity(MM::Instance * i, MM::Node * n, MM::UINT32 amount);
    MM::BOOLEAN hasResources(MM::Instance * i, MM::Node * n, MM::UINT32 amount);
    
    MM::VOID toString(MM::String * buf);
    MM::VOID toString(MM::String * buf, MM::Name * name);

  };
}
#endif /* defined(__mm__Pool__) */
