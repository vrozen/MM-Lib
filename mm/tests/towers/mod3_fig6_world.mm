//******************************************************************************
// AdapTower is a game created for the publication: "Adapting Game Mechanics
// with Micro-Machinations" by Riemer van Rozen and Joris Dormans,
// which appears in the proceedings of Foundations of Digital Games (FDG) 2014.
//
// These game modifications demonstrate the adaptability of
// game mechanics and gameplay using Micro-Machinations.
//
// Contributors:
//   * Riemer van Rozen - rozen@cwi.nl - HvA / CWI
//******************************************************************************

//3. Modification: First world definition.
//   Textual Micro-Machinations of Figure 6.

user source spawn        //Physics activates spawn source
pool creeps              //creeps in the world
create: spawn --> creeps //spawn creates one creep per step

pool essence             //essence in the world
user drain missed        //Physics activates missed essence
miss: essence --> missed //drain one essence per miss

pool gold at 120         //player gold starts at 120
pool towers of Tower     //number of towers in the world
pool bases of Base       //number of bases in the world
user converter buyTower  //user activates buyTower
user converter buyBase   //user activates buyBase
gold -20-> buyTower      //A tower costs 20 gold
gold -50-> buyBase       //A base costs 50 gold

buyTower --> towers
buyBase --> bases

assert lose : gold < 50 && bases == 0 "you lose"
assert win  : bases >= 20             "you win"

towerEssence: essence .=.> towers.essence
towerCreeps:  creeps  .=.> towers.creeps

baseEssence: essence .=.> bases.essence
baseCreeps:  creeps  .=.> bases.creeps
baseGold:    gold    .=.> bases.gold

modify //evaluating this modification changes the game