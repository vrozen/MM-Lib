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
    MSG_NEW_REF,
  
    //type deletion messages
    MSG_DEL_TYPE,
    MSG_DEL_DECL,
    MSG_DEL_POOL,
    MSG_DEL_SOURCE,
    MSG_DEL_DRAIN,
    MSG_DEL_REF,
    
    //type update messages
    MSG_UPD_TYPE,
    MSG_UPD_DECL,
    MSG_UPD_POOL,
    MSG_UPD_SOURCE,
    MSG_UPD_DRAIN,
    MSG_UPD_REF,
    
    //instance messages
    MSG_NEW_INST,
    MSG_DEL_INST,
    MSG_VAL_POOL,
    MSG_SIGNAL    //inst: signal condition
  } MSG;
  
  //callback type defintions
  typedef MM::VOID (*CALLBACK)
  (
    MM::VOID * caller,     //caller: Who're you gonna call?
    MM::MSG    message,    //what happened?
    MM::UINT32 instance,   //instance
    MM::UINT32 definition, //definition
    MM::UINT32 pool,       //pool when MSG_VAL_POOL, signal when MSG_SIGNAL
    MM::UINT32 val         //new value in case of MSG_VAL_POOL
  );
  
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
    T_Evaluator,
    T_Instance,
    T_Event,
    T_FlowEvent,
    T_StepEvent,
    T_Transition,
    //ast / type
    T_Location,
    T_Name,
    T_Element,
    T_Definition,
    T_Declaration,
    T_Assert,
    T_Delete,
    T_Edge,
    T_FlowEdge,
    T_StateEdge,
    T_Node,
    T_InterfaceNode,
    T_NodeBehavior,
    T_PoolNodeBehavior,
    T_DrainNodeBehavior,
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

