#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "bHeap.h"


#define ID_AIR_SIZE 5
#define ID_VOO_SIZE 7
#define INFINITO 65535
#define MINUTOS_DIA 1440

// INITIALIZE-SINGLE-SOURCE(G, s)
//    1 for each vertex v in G.V do
// 2 v.d <- INFINITY // peso do caminho mais curto de s a v
// 3 v.p <- NIL // predecessor de v nesse caminho
// 4 s.d <- 0
short getMinutosDeHoras(short h,short m)
{
    return h*60+m;
}

void somaMinutosAHoras(unsigned short *h,unsigned short *m,short minutosSoma)
{
    short totalMinutos = 60* *h+*m+minutosSoma;
    short horaMatematica= totalMinutos/60;
    short novosMinutos= totalMinutos%60;
     
    if (horaMatematica>=(short)24)
    {
        horaMatematica= horaMatematica-24;
    }
    if(novosMinutos == 60)
    {
        novosMinutos=0;
        horaMatematica++;
        if (horaMatematica==(short)24)
        {
            horaMatematica=0;
        }  
    }
    
    *h=horaMatematica;
    *m=novosMinutos;
}

void initializeSource(struct air *aeroportoPartida,short horaChegada,short minutoChegada)
{
    unsigned int index= search(aeroportoPartida->Id);

    //printf("%s\n",hashArray[index]->Id);
    if (index ==-1)
    {
        puts("Endereço incorreto no inicialize Source\n");
        return;
    }
    
    for (int i = 0; i < SIZE; i++)//inicializa todos os aeroportos
    {
        if (hashArray[i] != NULL)
        {
            hashArray[i]->tempoTotalDiskt = INFINITO;//Iniciliaza  tempoTotalDisk ao "+infinito"
            strcpy(hashArray[i]->vooP.IdAirPartida,"NIL");//marca um dummy
            //hashArray[i]->hourProntoParaPartir=(short)-1;
            //hashArray[i]->minProntoParaPartir=(short)-1;
        }
    }
    hashArray[index]->tempoTotalDiskt = 0;
    hashArray[index]->hourProntoParaPartir=(short)horaChegada;
    hashArray[index]->minProntoParaPartir=(short)minutoChegada;
}

void relax(struct air u, struct air *v,struct linkedFlights noDaLinkedList) 
{
    short htemp= noDaLinkedList.data.hourPartida;
    short mtemp= noDaLinkedList.data.minutePartida;
    
    if (v ==NULL)
    {
        puts("no relax ha erro\n");
        return;
    }
    unsigned short diffTempos=getMinutosDeHoras(noDaLinkedList.data.hourPartida,noDaLinkedList.data.minutePartida)-getMinutosDeHoras(u.hourProntoParaPartir,u.minProntoParaPartir);
    diffTempos=diffTempos+30+ noDaLinkedList.data.tempTotal + u.tempoTotalDiskt;
    if (diffTempos < v->tempoTotalDiskt)
    {
        v->tempoTotalDiskt=diffTempos;
        v->vooP=noDaLinkedList.data;
        somaMinutosAHoras(&noDaLinkedList.data.hourPartida,&noDaLinkedList.data.minutePartida,noDaLinkedList.data.tempTotal+30);
        v->hourProntoParaPartir=noDaLinkedList.data.hourPartida;
        v->minProntoParaPartir=noDaLinkedList.data.minutePartida;
        noDaLinkedList.data.hourPartida=htemp;
        noDaLinkedList.data.minutePartida=mtemp;
    }  
}

