/******************************************************************************
 * Copyright (c) 2013-2014, Amsterdam University of Applied Sciences (HvA) and
 *                          Centrum Wiskunde & Informatica (CWI)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contributors:
 *   * Riemer van Rozen - rozen@cwi.nl - HvA / CWI
 ******************************************************************************/
/*!
 * \namespace MM
 * \class     Machine
 * \brief     The Machine abstraction manages the creation of model elements,
 *            such that it can recycle and reuse them.
 * \note      Factory
 * \file      Machine.h
 * \author    Riemer van Rozen
 * \date      July 16th 2013
 */
/******************************************************************************/

#ifndef __mm__Machine__
#define __mm__Machine__

namespace MM
{
  class Machine : public MM::Recycler
  {
  public:
    static const MM::UINT32 LOG_SIZE; /**> log buffer size */

  public:
    class InstanceObserver : MM::Observer
    {
    private:
	  MM::UINT32 caller;
      MM::Instance * instance;
      MM::CALLBACK callback;
    public:
      InstanceObserver(MM::UINT32 caller,
		               MM::Instance * instance,
                       MM::CALLBACK callback) : Observer()
      {
		this->caller = caller;
        this->instance = instance;
        this->callback = callback;
        instance->addObserver(this);
      }
      
      ~InstanceObserver()
      {
        instance->removeObserver(this);
      }
      
      MM::TID getTypeId()
      {
        return MM::T_InstanceObserver;
      }
      
      MM::BOOLEAN instanceof(MM::TID tid)
      {
        if(tid == MM::T_InstanceObserver)
        {
          return MM_TRUE;
        }
        else
        {
          return MM::Observer::instanceof(tid);
        }
      }
      
      MM::VOID update(MM::Observable * observable, //observable object
                      MM::VOID * aux,              //auxiliary context
                      MM::UINT32 message,          //message
                      MM::VOID * object)           //subject object
      {
        this->callback(caller,                 //who are you going to call?
			           message,                //message: what happened?
                      (MM::UINT32) observable, //instance or definition to which something happened
                      (MM::UINT32) object,     //element that caused the change: e.g. pool
                      (MM::UINT32) aux);       //additional info: e.g. value or definition
      }
    };
    
    
  private:
    MM::Reflector  * reflector; /**> reflector for adapting definitions */
    MM::Evaluator  * evaluator; /**> evaluator for mutating instances */
    MM::Definition * type;      /**> global scope type definition */
    MM::String     * log;       /**> log of what happened */
    MM::Instance   * inst;      /**> global scope instance */

public:
    class Delegate : MM::Observer
    {
    private:
	  MM::UINT32 caller;
      MM::Observable * observable;
      MM::CALLBACK callback;
    public:
      Delegate(MM::Observable * observable,
          MM::UINT32 caller,     
		  MM::CALLBACK callback) : Observer()
      {
		this->caller = caller;
        this->observable = observable;
        this->callback = callback;
        observable->addObserver(this);
      }
      
      ~Delegate()
      {
        observable->removeObserver(this);
      }
      
      MM::TID getTypeId()
      {
        return MM::T_Delegate;
      }
      
      MM::BOOLEAN instanceof(MM::TID tid)
      {
        if(tid == MM::T_Delegate)
        {
          return MM_TRUE;
        }
        else
        {
          return MM::Observer::instanceof(tid);
        }
      }
      
      MM::VOID update(MM::Observable * observable, //observable object
                      MM::VOID * aux,              //auxiliary context
                      MM::UINT32 message,          //message
                      MM::VOID * object)           //subject object
      {		
		//return a cast pointer to the start of the most specific struct  
		MM::UINT32 obs = 0;
        if(observable->instanceof(MM::T_Definition) == MM_TRUE)
		{
		   MM::Definition * def = (MM::Definition *) observable;
		   obs = (MM::UINT32) def;
		}
		else if(observable->instanceof(MM::T_Instance) == MM_TRUE)
		{
	       MM::Instance * instance = (MM::Instance *) observable;
		   obs = (MM::UINT32) instance;
		}
		else
		{
		   obs = (MM::UINT32) observable;
		}

        this->callback(caller,                 //who to call back
			           message,                //message
                      (MM::UINT32) obs,        //instance
                      (MM::UINT32) object,     //element
                      (MM::UINT32) aux);       //value
      }
    };


    MM::Vector<MM::Machine::Delegate *> * delegates;

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
    
    //--------------------------------------------------------------------------
    //external API
    //--------------------------------------------------------------------------
    //evaluates input and adds elements to the model
	MM::VOID eval (const MM::CHAR * input);
	MM::VOID evalFile (const MM::CHAR * file);
	MM::VOID reflect (MM::Program * program);

    //takes a step in an MM model
	MM::VOID step ();
    MM::VOID step (MM::CHAR * buf, MM::UINT32 size);
    MM::VOID step (MM::UINT32 instance, MM::CHAR * buf, MM::UINT32 size);
    
