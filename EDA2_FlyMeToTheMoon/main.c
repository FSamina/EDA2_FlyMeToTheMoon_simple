#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "bHeap.h"


#define ID_AIR_SIZE 5
#define ID_VOO_SIZE 7
#define INFINITO 287998561
#define MINUTOS_DIA 1440


short getMinutosDeHoras(short h, short m) {
    return h * 60 + m;
}

void somaMinutosAHoras(unsigned short *h, unsigned short *m, short minutosSoma) {
    short totalMinutos = 60 * *h + *m + minutosSoma;
    short horaMatematica = totalMinutos / 60;
    short novosMinutos = totalMinutos % 60;

    if (horaMatematica >= (short) 24) {
        horaMatematica = horaMatematica - 24;
    }
    if (novosMinutos == 60) {
        novosMinutos = 0;
        horaMatematica++;
        if (horaMatematica == (short) 24) {
            horaMatematica = 0;
        }
    }

    *h = horaMatematica;
    *m = novosMinutos;
}

void initializeSource(struct air *aeroportoPartida, short horaChegada, short minutoChegada) {
    unsigned int index = search(aeroportoPartida->Id);


    for (int i = 0; i < SIZE; i++)//inicializa todos os aeroportos
    {
        if (hashArray[i] != NULL) {
            hashArray[i]->tempoTotalDiskt = INFINITO;//Iniciliaza  tempoTotalDisk ao "+infinito"
            strcpy(hashArray[i]->vooP.IdAirPartida, "NIL");//marca um dummy
            hashArray[i]->hourProntoParaPartir=(short)0;
            hashArray[i]->minProntoParaPartir=(short)0;
        }
    }
    hashArray[index]->tempoTotalDiskt = 0;
    hashArray[index]->hourProntoParaPartir = (short) horaChegada;
    hashArray[index]->minProntoParaPartir = (short) minutoChegada;
}

void relax(struct air u, struct air *v,struct linkedFlights noDaLinkedList) 
{
    short htemp= noDaLinkedList.data.hourPartida;
    short mtemp= noDaLinkedList.data.minutePartida;
    int diffTempos=getMinutosDeHoras(noDaLinkedList.data.hourPartida,noDaLinkedList.data.minutePartida)-getMinutosDeHoras(u.hourProntoParaPartir,u.minProntoParaPartir);
    diffTempos=diffTempos+ noDaLinkedList.data.tempTotal + u.tempoTotalDiskt;
    if (diffTempos < v->tempoTotalDiskt)
    {
        
        v->tempoTotalDiskt=diffTempos;
        v->vooP=noDaLinkedList.data;
        somaMinutosAHoras(&noDaLinkedList.data.hourPartida,&noDaLinkedList.data.minutePartida,noDaLinkedList.data.tempTotal);
        v->hourProntoParaPartir=noDaLinkedList.data.hourPartida;
        v->minProntoParaPartir=noDaLinkedList.data.minutePartida;
        noDaLinkedList.data.hourPartida=htemp;
        noDaLinkedList.data.minutePartida=mtemp;
        decreaseKey(indexfinder(v),diffTempos);
    }  
}

bool printVoos(struct air* airFinal,char IdAirPartida[5])
{
    if (strcmp(airFinal->vooP.IdAirPartida,"NIL")!=0)//chegamos ao aeroporto inicial
    {
        if (!printVoos(searchAir(airFinal->vooP.IdAirPartida),IdAirPartida))
        {
            return false;
        }
        
    }else if (strcmp(airFinal->vooP.IdAirPartida,"NIL")==0 && strcmp(airFinal->Id,IdAirPartida)!=0)
    {
        return false;
    }
    
    if(strcmp(airFinal->vooP.IdAirPartida,"NIL")!=0)
    {
        printf("%-4s %-4s %.2hd:%.2hd",airFinal->vooP.IdAirPartida,airFinal->vooP.IdAirChegada,airFinal->vooP.hourPartida,airFinal->vooP.minutePartida);

        somaMinutosAHoras(&airFinal->vooP.hourPartida,&airFinal->vooP.minutePartida,airFinal->vooP.tempTotal);
        printf(" %.2hd:%.2hd\n",airFinal->vooP.hourPartida,airFinal->vooP.minutePartida);
        return true;
    }else
    {
        printf("De   Para Parte Chega\n==== ==== ===== =====\n");
        return true;
    }
    return false;
}


void dijkstra(struct air *aeroportoPartida,char IdAirChegada[5], short horaChegada, short minutoChegada) {
    struct air tempAir;//criamos o novo aeroporto
    struct linkedFlights *tempLista;//instancia das linked list para a percorrer
    
    initializeSource(aeroportoPartida, horaChegada, minutoChegada);//inicializa os aeroportos para a pesquisa
    CreateHeap();
    h->firstpop = true;

    for (int i = 0; i < SIZE; i++)//mete todos os aeroportos  na queue
    {
        if (hashArray[i] != NULL) {


            insert_Heap(*hashArray[i]);

        }
    }


    while (h->count != 0) 
    {
        
        
        tempAir = PopMin();
        
        if(strcmp(tempAir.Id,IdAirChegada)!=0)
        {
            tempLista = tempAir.linkedVoos;
            while (tempLista != NULL)//ver todos os voos de tempAir
            {
                if ((strcmp(tempAir.Id,aeroportoPartida->Id)==0 && getMinutosDeHoras(tempLista->data.hourPartida,tempLista->data.minutePartida)  >= getMinutosDeHoras(tempAir.hourProntoParaPartir,tempAir.minProntoParaPartir)) ||
                    getMinutosDeHoras(tempLista->data.hourPartida,tempLista->data.minutePartida)  >= getMinutosDeHoras(tempAir.hourProntoParaPartir,tempAir.minProntoParaPartir)+30)
                {
                    relax(tempAir,searchAir(tempLista->data.IdAirChegada),*tempLista);
                }else
                {
                    tempAir.tempoTotalDiskt=tempAir.tempoTotalDiskt+MINUTOS_DIA;
                    relax(tempAir,searchAir(tempLista->data.IdAirChegada),*tempLista);
                    tempAir.tempoTotalDiskt=tempAir.tempoTotalDiskt-MINUTOS_DIA;//porque o voo que vem a seguir usa o mesmo aeroporto (se Nº Voos >1 no aeroporto)
                }

                tempLista = tempLista->son;
                
            }
            
        }else
        {
            freeHeap();
            return;
        }
        
        
    }
    freeHeap();
}