bool printVoos(struct air* airFinal,char IdAirPartida[5])
{
    if (strcmp(airFinal->vooP.IdAirPartida,"NIL")!=0)//chegamos ao aeroporto inicial
    {
        if (printVoos(searchAir(airFinal->vooP.IdAirPartida),IdAirPartida))
        {
            return false;
        }
        
    }else if (strcmp(airFinal->vooP.IdAirPartida,"NIL")==0 && strcmp(airFinal->Id,IdAirPartida)!=0)
    {
        return false;
    }
    
    if(strcmp(airFinal->vooP.IdAirPartida,"NIL")!=0)
    {
        struct air* temp = searchAir(airFinal->vooP.IdAirPartida);
        somaMinutosAHoras(&airFinal->vooP.hourPartida,&airFinal->vooP.minutePartida,airFinal->vooP.tempTotal);
        printf("%s %s  %.2hd:%.2hd %.2hd:%.2hd\n",airFinal->vooP.IdAirPartida,airFinal->vooP.IdAirChegada,temp->linkedVoos->data.hourPartida,temp->linkedVoos->data.minutePartida,airFinal->vooP.hourPartida,airFinal->vooP.minutePartida);
        return true;
    }else
    {
        printf("De   Para Parte Chega\n==== ==== ===== =====\n");
        return true;
    }
    return false;
    

}

// RELAX(u, v, w)
//    1 if u.d + w(u,v) < v.d then
//    2     v.d <- u.d + w(u,v)
// 3 v.p <- u
void dijkstra(struct air *aeroportoPartida,short horaChegada,short minutoChegada) {
    struct air tempAir;//criamos o novo aeroporto
    struct linkedFlights* tempLista;//instancia das linked list para a percorrer
    initializeSource(aeroportoPartida,horaChegada,minutoChegada);//inicializa os aeroportos para a pesquisa
    CreateHeap();
    h->firstpop=true;
    
    for (int i = 0; i < SIZE; i++)//mete todos os aeroportos  na queue
    {
        if (hashArray[i] != NULL) {
                            

            insert_Heap(*hashArray[i]);

        }
    }
 
    
    while (h->count != 0) 
    {
        tempAir = PopMin();
        tempLista = tempAir.linkedVoos;
        while (tempLista!=NULL)//ver todos os voos de tempAir
        {
            

            if (getMinutosDeHoras(tempLista->data.hourPartida,tempLista->data.minutePartida) > getMinutosDeHoras(tempAir.hourProntoParaPartir,tempAir.minProntoParaPartir))
            {
                relax(tempAir,searchAir(tempLista->data.IdAirChegada),*tempLista);
            }else
            {
                tempAir.tempoTotalDiskt=tempAir.tempoTotalDiskt+MINUTOS_DIA;
                relax(tempAir,searchAir(tempLista->data.IdAirChegada),*tempLista);
                tempAir.tempoTotalDiskt=tempAir.tempoTotalDiskt-MINUTOS_DIA;//porque o voo que vem a seguir usa o mesmo aeroporto (se Nº Voos >1 no aeroporto)
            }
            tempLista=tempLista->son;
        }
    }

}



//TR <aeroporto-partida> <aeroporto-destino> <hora-chegada-aeroporto>
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
    
    dijkstra(airPartida,hourChegadaAoAir,minuteChegadaAoAirPartida);
        // De   Para Parte Chega
// ==== ==== ===== =====
    //printf("De   Para Parte Chega\n==== ==== ===== =====\n");
    if (printVoos(airFinal,IdAirPartida))
    {
        printf("Tempo de viagem: %hu minutos\n",airFinal->tempoTotalDiskt);
    }else
    {
        printf("+ sem voos de %s para %s\n",IdAirPartida,IdAirChegada);
    }
    
    
    
    

}


//FD <aeroporto-partida> <aeroporto-destino> <hora-partida>
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

//FI <c´odigo> <aeroporto-partida> <aeroporto-destino> <hora-partida> <dura¸c~ao>
void intrudVoo(char IdAirPartida[5], char IdAirChegada[5], short hPartida, short mPartida,
               short tempoDeVoo)//temos de addicionar aerporto de partida
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
    //struct voos* novoVoo = (struct voos*) malloc(sizeof(struct voos));//criamos o novo aeroporto
    //strcpy(novoVoo->IdAirChegada,IdAirChegada);
    //novoVoo->hourPartida =hPartida;
    //novoVoo->minutePartida=mPartida;
    //novoVoo->tempTotal=tempoDeVoo;
    //enviar para  linked list


    //write(fileVoo,hashIndex,pos,novoVoo);
}

