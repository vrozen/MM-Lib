MM-Lib
======

Micro-Machinations Library

The MM lib enables game designers to modify economic game mechanics while a game is running.
More information will be provided as it becomes available.
Please note that MM is available under 3-clause BSD license,
but that MM is not yet mature and using it comes at your own risk.

---
April 14th 2014 (v0.10):
---
Status:
* Made MM available under 3-clause BSD license.
* Successfully applied MM in the AdapTower game prototype and demonstrated live mods at the Foundations of Digital Games (FDG) conference.

Next steps:
* Testing
  * regression test setup
  * reuse examples used to test MM-AiR
* Evaluator: add features
  * gate
* Machine: manage all instances
  * maps and vectors
* Simplify external API as done with AdapTower C# wrapper.
* Documentation
  * DoxyGen
  * Architecture, design decisions

---
Februari 14th 2014 (v0.01):
---
Status:
* Evaluator
  * Pool, Source, Drain, Flow edge, Trigger and Condition are working
  * Converters: seem to be working.
  * RefNodes and Aliases: seem to be working.
* Instance Pools
  * new feature that allows pools of objects (they do not flow between pools)
* Reflector: working, transforms types
  * add and replace work okay
  * update is still tricky
* Instances: observes definitions
* Declarations: observe definitions create InterfaceNodes, edges are resolved to these nodes
* Machine: tracks objects it owns
* Parser / Grammar: flex/bison working
  * Includes type transformations using "modify" keyword
  * Includes data transformations using "step" keyword
  * Identifiers are lexicals that are post-processed
  * Grammar has zero conflicts

