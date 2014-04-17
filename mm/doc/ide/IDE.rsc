@license{
  Copyright (c) 2009-2013 CWI / HvA
  All rights reserved. This program and the accompanying materials
  are made available under the terms of the Eclipse Public License v1.0
  which accompanies this distribution, and is available at
  http://www.eclipse.org/legal/epl-v10.html
}
/*****************************************************************************/
/*!
* Micro-Machinations IDE Contributions
* @package      lang::machinations
* @file         Machinations.rsc
* @brief        Defines Machinations IDE Contributions
* @contributor  Riemer van Rozen - rozen@cwi.nl - HvA, CREATE-IT / CWI
* @date         March 31th 2013
* @note         Compiler/Assembler: Rascal MPL.
*/
/*****************************************************************************/
module lang::mm::IDE

import lang::mm::Syntax;
import ParseTree;
import util::IDE;
import vis::Figure;
import IO;
import Message;

public str MM_NAME = "Micro-Machinations"; //language name
public str MM_EXT  = "mm" ;                //file extension

public void mm_register()
{
  Contribution mm_style =
    categories
    (
      (
        "Name" : {foregroundColor(color("royalblue"))},
        "TypeName" : {foregroundColor(color("darkblue")),bold()},
        "UnitName" : {foregroundColor(color("mediumblue")),bold()},
        "Comment": {foregroundColor(color("dimgray"))},
        "Value": {foregroundColor(color("firebrick"))},
        "String": {foregroundColor(color("teal"))}
        //,"MetaKeyword": {foregroundColor(color("blueviolet")), bold()}
      )
    );

  set[Contribution] mm_contributions =
  {
    mm_style
  };

  registerLanguage(MM_NAME, MM_EXT, lang::mm::Syntax::mm_parse);
  registerContributions(MM_NAME, mm_contributions);
}

//--------------------------------------------------------------------------------
//for quick testing purposes
//--------------------------------------------------------------------------------
public void probeer()
{
  loc f = |project://mm_new/test/mod1_fig7_tower1.mm|;
  mm_parse(f);
}