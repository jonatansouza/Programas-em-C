/**
*@author Jonatan Souza
*/

#ifndef _Queue
#define _Queue

#include <stdio.h>
#include <stdlib.h>

struct _queue;
typedef struct _queue Queue;

struct _queueC;
typedef struct _queueC QueueC;

void printQueue(Queue *s);
int queue(Queue **s, double value);
int dequeue(Queue **s, double *value);
int queueDestroy(Queue **s);
int queueC(QueueC **s, char value);
int dequeueC(QueueC **s, char *value);

#endif
