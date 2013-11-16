MM-Lib
======

Micro-Machinations Library

Status:
* Evaluator
  * Pool, Source, Drain, Flow edge, Trigger and Condition are working up to aliasing inside instances
  * RefNode: resolves aliases via alias edges
  * InterfaceNode: refers to nodes inside child instances
* Reflector: working, transforms types
* Instances: observes definitions
* Declarations: observe definitions create InterfaceNodes, edges are resolved to these nodes
* Machine: tracks objects it owns
* Parser / Grammar: flex/bison working
  * Includes type transformations using "modify" keyword
  * Includes data transformations using "step" keyword
  * Identifiers are lexicals that are post-processed
  * Grammar has zero conflicts

Next steps:
* Testing
  * regression test setup
  * reuse examples used to test MM-AiR
* Evaluator: add features
  * gate
  * aliases
    * edges on InterfaceNode require nodes inside instances to be aware of their environment!
* InterfaceNodes: perform binding
* Machine: manage all instances
  * maps and vectors 
* Renaming for clarity: low priority
  * Definition --> ... TypeDef ...
  * Reflector --> ... aptly named visitors ...
* External API using observers
