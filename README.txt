# COMP 2401 - Christine Laurendau - Final Project

Name:           Clint Galvez [SN: 101196386]
Date:           12 December 2021
Assignment:     COMP 2401-B Final Project
Purpose:        write a program in C, in the VM’s Linux environment, to simulate 
				multiple randomized executions (or runs) of a battle between our 
				two heroes and the pirate crew

**Note: when referring to terminal, it is assumed you are in the final directory**

## SOURCE AND HEADER FILES

- defs.h
- main.c
- deque.c
- pirates.c
- scenarios.c
- statistics.c

## COMPILATION COMMAND

- make

## LAUNCHING AND OPERATING INSTRUCTIONS

1. launch command:  
	- `./final runQuantity` or `valgrind --leak-check=yes ./final runQuantity`
		- the simulation runs 100 times by default (set by NUM_RUNS in defs.h)
		
	
**Note: runQuantity is an optional commandline argument used to specify the desired amount of runs the simulation will perform**
