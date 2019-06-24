#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroportoVoo.h"

/*
 * todo:
 * Baseado na implemetação do MOCHILA
 * */



void init(struct linkedFlights *head,
          char IdAirChegada[5],
          short hourPartida,
          short minutePartida,
          short tempTotal) {
    strcpy(head->data.IdAirChegada, IdAirChegada);
    head->data.hourPartida = hourPartida;
    head->data.minutePartida = minutePartida;
    head->data.tempTotal = tempTotal;
    head->son = NULL;
}


void print_list(struct linkedFlights *head) {
    struct linkedFlights *temp;
    for (temp = head; temp; temp = temp->son)
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
    }
    return NULL;
}

struct linkedFlights *add(struct linkedFlights *linkedFlights,
                          char IdAirChegada[5],
                          short hourPartida,
                          short minutePartida,
                          short tempTotal) {
    struct linkedFlights *tempHEAD = malloc(sizeof(struct linkedFlights));
    strcpy(tempHEAD->data.IdAirChegada, IdAirChegada);
    tempHEAD->data.hourPartida = hourPartida;
    tempHEAD->data.minutePartida = minutePartida;
    tempHEAD->data.tempTotal = tempTotal;
    tempHEAD->son = linkedFlights;
    return tempHEAD;
}


struct linkedFlights *remove_linkedFlights(struct linkedFlights *head,
                                           char IdAirChegada_remove[5],
                                           short hourPartida,
                                           short minutePartida) {
    struct linkedFlights *temp;
    struct linkedFlights *temp_pai;
    temp = head;
    while (temp != NULL) {
        if (strcmp(temp->data.IdAirChegada, IdAirChegada_remove) == 0) {
            if (temp->data.hourPartida == hourPartida)
                if (temp->data.minutePartida == minutePartida) {
                    if (temp_pai != NULL) {
                        temp_pai->son = temp->son;
                        return head;
                    } else
                        return temp->son;
                }

        }
        temp_pai = temp;
    }

}

int main (){
    struct linkedFlights *testeDOStestes=malloc(sizeof(struct linkedFlights));
    init(testeDOStestes,"helo",1,1,1);
    testeDOStestes=add(testeDOStestes,"helo2",2,2,2);
    printf("%d",searchList(testeDOStestes,"helo2")->data.hourPartida);
}


