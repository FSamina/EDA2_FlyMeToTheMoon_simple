#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disk.h"


void exit_FMTTM()//Alterar o nome
{
    fseek(file_ht,0,SEEK_SET);
    fseek(file_ll,0,SEEK_SET);
    for (int i = 0; i < SIZE; ++i) {
        if (hashArray[i] != NULL) {
            //puts("AQUI NO EXIT\n");
            fprintf(file_ht, "%s\n", hashArray[i]->Id);
            //printf("i_exit:%i",i);
            struct linkedFlights *temp = hashArray[i]->linkedVoos;
            while (temp != NULL) {
                fprintf(file_ll, "%s %hd %hd %hd\n", temp->data.IdAirChegada, temp->data.hourPartida,
                        temp->data.minutePartida, temp->data.tempTotal);
                temp = temp->son;
            }
            fprintf(file_ll, "- 0 0 0\n");
        } else
            fprintf(file_ht, "0\n");
    }


}

void enter_FMTTM() {
    char id_temp[5];
    char IdAirChegada_t[5];
    short hourPartida_t;
    short minutePartida_t;
    short tempTotal_t;
    for (int i = 0; i < SIZE; ++i) {
        if (fscanf(file_ht, "%s", id_temp) == EOF)
            i = SIZE;
        else if (strcmp(id_temp, "0") != 0) {
            struct air *novoAir = (struct air *) malloc(sizeof(struct air));//criamos o novo aeroporto
            strcpy(novoAir->Id, id_temp);
            novoAir->linkedVoos = NULL;
            hashArray[i] = novoAir;
            //printf("i_enter:%i",i);
            while (fscanf(file_ll, "%s %hd %hd %hd", IdAirChegada_t, &hourPartida_t, &minutePartida_t, &tempTotal_t) !=
                   0) {
                if (strcmp(IdAirChegada_t, "-") != 0)
                    hashArray[i]->linkedVoos = add_from_disk(hashArray[i]->linkedVoos, id_temp, IdAirChegada_t, hourPartida_t,
                                                   minutePartida_t,
                                                   tempTotal_t);
                else break;
            }
        }

    }

}

void openTable_FMTTM() {

    file_ht = fopen(FNAMEHT, "r+");
    if (file_ht == NULL) {
        file_ht = fopen(FNAMEHT, "w+");
    }
    if (file_ht == NULL) {
        exit(6);
    }

    file_ll = fopen(FNAMELL, "r+");
    if (file_ll == NULL) {
        file_ll = fopen(FNAMELL, "w+");
    }
    if (file_ll == NULL) {
        exit(6);
    }
    
}