    //resets all instances to definition start values
    MM::VOID reset ();
    MM::VOID reset (MM::UINT32 instance);

    //activates an interactive node in an instance
    MM::VOID activate (MM::UINT32 node,
                       MM::UINT32 instance);
    
    //retrieves a definition from a parent element by name    
    MM::UINT32 getInstance(MM::UINT32 instance, //0 -> global scope
                           MM::CHAR  * name);
    
    MM::VOID getName (MM::UINT32   element,
                      MM::CHAR *   buffer,
                      MM::UINT32   bufferSize);
    
	MM::VOID MM::Machine::getInstanceName(MM::UINT32 instance,
                                          MM::CHAR * buffer,
                                          MM::UINT32 bufferSize);
    
    //retrieves a definition from a parent element by name
    //MM::UINT32 getDefinition(MM::UINT32   def,  //0 -> global scope type
    //                         MM::CHAR   * name);
    
    //adds an observer to the model
    //the caller receives a callback
    //MM::UINT32 addObserver(MM::UINT32 definition,
    //                       MM::VOID * caller,
    //                       MM::CALLBACK callback);
   
    /*MM::UINT32 addObserver(MM::UINT32 instance,
                           MM::UINT32 caller,
                           MM::CALLBACK callback);*/

	MM::UINT32 addInstanceObserver(MM::UINT32 instance,  MM::UINT32 caller, MM::CALLBACK callback);

    MM::UINT32 addDefinitionObserver(MM::UINT32 definition,  MM::UINT32 caller,  MM::CALLBACK callback);


    //removes an observer from a pools
    MM::VOID removeObserver (MM::UINT32 observer);
        
    //--------------------------------------------------------------------------
    // Create
    //--------------------------------------------------------------------------
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
    
    MM::Name * createName(MM::CHAR * buf);
    
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
    
    MM::FlowEvent * createFlowEvent(MM::Instance * actInstance,
                                    MM::Node     * actNode,
                                    MM::Edge     * actEdge,
                                    MM::Instance * srcInstance,
                                    MM::Node     * srcNode,
                                    MM::UINT32     amount,
                                    MM::Instance * tgtInstance,
                                    MM::Node     * tgtNode);

    MM::TriggerEvent * createTriggerEvent(MM::Instance * instance,
                                          MM::Edge     * edge);

    MM::TriggerEvent * createTriggerEvent(YYLTYPE * failLoc,
                                          MM::Name * name);

    MM::Prevention * createPrevention(MM::Instance * instance,
                                      MM::Edge     * edge);

    MM::Prevention * createPrevention(YYLTYPE * preventLoc,
                                      MM::Name * name);
	
	MM::Failure * createFailure(MM::Instance * instance,
                                MM::Node     * node);

    MM::Failure * createFailure(YYLTYPE * failLoc,
                                MM::Name * name);

    MM::Activation * createActivation(MM::Instance * instance,
                                      MM::Node     * node);

    MM::Activation * createActivation(YYLTYPE * activateLoc,
                                      MM::Name * name);

	MM::Enablement * createEnablement(MM::Instance * instance,
                                      MM::Node     * node);

    MM::Enablement * createEnablement(YYLTYPE * disableLoc,
                                      MM::Name * name);

	MM::Disablement * createDisablement(MM::Instance * instance,
                                        MM::Node     * node);

    MM::Disablement * createDisablement(YYLTYPE * disableLoc,
                                        MM::Name * name);

	MM::Violation * createViolation(MM::Instance * instance,
                                    MM::Assertion * assertion);

    MM::Violation * createViolation(YYLTYPE * deleteLoc,
                                    MM::Name * name);

	MM::Node * createSourceNode(MM::NodeBehavior::IO    io,
                                MM::NodeBehavior::When  when,
                                MM::Name      * name);
    
    MM::Node * createDrainNode(MM::NodeBehavior::IO    io,
                               MM::NodeBehavior::When  when,
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
                              MM::Name      * of,
                              MM::UINT32      at,
                              MM::UINT32      max,
                              MM::Exp       * exp);
    
    MM::Node * createConverterNode(MM::NodeBehavior::IO    io,
                                   MM::NodeBehavior::When  when,
                                   MM::Name      * name,
                                   MM::Name      * from,
                                   MM::Name      * to);
                                  
    MM::Node * createRefNode(MM::NodeBehavior::IO io, MM::Name * name);
    
    MM::InterfaceNode * createInterfaceNode(MM::Name    * name,
                                            MM::Element * parent,
                                            MM::Node    * ref);
    
    MM::StateEdge * createStateEdge(MM::Name * name,
                                    MM::Name * src,
                                    MM::Exp  * exp,
                                    MM::Name * tgt);
    
    MM::StateEdge * createAnonymousTriggerEdge(MM::Node * src,
                                               MM::Node * tgt);
    
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
                                  MM::Element * decl);
  };
}
#endif /* defined(__mm__Machine__) */

