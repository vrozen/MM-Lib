//
//  Types.h
//  mm
//
//  Created by Riemer van Rozen on 7/10/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef mm_Types_h
#define mm_Types_h

namespace MM
{
  typedef unsigned char UINT8;   /**> unsigned byte type */
  typedef long          INT32;   /**> signed 32 bits integer type */
  typedef unsigned long UINT32;  /**> unsigned 32 bits integer type */
  typedef char          CHAR;    /**> character type */
  typedef void          VOID;    /**> void type */
  typedef bool          BOOLEAN; /**> boolean type */
  
  #define MM_MAX_RESOURCES ULLONG_MAX
  
  #define MM_TRUE  true  /**> true value */
  #define MM_FALSE false /**> false value */
  #define MM_NULL  0     /**> null value */
  
  typedef enum MESSAGE
  {
    MSG_ERROR,    //error message
    
    //type creation messages
    MSG_NEW_TYPE,   //a new type definition was created
    MSG_NEW_DECL,   //a declaration of a certain type was made in a definition
    MSG_NEW_POOL,   //a pool was added to a definiton
    MSG_NEW_SOURCE, //a source was added to a definition
    MSG_NEW_DRAIN,  //a drain was added to a definition
    MSG_NEW_GATE,   //a gate was added to a definition
    MSG_NEW_REF,    //a reference (alias) was added to a definition
  
    //type deletion messages
    MSG_DEL_TYPE,   //a type definition was deleted
    MSG_DEL_DECL,   //a declaration was undeclared from a definition
    MSG_DEL_POOL,   //a pool was removed from a definition
    MSG_DEL_SOURCE, //a source was removed from a definition
    MSG_DEL_DRAIN,  //a drain was removed from a definition
    MSG_DEL_GATE,   //a gate was removed from a definition
    MSG_DEL_REF,    //a reference (alias) was removed from a definition
    
    //type update messages
    MSG_UPD_TYPE,   //a type definition was updated
    MSG_UPD_DECL,   //a declaration was updated (it changed type!)
    MSG_UPD_POOL,   //a pool was updated (changed modifiers)
    MSG_UPD_SOURCE, //a source was updated (changed modifiers)
    MSG_UPD_DRAIN,  //a drain was updated (changed modifiers)
    MSG_UPD_GATE,   //a gate was updated (changed modifiers)
    MSG_UPD_REF,    //a reference was updated (can this happen?)
    
    //instance messages
    MSG_NEW_INST,   //a new instance was created inside another instance
    MSG_DEL_INST,   //an instance was deleted from another instance
    
    //instance flow messages needed?
    
    //instance pool message
    MSG_VALUE,     //a pool inside an instance has a new value
    
    //instance trigger message
    MSG_TRIGGER,   //a trigger inside an instance happened

    //instance activated message
    MSG_ACTIVATED, //a node inside an instance was activated
    
    //instance disabled message
    MSG_DISABLED,  //a node inside an instance was not activated
                   //because at least one of its conditions was false
    
    //instance signal condition message
    MSG_SIGNAL     //an invariant inside an instance was violated
  } MSG;
  
  /*
   //NOTE: use observers for now
  //callback type defintions
  typedef MM::VOID (* CALLBACK)
  (
    MM::VOID * caller,     //caller: Who're you gonna call?
    MM::MSG    message,    //what happened?
    MM::UINT32 instance,   //instance in which it happened
                           //MM::UINT32 definition, //definition of the instance
    MM::UINT32 element,    //element (node or assertion) which caused the event
    MM::UINT32 val         //new value in case of MSG_VALUE
  );
   */
  
  //The following enum is not OOP
  //Its reason is avoiding doublde dispatch
  //and matching object type in switch statements
  typedef enum TID
  {
    //base
    T_NULL,
    T_Recycler,
    T_Recyclable,
    T_Observer,
    T_Observable,
    T_String,
    T_Map,
    T_Vector,
    //type transformation
    T_Reflector,
    T_Machine,
    //data transformation
    T_Program,
    T_Evaluator,
    T_Instance,
    T_Transformation,
    T_Transition,
    T_Modification,
    //ast / type
    T_Location,
    T_Name,
    T_Element,
    T_Definition,
    T_Declaration,
    T_Assertion,
    T_Signal,
    T_Deletion,
    T_Edge,
    T_FlowEdge,
    T_StateEdge,
    T_Node,
    T_InterfaceNode,
    T_NodeBehavior,
    T_PoolNodeBehavior,
    T_DrainNodeBehavior,
    T_GateNodeBehavior,
    T_SourceNodeBehavior,
    T_RefNodeBehavior,
    //expressions
    T_Exp,
    T_TriggerExp,
    T_AliasExp,
    T_OneExp,
    T_ActiveExp,
    T_DieExp,
    T_OverrideExp,
    T_VarExp,
    T_AllExp,
    T_BinExp,
    T_UnExp,
    T_ValExp,
    T_BooleanValExp,
    T_NumberValExp,
    T_RangeValExp
  } TID;
}

#endif

