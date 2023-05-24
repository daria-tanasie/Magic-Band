/* TĂNASIE Daria-Maria - 312CD */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "coada.h"
#include "banda.h"
#include "stive.h"

int main() {
    char input_filename[] = "tema1.in";
    char output_filename[] = "tema1.out";
    FILE *in = fopen(input_filename, "rt");
    FILE *out = fopen(output_filename, "w");
    int nr_cmd = 0;
    char cmd[20];

    List *band = createList();
    TQueue queue = allocQueue();
    uStack undoS = initUndo();
    rStack redoS = initRedo();

    band->sentinel = initList();
    insertFirst(band, '#');
    
    fscanf(in, "%d", &nr_cmd);

    /*citim fiecare linie din fisier, iar daca sunt comenzi
    de tip UPDATE le adaugam in coada, altfel executam comanda primita*/

    while(fgets(cmd, sizeof(cmd), in)) {
        if(cmd[strlen(cmd) - 1] == '\n')
            cmd[strlen(cmd) - 1] = '\0'; //punem NULL pe ultima pozitie

        if(strcmp(cmd, "EXECUTE") == 0) {
            if(strncmp(queue->head->data, "MOVE_RIGHT", 11) == 0) {
                if(band->current->next == NULL)
                    insert(band->current, '#');
                Upush(undoS, band->current);
                band->current = band->current->next;
            }

            if(strncmp(queue->head->data, "MOVE_LEFT", 10) == 0) {
                if(band->current != band->sentinel->next) {
                    Upush(undoS, band->current);
                    if(band->current == band->sentinel->next->next) {
                        band->current = band->sentinel->next;
                    } else {
                        Banda tmp = band->sentinel;
                        while(tmp->next != band->current) {
                            tmp = tmp->next;
                        }  
                        band->current = tmp;
                    }
                }    
            }

            if(strncmp(queue->head->data,"MOVE_RIGHT_CHAR", 15) == 0) {
                char charact;
                charact = queue->head->data[16];
                if(!searchRight(band, band->current, charact)) {
                    Banda tmp = band->current;
                    while(tmp->next != NULL)
                        tmp = tmp->next;
                    insert(tmp, '#');
                    band->current = tmp->next;
                }
            }
            if(strncmp(queue->head->data,"MOVE_LEFT_CHAR", 14) == 0) {
                char charact;
                charact = queue->head->data[15];
                if(band->current->data != charact)
                    if(!searchLeft(band->sentinel, band, band->current, charact)) {
                    fprintf(out, "ERROR\n");
                    }
            }

            if(strncmp(queue->head->data, "WRITE", 5) == 0) {
                char charact;
                charact = queue->head->data[6];
                band->current->data = charact;
                if(undoS->top != NULL)
                    deleteElemU(undoS);
                if(redoS->top != NULL)
                    deleteElemR(redoS);
            }

            if(strncmp(queue->head->data,"INSERT_RIGHT", 12) == 0) {
                char charact;
                charact = queue->head->data[13];
                insert(band->current, charact);
                band->current = band->current->next;
            }

            if(strncmp(queue->head->data,"INSERT_LEFT", 11) == 0) {
                char charact;
                charact = queue->head->data[12];
                if(band->current->prev == band->sentinel)
                    fprintf(out, "ERROR\n");
                else {
                    Banda tmp = band->sentinel;
                        while(tmp->next != band->current) {
                            tmp = tmp->next;
                        }
                        band->current = tmp;
                    insertLeft(band->current->next, tmp, charact);
                    band->current = band->current->next;
                }
            }

            dequeue(queue); //dupa ce executam o comanda o stergem din coada
        
        } else {
        if(strcmp(cmd, "SHOW") == 0) {
            Banda iter = band->sentinel->next;
            while(iter != NULL) {
            if(band->current == iter)
                fprintf(out, "|%c|", iter->data);
            else fprintf(out, "%c", iter->data);
            iter = iter->next;
            }
            fprintf(out, "\n");
        }

        if(strcmp(cmd, "SHOW_CURRENT") == 0) {
            fprintf(out, "%c\n", band->current->data);    
        }

       if(strcmp(cmd, "UNDO") == 0) {
            Rpush(redoS,band->current);
            band->current = undoS->top->pos;
            popU(undoS);
        }

        if(strcmp(cmd, "REDO") == 0) {
            Upush(undoS,band->current);
            band->current = redoS->top->pos;
            popR(redoS);
        }

        if(strcmp(cmd,"MOVE_RIGHT") == 0 || strcmp(cmd,"MOVE_LEFT") == 0) {
            queue = enqueue(queue, cmd);
        }

        if(strncmp(cmd,"MOVE_RIGHT_CHAR", 15) == 0 ||
            strncmp(cmd,"MOVE_LEFT_CHAR", 14) == 0) {
                queue = enqueue(queue, cmd);
        }

        if(strncmp(cmd, "WRITE", 5) == 0) {
            queue = enqueue(queue, cmd);
        }

        if(strncmp(cmd,"INSERT_RIGHT", 12) == 0 ||
            strncmp(cmd,"INSERT_LEFT", 11) == 0) {
                queue = enqueue(queue, cmd);
        }
        }
    }

    fclose(in);
    fclose(out);

    freeList(band);
    freeU(undoS);
    freeR(redoS);
    freeQueue(queue);

    return 0;
}