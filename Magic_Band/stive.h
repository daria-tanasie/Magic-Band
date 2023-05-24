/* TĂNASIE Daria-Maria - 312CD */
#ifndef _STIVE_H_
#define _STIVE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banda.h"

// nod ce reprezinta pozitia precedenta a degetului din stiva pentru UNDO

typedef struct undoPos {
    Banda pos;
    struct undoPos *next;
} *uPos;

// stiva pentru UNDO unde se retine pozitia ultimului element adaugat

typedef struct undoStack {
    uPos top;
} *uStack;

// nod din stiva pentru REDO unde se retine pointer la ultima pozitie

typedef struct redoPos {
    Banda pos;
    struct redoPos *next;
} *rPos;

// stiva pentru REDO unde se retine pozitia ultimului element adaugat

typedef struct redoStack {
    rPos top;
} *rStack;

// initializeaza stiva pt UNDO

uStack initUndo() {
    uStack stiva = (uStack) malloc(sizeof(struct undoStack));
    stiva->top = NULL;
    return stiva;
}

// initializeaza stiva pt REDO

rStack initRedo() {
    rStack stiva = (rStack) malloc(sizeof(struct redoStack));
    stiva->top = NULL;
    return stiva;
}

//verifica daca stiva UNDO este goala

int isUEmpty(uStack s) {
    if(s->top == NULL)
        return 1;
    return 0;    
}

//verifica daca stiva REDO este goala

int isREmpty(rStack s) {
    if(s->top == NULL)
        return 1;
    return 0;    
}

// adauga o noua pozitie in stiva UNDO

void Upush(uStack s, Banda pos) {
    uPos position = (uPos) malloc(sizeof(struct undoPos));
    position->next = NULL;
    position->pos = pos;
    if(isUEmpty(s)) {
        s->top = position;
        return;
    }
    position->next = s->top;
    s->top = position;
    return;
}

//adauga o noua pozitie in stiva REDO

void Rpush(rStack s, Banda pos) {
    rPos position = (rPos) malloc(sizeof(struct redoPos));
    position->next = NULL;
    position->pos = pos;
    if(isREmpty(s)) {
        s->top = position;
        return;
    }
    position->next = s->top;
    s->top = position;
    return;
}

//elimina elementul din varful stivei UNDO

void popU(uStack s) {
    if(!isUEmpty(s)) {
        uPos tmp = s->top;
        s->top = s->top->next;
        free(tmp);
    }    
}

//elimina elementul din varful stivei REDO

void popR(rStack s) {
    if(!isREmpty(s)) {
        rPos tmp = s->top;
        s->top = s->top->next;
        free(tmp);
    }    
}

//elibereaza spatiul alocat pentru elementele stivei UNDO si pt stiva UNDO

void freeU(uStack s) {
    while(!isUEmpty(s))
        popU(s);
    free(s);    
}

//elibereaza spatiul alocat pentru elementele stivei REDO si pt stiva REDO

void freeR(rStack s) {
    while(!isREmpty(s))
        popR(s);
    free(s);
}

//elibereaza elementele din stiva UNDO fara a sterge stiva

void deleteElemU(uStack s) {
    while(!isUEmpty(s))
        popU(s); 
}

//elibereaza elementele din stiva REDO fara a sterge stiva

void deleteElemR(rStack s) {
    while(!isREmpty(s))
        popR(s);
}

#endif