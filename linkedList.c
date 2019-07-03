#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

void print_list(struct linkedFlights *head) //esta função faz print dos voos todos
{
    struct linkedFlights *temp;
    for (temp = head; temp==NULL; temp = temp->son)
        printf("%s ->", temp->son->data.IdAirChegada);
    puts("");
}

struct linkedFlights *searchList(struct linkedFlights *head, char IdAirChegada_search[5])
// esta função procura e devolve um voo
{
    struct linkedFlights *temp;
    temp = head;
    while (temp != NULL)// percorre a lista de voos ate ao fim 
    {
        if (strcmp(temp->data.IdAirChegada, IdAirChegada_search) == 0) // se enconta o voo que estamos a pesquisar
        {
            return temp;//retorna-o
        }
        temp = temp->son;
    }
    return NULL;
}

bool search_fligths(struct linkedFlights *head,char IdAirChegada_search[5],
short hourPartida_search,short minutePartida_search) 
// esta função faz a verificação da existencia de um voo
{
    struct linkedFlights *temp;
    temp = head;
    while (temp != NULL) // percorre a lista de voos ate ao fim 
    {
        if (strcmp(temp->data.IdAirChegada, IdAirChegada_search) == 0)// se enconta o voo que estamos a pesquisar 
        {
            if (temp->data.hourPartida == hourPartida_search)
                if (temp->data.minutePartida == minutePartida_search)
                    return true;// verifca que podemos inserir o voo
        }
        temp = temp->son;
    }
    return false;
}

struct linkedFlights *add(struct linkedFlights *linkedFlights, char IdAirPartida[5], char IdAirChegada[5], short hourPartida,
    short minutePartida,
    short tempTotal) 
//esta função é responsavel pela adição de voos na linkedList de cada aeroproto
{
    if (!search_fligths(linkedFlights, IdAirChegada, hourPartida, minutePartida))
    //se nao existir o voo que queremos inserir então avançamos para inserção 
    {
        printf("+ novo voo %s %s %.2hd:%.2hd\n",IdAirPartida,IdAirChegada,hourPartida,minutePartida);
        struct linkedFlights *tempHEAD = malloc(sizeof(struct linkedFlights)); // aloca espaço par ao novo voo
        //setup do voo
        strcpy(tempHEAD->data.IdAirPartida, IdAirPartida);
        strcpy(tempHEAD->data.IdAirChegada, IdAirChegada);
        tempHEAD->data.hourPartida = hourPartida;
        tempHEAD->data.minutePartida = minutePartida;
        tempHEAD->data.tempTotal = tempTotal;
        if (linkedFlights != NULL) //se já existir voos
        {
            tempHEAD->son = linkedFlights;//a cabeça passa a ser o filho do novo no (voo)
        } else// se ainda não exite voos nesse aerporto
            tempHEAD->son = NULL;
        return tempHEAD;
    } else
        printf("+ voo %s %s %.2hd:%.2hd existe\n", IdAirPartida, IdAirChegada, hourPartida, minutePartida);
    return linkedFlights;
}

struct linkedFlights *add_from_disk(struct linkedFlights *linkedFlights, char IdAirPartida[5], char IdAirChegada[5], short hourPartida,
                          short minutePartida,
                          short tempTotal)
//esta função trata de adicionar os voos lidos do disco
{
    
    struct linkedFlights *tempHEAD = malloc(sizeof(struct linkedFlights));// aloca espaço par ao novo voo
    //setup do voo
    strcpy(tempHEAD->data.IdAirPartida, IdAirPartida);
    strcpy(tempHEAD->data.IdAirChegada, IdAirChegada);
    tempHEAD->data.hourPartida = hourPartida;
    tempHEAD->data.minutePartida = minutePartida;
    tempHEAD->data.tempTotal = tempTotal;
    if (linkedFlights != NULL) //se já existir voos
    {
       
        tempHEAD->son = linkedFlights;//a cabeça passa a ser o filho do novo no (voo)
      
    } else
        tempHEAD->son = NULL;
    return tempHEAD;
    
}



struct linkedFlights *remove_linkedFlights(struct linkedFlights *head,char IdAirPartida_remove[5],
char IdAirChegada_remove[5],short hourPartida,short minutePartida) 
//esta função remove um voo da lista do aeroporto correspondente
{
    struct linkedFlights *temp;
    struct linkedFlights *temp_pai=NULL;
    temp = head;
    while (temp != NULL)//percorre a lista dos voos
    {
        if (strcmp(temp->data.IdAirChegada, IdAirChegada_remove) == 0)//se for este o voo que queremos remover
        {
            if (temp->data.hourPartida == hourPartida)//se for este o voo que queremos remover
            {
                if (temp->data.minutePartida == minutePartida) //se for este o voo que queremos remover
                {
                    printf("+ voo %s %s %.2hd:%.2hd removido\n", IdAirPartida_remove, IdAirChegada_remove, hourPartida,
                           minutePartida);
                    if (temp_pai != NULL)//caso estejamos a remover do meio 
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
