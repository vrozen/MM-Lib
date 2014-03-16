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

//5. Modification: First Base adaptations.
//   Textual Micro-Machinations of Figure 10.

Base //base definition difference
{
  auto drain destroyBase   //bases can be destroyed
  pool heat                //bases heat up
  user drain tick //Game notifies time passing
  pool HP at 5             //FIXME = new?!
  //bases are weakened when they have zero health
  weakened:  HP . HP == 0 .> destroyBase //add
  heatUp:    hitByEssence --> heat //heat up
  coolDown:  heat --> tick         //time cools bases
  //this changes the way bases are destroyed
  destroy:   self --> destroyBase  //change: edge source
  //changes the way gold is generated
  //is the expression correct?
  cash: hitByEssence -(3-heat)-> gold //change exp
}

modify //evaluating this modification changes the game