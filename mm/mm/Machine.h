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
  class Definition;
  
  class Machine : public MM::Recycler
  {
  private:
    //MM::Definition * def;
    //MM::Map<Name *, Definition *> * types;
    //MM::Vector<Instance *> * instances;
    MM::Reflector * reflector;
    
  public:
    Machine();
    ~Machine();
        
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::Reflector * getReflector();
    
    MM::VOID setDefinition(MM::Definition * def);
    MM::Definition * getDefinition();
    
    //evaluates input and adds elements to the model
    MM::VOID eval (const MM::CHAR * input);
    
    /*
    //takes a step in an MM model
    MM::Transition * step       ();
    
    //retrieves a definition from a parent element by name
    MM::UINT32 get              (MM::UINT32   def,  //0 -> global scope
                                 MM::CHAR   * name);
    
    MM::VOID   getName          (MM::UINT32   node,
                                 MM::CHAR *   buffer,
                                 MM::UINT32   bufferSize);
    
    //activates an interactive node in an instance
    MM::VOID   activate         (MM::UINT32   node,
                                 MM::UINT32   instance);
    
    //removes an element from a type definition
    MM::VOID   destroy          (MM::UINT32   def,   //0 -> global scope
                                 MM::UINT32   node); //0 -> global scope
    
    //resets all instances to definition start values
    MM::VOID   reset            ();
    
    
    //adds an observer to the model
    //the caller receives a callback
    MM::UINT32 addObserver(MM::UINT32 definition,
                           MM::VOID * caller,
                           MM::CALLBACK callback);
    
    //removes an observer from a pools
    MM::VOID   removeObserver   (MM::UINT32 observer);
    */
    
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
    
    
    //MM::Definition * getDefinition(MM::Name * name);
    
    //MM::VOID putDefinition(MM::Name * name, MM::Definition * def);
    
    //------------------------------------------------------------
    // Create
    //------------------------------------------------------------
    MM::Vector<MM::Element *> * createElementVector();
    //MM::Vector<MM::Element *> * createElementVector(MM::Vector<MM::Element*> * elements,
    //                                                MM::Element * element);
    MM::Vector<MM::Node *> * createNodeVector();
    
    MM::Vector<MM::Edge *> * createEdgeVector();
    
    MM::Map<MM::Name *, MM::Element *, MM::Name::Compare> * createName2ElementMap();
    
    MM::Map<MM::Name *, MM::Node *, MM::Name::Compare> * createName2NodeMap();
    
    MM::String * createString(MM::UINT32 size);
    
    MM::Location * createLocation(YYLTYPE * loc);
    
    MM::Name * createName(MM::Name * n1,
                          MM::CHAR * str,
                          YYLTYPE  * strLoc);
    
    MM::Name * createName(MM::CHAR   * str,
                          MM::UINT32 * len,
                          MM::UINT32 * start,
                          MM::UINT32 * end);
    
    MM::VOID eatWhiteSpace(MM::CHAR   * str,
                           MM::UINT32 * start,
                           MM::UINT32 * end);
  
    MM::Name * createName(MM::CHAR * str, YYLTYPE  * strLoc);
        
    MM::Node * createSourceNode(MM::NodeBehavior::IO    io,
                                MM::NodeBehavior::When  when,
                                MM::NodeBehavior::Act   act,
                                MM::NodeBehavior::How   how,
                                MM::Name      * name);
    
    MM::Node * createDrainNode(MM::NodeBehavior::IO    io,
                               MM::NodeBehavior::When  when,
                               MM::NodeBehavior::Act   act,
                               MM::NodeBehavior::How   how,
                               MM::Name      * name);
    
    MM::Node * createPoolNode(MM::NodeBehavior::IO    io,
                              MM::NodeBehavior::When  when,
                              MM::NodeBehavior::Act   act,
                              MM::NodeBehavior::How   how,
                              MM::Name      * name,
                              MM::UINT32      at,
                              MM::UINT32      max,
                              MM::Exp       * exp);
    
    MM::Node * createRefNode(MM::Name * name);
    
    MM::StateEdge * createStateEdge(MM::Name * name,
                                    MM::Name * src,
                                    MM::Exp  * exp,
                                    MM::Name * tgt);
    
    MM::FlowEdge * createFlowEdge(MM::Name * name,
                                  MM::Name * src,
                                  MM::Exp  * exp,
                                  MM::Name * tgt);

    MM::Definition * createDefinition(MM::Name * name,
                                      MM::Vector<Element*> * elements);
    
    MM::Declaration * createDeclaration(MM::Name * type,
                                        MM::Name * name);
    
    MM::Assert * createAssert(MM::Name * name,
                              MM::Exp  * exp,
                              MM::CHAR * msg,
                              YYLTYPE  * msgLoc);

    MM::Delete * createDelete(MM::Name * name);
    
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
    MM::VOID recycle(MM::Location * loc);
    
    MM::VOID recycle(MM::Name * name);
    
    MM::VOID recycle(MM::SourceNodeBehavior * node);
    
    MM::VOID recycle(MM::DrainNodeBehavior * node);
    
    MM::VOID recycle(MM::PoolNodeBehavior * node);
    
    MM::VOID recycle(MM::RefNodeBehavior * node);
    
    MM::VOID recycle(MM::StateEdge * edge);
    
    MM::VOID recycle(MM::FlowEdge * edge);
    
    MM::VOID recycle(MM::Definition * def);
    
    MM::VOID recycle(MM::Declaration * decl);
    
    MM::VOID recycle(MM::Assert * assert);
    
    MM::VOID recycle(MM::UnExp * exp);
    
    MM::VOID recycle(MM::BinExp * exp);
    
    MM::VOID recycle(MM::OverrideExp * exp);
    
    MM::VOID recycle(MM::RangeValExp * exp);
    
    MM::VOID recycle(MM::NumberValExp * exp);
    
    MM::VOID recycle(MM::BooleanValExp * exp);
    
    MM::VOID recycle(MM::AllExp * exp);
    
    MM::VOID recycle(MM::ActiveExp * exp);
    
    MM::VOID recycle(MM::AliasExp * exp);
    
    MM::VOID recycle(MM::OneExp * exp);
    
    MM::VOID recycle(MM::VarExp * exp);    
    
  };
}
#endif /* defined(__mm__Machine__) */

