#include "defs.h"

/*
  Function: initFighter
  Purpose:  dynamically allocates the memory for a new fighter as a FighterType structure,
            initializes its fields with the given parameters, and returns the new fighter 
            using an output parameter
       in:  the strength
       in:  the armour
       in:  the health
   in-out:  the initialized fighter
   return:  nothing
*/
void initFighter(int strength, int armour, int health, FighterType **fighter)
{
    *fighter = malloc(sizeof(FighterType));

    (*fighter)->strength = strength;
    (*fighter)->armour = armour;
    (*fighter)->health = health;
}

/*
  Function: initPirate
  Purpose:  dynamically allocates the memory for a new pirate as a FighterType structure
            using a helper function
       in:  the pirate
   return:  nothing
*/
void initPirate(FighterType **pirate)
{
    int strength = randm(5) + 5;
    int armour = randm(4) + 1;
    initFighter(strength, armour, PIRATE_HEALTH, pirate);
}

/*
  Function: initPirates
  Purpose:  creates and initializes a crew of 10 pirates with randomized 
            properties, and adds each pirate to a given deque
   in-out:  the given deque initialized with pirates
   return:  nothing
*/
void initPirates(DequeType *deque)
{
    FighterType *pirate;

    for (int i = 0; i < 10; ++i)
    {
        initPirate(&pirate);
        addFighter(deque, pirate);
    }
}

/*
  Function: printFighter
  Purpose:  prints to the screen all the fields of a given fighter
       in:  the fighter
   return:  nothing
*/
void printFighter(FighterType *fighter)
{
    printf("FIGHTER\nStrength: %d\nArmour: %d\nHealth: %d\n\n", fighter->strength, fighter->armour, fighter->health);
}