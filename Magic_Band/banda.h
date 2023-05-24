/* TĂNASIE Daria-Maria - 312CD */
#ifndef _BANDA_H_
#define _BANDA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//elemnt din banda

typedef struct banda{
	char data;
	struct banda* next;
	struct banda* prev;
} *Banda;

//santinela(prima pozitie din banda) si pozitia degetului

typedef struct List{
	Banda sentinel;
    Banda current;
}List;

//creeaza lista cu santinela si elem curent

List* createList(void){
	List *list =  (List*) malloc(sizeof(struct List));
	list->sentinel = NULL;
    list->current = NULL;
	return list;
}

//creeaza santinela

Banda initList(void) {
	Banda sentinel =  (Banda) calloc(1, sizeof(struct banda));
	sentinel->prev = NULL;
	sentinel->next = NULL;
	return sentinel;
}

// creeaza un nou elemnt pentru banda alocand spatiu

Banda createNode(char elem) {
	Banda node =  (Banda) malloc(sizeof(struct banda));
	node->data = elem;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

/*insereaza un element dat ca parametru pe prima pozitie in
    banda(dupa santinela) */

void insertFirst(List* band, char data) {
    Banda node = createNode(data);
    node->next = band->sentinel->next;
    band->sentinel->next = node;
    node->prev = band->sentinel;
    band->current = band->sentinel->next;

}

// dezaloca spatiul ocupat de banda

Banda freeList(List* list) {
    if(list == NULL) {
        return NULL;
    }
    Banda iter, temp;
    iter = list->sentinel;
    while(iter != NULL) {
        temp = iter;
        iter = iter->next;
        free(temp);
    }
    free(list);
    return NULL;
}

/* creeaza un nod cu elementul dat ca parametru
    si il insereaza dupa elementul "list" */

void insert(Banda list, char data) {
    Banda node = createNode(data);
    if(list->next == NULL) {
        list->next = node;
        node->prev = list;
    } else {
    node->next = list->next;
    list->next->prev = node;
    list->next = node;
    }
}

// functie pt inserarea la stanga elementului dat ca parametru(list)

void insertLeft(Banda list, Banda prev, char data) {
    Banda node = createNode(data);
    Banda anterior = prev;
    anterior->next = node;
    list->prev = node;
    node->next = list;
    node->prev = anterior;
}

/* functie utilizata pentru comanda MOVE_RIGHT_CHAR pentru a cauta
    elementul dat ca parametru in banda */

int searchRight(List* curr, Banda list, char data) {
    Banda tmp = list;
    while(tmp != NULL) {
        if(tmp->data == data) {
            curr->current = tmp;
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

/* functie utilizata pentru comanda MOVE_LEFT_CHAR pentru a cauta
    elementul dat ca parametru in banda */

int searchLeft(Banda first, List* curr, Banda list, char data) {
    Banda iter = list->prev;
    while(iter != first) {
        if(iter->data == data) {
            curr->current = iter;
            return 1;
        }
        iter = iter->prev;
    }
    return 0;
}

#endif