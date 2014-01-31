//
//  Instance.h
//  mm
//
//  Created by Riemer van Rozen on 7/23/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

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
