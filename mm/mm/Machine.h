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
  class Machine : public MM::Recycler
  {
  public:
    static const MM::UINT32 LOG_SIZE;

  private:
    MM::Reflector  * reflector;
    MM::Evaluator  * evaluator;
    MM::Definition * type;    //global current types
    MM::String     * log;     //global log of what happened
    MM::Instance   * inst;    //global instance
    
  public:
    Machine();
    ~Machine();
        
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::Reflector * getReflector();
    MM::Evaluator * getEvaluator();
    MM::Definition * getDefinition();
    MM::Instance * getInstance();
    MM::String * getLog();
    
    MM::VOID setDefinition(MM::Definition * def);
    MM::VOID setInstance(MM::Instance * inst);
    
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
    MM::Vector<MM::Transformation *> * createTransformationVector();
    
    MM::Vector<MM::Element *> * createElementVector();

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
  
    MM::Name * createName(MM::CHAR * str,
                          YYLTYPE  * strLoc);
    
    MM::Name * createName(MM::Name * name);
    
    MM::Program * createProgram();
    
    MM::Program * createProgram(MM::Vector<MM::Transformation *> *
                                transformations);

    MM::Modification * createModification();
 
    MM::Modification * createModification(MM::Vector<MM::Element *> *
                                          transformations);
    
    MM::Modification * createModification(MM::Vector<MM::Element *> *
                                          transformations,
                                          YYLTYPE * modifyLoc);

    MM::Transition * createTransition();
    
    MM::Transition * createTransition(MM::Vector<MM::Element *> * elements);
    
    
    MM::Transition * createTransition(MM::Vector<MM::Element *> * elements,
                                      YYLTYPE * stepLoc);
    
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
    
    MM::Node * createGateNode(MM::NodeBehavior::IO    io,
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
    
    MM::Node * createRefNode(MM::NodeBehavior::IO io, MM::Name * name);
    
    MM::InterfaceNode * createInterfaceNode(MM::Name * name,
                                            MM::Declaration * decl,
                                            MM::Node * ref);
    
    MM::StateEdge * createStateEdge(MM::Name * name,
                                    MM::Name * src,
                                    MM::Exp  * exp,
                                    MM::Name * tgt);
    
    MM::FlowEdge * createFlowEdge(MM::Name * name,
                                  MM::Name * src,
                                  MM::Exp  * exp,
                                  MM::Name * tgt);

    MM::Definition * createDefinition();
    
    MM::Definition * createDefinition(MM::Name * name,
                                      MM::Vector<Element*> * elements);
    
    MM::Declaration * createDeclaration(MM::Name * type,
                                        MM::Name * name);
    
    MM::Assertion * createAssertion(YYLTYPE  * assertLoc,
                                    MM::Name * name,
                                    MM::Exp  * exp,
                                    MM::CHAR * msg);

    MM::Assertion * createAssertion(MM::Name * name,
                                    MM::Exp  * exp,
                                    MM::CHAR * msg);
    
    MM::Deletion * createDeletion(MM::Name * name);
    
    MM::Deletion * createDeletion(YYLTYPE * deleteLoc,
                                  MM::Name * name);
    
    MM::Signal * createSignal(MM::Name * name);

    MM::Signal * createSignal(YYLTYPE * signalLoc,
                              MM::Name * name);
                              
    MM::UnExp * createUnExp(MM::Operator::OP  op,
                            YYLTYPE         * opLoc,
                            MM::Exp         * exp);
    
    MM::UnExp * createUnExp(MM::Operator::OP  op,
                            MM::Exp         * exp);
    
    MM::BinExp * createBinExp(MM::Exp          * e1,
                              MM::Operator::OP   op,
                              YYLTYPE          * opLoc,
                              MM::Exp          * e2);

    MM::BinExp * createBinExp(MM::Exp          * e1,
                              MM::Operator::OP   op,
                              MM::Exp          * e2);
    
    MM::OverrideExp * createOverrideExp(YYLTYPE * lparenLoc,
                                        MM::Exp * e,
                                        YYLTYPE * rparenLoc);
    
    MM::OverrideExp * createOverrideExp(MM::Exp * e);
    
    MM::RangeValExp * createRangeValExp(MM::INT32   v1,
                                        YYLTYPE   * v1Loc,
                                        YYLTYPE   * rangeLoc,
                                        MM::INT32   v2,
                                        YYLTYPE   * v2Loc);
    
    MM::RangeValExp * createRangeValExp(MM::INT32 v1, MM::INT32 v2);
    
    MM::NumberValExp * createNumberValExp(MM::INT32  val,
                                          YYLTYPE  * valLoc);
    
    MM::NumberValExp * createNumberValExp(MM::INT32 val);
    
    MM::BooleanValExp * createBooleanValExp(MM::BOOLEAN val,
                                            YYLTYPE * valLoc);
    
    MM::BooleanValExp * createBooleanValExp(MM::BOOLEAN val);
    
    MM::AllExp * createAllExp(YYLTYPE * allLoc);
    
    MM::ActiveExp * createActiveExp(YYLTYPE  * activeLoc,
                                    MM::Name * name);
    
    MM::ActiveExp * createActiveExp(MM::Name * name);
    
    MM::AliasExp * createAliasExp(YYLTYPE * aliasLoc);
    
    MM::AliasExp * createAliasExp();
    
    MM::OneExp * createOneExp(YYLTYPE * epsilonLoc);
    
    MM::OneExp * createOneExp();
    
    MM::VarExp * createVarExp(MM::Name * name);

    MM::Instance * createInstance(MM::Instance * parent,
                                  MM::Definition * def,
                                  MM::Name * name);
  };
}
#endif /* defined(__mm__Machine__) */

