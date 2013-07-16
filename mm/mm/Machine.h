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
    MM::VOID   eval             (MM::CHAR   * input);
    
    //adds a type definition and returns its API handle (definitions are global)
    MM::UINT32 createDefinition (MM::CHAR   * name);
    
    //adds an instance to a parent element
    MM::UINT32 createInstance   (MM::UINT32   instance,   //0 -> global scope)
                                 MM::UINT32   definition);
    
    //adds a pool to a perent element
    MM::UINT32 createPool       (MM::UINT32   definition, //0 -> global scope)
                                 MM::When     when,
                                 MM::Act      act,
                                 MM::How      how,
                                 MM::CHAR   * name,
                                 MM::INT32    at,
                                 MM::UINT32   max,
                                 MM::Exp    * exp);
    
    //adds a source to a parent element
    MM::UINT32 createSource     (MM::UINT32   definition, //0 -> global scope)
                                 MM::When     when,
                                 MM::Act      act,
                                 MM::How      how,
                                 MM::CHAR  *  name);
    
    //adds a drain to a parent element
    MM::UINT32 createDrain      (MM::UINT32   definition, //0 -> global scope)
                                 MM::When     when,
                                 MM::Act      act,
                                 MM::How      how,
                                 MM::CHAR *   name);
    
    //adds a flow edge between two nodes
    MM::UINT32 createFlow       (MM::UINT32   src,
                                 MM::Exp    * exp,
                                 MM::UINT32   tgt);
    
    //adds a condition between two nodes
    MM::UINT32 createCondition  (MM::UINT32   src,
                                 MM::Exp    * exp,
                                 MM::UINT32   tgt);
    
    //adds a trigger
    MM::UINT32 createTrigger    (MM::UINT32   src,
                                 MM::UINT32   tgt);
    
    //retrieves a handle from a parent element by name
    MM::UINT32 get              (MM::UINT32   instance,  //0 -> global scope)
                                 MM::CHAR   * name);
    
    //removes an element from the model
    MM::VOID   destroy          (MM::UINT32   node); //0 -> global scope)
    
    //adds an observer to the model
    //the caller receives a callback
    MM::UINT32 addObserver      (MM::UINT32     pool,
                                 MM::VOID     * caller,
                                 MM::CALLBACK   callback);
    
    //removes an observer from a node
    MM::VOID   removeObserver   (MM::UINT32     node);
  };
}
#endif /* defined(__mm__Machine__) */

