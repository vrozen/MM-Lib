/******************************************************************************
 * Tribbles.
 ******************************************************************************
 * http://en.wikipedia.org/wiki/Tribble
 * "Tribbles are fictional animals in the Star Trek universe who first appeared
 *  in the episode titled "The Trouble With Tribbles".
 *  They are depicted as small, furry, soft, gentle, and slow-moving,
 *  and they usually produce a soothing purring or cooing sound when stroked,
 *  all of which are endearing traits to humans and Vulcans.
 *  However, because tribbles reproduce enormously fast,
 *  and consume exponentially larger and larger amounts of food as they multiply
 *  and crawl stealthily from one place to another, Starfleet considers them
 *  dangerous organisms and forbids their transportation."
 ******************************************************************************/

Tribble
{
  in ref food
  out ref tribbles

  pool hunger at 1
  auto converter eat
  
  consume:  food -hunger-> eat
  appetite: eat -hunger-> hunger
  produce:  eat --> tribbles
}

source food
pool tribbles of Tribble at 1

tribbleFood:     food     .=.> tribbles.food
tribbleTribbles: tribbles .=.> tribbles.tribbles

modify

/******************************************************************************
 * Now suppose we want to track how much food the tribbles have eaten.
 ******************************************************************************/
Tribble
{
  out ref consumed
  eaten: eat -hunger-> consumed
}

pool consumed

count: consumed .=.> tribbles.consumed

modify

/******************************************************************************
 * Starfleet has sent 10 Vulcan sehlats to eat the tribbles
 ******************************************************************************/
Sehlat
{
  in ref tribbles
  auto drain devour
  consume: tribbles --> devour
}

pool sehlats of Sehlat at 10
shelatTribbles: tribbles .=.> sehlats.tribbles

modify
