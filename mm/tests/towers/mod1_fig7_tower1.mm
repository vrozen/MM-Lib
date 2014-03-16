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

//1. Modification: First Tower definition.
//   Textual Micro-Machinations of Figure 7.

Tower //tower definition
{
  pool self at 1   //self represents this instance
  in ref creeps    //input reference: creeps in the world
  out ref essence  //output reference: essence in the world
  
  //note:  specify physics units of measurements here
  pool range at 150        //tower range is 150
  pool firePower at 50     //tower fire power is 50
  pool rotationSpeed at 20 //tower rotation speed is 20
  
  user converter hitByCreep //Physics creep collision
  user converter killCreep  //Physics creep kill
  
  collapse: self --> hitByCreep //collapsing this tower
  burry: creeps --> hitByCreep  //burries a creep
  
  die: creeps --> killCreep           //killing a kreep
  gainEssence: killCreep -5-> essence //generates 5 essence
}

modify //evaluating this modification changes the game