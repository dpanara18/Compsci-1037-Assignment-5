/* CS1037a 2022 */
/* Assignment 05 BONUS */
/* Dev Panara */
/* 251208360 */
/* dpanara */
/* 06/12/2022 */

#include "mainHeaders.h"

QUEUE* createQueue (void)
{
    QUEUE* queue;
    queue = (QUEUE*) malloc (sizeof(QUEUE));

    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;

    return queue;
}	// createQueue

bool enqueue (QUEUE* queue, int customer, int serviceTime, int entryTime)
{
    QUEUE_NODE* newPtr;
    if(!(newPtr = (QUEUE_NODE*) malloc (sizeof(QUEUE_NODE))))
        return false;

    newPtr->customer = customer;
    newPtr->entryTime = entryTime;
    newPtr->serviceTime = serviceTime;
    newPtr->next = NULL;

    if(queue->count == 0)
        queue->front = newPtr;
    else
        queue->rear->next = newPtr;

    (queue->count)++;
    queue->rear = newPtr;

    //free(newPtr);
    return true;
}	// enqueue


void dequeue (QUEUE* queue)
{
    QUEUE_NODE* deleteLoc;

    deleteLoc = queue->front;

    if(queue->count == 1)
        queue->rear = queue->front = NULL;
    else
        queue->front = queue->front->next;

    (queue->count)--;
    free(deleteLoc);

}	  // dequeue

void printQueue(QUEUE* queue, int numQueue)
{
    if(queue->front == NULL)
        printf(" - Queue %d:  Queue is currently empty\n", numQueue);

    else{
        printf(" - Queue %d: ", numQueue);
        QUEUE_NODE* newPtr = queue->front;
        while (newPtr != NULL) {
            printf("%d ", newPtr->customer);
            newPtr = newPtr->next;
        }
    printf("\n");
    }

}	// printOne Queue


void freeMemory(QUEUE* queue)
{
    while(queue->front != NULL){
        dequeue(queue);
    }
    free(queue);
}

