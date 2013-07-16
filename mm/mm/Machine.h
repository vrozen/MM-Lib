//
//  Machine.h
//  mm
//
//  Created by Riemer van Rozen on 7/16/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Machine__
#define __mm__Machine__


namespace MM
{
  //callback type defintion
  typedef MM::VOID (*CALLBACK)
  (
    MM::VOID *caller, //caller
    MM::UINT32 pool,  //pool element handle
    MM::UINT32 val    //new pool value
  );
  
  class Machine
  {
  public:
    Machine();
    ~Machine();
    
    //takes a step in an MM model
    MM::VOID   step();
    
    //evaluates input and adds elements to the model
    MM::VOID   eval          (MM::String input);
    
    //adds a type definition and returns its API handle (definitions are global)
    MM::UINT32 addDefinition (MM::String name);
    
    //adds an instance to a parent element
    MM::UINT32 addInstance   (MM::UINT32 parent,   //0 -> global scope)
                              MM::UINT32 instance);
    
    //adds a pool to a perent element
    MM::UINT32 addPool       (MM::UINT32   parent, //0 -> global scope)
                              MM::When     when,
                              MM::Act      act,
                              MM::How      how,
                              MM::String * name,
                              MM::INT32    at,
                              MM::UINT32   max,
                              MM::Exp    * exp);
    
    //adds a source to a parent element
    MM::UINT32 addSource     (MM::UINT32   parent, //0 -> global scope)
                              MM::When     when,
                              MM::Act      act,
                              MM::How      how,
                              MM::String * name);
    
    //adds a drain to a parent element
    MM::UINT32 addDrain      (MM::UINT32   parent, //0 -> global scope)
                              MM::When     when,
                              MM::Act      act,
                              MM::How      how,
                              MM::String * name);
    
    //adds a flow edge between two nodes
    MM::UINT32 addFlow       (MM::UINT32   src,
                              MM::Exp    * exp,
                              MM::UINT32   tgt);

    //adds a condition between two nodes
    MM::UINT32 addCondition  (MM::UINT32   src,
                              MM::Exp    * exp,
                              MM::UINT32   tgt);

    //adds a trigger
    MM::UINT32 addTrigger    (MM::UINT32   src,
                              MM::UINT32   tgt);
    
    //retrieves a handle from a parent element by name
    MM::UINT32 get           (MM::UINT32 parent,  //0 -> global scope)
                              MM::String * name);
    
    //removes an element from the model
    MM::VOID   remove        (MM::UINT32 parent); //0 -> global scope)
    
    //adds an observer to the model
    //the caller receives a callback
    MM::UINT32 addObserver   (MM::UINT32     pool,
                              MM::VOID     * caller,
                              MM::CALLBACK   callback);
    
    //removes an observer from a node
    MM::VOID   removeObserver(MM::UINT32     node);
  };
}
#endif /* defined(__mm__Machine__) */

