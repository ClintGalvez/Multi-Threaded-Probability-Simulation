#include "defs.h"

/*
  Function: initDeque
  Purpose:  initializes the fields of a given deque
   in-out:  the initialized deque
   return:  nothing
*/
void initDeque(DequeType **deque)
{
    *deque = malloc(sizeof(DequeType));

    (*deque)->head = NULL;
    (*deque)->tail = NULL;
}

/*
  Function: addFighter
  Purpose:  adds a given fighter to the back of a given deque
       in:  the fighter
   in-out:  the deque
   return:  nothing
*/
void addFighter(DequeType *deque, FighterType *fighter)
{
    NodeType *currNode;
    NodeType *prevNode;
    NodeType *newNode;

    currNode = deque->head;
    prevNode = NULL;

    while (currNode != NULL) // loops until it reaches the tail of the given deque
    {
        prevNode = currNode;
        currNode = currNode->next;
    }

    newNode = malloc(sizeof(NodeType));
    newNode->data = fighter;
    newNode->next = NULL;
    
    if (prevNode == NULL)  // update head
    {
        deque->head = newNode;
    }
    else
    {
        prevNode->next = newNode;
    }

    deque->tail = newNode;
}

/*
  Function: removeFighterFront
  Purpose:  removes a fighter from the front of a given deque, and returns the fighter
       in:  the deque
      out:  the removed fighter
   return:  nothing
*/
void removeFighterFront(DequeType *deque, FighterType **fighter)
{
    // retrieve fighter
    *fighter = deque->head->data;

    // get new head node
    NodeType *headNode;
    headNode = deque->head->next;

    // free current head node
    free(deque->head);

    // update head node
    deque->head = headNode;
}

/*
  Function: removeFighterBack
  Purpose:  removes a fighter from the back of a given deque, and returns the fighter
       in:  the deque
      out:  the removed fighter
   return:  nothing
*/
void removeFighterBack(DequeType *deque, FighterType **fighter)
{
    // retrieve fighter
    *fighter = deque->tail->data;

    // get new tail node
    NodeType *currNode;
    NodeType *tailNode;

    currNode = deque->head;
    tailNode = NULL;

    while (currNode != deque->tail) // loops until it reaches the tail of the given deque
    {
        tailNode = currNode;
        currNode = currNode->next;
    }

    // free current tail node
    free(deque->tail);

    // update tail node
    // tailNode->next = NULL; // breaks code for some reason
    deque->tail = tailNode;
}

/*
  Function: copyDeque
  Purpose:  performs a deep copy of a source deque and its data into a destination deque; this
            populates the destination deque with copies of all the same fighters, in the same order
       in:  the source deque
      out:  the destination deque
   return:  nothing
*/
void copyDeque(DequeType *destination, DequeType *source)
{
    NodeType *currNode;     // source node
    NodeType *newNode;      // destination node(s)
    NodeType *prevNewNode;  // |

    currNode = source->head;
    prevNewNode = NULL;

    while (currNode != NULL) // loops until it reaches the tail of the given deque
    {
        // setup data
        FighterType *fighter;
        initFighter(currNode->data->strength, currNode->data->armour, currNode->data->health, &fighter);

        // setup node
        newNode = malloc(sizeof(NodeType));
        newNode->data = fighter;
        newNode->next = NULL;
        
        if (destination->head == NULL)      // update head
        {
            destination->head = newNode;
        }

        destination->tail = newNode;        // update tail

        currNode = currNode->next;

        if (prevNewNode != NULL)
        {
            prevNewNode->next = newNode;
        }

        prevNewNode = newNode;
    }
}

/*
  Function: printFighters
  Purpose:  prints all the fighters in a given deque
       in:  the deque
   return:  nothing
*/
void printFighters(DequeType *deque)
{
    NodeType *currNode;
    currNode = deque->head;

    // loop through the entire deque
    while (currNode != NULL)
    {
        printFighter(currNode->data);

        currNode = currNode->next;
    }
}

/*
  Function: cleanupDeque
  Purpose:  cleans up all the dynamically allocated memory for a given deque
       in:  the deque
   return:  nothing
*/
void cleanupDeque(DequeType *deque)
{
    NodeType *currNode;
    NodeType *nextNode;

    currNode = deque->head;
    nextNode = NULL;

    while (currNode != NULL)
    {
        // free inner memory allocated data
        free(currNode->data);

        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }

    free(deque);
}