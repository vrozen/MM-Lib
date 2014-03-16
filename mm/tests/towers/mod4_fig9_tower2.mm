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

//4. Modification: First Tower adaptation.
//   Textual Micro-Machinations of Figure 9.

Tower //tower definition diff
{
  pool xp                  //towers have experience
  gainXP: killCreep --> xp //gained by killing creeps
  
  //I don't get the +25/5 notation
  //what does it mean? not 5 right?
  pool range at 150 add (5 * xp)        //add xp bonus
  pool firePower at 50 add (2 * xp)     //add xp bonus
  pool rotationSpeed at 20 add (2 * xp) //add xp bonus
}

modify //evaluating this modification changes the game