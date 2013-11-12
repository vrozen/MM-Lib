MM-Lib
======

Micro-Machinations Library

Status:
* Evaluator: pool, flow edge and condition are working
* Reflector: working, transforms types
* Instances: observes definitions
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
  * source, drain, gate, triggers
* InterfaceNodes: perform binding
* Machine: manage all instances
  * maps and vectors 
* Renaming for clarity: low priority
  * Definition --> ... TypeDef ...
  * Reflector --> ... aptly named visitors ...
* External API using observers
