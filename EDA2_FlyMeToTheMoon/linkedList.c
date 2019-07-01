#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

void print_list(struct linkedFlights *head) {
    struct linkedFlights *temp;
    for (temp = head; temp==NULL; temp = temp->son)
        printf("%s ->", temp->son->data.IdAirChegada);
    puts("");
}

struct linkedFlights *searchList(struct linkedFlights *head, char IdAirChegada_search[5]) {
    struct linkedFlights *temp;
    temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data.IdAirChegada, IdAirChegada_search) == 0) {
            return temp;
        }
        temp = temp->son;
    }
    return NULL;
}

bool search_fligths(struct linkedFlights *head,
                    char IdAirChegada_search[5],
                    short hourPartida_search,
                    short minutePartida_search) {
    struct linkedFlights *temp;
    temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data.IdAirChegada, IdAirChegada_search) == 0) {
            if (temp->data.hourPartida == hourPartida_search)
                if (temp->data.minutePartida == minutePartida_search)
                    return true;
        }
        temp = temp->son;
    }
    return false;
}

struct linkedFlights *add(struct linkedFlights *linkedFlights, char IdAirPartida[5], char IdAirChegada[5], short hourPartida,
    short minutePartida,
    short tempTotal) 
{
    if (!search_fligths(linkedFlights, IdAirChegada, hourPartida, minutePartida)) 
    {
        printf("+ novo voo %s %s %.2hd:%.2hd\n",IdAirPartida,IdAirChegada,hourPartida,minutePartida);

        struct linkedFlights *tempHEAD = malloc(sizeof(struct linkedFlights));
        strcpy(tempHEAD->data.IdAirPartida, IdAirPartida);
        strcpy(tempHEAD->data.IdAirChegada, IdAirChegada);
        tempHEAD->data.hourPartida = hourPartida;
        tempHEAD->data.minutePartida = minutePartida;
        tempHEAD->data.tempTotal = tempTotal;
        if (linkedFlights != NULL) {
            if (linkedFlights->data.tempTotal != 0)
                tempHEAD->son = linkedFlights;
            else
                tempHEAD->son = NULL;
        } else
            tempHEAD->son = NULL;
        return tempHEAD;
    } else
        printf("+ voo %s %s %.2hd:%.2hd existe\n", IdAirPartida, IdAirChegada, hourPartida, minutePartida);
    return linkedFlights;
}

struct linkedFlights *add_from_disk(struct linkedFlights *linkedFlights, char IdAirPartida[5], char IdAirChegada[5], short hourPartida,
                          short minutePartida,
                          short tempTotal)
{
    
    struct linkedFlights *tempHEAD = malloc(sizeof(struct linkedFlights));
    strcpy(tempHEAD->data.IdAirPartida, IdAirPartida);
    strcpy(tempHEAD->data.IdAirChegada, IdAirChegada);
    tempHEAD->data.hourPartida = hourPartida;
    tempHEAD->data.minutePartida = minutePartida;
    tempHEAD->data.tempTotal = tempTotal;
    if (linkedFlights != NULL) {
        if (linkedFlights->data.tempTotal != 0)
            tempHEAD->son = linkedFlights;
        else
            tempHEAD->son = NULL;
    } else
        tempHEAD->son = NULL;
    return tempHEAD;
    
}



struct linkedFlights *remove_linkedFlights(struct linkedFlights *head,
                                           char IdAirPartida_remove[5],
                                           char IdAirChegada_remove[5],
                                           short hourPartida,
                                           short minutePartida) {
    struct linkedFlights *temp;
    struct linkedFlights *temp_pai=NULL;
    temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data.IdAirChegada, IdAirChegada_remove) == 0) 
        {
            if (temp->data.hourPartida == hourPartida)
            {
                if (temp->data.minutePartida == minutePartida) 
                {
                    printf("+ voo %s %s %.2hd:%.2hd removido\n", IdAirPartida_remove, IdAirChegada_remove, hourPartida,
                           minutePartida);
                    if (temp_pai != NULL)
                    {
                        temp_pai->son = temp->son;
                        free(temp);
                        return head;
                    } else
                    {   
                        temp_pai= temp->son;
                        free(temp);
                        return temp_pai;
                    }
                }
            }
               
        }
        temp_pai = temp;
        temp=temp->son;
    }
    printf("+ voo %s %s %.2hd:%.2hd inexistente\n", IdAirPartida_remove, IdAirChegada_remove, hourPartida, minutePartida);
    return head;
}
