#include "defs.h"

int main(int argc, char *argv[])
{
  // set random seed based on time to ensure different results each run
  srand( (unsigned)time( NULL ) );

  // determine number of runs
  int runQuantity = NUM_RUNS;
  if (argc > 1) // check if an commandline argument was given 
  {
    sscanf(argv[1], "%d", &runQuantity);
  }

  /*
    setup stats

    since NUM_SCENARIOS == 3:
      - index 0 --> toroise has the sword
      - index 1 --> hare has the sword
      - index 2 --> no one has the sword

    note:
      for the for loop below you can replace NUM_SCENARIOS with "sizeof(scenarioStats) / sizeof(scenarioStats[0])" 
      linking it to the number of elements of the array rather than the constant, 
      though this method is probably less efficient due to the extra computation
  */
  StatsType *scenarioStats[NUM_SCENARIOS];
  for (int i = 0; i < NUM_SCENARIOS; ++i)
  {
    initStats(&scenarioStats[i]);
  }

  // run implementation for the simulation
  for (int i = 0; i < runQuantity; ++i)
  {
    run(scenarioStats);
  }

  printResults(runQuantity, scenarioStats);

  // cleanup remaining memory (ie. stats)
  for (int i = 0; i < NUM_SCENARIOS; ++i)
  {
    free(scenarioStats[i]);
  }

  return 0;
}

/*
  Function:  randm
  Purpose:   returns a pseudo randomly generated number, 
             in the range 0 to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1) 
*/
int randm(int max)
{
  double r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) ); 

  return (int)(r * max);
}

/*
  Function: run
  Purpose:  performs a singular execution (or run) of the simulation
       in:  the statistics
   return:  nothing
*/
void run(StatsType **stats)
{
  // setup deque for each scenario
  DequeType *deques[NUM_SCENARIOS];
  for (int i = 0; i < NUM_SCENARIOS; ++i)
  {
    initDeque(&deques[i]);
  }
  
  initPirates(deques[0]);

  for (int i = 1; i < NUM_SCENARIOS; ++i)
  {
    copyDeque(deques[i], deques[0]);
  }

  // setup heroes
  FighterType *tort[NUM_SCENARIOS];
  FighterType *hare[NUM_SCENARIOS];
  for (int i = 0; i < NUM_SCENARIOS; ++i)
  {
    if (i == 0) // tort will have the sword in the first scenario
    {
      initFighter(TORT_STRENGTH + SWORD_STRENGTH, TORT_ARMOUR, HERO_HEALTH, &tort[i]);
      initFighter(HARE_STRENGTH, HARE_ARMOUR, HERO_HEALTH, &hare[i]);
    }
    else if (i == 1) // hare will have the sword in the second scenario
    {
      initFighter(TORT_STRENGTH, TORT_ARMOUR, HERO_HEALTH, &tort[i]);
      initFighter(HARE_STRENGTH + SWORD_STRENGTH, HARE_ARMOUR, HERO_HEALTH, &hare[i]);
    }
    else // no hero will have the sword
    {
      initFighter(TORT_STRENGTH, TORT_ARMOUR, HERO_HEALTH, &tort[i]);
      initFighter(HARE_STRENGTH, HARE_ARMOUR, HERO_HEALTH, &hare[i]);
    }
  }

  // setup scenarios
  RunSpecsType *scenarios[NUM_SCENARIOS];
  for (int i = 0; i < NUM_SCENARIOS; ++i)
  {
    initScenarioRunSpecs(deques[i], tort[i], hare[i], stats[i], &scenarios[i]);
  }

  // setup scenario threads
  pthread_t scenarioThreads[NUM_SCENARIOS];
  for (int i = 0; i < NUM_SCENARIOS; ++i)
  {
    pthread_create(&scenarioThreads[i], NULL, scenarioThreadFunc, scenarios[i]);
    pthread_join(scenarioThreads[i], NULL);
  }

  // cleanup run memory
  for (int i = 0; i < NUM_SCENARIOS; ++i)
  {
    cleanupScenario(scenarios[i]);
  }
}