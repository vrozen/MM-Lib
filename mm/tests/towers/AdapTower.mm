//1: first Tower definition

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
  auto /*user*/ converter killCreep  //Physics creep kill
  
  collapse: self --> hitByCreep //collapsing this tower
  burry: creeps --> hitByCreep  //burries a creep
  
  die: creeps --> killCreep           //killing a kreep
  gainEssence: killCreep -5-> essence //generates 5 essence
}

//modify

//2. first Base definition
Base  //base definition
{
  pool self at 1 //self represents this instance
  in ref creeps  //input reference: creeps in the world
  in ref essence //input reference: essence in the world
  out ref gold   //output reference: gold the player has
  
  user converter hitByCreep   //Physics creep collision
  auto /*user*/ converter hitByEssence //Physics essence collision
  
  die:     creeps --> hitByCreep //when a creep collides
  destroy: self --> hitByCreep   //this base is destroyed
  
  absorb:  essence --> hitByEssence //when essence hits
  cash:    hitByEssence --> gold    //gold is generated
}

modify

//3. first world definition

auto /*user*/ source spawn        //Physics activates spawn source
pool creeps              //creeps in the world
create: spawn --> creeps //spawn creates one creep per step

pool essence             //essence in the world
user drain missed        //Physics activates missed essence
miss: essence --> missed //drain one essence per miss

pool gold at 70         //player gold starts at 120
pool towers of Tower     //number of towers in the world
pool bases of Base       //number of bases in the world
auto /*user*/ converter buyTower  //User activates buyTower
auto /*user*/ converter buyBase   //User activates buyBase
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

modify

//4. first Tower adaptation

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

modify

//5. first Base adaptation

Base //base definition difference
{
  auto drain destroyBase   //bases can be destroyed
  pool heat                //bases heat up
  auto /*user*/ drain tick //Game notifies time passing
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

modify

//6. second Tower adaptation

Tower
{  
  auto /*user*/ drain tick   //add: Game time passing
  drainXP: xp --> tick       //add: time passing drains xp
  gainXP:  killCreep -3-> xp //change: gaining more xp
  
  //decreased the gained essence amount
  gainEssence: killCreep - (5 - xp) -> essence //change
  //more range/power/speed means less essence?
  //towers are at maximum efficiency after two kills
}

modify

//7. second Base adaptation

Base //base definition difference
{
  inout ref essence   //change: essence is output
  converter amplify   //add: amplify essence
  converter transmute //add: transmute essence
  
  //Note: if we delete tick we never produce gold again after overheating...
  delete tick         //remove: tick drain

  auto /*user*/ source hitByEssence      //change: hit by essence
  tA: hitByEssence .*.> amplify   //add: trigger amplify
  tT: hitByEssence .*.> transmute //add: trigger transmute
  touch:   essence --> amplify  //add: touch essense
  release: amplify -2-> essence //add: amplify times two  
  absorb:  essence   --> transmute  //change: consume essence
  cash:    transmute --> gold       //change: produce cash
  
  overheated: heat .(heat >= 10).> amplify
  cooled:     heat .(heat < 10).> transmute
}

modify

//8. third Tower adaptation

Tower
{
  pool range at 150        //change: remove xp bonus
  pool firePower at 50     //change: remove xp bonus
  pool rotationSpeed at 20 //change: remove xp bonus  
  pool soulReaping         //add soul reaping efficiency

  delete tick

  //adding user upgrades: choices to spend xp
  auto /*user*/ converter upgradeRange   //add upgrade tower range
  auto /*user*/ converter upgradePower   //add upgrade tower power
  auto /*user*/ converter upgradeSpeed   //add upgrade rotation speed
  auto /*user*/ converter upgradeReaping //add upgrade soul reaping

  //upgrading range is increasingly expensive
  buyRange: xp -(10+range/50)-> upgradeRange
  getRange: upgradeRange -50-> range
  //upgrading power is increasinly expensive
  buyPower: xp -(10+firePower/10)-> upgradePower
  getPower: upgradePower -10-> firePower
  //upgrading speped is increasingly expensive
  buySpeed: xp -(10+rotationSpeed/10) -> upgradeSpeed
  getSpeed: upgradeSpeed -10-> rotationSpeed
  //upgrading soul reaping scales linearly
  buyReaping: xp -2-> upgradeReaping
  getReaping: upgradeReaping --> soulReaping
  
  //nice this same edge is modified twice
  //gaining essence increases with soulReaping efficiency
  gainEssence: killCreep -(5+soulReaping)-> essence
}

modify


