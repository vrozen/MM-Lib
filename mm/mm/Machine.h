//
//  Machine.h
//  mm
//
//  Created by Riemer van Rozen on 7/16/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Machine__
#define __mm__Machine__

#define MAX_DEFS  1024
#define MAX_INSTS 1024

namespace MM
{
  typedef enum __MESSAGE
  {
    MSG_ERROR,    //error message
    MSG_NEW_INST, //instance created
    MSG_DEL_INST, //instance deleted
    MSG_NEW_POOL, //pool created
    MSG_DEL_POOL, //pool deleted
    MSG_VAL_POOL, //pool value changed
    MSG_SIGNAL    //signal condition
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
  
  typedef struct __Instance
  {
    MM::UINT32 type;
    MM::UINT32 pools;
    MM::UINT32 gates;
    MM::UINT32 insts;
    MM::CHAR mem[];
  } Instance;
  
  class Definition;
  
  class Machine
  {
  private:
    MM::UINT32 curDef;
    MM::UINT32 curInst;
    MM::Definition * defs[MAX_DEFS];
    MM::Instance   * insts[MAX_INSTS];
        
  public:
    Machine();
    ~Machine();
    
    //takes a step in an MM model
    MM::Transition * step       ();
    
    //evaluates input and adds elements to the model
    MM::VOID * eval             (MM::CHAR   * input);
    
    //retrieves a definition from a parent element by name
    MM::UINT32 get              (MM::UINT32   node,  //0 -> global scope
                                 MM::CHAR   * name);
    
    MM::VOID   getName          (MM::UINT32   node,
                                 MM::CHAR *   buffer,
                                 MM::UINT32   bufferSize);
    
    //activates an interactive node
    MM::VOID   activate         (MM::UINT32   node);
    
    //removes an element from the model
    MM::VOID   destroy          (MM::UINT32   node); //0 -> global scope
    
    //resets all instances to definition start values
    MM::VOID   reset            ();
    
    
    //adds an observer to the model
    //the caller receives a callback
    MM::UINT32 addObserver(MM::UINT32 definition,
                           MM::VOID * caller,
                           MM::CALLBACK);
    
    //removes an observer from a pools
    MM::VOID   removeObserver   (MM::UINT32 observer);
    
    
    /*
     //adds a type definition and returns its API handle (definitions are global)
     MM::UINT32 addDefinition    (MM::CHAR   * name);
     
     //adds an instance to a parent element
     MM::UINT32 addDeclaration   (MM::UINT32   type, //0 -> global scope
     MM::UINT32   decl_type,
     MM::CHAR   * name);
     
     //adds a pool to a perent element
     MM::UINT32 addPool          (MM::UINT32     type, //0 -> global scope
     MM::Node::When when,
     MM::Node::Act  act,
     MM::Node::How  how,
     MM::CHAR     * name,
     MM::INT32      at,
     MM::UINT32     max,
     MM::CHAR     * exp);
     
     //adds a source to a parent element
     MM::UINT32 addSource        (MM::UINT32      type, //0 -> global scope
     MM::Node::When  when,
     MM::Node::Act   act,
     MM::Node::How   how,
     MM::CHAR      * name);
     
     //adds a drain to a parent element
     MM::UINT32 addDrain         (MM::UINT32      type, //0 -> global scope
     MM::Node::When  when,
     MM::Node::Act   act,
     MM::Node::How   how,
     MM::CHAR      * name);
     
     //adds a flow edge between two nodes
     MM::UINT32 addFlow          (MM::UINT32   src,
     MM::CHAR   * exp,
     MM::UINT32   tgt);
     
     //adds a condition between two nodes
     MM::UINT32 addCondition     (MM::UINT32   src,
     MM::CHAR   * exp,
     MM::UINT32   tgt);
     
     //adds a trigger
     MM::UINT32 addTrigger       (MM::UINT32   src,
     MM::UINT32   tgt);
     */
    
    
    
    //------------------------------------------------------------
    // Create
    //------------------------------------------------------------
    std::vector<MM::Element*> * createList();
    std::vector<MM::Element*> * createList(std::vector<MM::Element*> * elements, MM::Element * element);
    
    MM::Location * createLocation(YYLTYPE * loc);
    
    MM::Name * createName(MM::Name * n1,
                          MM::CHAR * str,
                          YYLTYPE  * strLoc);
  
    MM::Name * createName(MM::CHAR * str,
                          YYLTYPE  * strLoc);
    
    MM::SourceNode * createSourceNode(MM::Node::IO    io,
                                      MM::Node::When  when,
                                      MM::Node::Act   act,
                                      MM::Node::How   how,
                                      MM::Name      * name);
    
    MM::DrainNode * createDrainNode(MM::Node::IO    io,
                                    MM::Node::When  when,
                                    MM::Node::Act   act,
                                    MM::Node::How   how,
                                    MM::Name      * name);
    
    MM::PoolNode * createPoolNode(MM::Node::IO    io,
                                  MM::Node::When  when,
                                  MM::Node::Act   act,
                                  MM::Node::How   how,
                                  MM::Name      * name,
                                  MM::UINT32      at,
                                  MM::UINT32      max,
                                  MM::Exp       * exp);
    
    MM::RefNode * createRefNode(MM::Name * name);
    
    MM::StateEdge * createStateEdge(MM::Name * src,
                                    MM::Exp  * exp,
                                    MM::Name * tgt);
    
    MM::FlowEdge * createFlowEdge(MM::Name * src,
                                  MM::Exp  * exp,
                                  MM::Name * tgt);

    MM::Definition * createDefinition(MM::Name * name,
                                      std::vector<Element*> * es);
    
    MM::Declaration * createDeclaration(MM::Name * type,
                                        MM::Name * name);
    
    MM::Assert * createAssert(MM::Name * name,
                              MM::Exp  * exp,
                              MM::CHAR * msg,
                              YYLTYPE  * msgLoc);
    
    MM::UnExp * createUnExp(MM::Operator::OP  op,
                            YYLTYPE         * opLoc,
                            MM::Exp         * exp);
    
    MM::BinExp * createBinExp(MM::Exp          * e1,
                              MM::Operator::OP   op,
                              YYLTYPE          * opLoc,
                              MM::Exp          * e2);
    
    MM::OverrideExp * createOverrideExp(YYLTYPE * lparenLoc,
                                        MM::Exp * e,
                                        YYLTYPE * rparenLoc);
    
    MM::RangeValExp * createRangeValExp(MM::INT32   v1,
                                        YYLTYPE   * v1Loc,
                                        YYLTYPE   * rangeLoc,
                                        MM::INT32   v2,
                                        YYLTYPE   * v2Loc);
    
    MM::NumberValExp * createNumberValExp(MM::INT32  val,
                                          YYLTYPE  * valLoc);
    
    MM::BooleanValExp * createBooleanValExp(MM::BOOLEAN val,
                                            YYLTYPE * valLoc);
    
    MM::AllExp * createAllExp(YYLTYPE * allLoc);
    
    MM::ActiveExp * createActiveExp(YYLTYPE  * activeLoc,
                                    MM::Name * name);
    
    MM::AliasExp * createAliasExp(YYLTYPE * aliasLoc);
    
    MM::OneExp * createOneExp(YYLTYPE * epsilonLoc);
    
    MM::VarExp * createVarExp(MM::Name * name);

    
    //------------------------------------------------------------
    // Recycle
    //------------------------------------------------------------
    MM::VOID recycleLocation(MM::Location * loc);
    
    MM::VOID recycleName(MM::Name * name);
    
    MM::VOID recycleSourceNode(MM::SourceNode * node);
    
    MM::VOID recycleDrainNode(MM::DrainNode * node);
    
    MM::VOID recyclePoolNode(MM::PoolNode * node);
    
    MM::VOID recycleRefNode(MM::RefNode * node);
    
    MM::VOID recycleStateEdge(MM::StateEdge * edge);
    
    MM::VOID recycleFlowEdge(MM::FlowEdge * edge);
    
    /* MM::Assert * createAssert */
    
    MM::VOID recycleUnExp(MM::UnExp * exp);
    
    MM::VOID recycleBinExp(MM::BinExp * exp);
    
    MM::VOID recycleOverrideExp(MM::OverrideExp * exp);
    
    MM::VOID recycleRangevalExp(MM::RangeValExp * exp);
    
    MM::VOID recycleNumberValExp(MM::NumberValExp * exp);
    
    MM::VOID recycleBooleanValExp(MM::BooleanValExp * exp);
    
    MM::VOID recycleAllExp(MM::AllExp * exp);
    
    MM::VOID recycleActiveExp(MM::ActiveExp * exp);
    
    MM::VOID recycleAliasExp(MM::AliasExp * exp);
    
    MM::VOID recycleOneExp(MM::OneExp * exp);
    
    MM::VOID recycleVarExp(MM::VarExp * exp);    
    
  };
}
#endif /* defined(__mm__Machine__) */

