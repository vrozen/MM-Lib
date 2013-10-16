MM-Lib
======

Micro-Machinations Library

Status:
* Parser: flex/bison working
  * Identifiers are lexicals that are post-processed
  * Grammar has zero conflicts
* Machine: tracks objects it owns
* Reflector: transforms types

Next steps:
* Evaluator: transforms data
* Instance: observes definitions
* InterfaceNodes
* Merge Micro-Machinations and Micro-Machination Trace Languages
  * Refactor Events into Elements
* Renaming for clarity
  * Definition --> TypeDef
  * Delete --> Deletion
  * Assert --> Assertion
  * Reflector --> ... aptly named visitors ...
* External API also through observers
