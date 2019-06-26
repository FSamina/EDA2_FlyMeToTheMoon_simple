#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "bHeap.h"


#define ID_AIR_SIZE 5
#define ID_VOO_SIZE 7
#define INFINITO 65535

// INITIALIZE-SINGLE-SOURCE(G, s)
//    1 for each vertex v in G.V do
// 2 v.d <- INFINITY // peso do caminho mais curto de s a v
// 3 v.p <- NIL // predecessor de v nesse caminho
// 4 s.d <- 0

short* somaMinutosAHoras(short h,short m,short minutosSoma)
{
    short arrayH[1];
    short totalMinutos = 60*h+m+minutosSoma;
    float horaMatematica= totalMinutos/60;
    short horaMatematicaSemFloat= (short)horaMatematica;//Horas completas
    horaMatematica= horaMatematica-horaMatematicaSemFloat;//Minutos restantes
    float novosMinutos= horaMatematica*60;
    short novosMinutosShort = roundf(novosMinutos);
   

    if (horaMatematicaSemFloat>=24)
    {
        horaMatematicaSemFloat= horaMatematicaSemFloat-24;
    }
    if(novosMinutos == 60)
    {
        novosMinutos=0;
        horaMatematicaSemFloat++;
        if (horaMatematicaSemFloat==24)
        {
            horaMatematicaSemFloat==0;
        }  
    }
    arrayH[0]=horaMatematicaSemFloat;
    arrayH[1]=novosMinutosShort;
    return arrayH;
} 

void initializeSource(struct air *aeroportoPartida)
{
    aeroportoPartida->tempoTotalDiskt = 0;
    for (int i = 0; i < SIZE; i++)//inicializa todos os aeroportos
    {
        if (hashArray[i] != NULL) {
            hashArray[i]->tempoTotalDiskt = 1450;//Iniciliaza  tempoTotalDisk ao "+infinito"
            strcpy(hashArray[i]->vooP, "NIL");
        }
    }
}

// void relax(struct air u, struct air *v,int vooDuração) {
//     if (u.tempoTotalDiskt + vooDuração/* + Tempo do caminho(u ,v) */ < v->tempoTotalDiskt) {
//         v->tempoTotalDiskt = u.tempoTotalDiskt+ vooDuração /* + Tempo do caminho(u ,v) */;
//         strcpy(v->IdPrecessor, u.IdPrecessor);
//     }
// }

// RELAX(u, v, w)
//    1 if u.d + w(u,v) < v.d then
//    2     v.d <- u.d + w(u,v)
// 3 v.p <- u
void dijkstra(struct air *aeroportoPartida) {
    struct air tempAir;//criamos o novo aeroporto
    struct linkedFlights* tempLista;//instancia das linked list para a percorrer
    unsigned int possivelIndexHash=1;
    initializeSource(aeroportoPartida);
    for (int i = 0; i < SIZE; i++)//mete todos os aeroportos  na queue
    {
        if (hashArray[i] != NULL) {
            insert(hashArray[i]);
        }
    }
    while (h->count != 0) {

        tempAir = PopMin();
        push_Stack(tempAir);
        tempLista = tempAir.linkedVoos;
        //ver todos os voos de cada aeroporto
        while (tempLista!=NULL)
        {
            //pocura a posição do aeroporto do voo em questão
            possivelIndexHash= search(tempLista->data.IdAirChegada);
            while (strcpy(hashArray[possivelIndexHash]->Id,tempLista->data.IdAirChegada)!=0)//confirma que encontramos o aeroporto de chegada
            {
                possivelIndexHash++;
                //wrap around the table
                possivelIndexHash %= SIZE;//casu haja loop experimenta tirar isto
                
            }
            
            relax(tempAir,hashArray[possivelIndexHash],tempLista->data.tempTotal);
            tempLista=tempLista->son;
        }
    }
    
}



//TR <aeroporto-partida> <aeroporto-destino> <hora-chegada-aeroporto>
void calcViagem(char IdAirPartida[5], char IdAirChegada[5], short hourChegadaAoAir, short minuteChegadaAoAirPartida) 
{
    struct air data;
    struct air peek;
    short novaHora=-1;
    short novaMin=-1;

    int possivelIndexHash=-1;
    possivelIndexHash= search(IdAirPartida);
            while (strcpy(hashArray[possivelIndexHash]->Id,IdAirPartida)!=0)//confirma que encontramos o aeroporto de chegada
            {
                possivelIndexHash++;
                //wrap around the table
                possivelIndexHash %= SIZE;//casu haja loop experimenta tirar isto
                
            }
    dijkstra(hashArray[possivelIndexHash]);    
  
// De   Para Parte Chega
// ==== ==== ===== =====
// CSOH VYN  00:40 19:38
// VYN  EVX  21:44 02:56
// EVX  HATP 06:16 19:02
// HATP JKPF 22:16 23:40
// JKPF NHAX 11:08 11:55
// NHAX DWG  08:10 05:18
// Tempo de viagem: 6228 minutos

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
    // FILE *file;
    // FILE *fileVoos;
    // fileVoos = abrir();
    // file = openTable();
    //testar hastable

    char cod[5] = "";
    openTable_FMTTM();
    enter_FMTTM();
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
            exit_FMTTM();
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
            //printf("%s %s %hd:%hd\n", idAirPartida, idAirDestino, hLocal, mLocal);
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