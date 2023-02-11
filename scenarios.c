#include "defs.h"

/*
  Function: initScenarioRunSpecs
  Purpose:  initializes the fields of a scenario run
       in:   the pirates
       in:   the tortoise
       in:   the hare
       in:   the stats
   in-out:  the initialized scenario run
   return:  nothing
*/
void initScenarioRunSpecs(DequeType *pirates, FighterType *tort, FighterType *hare, StatsType *stats, RunSpecsType **run)
{
    *run = malloc(sizeof(RunSpecsType));

    (*run)->pirates = pirates;
    (*run)->tort = tort;
    (*run)->hare = hare;
    (*run)->stats = stats;
}

/*
  Function: initFightSpecs
  Purpose:  initializes the fields of a fight
       in:   the hero
       in:   the pirates
       in:   the direction
       in:   the mutex
   in-out:  the initialized fight
   return:  nothing
*/
void initFightSpecs(FighterType *hero, DequeType *pirates, DirectionType dir, sem_t *dqMutex, FightSpecsType **fight)
{
    *fight = malloc(sizeof(FightSpecsType));

    (*fight)->hero = hero;
    (*fight)->pirates = pirates;
    (*fight)->dir = dir;
    (*fight)->dqMutex = dqMutex;
}

/*
  Function:  scenarioThreadFunc
  Purpose:   runs a simulated scenario
       in:   arg
   return:   nothing
*/
void *scenarioThreadFunc(void *arg)
{
    // cast the argument to a fightspecstype pointer
    RunSpecsType scenario = *((RunSpecsType *)arg);

    // setup mutex
    sem_t mutex;
    if (sem_init(&mutex, 0, 1) < 0) 
    {
        printf("semaphore initialization error\n");
        exit(1);
    }

    // setup fights
    FightSpecsType *front, *back;
    initFightSpecs(scenario.tort, scenario.pirates, FRONT, &mutex, &front);
    initFightSpecs(scenario.hare, scenario.pirates, BACK, &mutex, &back);

    // setup fight threads
    pthread_t frontFightThread, backFightThread;
    pthread_create(&frontFightThread, NULL, fightThreadFunc, front);
    pthread_create(&backFightThread, NULL, fightThreadFunc, back);
    pthread_join(frontFightThread, NULL);
    pthread_join(backFightThread, NULL);

    // compute results
    computeScenarioResults(scenario);

    // cleanup scenario memory allocated in the thread
    free(front);
    free(back);

    return(0);
}

/*
  Function:  fightThreadFunc
  Purpose:   runs a simulated fight
       in:   arg
   return:   nothing
*/
void *fightThreadFunc(void *arg)
{
  // cast the argument to a fightspecstype pointer
  FightSpecsType fightSpecs = *((FightSpecsType *)arg);

  int lastNode = C_FALSE;

  // check if the pirate deque is empty by seeing if the head and tail are the same and that they are both set to NULL
  while (!(fightSpecs.pirates->head == fightSpecs.pirates->tail && fightSpecs.pirates->head == NULL))
  {
    // access mutex in the fightspecstype
    if (sem_wait(fightSpecs.dqMutex) < 0)
    {
      printf("semaphore wait error\n");
      exit(1);
    }
    
    if (fightSpecs.pirates->head == fightSpecs.pirates->tail) // check if current node is the last node
    {
      if (fightSpecs.pirates->head == NULL) // check if the last node has already been removed
      {
        break;
      }

      lastNode = C_TRUE;
    }

    FighterType *pirate;
    
    // determine which pirate to fight based on the direction
    switch(fightSpecs.dir)
    {
      case FRONT:
        removeFighterFront(fightSpecs.pirates, &pirate);
        break;
      case BACK:
        removeFighterBack(fightSpecs.pirates, &pirate);
        break;
      default:
        // NOTHING
        break;
    }

    if (lastNode)
    {
      fightSpecs.pirates->head = NULL;
      fightSpecs.pirates->tail = NULL;
    }

    if (sem_post(fightSpecs.dqMutex) < 0)
    {
      printf("semaphore post error\n");
      exit(1);
    }

    runFight(fightSpecs.hero, pirate);
    free(pirate);

    usleep(100);
  }

  return(0);
}

/*
  Function:  runFight
  Purpose:   runs a simulated fight
       in:   the hero
       in:   the pirate
   return:   nothing
   return:   C_OK for success, C_NOK for failure
*/
void runFight(FighterType *hero, FighterType *pirate)
{
    int damage;
    
    while (hero->health > 0)
    {
      // hero attacks first
      damage = hero->strength - pirate->armour;
      if (damage < 0)
      {
        damage = 0;
      }
      pirate->health -= damage;
      
      // check if pirate dies
      if (pirate->health <= 0)
      {
        pirate->health = 0;
        hero->health += 3;
        if (hero->health > 20)
        {
          hero->health = 20;
        }
        break;
      }

      // pirate attacks last
      damage = (pirate->strength + randm(pirate->strength - 1)) - hero->armour;
      if (damage < 0)
      {
        damage = 0;
      }
      hero->health -= damage;

      // check if hero dies
      if (hero->health <= 0)
      {
        hero->health = 0;
      }
    }
}

/*
  Function:  computeScenarioResults
  Purpose:   compute the results of the given scenario
       in:   arg
   return:   nothing
*/
void computeScenarioResults(RunSpecsType scenario)
{
  if (scenario.hare->health == 0 && scenario.tort->health == 0)
  {
    updateStats(FAILURE, scenario.stats);
  }
  else if ((scenario.hare->health > 0 && scenario.tort->health == 0) || (scenario.hare->health == 0 && scenario.tort->health > 0))
  {
    updateStats(PART_SUCCESS, scenario.stats);
  }
  else
  {
    updateStats(SUCCESS, scenario.stats);
  }
}

/*
  Function: cleanupScenario
  Purpose:  cleans up all the dynamically allocated memory for a given scenario
       in:  the scenario
   return:  nothing
*/
void cleanupScenario(RunSpecsType *scenario)
{
    cleanupDeque(scenario->pirates);
    free(scenario->tort);
    free(scenario->hare);
    free(scenario);
}