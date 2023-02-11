#include "defs.h"

/*
  Function: initStatistics
  Purpose:  initializes the fields of a given deque
   in-out:  the initialized deque
   return:  nothing
*/
void initStats(StatsType **stats)
{
    *stats = malloc(sizeof(StatsType));

    (*stats)->numSuccess = 0;
    (*stats)->numPartSuccess = 0;
    (*stats)->numFailure = 0;
}

/*
  Function: updateStats
  Purpose:  initializes the fields of a given deque
   in-out:  the initialized deque
   return:  nothing
*/
void updateStats(ResultType result, StatsType *stats)
{
    switch(result)
    {
        case SUCCESS:
            ++stats->numSuccess;
            break;
        
        case FAILURE:
            ++stats->numFailure;
            break;
        
        case PART_SUCCESS:
            ++stats->numPartSuccess;
            break;

        default: // RES_UNKNOWN
            // NOTHING
            break;
    }
}

/*
  Function: printResults
  Purpose:  prints the simulation results of n runs
       in:  the colletion of results
   return:  nothing
*/
void printResults(int totalRuns, StatsType **scenarioStats)
{
  printf("\n");

  // categories
  printLine();
  printf("| Hero with sword |  %% success  |  %% partial  |  %% failure  |\n");
  printLine();

  // results
  printf("|   Tortoise      |     %-3d     |     %-3d     |     %-3d     |\n", scenarioStats[0]->numSuccess*100/totalRuns, scenarioStats[0]->numPartSuccess*100/totalRuns, scenarioStats[0]->numFailure*100/totalRuns);
  printLine();
  printf("|   Hare          |     %-3d     |     %-3d     |     %-3d     |\n", scenarioStats[1]->numSuccess*100/totalRuns, scenarioStats[1]->numPartSuccess*100/totalRuns, scenarioStats[1]->numFailure*100/totalRuns);
  printLine();
  printf("|   None          |     %-3d     |     %-3d     |     %-3d     |\n", scenarioStats[2]->numSuccess*100/totalRuns, scenarioStats[2]->numPartSuccess*100/totalRuns, scenarioStats[2]->numFailure*100/totalRuns);
  printLine();

  printf("\nTotal runs: %d\n\n", totalRuns);
}

/*
  Function: printLine
  Purpose:  a helper function that prints a line for the print results function
   return:  nothing
*/
void printLine()
{
  printf("+");
  for (int i = 0; i < 59; ++i)
  {
    printf("-");
  }
  printf("+\n");
}