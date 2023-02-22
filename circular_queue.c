/*
Implementation of a circular queue in C. Advantages of a circular queue over a linear queue are that
circular are more memory efficient, as dequeued entries don't take up unecessary space. This implementation
uses linked lists, so there is also no fixed length for the circular queue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  // enables use of bool type
#include <memory.h>   // enables use of malloc

typedef struct {
    int value;
    struct node *next;
} node;

typedef struct {
    node *head;
    node *tail; 
} circular_queue;

void init_queue(circular_queue *q) {
    // initialize queue as empty
    q->head = NULL;
    q->tail = NULL;
}

bool enqueue(circular_queue *q, int value) {
    // create new node
    node *new_node = malloc(sizeof(node));  // get pointer to memory we allocated to the variabl new_node
    if (new_node == NULL) {  // malloc failed; no memory remaining
        return false;
    }

    bool empty = isEmpty(q);

    // if queue isn't empty, connect point the no-longer-tail-node to the new tail node
    if (!empty) {
        q->tail->next = new_node;
    }

    new_node->value = value;
    new_node->next = q->head;  // bc this is a circular queue, new node next points to head of queue

    // set the new tail node
    q->tail = new_node;

    // if queue was empty, new node is head
    if (empty) {
        q->head = new_node;
    }

    return true;
}

int dequeue(circular_queue *q) {
    // if queue is empty, return -1
    if (isEmpty(q)) {
        return -1;
    }

    // save value of head of queue that we're gonna return
    int value = q->head->value;

    // if queue has only one node, set dequeue it, return its value, and set head and tail to NULL
    if (q->head == q->tail) {
        q->head = NULL;
        q->tail = NULL;
        return value;
    }

    // take the head off the queue
    q->head = q->head->next;

    // if the queue is now empty, set tail to NULL
    if (isEmpty(q)) {
        q->tail = NULL;
    }
    else {
        // bc this is a circular queue, new tail node next points to head of queue
        q->tail->next = q->head;  
    }

    // return value of the former head of queue
    return value;
}

int isEmpty(circular_queue *q) {
    // if queue is empty, return 1
    if (q->head == NULL) {
        return 1;
    }
    return 0;
}

int main() {
    circular_queue q1;

    init_queue(&q1);
    enqueue(&q1, 52);
    enqueue(&q1, 22);
    printf("%d\n", dequeue(&q1));
    enqueue(&q1, 33);

    printf("%d\n", dequeue(&q1));
    printf("%d\n", dequeue(&q1));
    printf("%d\n", dequeue(&q1));
    enqueue(&q1, 44);
    printf("%d\n", dequeue(&q1));
}