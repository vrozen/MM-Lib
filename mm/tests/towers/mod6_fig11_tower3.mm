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

//6. Modification: Second Tower adaptations.
//   Textual Micro-Machinations of Figure 11.

Tower
{  
  user drain tick   //add: Game time passing
  drainXP: xp --> tick       //add: time passing drains xp
  gainXP:  killCreep -3-> xp //change: gaining more xp
  
  //decreased the gained essence amount
  gainEssence: killCreep - (5 - xp) -> essence //change
  //more range/power/speed means less essence?
  //towers are at maximum efficiency after two kills
}

modify //evaluating this modification changes the game