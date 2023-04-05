/* CS1037a 2022 */
/* Assignment 05 BONUS */
/* Dev Panara */
/* 251208360 */
/* dpanara */
/* 06/12/2022 */

#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

// Queue ADT Type Definitions
   typedef struct node
   {
      int            customer;
      int            serviceTime;
      int            entryTime;
      struct node*   next;
   } QUEUE_NODE;

   typedef struct
   {
      QUEUE_NODE*   front;
      QUEUE_NODE*   rear;
      int           count;
   } QUEUE;

#endif // DEFINITIONS_H_INCLUDED
