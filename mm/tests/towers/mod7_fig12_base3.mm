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

//7. Modification: Second Base adaptations.
//   Textual Micro-Machinations of Figure 12.

Base //base definition difference
{
  inout ref essence   //change: essence is output
  converter amplify   //add: amplify essence
  converter transmute //add: transmute essence
  
  //Note: if we delete tick we never produce gold again after overheating...
  delete tick         //remove: tick drain

  user source hitByEssence      //change: hit by essence
  tA: hitByEssence .*.> amplify   //add: trigger amplify
  tT: hitByEssence .*.> transmute //add: trigger transmute
  touch:   essence --> amplify  //add: touch essense
  release: amplify -2-> essence //add: amplify times two  
  absorb:  essence   --> transmute  //change: consume essence
  cash:    transmute --> gold       //change: produce cash
  heatUp:  transmute --> heat       //change: produce heat
  
  overheated: heat .(heat >= 100).> amplify
  cooled:     heat .(heat < 100).> transmute
}

modify //evaluating this modification changes the game