//
//  Reflector.h
//  mm
//
//  Created by Riemer van Rozen on 9/29/13.
//  Copyright (c) 2013 Riemer van Rozen. All rights reserved.
//

#ifndef __mm__Reflector__
#define __mm__Reflector__

namespace  MM
{
  class Reflector
  {
  private:
    MM::Machine * m;
  public:
    Reflector(MM::Machine * m);
    ~Reflector();
    
    MM::TID getTypeId();
    MM::BOOLEAN instanceof(MM::TID tid);
    
    MM::Definition * getDefinition();
    MM::Instance * getInstance();
  
    //add an element to a definition
    //performs the necessary initialization
    //the element must have a simple name (nesting is removed)
    MM::VOID addElement(MM::Definition * def, MM::Element * element);
    
    //remove an element from a definition
    //performs the necessary deinitialization
    //the element must have a simple name (nesting is removed)
    MM::VOID removeElement(MM::Definition * def, MM::Element * element);

    
    //transform the current state based on a delta definition
    MM::VOID merge(MM::Modification * modification);
  
    MM::VOID init(MM::Definition * def);
    
  private:
    MM::BOOLEAN navigate(MM::Definition  * root,
                         MM::Element     * element,
                         MM::Definition ** def,
                         MM::Element    ** found);

    //MM::BOOLEAN navigateEdgeName(MM::Definition  * root, //in: type
    //                             MM::Name        * name, //in: name
    //                             MM::Node::IO      direction, //in: direction
    //                             MM::Definition ** ref,
    //                             MM::Node       ** node);
    
    // MM::BOOLEAN navigateEdge(MM::Definition  * root,
    //                         MM::Edge        * edge,
    //                         MM::Definition ** def);
    
    /**************************************************************************
     * Reflect
     * Visitor that merges elements with definitions
     * The elements can have complex names (nesting is present).
     **************************************************************************/
    MM::VOID merge(MM::Definition * def, MM::Definition * def2);
    MM::VOID merge(MM::Definition * def, MM::Element * element);
    MM::VOID merge(MM::Definition * def, MM::Node * node);
    MM::VOID merge(MM::Definition * def, MM::Edge * edge);
    
        
    /**************************************************************************
     * Init
     * Visitor that deinitializes an element inside a definition.
     * The elements must have "simple" names (nesting is removed).
     **************************************************************************/    

    MM::VOID init(MM::Definition * def, MM::Element * element);
    MM::VOID init(MM::Definition * def, MM::Node * node);
    //MM::VOID init(MM::Declaration * decl, MM::InterfaceNode * node);
  public:
    MM::VOID init(MM::Node * node);
  private:
    MM::VOID init(MM::Definition * def, MM::Edge * edge);
    
    //these are private because nodes and edges must be processed
    //in general before they are processed specifically
    MM::VOID init(MM::Definition * def, MM::Node * node, MM::PoolNodeBehavior * behavior);
    MM::VOID init(MM::Definition * def, MM::Node * node, MM::DrainNodeBehavior * behavior);
    MM::VOID init(MM::Definition * def, MM::Node * node, MM::SourceNodeBehavior * behavior);
    MM::VOID init(MM::Definition * def, MM::Node * node, MM::RefNodeBehavior * behavior);
    MM::VOID init(MM::Definition * def, MM::Node * node, MM::GateNodeBehavior * behavior);
    MM::VOID init(MM::Definition * def, MM::Node * node, MM::ConverterNodeBehavior * behavior);
    MM::VOID init(MM::Definition * def, MM::Definition * def2);
    MM::VOID init(MM::Definition * def, MM::Declaration * decl);
    MM::VOID init(MM::Definition * def, MM::FlowEdge * edge);
    MM::VOID init(MM::Definition * def, MM::StateEdge * edge);
    MM::VOID init(MM::Definition * def, MM::Assertion * assert);
    MM::VOID init(MM::Definition * def, MM::Deletion * del);
    
   /**************************************************************************
    * Deinit
    * Visitor that deinitializes an element inside a definition.
    * The elements must have "simple" names (nesting is removed).
    **************************************************************************/    
    MM::VOID deinit(MM::Definition * def);
    MM::VOID deinit(MM::Definition * def, MM::Element * element);
    MM::VOID deinit(MM::Definition * def, MM::Node * node);
    //    MM::VOID deinit(MM::Declaration * decl, MM::InterfaceNode * node);
  public:
    MM::VOID deinit(MM::Definition * def, MM::Edge * edge);
  private:
    MM::VOID deinit(MM::Definition * def, MM::Node * node, MM::PoolNodeBehavior * behavior);
    MM::VOID deinit(MM::Definition * def, MM::Node * node, MM::DrainNodeBehavior * behavior);
    MM::VOID deinit(MM::Definition * def, MM::Node * node, MM::SourceNodeBehavior * behavior);
    MM::VOID deinit(MM::Definition * def, MM::Node * node, MM::RefNodeBehavior * behavior);
    MM::VOID deinit(MM::Definition * def, MM::Definition * def2);
    MM::VOID deinit(MM::Definition * def, MM::Declaration * decl);
    MM::VOID deinit(MM::Definition * def, MM::FlowEdge * edge);
    MM::VOID deinit(MM::Definition * def, MM::StateEdge * edge);
    MM::VOID deinit(MM::Definition * def, MM::Assertion * assert);
    MM::VOID deinit(MM::Definition * def, MM::Deletion * del);
        
    /**************************************************************************
    * Replace
    * Visitor that replaces an element by another element inside a definition.
    * The elements must have "simple" names (nesting is removed).
    **************************************************************************/
    MM::VOID replace(MM::Definition * def,
                     MM::Element * e1,
                     MM::Element * e2);
    
    MM::VOID replace(MM::Definition * def,
                     MM::Node * node,
                     MM::Element * element);

    MM::VOID replace(MM::Definition * def,
                     MM::Node * node,
                     MM::PoolNodeBehavior * behavior,
                     MM::Node * node2);
    
    MM::VOID replace(MM::Definition * def,
                     MM::Node * node,
                     MM::DrainNodeBehavior * behavior,
                     MM::Node * node2);
    
    MM::VOID replace(MM::Definition * def,
                     MM::Node * node,
                     MM::SourceNodeBehavior * behavior,
                     MM::Node * node2);
    
    MM::VOID replace(MM::Definition * def,
                     MM::Node * node,
                     MM::RefNodeBehavior * behavior,
                     MM::Node * node2);
    
    MM::VOID replace(MM::Definition * def,
                     MM::Edge * edge,
                     MM::Element * element);
    
    MM::VOID replace(MM::Definition * def,
                     MM::FlowEdge * edge,
                     MM::Element * element);
    
    MM::VOID replace(MM::Definition * def,
                     MM::StateEdge * edge,
                     MM::Element * element);
    
    MM::VOID replace(MM::Definition * def,
                     MM::Definition * def2,
                     MM::Element * element);
    
    MM::VOID replace(MM::Definition * def,
                     MM::Declaration * decl,
                     MM::Element * element);
    
    MM::VOID replace(MM::Definition * def,
                     MM::Assertion * assert,
                     MM::Element * element);
    
    MM::VOID replace(MM::Definition * def,
                     MM::Deletion * del,
                     MM::Element * element);
    
    MM::VOID replace(MM::Definition * def,
                     MM::Node * node,
                     MM::Node * node2);
  };
}

#endif /* defined(__mm__Reflector__) */