void calcViagem(char IdAirPartida[5], char IdAirChegada[5], short hourChegadaAoAir, short minuteChegadaAoAirPartida)
{
    struct air* airFinal=searchAir(IdAirChegada);
    struct air* airPartida=searchAir(IdAirPartida);
    if (airPartida == NULL)
    {
        printf("+ aeroporto %s desconhecido\n",IdAirPartida);
        return;
    }
    if (airFinal == NULL)
    {
        printf("+ aeroporto %s desconhecido\n",IdAirChegada);
        return;
    }
    
    dijkstra(airPartida,IdAirChegada,hourChegadaAoAir,minuteChegadaAoAirPartida);
    
    if (printVoos(airFinal,IdAirPartida))
    {
        printf("Tempo de viagem: %u minutos\n",airFinal->tempoTotalDiskt);
    }else
    {
        printf("+ sem voos de %s para %s\n",IdAirPartida,IdAirChegada);
    }
    
    
    
    

}


void delVoo(char IdAirPartida[5], char IdAirChegada[5], short hourPartida, short minutePartida) {
    int hashIndex = search(IdAirPartida);
    int hashIndex_chegada = search(IdAirChegada);
    if (hashIndex != -1 && hashIndex_chegada != -1)
        hashArray[hashIndex]->linkedVoos = remove_linkedFlights(hashArray[hashIndex]->linkedVoos, IdAirPartida,
                                                                IdAirChegada, hourPartida,
                                                                minutePartida);
    else
        printf("+ voo %s %s %.2hd:%.2hd inexistente\n", IdAirPartida, IdAirChegada, hourPartida, minutePartida);

}

void intrudVoo(char IdAirPartida[5], char IdAirChegada[5], short hPartida, short mPartida,
               short tempoDeVoo)
{
    int hashIndex = search(IdAirPartida);
    int hashIndex_chegada = search(IdAirChegada);
    if (hashIndex != -1 && hashIndex_chegada != -1)
        hashArray[hashIndex]->linkedVoos = add(hashArray[hashIndex]->linkedVoos, IdAirPartida, IdAirChegada, hPartida,
                                               mPartida,
                                               tempoDeVoo);
    else if (hashIndex == -1)
        printf("+ aeroporto %s desconhecido\n", IdAirPartida);
    else
        printf("+ aeroporto %s desconhecido\n", IdAirChegada);

}


void intrudAir(char key[5])//recebe como argumento codigo e hora local
{
    bool check;
    struct air *novoAir = (struct air *) malloc(sizeof(struct air));//criamos o novo aeroporto
    strcpy(novoAir->Id, key);
    novoAir->linkedVoos = NULL;
    check = insert(novoAir);
    if (check) {
        printf("+ novo aeroporto %s\n", novoAir->Id);
    } else {
        printf("+ aeroporto %s existe\n", novoAir->Id);
    }
        
}

int main(void) {
    char cod[5] = "";
    openTable_FMTTM();
    enter_FMTTM();
    char idAir[ID_AIR_SIZE] = "";//Declara e inicializa o array de chars a 0
    char idAirPartida[ID_AIR_SIZE] = "";//Declara e inicializa o array de chars a 0
    char idAirDestino[ID_AIR_SIZE] = "";//Declara e inicializa o array de chars a 0
    short hLocal = 0;
    short mLocal = 0;
    short duracaoVoo = 0;

    while (scanf("%s", cod) != EOF)// enquanto houver mais linhas tem valor bool true
    {
        if (strcmp(cod, "X") == 0) {
            exit_FMTTM();
            //Termina o programa
            return 0;
        } else if (strcmp(cod, "AI") == 0) {

            scanf("%s", idAir);
            intrudAir(idAir);
        } else if (strcmp(cod, "FI") == 0) {
            scanf("%s %s %hd:%hd %hd", idAirPartida, idAirDestino, &hLocal, &mLocal, &duracaoVoo);
            intrudVoo(idAirPartida, idAirDestino, hLocal, mLocal, duracaoVoo);
        } else if (strcmp(cod, "FD") == 0) {
         
            scanf("%s %s %hd:%hd", idAirPartida, idAirDestino, &hLocal, &mLocal);

            delVoo(idAirPartida, idAirDestino, hLocal, mLocal);
        } else if (strcmp(cod, "TR") == 0) {
       
            scanf("%s %s %hd:%hd", idAirPartida, idAirDestino, &hLocal, &mLocal);
            calcViagem(idAirPartida, idAirDestino, hLocal, mLocal);
        }

    }
    return 0;
}
