# Micro-Machinations Library (MM-Lib)

## Introduction

The Micro-Machinations (MM) library enables game designers to modify economic game mechanics while a game is running.
More information will be provided here as it becomes available.

| Directory | Platform  | Description |
| --------- | --------- | ----------- |
| [mm/mm](https://github.com/vrozen/MM-Lib/tree/master/mm/mm)       | C++ | The MM library currently requires [STL](http://en.wikipedia.org/wiki/Standard_Template_Library), [Flex](http://flex.sourceforge.net) and [Bison](http://www.gnu.org/software/bison/). |
| [mm/LibMM](https://github.com/vrozen/MM-Lib/tree/master/mm/LibMM) | C++ .NET | Wraps the MM library for usage with Microsoft .NET |
| [mm/doc](https://github.com/vrozen/MM-Lib/tree/master/mm/doc)     |  | Contains an early reference manual and a game prototype |
| [mm/tests](https://github.com/vrozen/MM-Lib/tree/master/mm/tests) | MM | Contains textual Micro-Machinations examples |

### Playing with MM
![AdapTower](https://github.com/vrozen/MM-Lib/raw/master/mm/doc/AdapTower.png)

AdapTower is an academic game prototype that embeds the MM Libary which was created with the Foundations of Digital Games (FDG) paper *"Adapting Game Mechanics with Micro-Machinations"* by Riemer van Rozen and Joris Dormans ([PDF](https://github.com/vrozen/MM-Lib/raw/master/mm/doc/fdg2014_paper_34.pdf)). The paper describes a series of modifications to the game's mechanics using visual MM. Here we provide the game and the equivalent [textual MM](https://github.com/vrozen/MM-Lib/tree/master/mm/tests/towers) it interprets. The game and its mods were demoed live at FDG. You can download the game and try it out for yourself.

**Installing AdapTower.**
AdapTower runs on Windows and requires the .NET and XNA frameworks.

| Download      | Description |
| ------------- | ----------- | 
| [AdapTower.zip](https://github.com/vrozen/MM-Lib/raw/master/mm/doc/AdapTower.zip) | Contains AdapTower binaries, DLLs and MM models.|
| [Microsoft .NET Framework 4.5](http://www.microsoft.com/en-us/download/details.aspx?id=30653) | AdapTower runs on the Microsoft .NET Framework.|
| [Microsoft XNA Framework Redistributable 4.0](http://www.microsoft.com/en-us/download/details.aspx?id=27598) | AdapTower is built using the XNA Framework.|

**Running AdapTower.**
When running the game, a right click creates a tower and a left click creates a base. Hit ESC for viewing the MM state, and click the next button to evaluate the next modification. Click on a tower or base to view its MM values. Edit files for making your own modifications.

**Kudos:** AdapTower is based on [Phantom](https://github.com/ludomotion/phantom), an Entity Component based Game Engine for XNA 4.0 developed at Dutch game business [Ludomotion](http://ludomotion.com).

**Note:** We plan to make the sources of AdapTower available here.

### Modeling MM
For modeling MM knowledge about the language is required. We provide links to selected publications about the Machinations language. Machinations were originally only intended for game design [1] and have evolved into Micro-Machinations [3,4] which are also intended for software development. Please note that the Flash based Machinations tool [2] relates to the prior work. Since we currently lack a graphical MM editor, writing MM on a whiteboard and then translating manually to textual MM is advised. For now, we provide a [grammar of MM](https://github.com/vrozen/MM-Lib/tree/master/mm/doc/ide) which provides syntax highlighting in [Rascal](http://www.rascal-mpl.org), a meta-programming language and language workbench based on Eclipse. A more comprehensive IDE called Micro-Machinations Analysis in Rascal (MM AiR) will become available later.

Below is the Machinations logo, the textual MM that encode the diagram and a table showing resource amounts in pool *p* and flow *f* progressing over time steps.

<img src="https://github.com/vrozen/MM-Lib/raw/master/mm/doc/machinations_logo.png" width="140px"/>

![IDE](https://github.com/vrozen/MM-Lib/raw/master/mm/doc/MM_IDE.png)

| state | pool *p* amount | flow *f* amount |
| -----:| ---------------:| ---------------:|
|     0 |               7 |               7 |
|     1 |              14 |              14 |
|     2 |              28 |              28 |
|     3 |              56 |              56 |
|     4 |             112 |             112 |
Table showing logo diagram resource amounts progressing over time.

### Building MM

The MM library has been built on MacOS and Windows.

**MacOS**
* For MacOS we provide the XCode project *mm.xcodeproj*.
* Flex and Bison are part of XCode, the scanner and the parser are regenerated automatically.

**Windows**
* For Windows we provide the Visual Studio 2010 *LibMM* wrapper project.
* Flex and Bison are not required, precompiled sources of the scanner and parser are included.

### Using MM

The MM Library is provided under the 3-clause BSD license.

**Warning:** Please note that the MM Library is an academic prototype, and as such has not undergone rigorous industrial testing. Using the library comes at your own risk.

#### License

```
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
```

#### API Documentation
An early reference manual generated by Doxygen is provided here ([PDF](https://github.com/vrozen/MM-Lib/raw/master/mm/doc/MM_Doxygen_Refman.pdf)).

**Note:** The API is still being improved and a How-To document is not yet available.

## Changelog

### April 16th 2014 (v0.10):
Status:
* Made MM available under 3-clause BSD license.

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

### Februari 14th 2014 (v0.01):
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

