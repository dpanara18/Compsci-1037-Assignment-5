/* CS1037a 2022 */
/* Assignment 05 BONUS */
/* Dev Panara */
/* 251208360 */
/* dpanara */
/* 06/12/2022 */

#include "mainHeaders.h"

int main()
{
    int simDuration, entryInterval, serviceInterval, numOfQueues;
    int customer, serviceTime, entryTime;
    int maxCount, maxWaitTime;
    int loop = 1;
    char repeat;
    QUEUE** queue;
    QUEUE_NODE** tempNode;
    srand(time(NULL));

    do{
    printf("SUPERMARKET SIMULATION:\n\n");
    printf("|-------------------------|   |-----------------------------|\n\n");
    printf("Enter the values for this run of this simulation:\n\n");

    while(loop){
    printf("Enter Simulation Duration (in minutes): ");
    scanf("%d", &simDuration);
    if(simDuration < 1)
        printf("Please enter an integer value greater than 0\n");
    else
        loop = 0;
    }
    loop = 1;
    while(loop){
    printf("Enter Customer Entry Interval (in minutes): 1 to ");
    scanf("%d", &entryInterval);
    if(entryInterval < 1)
        printf("Please enter an integer value greater than 0\n");
    else
        loop = 0;
    }
    loop = 1;
    while(loop){
    printf("Enter Customer Service Time Interval (in minutes): 1 to ");
    scanf("%d", &serviceInterval);
    if(serviceInterval < 0)
        printf("Please enter an integer value greater than 0\n");
    else
        loop = 0;
    }
    loop = 1;
    while(loop){
    printf("Enter Number of Checkout Lines: ");
    scanf("%d", &numOfQueues);
    if(numOfQueues < 1)
        printf("Please enter an integer value greater than 0\n");
    else
        loop = 0;
    }
    loop = 1;
    printf("\n|---------------------------------------------|\n");

    queue = (QUEUE**) malloc (numOfQueues * sizeof(QUEUE*));
    for(int i = 0; i < numOfQueues; i++){
        queue[i] = createQueue();
    }

    int waitTime[numOfQueues];
    customer = 1;
    serviceTime = (rand() % serviceInterval) + 1;
    entryTime = (rand() % entryInterval) + 1;
    maxCount = 0;
    for(int i = 0; i < numOfQueues; i++){
        waitTime[i] = 0;
    }
    maxWaitTime = 0;
    QUEUE* tempQueue;
    int min;
    tempNode = (QUEUE_NODE**) malloc (numOfQueues * sizeof(QUEUE*));
    int count = 0;

    for(int currentTime = 1; currentTime <= simDuration; currentTime++){
        printf("\nCurrent Cycle Minute: %d\n", currentTime);

//        if(entryTime == currentTime){
//            for(int i = 0; i < numOfQueues; i++){
//
//            }
//
//
//        }

        if(entryTime == currentTime){
            tempQueue = queue[0];
            min = 0;
            for(int i = 1; i < numOfQueues; i++){
                if(tempQueue->count > queue[i]->count){
                    tempQueue = queue[i];
                    min = i;
                }
            }
            tempNode[min] = queue[min]->front;

            if(queue[min]->front != NULL){
            if(tempNode[min]->next == NULL){
                waitTime[min] = tempNode[min]->serviceTime + serviceTime;
            }
            else{
                waitTime[min] = serviceTime;
                while(tempNode[min] != NULL){
                    waitTime[min] = waitTime[min] + tempNode[min]->serviceTime;
                    tempNode[min] = tempNode[min]->next;
                    }
                }
            }
            else
                waitTime[min] = serviceTime;
            queue[min] = tempQueue;
            enqueue(queue[min], customer, serviceTime, entryTime);
            printf(" ++++ New customer: %d added at: %d to Check Out Line: %d - Service Time: %d and will be done at: %d <-> Total Wait Time: %d\n", customer, currentTime, min + 1, serviceTime , (queue[min]->rear->entryTime) + waitTime[min], waitTime[min]);
            entryTime = ((rand() % entryInterval) + 1) + currentTime;
            serviceTime = (rand() % serviceInterval) + 1;
            customer ++;
        }

        for(int i = 0; i < numOfQueues; i++){
            if(queue[i]->front != NULL){
                if(queue[i]->front->serviceTime == 0){
                    printf(" ---- Customer number: %d has been serviced and has left the store\n", queue[i]->front->customer);
                    dequeue(queue[i]);
                }
            }

            if(queue[i]->front != NULL)
                (queue[i]->front->serviceTime)--;

            //printQueue(queue);

            if(maxCount < queue[i]->count)
                maxCount = queue[i]->count;

            if(maxWaitTime < waitTime[i])
                maxWaitTime = waitTime[i];

            }
//        if(queue->front != NULL){
//            if(queue->front->serviceTime == 0){
//                printf(" ---- Customer number: %d has been serviced and has left the store\n", queue->front->customer);
//                dequeue(queue);
//            }
//        }
//
//        if(queue->front != NULL)
//            (queue->front->serviceTime)--;
//
        for(int i = 0; i < numOfQueues; i++){
            printQueue(queue[i], i + 1);
        }
//      printQueue(queue);
//
//        if(maxCount < queue->count)
//            maxCount = queue->count;
//
//        if(maxWaitTime < waitTime)
//            maxWaitTime = waitTime;
    }

    for(int i = 0; i < numOfQueues; i++){
        count = count + queue[i]->count;
    }

    printf("\nThe simulation ended with %d customers in the Check Out Line.\n", count);
    printf("The most customers in the Check Out Line at any one time was %d.\n", maxCount);
    printf("The longest wait time for any single customer was %d minutes.\n", maxWaitTime);

    for(int i = 0; i < numOfQueues; i++){
        freeMemory(queue[i]);
    }
    free(queue);

    printf("\nDo you wish to run the simulation again (y/n) ");
    scanf("%s", &repeat);

    } while(repeat == 'y' || repeat == 'Y');

    printf("\n----------Assignment(05) BONUS written by Dev Panara (dpanara)----------\n")
    return 0;
}
