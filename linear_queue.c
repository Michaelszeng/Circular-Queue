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
} linear_queue;

void init_queue(linear_queue *q) {
    // initialize queue as empty
    q->head = NULL;
    q->tail = NULL;
}

bool enqueue(linear_queue *q, int value) {
    // create new node
    node *new_node = malloc(sizeof(node));  // get pointer to memory we allocated to the variabl new_node
    if (new_node == NULL) {  // malloc failed; no memory remaining
        return false;
    }
    new_node->value = value;
    new_node->next = NULL;  // new node has nothing after it

    // if there's a tail, connect the tail to the new node
    if (q->tail != NULL) {
        q->tail->next = new_node;  // old tail points to new node
    }
    q->tail = new_node;

    // if queue was empty, new node is head
    if (q->head == NULL) {
        q->head = new_node;
    }

    return true;
}

int dequeue(linear_queue *q) {
    // if queue is empty, return -1
    if (q->head == NULL) {
        return -1;
    }

    // save value of head of queue that we're gonna return
    // node *tmp = q->head;
    // int value = tmp->value;
    int value = q->head->value;

    // take the head off the queue
    q->head = q->head->next;

    // if the queue is now empty, set tail to NULL
    if (q->head == NULL) {
        q->tail = NULL;
    }

    // return the former head of queue
    return value;
}

int main() {
    linear_queue q1, q2, q3;

    // init_queue(&q1);
    init_queue(&q2);
    // init_queue(&q3);

    // enqueue(&q1, 1);

    enqueue(&q2, 52);
    enqueue(&q2, 22);
    enqueue(&q2, 33);

    // enqueue(&q3, 555);

    int t;
    while ((t = dequeue(&q2)) != -1) {
        printf("t = %d\n", t);
    }
}