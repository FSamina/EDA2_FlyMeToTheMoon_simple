#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disk.h"


void exit(){
    for (int i = 0; i < SIZE; ++i) {
        if(strcmp(hashArray[1]->Id,"\000")!=0) {
            fprintf(file, "%s\n", hashArray[i]->Id);
            struct linkedFlights *temp=hashArray[i]->linkedVoos;
            while (temp != NULL) {
                fprintf(file,"%s %hd %hd %hd\n",temp->data.IdAirChegada,temp->data.hourPartida,temp->data.minutePartida,temp->data.tempTotal);
                temp=temp->son;
            }
        } else
            fprintf(file,"0");
        fprintf(file,"\n");
    }


}

void enter(){
    char id_temp[5];
    char IdAirChegada_t[5];
    short hourPartida_t;
    short minutePartida_t;
    short tempTotal_t;
    for (int i = 0; i < SIZE; ++i) {
        fscanf(file, "%s",id_temp);
        if(strcmp(id_temp,"0")!=0){
            bool check;
            struct air *novoAir = (struct air *) malloc(sizeof(struct air));//criamos o novo aeroporto
            strcpy(novoAir->Id, id_temp);
            novoAir->tempoTotalDiskt = -1;
            novoAir->linkedVoos = NULL;
            strcpy(novoAir->IdPrecessor, "NULL");
            check = insert(novoAir);
            if(!check)
                exit(15);
            while(fscanf(file,"%s %hd %hd %hd\n",IdAirChegada_t,&hourPartida_t,&minutePartida_t,&tempTotal_t)){
                hashArray[i]->linkedVoos = add(hashArray[i]->linkedVoos, IdAirChegada_t, hourPartida_t, minutePartida_t,
                                                       tempTotal_t);
            }
        }

    }

}

void openTable() {
    file = fopen(FNAMET, "r+");
    if (file == NULL) {
        file = fopen(FNAMET, "w+");
    }if (file == NULL) {
        exit(6);
    }
}
