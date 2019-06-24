#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "hashtable.h"
#include "linkedList.c"

#define ID_AIR_SIZE 5
#define ID_VOO_SIZE 7

// INITIALIZE-SINGLE-SOURCE(G, s)
//    1 for each vertex v in G.V do
// 2 v.d <- INFINITY // peso do caminho mais curto de s a v
// 3 v.p <- NIL // predecessor de v nesse caminho
// 4 s.d <- 0

void initializeSource(struct air *aeroportoPartida) {
    aeroportoPartida->tempoTotalDiskt = 0;
}

void relax(struct air *u, struct air *v) {
    if (u->tempoTotalDiskt /* + Tempo do caminho(u ,v) */ < v->tempoTotalDiskt) {
        v->tempoTotalDiskt = u->tempoTotalDiskt /* + Tempo do caminho(u ,v) */;
        strcpy(v->IdPrecessor, u->IdPrecessor);
    }


}

// RELAX(u, v, w)
//    1 if u.d + w(u,v) < v.d then
//    2     v.d <- u.d + w(u,v)
// 3 v.p <- u
void dijkstra(struct air *aeroportoPartida) {
    initializeSource(aeroportoPartida);
    //temos de ter uma queue com prioridade
}


//TR <aeroporto-partida> <aeroporto-destino> <hora-chegada-aeroporto>
void calcViagem(char IdAirPartida[5], char IdAirChegada[5], short hourPartida, short minutePartida) {
    //Podes começar a pensar sobre isto caralho!

}

//FD <aeroporto-partida> <aeroporto-destino> <hora-partida>
void delVoo(char IdAirPartida[5], char IdAirChegada[5], short hourPartida, short minutePartida) {
    int hashIndex = search(IdAirPartida);
    hashArray[hashIndex]->linkedVoos = remove_linkedFlights(hashArray[hashIndex]->linkedVoos, IdAirChegada,hourPartida, minutePartida);
}

//FI <c´odigo> <aeroporto-partida> <aeroporto-destino> <hora-partida> <dura¸c~ao>
void intrudVoo(char IdAirPartida[5], char IdAirChegada[5], short hPartida, short mPartida,
               short tempoDeVoo)//temos de addicionar aerporto de partida
{
    int hashIndex = search(IdAirPartida);
    hashArray[hashIndex]->linkedVoos = add(hashArray[hashIndex]->linkedVoos, IdAirChegada, hPartida, mPartida,
                                           tempoDeVoo);

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
    novoAir->tempoTotalDiskt = -1;
    novoAir->linkedVoos = NULL;
    strcpy(novoAir->IdPrecessor, "NULL");
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

    char idAir[ID_AIR_SIZE] = "";//Declara e inicializa o array de chars a 0
    char idVoo[ID_VOO_SIZE] = "";//Declara e inicializa o array de chars a 0
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
            printf("%s\n", idVoo);
        } else if (strcmp(cod, "TR") == 0) {
            //TR LIS PDL 00:00
            //TR <aeroporto-partida> <aeroporto-destino> <hora-chegada-aeroporto>
            scanf("%s %s %hd:%hd", idAirPartida, idAirDestino, &hLocal, &mLocal);
            calcViagem(idAirPartida, idAirDestino, hLocal, mLocal);
            printf("%s %s %hd:%hd\n", idAirPartida, idAirDestino, hLocal, mLocal);
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