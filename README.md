MM-Lib
======

Micro-Machinations Library

Status:
* Parser / Grammar: flex/bison working
  * Includes type transformations using "modify" keyword
  * Includes data transformations using "step" keyword
  * Identifiers are lexicals that are post-processed
  * Grammar has zero conflicts
* Machine: tracks objects it owns
  * TODO: maps and vectors 
* Reflector: transforms types

Next steps:
* Evaluator: transform data / do transitions
* Instance: observe definitions
* InterfaceNodes: perform binding
* Renaming for clarity
  * Definition --> ... TypeDef ...
  * Reflector --> ... aptly named visitors ...
* External API using observers
