#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disk.h"


void exit_FMTTM()//Alterar o nome
{
    for (int i = 0; i < SIZE; ++i) {
        if (hashArray[i] != NULL) {
            fprintf(file, "%s\n", hashArray[i]->Id);
            struct linkedFlights *temp = hashArray[i]->linkedVoos;
            while (temp != NULL) {
                fprintf(file, "%s %hd %hd %hd\n", temp->data.IdAirChegada, temp->data.hourPartida,
                        temp->data.minutePartida, temp->data.tempTotal);
                temp = temp->son;
            }
        } else
            fprintf(file, "0");
        fprintf(file, "- 0 0 0\n");
    }


}

void enter_FMTTM() {
    char id_temp[5];
    char IdAirChegada_t[5];
    short hourPartida_t;
    short minutePartida_t;
    short tempTotal_t;
    int i = 0;
    int i_temp;
    while (i < SIZE) {
        i++;
        if (fscanf(file, "%s", id_temp) == EOF)
            i = SIZE;
        else if (strcmp(id_temp, "0") != 0) {
            struct air *novoAir = (struct air *) malloc(sizeof(struct air));//criamos o novo aeroporto
            strcpy(novoAir->Id, id_temp);
            novoAir->linkedVoos = NULL;
            hashArray[i] = novoAir;
            i_temp = 0;
            while (fscanf(file, "%s %hd %hd %hd", IdAirChegada_t, &hourPartida_t, &minutePartida_t, &tempTotal_t) !=
                   0) {
                i_temp++;
                if (strcmp(IdAirChegada_t, "-") != 0)
                    hashArray[i]->linkedVoos = add(hashArray[i]->linkedVoos, id_temp, IdAirChegada_t, hourPartida_t,
                                                   minutePartida_t,
                                                   tempTotal_t);
                else {
                    i += i_temp;
                    break;

                }
            }
        }

    }

}

void openTable_FMTTM() {
    file = fopen(FNAMET, "r+");
    if (file == NULL) {
        file = fopen(FNAMET, "w+");
    }
    if (file == NULL) {
        exit(6);
    }
}