/* TĂNASIE Daria-Maria - 312CD */
#ifndef _COADA_H_
#define _COADA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// nod pentru o comanda

typedef struct command {
    char* data;
    struct command *next;
} Command;

// coada pt comenzi

typedef struct queue {
    Command *head, *tail;
} *TQueue;

//aloca spatiu pt o comada si creeaza nodul

Command *createCommand(char* data) {
    Command *command = (Command*) malloc(sizeof(struct command));
    if(command == NULL)
        return NULL;
    command->data = (char*) malloc (strlen(data) + 1);
    strcpy(command->data, data);
    command->next = NULL;
    return command;
}

// initializeaza coada

TQueue allocQueue() {
    TQueue queue = (TQueue) malloc(sizeof(struct queue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

// adauga comanda la coada

TQueue enqueue(TQueue queue, char* data) {
    Command *command;
    command = createCommand(data);
    if(queue->head == NULL) {
        queue->head = command;
        queue->tail = command;
    } else {
    queue->tail->next = command;
    queue->tail = command;
    }
    return queue;
}

// verifica daca coada este goala 

int queueEmpty(TQueue queue) {
    return queue == NULL || queue->head == NULL;
}

//elimina din coada ultima comanda adaugata 

TQueue dequeue(TQueue queue) {
    if(queueEmpty(queue))
        return NULL;

    Command* tmp = queue->head;

    if(queue->head == queue->tail) {
        queue->head = NULL;
        queue->tail = NULL;
    } else queue->head = queue->head->next;

    free(tmp->data);
    free(tmp);

    return queue;
}

//dezaloca spatiul alocat pentru coada

TQueue freeQueue(TQueue queue) {
    while(!queueEmpty(queue))
       queue = dequeue(queue);
    if(queue != NULL)
        free(queue);
    return NULL;
}

#endif