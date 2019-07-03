#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disk.h"


void exit_FMTTM()// esta função guarda a hashtable em disco
{
    fseek(file_ht,0,SEEK_SET);//inicia o ponteiro na primeira posição de ambos os ficheiros
    fseek(file_ll,0,SEEK_SET);
    for (int i = 0; i < SIZE_HASH_TABLE; ++i) // percorre toda a hasatble e gaurda no disco
    {
        if (hashArray[i] != NULL) // se tivermos num voo difernte de null vamos guarda-lo
        {
            fprintf(file_ht, "%s\n", hashArray[i]->id);
            struct linkedFlights *temp = hashArray[i]->linkedVoos;
            while (temp != NULL)//guarda os voos correspondentes  de cada aeroporto
            {
                fprintf(file_ll, "%s %hd %hd %hd\n", temp->data.IdAirChegada, temp->data.hourPartida,
                        temp->data.minutePartida, temp->data.tempTotal);
                temp = temp->son;
            }
            fprintf(file_ll, "- 0 0 0\n");//terminador dos voos
        } else
            fprintf(file_ht, "0\n");//separa os aeroportos
    }


}

void enter_FMTTM()//inicaliza os dados anteriores para a memoria RAM
{
    char id_temp[5];
    char IdAirChegada_t[5];
    short hourPartida_t;
    short minutePartida_t;
    short tempTotal_t;
    for (int i = 0; i < SIZE_HASH_TABLE; ++i)// percorremos o ficheiro e copiamos o seu conteudo para a hashtable 
    {
        struct air *novoAir = (struct air *) malloc(sizeof(struct air));//criamos o novo aeroporto        
        if (fscanf(file_ht, "%s", id_temp) == EOF)
            i = SIZE_HASH_TABLE;
        else if (strcmp(id_temp, "0") != 0) {
            strcpy(novoAir->id, id_temp);
            novoAir->linkedVoos = NULL;
            hashArray[i] = novoAir;
            while (fscanf(file_ll, "%s %hd %hd %hd", IdAirChegada_t, &hourPartida_t, &minutePartida_t, &tempTotal_t) !=0) 
            {
                if (strcmp(IdAirChegada_t, "-") != 0)
                    hashArray[i]->linkedVoos = add_from_disk(hashArray[i]->linkedVoos, id_temp, IdAirChegada_t, hourPartida_t,
                                                   minutePartida_t,
                                                   tempTotal_t);
                else break;
            }
            
        }
    }

}

void openTable_FMTTM()//incializa os ficheiros
{

    file_ht = fopen(FNAMEHT, "r+");//se ja existir trabalhos com o que existe
    if (file_ht == NULL) 
    {
        file_ht = fopen(FNAMEHT, "w+");//se não tarbalhos com um novo
    }
    if (file_ht == NULL) 
    {
        exit(6);
    }

    file_ll = fopen(FNAMELL, "r+");//se ja existir trabalhos com o que existe
    if (file_ll == NULL) 
    {
        file_ll = fopen(FNAMELL, "w+");//se não tarbalhos com um novo
    }
    if (file_ll == NULL) 
    {
        exit(6);
    }
    
}