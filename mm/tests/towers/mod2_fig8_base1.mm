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

//2. Modification: First Base definition.
//   Textual Micro-Machinations of Figure 8.

Base  //base definition
{
  pool self at 1 //self represents this instance
  in ref creeps  //input reference: creeps in the world
  in ref essence //input reference: essence in the world
  out ref gold   //output reference: gold the player has
  
  user converter hitByCreep   //Physics creep collision
  user converter hitByEssence //Physics essence collision
  
  die:     creeps --> hitByCreep //when a creep collides
  destroy: self --> hitByCreep   //this base is destroyed
  
  absorb:  essence --> hitByEssence //when essence hits
  cash:    hitByEssence --> gold    //gold is generated
}

modify //evaluating this modification changes the game