//AI <código> <fuso-hor´ario>
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
    //openTable_FMTTM();
    //enter_FMTTM();
    char idAir[ID_AIR_SIZE] = "";//Declara e inicializa o array de chars a 0
    char idAirPartida[ID_AIR_SIZE] = "";//Declara e inicializa o array de chars a 0
    char idAirDestino[ID_AIR_SIZE] = "";//Declara e inicializa o array de chars a 0
    short hLocal = 0;
    short mLocal = 0;
    short duracaoVoo = 0;
    //AI LIS 00:00

    while (scanf("%s", cod) != EOF)// enquanto houver mais linhas // le strings
    {
        if (strcmp(cod, "X") == 0) {
            //exitTable(file,hashArray);
            //exit_FMTTM();
            //Termina o programa
            return -1;
        } else if (strcmp(cod, "AI") == 0) {

            scanf("%s", idAir);
            intrudAir(idAir);
        } else if (strcmp(cod, "FI") == 0) {
            //FI IB3111 PDL MAD 09:50 80
            scanf("%s %s %hd:%hd %hd", idAirPartida, idAirDestino, &hLocal, &mLocal, &duracaoVoo);
            intrudVoo(idAirPartida, idAirDestino, hLocal, mLocal, duracaoVoo);
            //printf("%s %s %s %hd:%hd %hd\n",idVoo,idAirPartida,idAirDestino,hLocal,mLocal,duracaoVoo);
        } else if (strcmp(cod, "FD") == 0) {
            //FD BA1
            scanf("%s %s %hd:%hd", idAirPartida, idAirDestino, &hLocal, &mLocal);

            delVoo(idAirPartida, idAirDestino, hLocal, mLocal);
        } else if (strcmp(cod, "TR") == 0) {
            //TR LIS PDL 00:00
            //TR <aeroporto-partida> <aeroporto-destino> <hora-chegada-aeroporto>
            scanf("%s %s %hd:%hd", idAirPartida, idAirDestino, &hLocal, &mLocal);
            calcViagem(idAirPartida, idAirDestino, hLocal, mLocal);
        }

    }


    // //5 Aeroportos de teste
    // struct air *itemA = malloc(sizeof(struct air));
    // char  arrA[5] = "LISB";
    // strcpy(itemA->Id,arrA);
    // itemA->flag =false;
    // insert(itemA);
    // struct air *itemB = malloc(sizeof(struct air));
    // char arrB[5] = "MADR";
    // strcpy(itemB->Id,arrB);
    // itemB->flag =false;
    // insert(itemB);
    // struct air *itemC =  malloc(sizeof(struct air));
    // char arrC[5] = "NY";
    // strcpy(itemC->Id,arrC);
    // itemC->flag =false;
    // insert(itemC);
    // struct air *itemD =  malloc(sizeof(struct air));
    // char arrD[5] = "PORT";
    // strcpy(itemD->Id,arrD);
    // itemD->flag =false;
    // insert(itemD);
    // struct air *itemE =  malloc(sizeof(struct air));
    // char arrE[5] = "LIBA";
    // strcpy(itemE->Id,arrE);
    // itemE->flag =false;
    // insert(itemE);

    // item = search("PORT");

    // if(item != NULL) {
    //     printf("Element found: %s\n", item->Id);
    // } else {
    //     printf("Element not found\n");
    // }

    // delete(item);
    // item = search("LISB");

    // if(item != NULL) {
    //     printf("Element found: %s\n", item->Id);
    // } else {
    //     printf("Element not found\n");
    // }

    //display();


    //disk save




    return -1;
}