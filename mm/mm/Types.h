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
  
  #define MM_TRUE  true  /**> true value */
  #define MM_FALSE false /**> false value */
  #define MM_NULL  0     /**> null value */
  
  typedef enum MESSAGE
  {
    MSG_ERROR,    //error message
    
    //type creation messages
    MSG_NEW_TYPE,
    MSG_NEW_DECL,
    MSG_NEW_POOL,
    MSG_NEW_SOURCE,
    MSG_NEW_DRAIN,
    MSG_NEW_GATE,
    MSG_NEW_REF,
  
    //type deletion messages
    MSG_DEL_TYPE,
    MSG_DEL_DECL,
    MSG_DEL_POOL,
    MSG_DEL_SOURCE,
    MSG_DEL_DRAIN,
    MSG_DEL_GATE,
    MSG_DEL_REF,
    
    //type update messages
    MSG_UPD_TYPE,
    MSG_UPD_DECL,
    MSG_UPD_POOL,
    MSG_UPD_SOURCE,
    MSG_UPD_DRAIN,
    MSG_UPD_GATE,
    MSG_UPD_REF,
    
    //instance messages
    MSG_NEW_INST,
    MSG_DEL_INST,
    
    //instance flow message?
    
    //instance pool message
    MSG_VALUE,     //a pool has a new value
    
    //instance trigger message
    MSG_TRIGGER,   //a trigger happened

    //instance activated message
    MSG_ACTIVATED, //a node was activated
    
    //instance disabled message
    MSG_DISABLED,  //a node was not activated because its conditions where false
    
    //instance signal condition message
    MSG_SIGNAL     //an invariant was violated
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

