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


short getMinutosDeHoras(short h, short m) //calcula os minutos de umas horas dadas
{
    return h * 60 + m;
}

void somaMinutosAHoras(unsigned short *h, unsigned short *m, short minutosSoma)//soma minutos a umas horas
{
    short totalMinutos = 60 * *h + *m + minutosSoma;// converte as horas para minutos
    short horaMatematica = totalMinutos / 60;// decobre novas horas
    short novosMinutos = totalMinutos % 60;// decobre os novos minutos

    if (horaMatematica >= (short) 24) //caso a hora for superior a 24
    {
        horaMatematica = horaMatematica - 24;// retiramos 24 para nao fujir do limites do fuso horario
    }
    if (novosMinutos == 60)// se os minutos forem iguais a 60 
    {
        novosMinutos = 0;
        horaMatematica++;//aumentamos a hora
        if (horaMatematica == (short) 24) //caso a hora for superior a 24
        {
            horaMatematica = 0; //metemos a hora a 0
        }
    }

    *h = horaMatematica;// escrevemos as novas horas no endereço das horas recebidas
    *m = novosMinutos;// escrevemos os novos minutos no endereço dos minutos recebidos
}
bool printVoos(struct air* airFinal,char IdAirPartida[5])// esta função é responsavel pelos prints dos caminbos encontrados
{
    if (strcmp(airFinal->vooP.IdAirPartida,"NIL")!=0)//Se chegamos ao aeroporto inicial entramos para o if
    {
        if (!printVoos(searchAir(airFinal->vooP.IdAirPartida),IdAirPartida))//se o aeroporto a que chegamos é mesmo o inicial
        {
            return false;
        }
        
    }else if (strcmp(airFinal->vooP.IdAirPartida,"NIL")==0 && strcmp(airFinal->id,IdAirPartida)!=0)// se nao existe caminho
    {
        return false;
    }
    
    if(strcmp(airFinal->vooP.IdAirPartida,"NIL")!=0)// existe um caminho para imprimir
    {
        printf("%-4s %-4s %.2hd:%.2hd",airFinal->vooP.IdAirPartida,airFinal->vooP.IdAirChegada,airFinal->vooP.hourPartida,airFinal->vooP.minutePartida);
        //calculamos as novas horas consoante o tempo que demoramos
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


void initializeSource(struct air *aeroportoPartida, short horaChegada, short minutoChegada)// inicializamos todos os aeroportos  para prepararmos o calculo de caminhos 
{
    unsigned int index = search(aeroportoPartida->id);// descobrimos a possição do aeroporto de onde partimos

    strcpy(hashArray[index]->vooP.IdAirPartida, "NIL");// inicializamos o vooP com a string NIL (estamos ciente que isto impede a existencia de um aeroporto com id= "NIL")
    hashArray[index]->tempoTotalDijkstra = 0;// inicializamos o "d" a 0
    hashArray[index]->hourProntoParaPartir = (short) horaChegada;// inicializamos as horas pronto a partir para o argumento
    hashArray[index]->minProntoParaPartir = (short) minutoChegada;// inicializamos os m inutos pronto a partir para o argumento
    insert_Heap(*hashArray[index]);//inserimos o primeiro no na heap

    for (int i = 0; i < SIZE_HASH_TABLE; i++)//inicializa todos os aeroportos
    {
        if (hashArray[i] != NULL&& i!=index)// se encontramos um aeropor vamos inicializa-lo 
        {
            hashArray[i]->tempoTotalDijkstra = INFINITO;//Iniciliaza  tempoTotalDisk ao "+infinito"
            strcpy(hashArray[i]->vooP.IdAirPartida, "NIL");//marca um dummy
            hashArray[i]->hourProntoParaPartir=(short)0;
            hashArray[i]->minProntoParaPartir=(short)0;
            
        }
        
    }
    
}

void relax(struct air u, struct air *v,struct linkedFlights noDaLinkedList)//vamos averiguar se encontramos um caminho melhor de um aeroporto para outro 
{
    short htemp= noDaLinkedList.data.hourPartida;//hora de partida do voo para nao perdemos estes dados depois de os alterar
    short mtemp= noDaLinkedList.data.minutePartida;//minutos de partida do voo para nao perdemos estes dados depois de os alterar
    
    // calculamos a dirença das horas de partida com as hroas a que podemos partir
    int diffTempos=getMinutosDeHoras(noDaLinkedList.data.hourPartida,noDaLinkedList.data.minutePartida)-getMinutosDeHoras(u.hourProntoParaPartir,u.minProntoParaPartir);
    diffTempos=diffTempos+ noDaLinkedList.data.tempTotal + u.tempoTotalDijkstra;//somamos a essa diferença o peso do voo que ja tinhamos com o peso do novo voo
   
    if (diffTempos < v->tempoTotalDijkstra)// se o tempo for menor então encontramos um novo caminho mais curto
    {
        if (!v->inHeap)//se nao tiver na heap vai para la
        {
            insert_Heap(*hashArray[search(v->id)]);
        }
        v->tempoTotalDijkstra=diffTempos;// ateramos o "d" para o melhor encontrado
        v->vooP=noDaLinkedList.data;// alteramos o vooP de V 
        // calculamos as novas horas prontos para partir quando pegamos este voo
        somaMinutosAHoras(&noDaLinkedList.data.hourPartida,&noDaLinkedList.data.minutePartida,noDaLinkedList.data.tempTotal);
        v->hourProntoParaPartir=noDaLinkedList.data.hourPartida;
        v->minProntoParaPartir=noDaLinkedList.data.minutePartida;
        noDaLinkedList.data.hourPartida=htemp;//hora de partida
        noDaLinkedList.data.minutePartida=mtemp;//minuto de partida
        decreaseKey(v->indexNaHeap,diffTempos);//garantimos que o aeroporto V na heap é reordenado na heap
    }  
}

void dijkstra(struct air *aeroportoPartida,char IdAirChegada[5], short horaChegada, short minutoChegada)
//esta função é a que prepara o processo do algoritmo de dijkstra
{
    struct air tempAir;//criamos o novo aeroporto
    struct linkedFlights *tempLista;//instancia das linked list para a percorrer
    createHeap();// inicalizamos a heap
    initializeSource(aeroportoPartida, horaChegada, minutoChegada);//inicializa os aeroportos para a pesquisa
    
    while (h->count != 0)// enquanto houver aeroportos na heap 
    {
        
        
        tempAir = popMin();//fazemos pop do aeroporto com d minimo
        if(strcmp(tempAir.id,IdAirChegada)!=0)// se o aeroporpt que fizemos pop é difernte do destino entramos no if
        {
            tempLista = tempAir.linkedVoos;// cabeça da linked list de voos do aeroporto que fizemos pop
            while (tempLista != NULL)//ver todos os voos de tempAir
            {
                //se podemos entrar a tempo neste  voo entramos no if
                if ((strcmp(tempAir.id,aeroportoPartida->id)==0 && getMinutosDeHoras(tempLista->data.hourPartida,tempLista->data.minutePartida)  >= getMinutosDeHoras(tempAir.hourProntoParaPartir,tempAir.minProntoParaPartir)) ||
                    getMinutosDeHoras(tempLista->data.hourPartida,tempLista->data.minutePartida)  >= getMinutosDeHoras(tempAir.hourProntoParaPartir,tempAir.minProntoParaPartir)+30)
                {
                    relax(tempAir,searchAir(tempLista->data.IdAirChegada),*tempLista);// averiguamos se  encontramos um cmainho mais curto
                }else// ja nao fomos a tempo de entrar no voo por isso entramos aqui
                {
                    tempAir.tempoTotalDijkstra=tempAir.tempoTotalDijkstra+MINUTOS_DIA;// somamos 1 dia ao "d"
                    relax(tempAir,searchAir(tempLista->data.IdAirChegada),*tempLista);// averiguamos se  encontramos um cmainho mais curto
                    tempAir.tempoTotalDijkstra=tempAir.tempoTotalDijkstra-MINUTOS_DIA;//porque o voo que vem a seguir usa o mesmo aeroporto (se Nº Voos >1 no aeroporto)
                }

                tempLista = tempLista->son;// vamos para o proximo voo na lista
                
            }
            
        }else
        {
            freeHeap();// libertamos a heap
            return;
        }
        
        
    }
    freeHeap();// libertamos a heap
}


void calcViagem(char IdAirPartida[5], char IdAirChegada[5], short hourChegadaAoAir, short minuteChegadaAoAirPartida)
//aqui começa todo o proceso de calculo de uma viagem
{
    struct air* airFinal=searchAir(IdAirChegada);//procuramos o aeroporto de chegada
    struct air* airPartida=searchAir(IdAirPartida);//procuramos o aeroporto de partida
    if (airPartida == NULL)// se nao existir
    {
        printf("+ aeroporto %s desconhecido\n",IdAirPartida);
        return;
    }
    if (airFinal == NULL)//se nao existir
    {
        printf("+ aeroporto %s desconhecido\n",IdAirChegada);
        return;
    }
    //como exite vamos ter em consiederação este percuso
    dijkstra(airPartida,IdAirChegada,hourChegadaAoAir,minuteChegadaAoAirPartida);
    
    if (printVoos(airFinal,IdAirPartida))// se foi possivel fazer encontrar um caminho
    {
        printf("Tempo de viagem: %u minutos\n",airFinal->tempoTotalDijkstra);
    }else
    {
        printf("+ sem voos de %s para %s\n",IdAirPartida,IdAirChegada);
    }
    
    
    
    

}


void delVoo(char IdAirPartida[5], char IdAirChegada[5], short hourPartida, short minutePartida)
//esta função faz delete dos voos
{
    int hashIndex = search(IdAirPartida);//procuramos o aeroporto que contem o voo
    int hashIndex_chegada = search(IdAirChegada);// procuramos o aeroporto de chegada para garantimos que o voo existe sequer
    if (hashIndex != -1 && hashIndex_chegada != -1)// se existem estes aeroprotos então procuramos o voo
    //vamos ao aeroporto de partida e revovemos o voo da linkedlist
        hashArray[hashIndex]->linkedVoos = remove_linkedFlights(hashArray[hashIndex]->linkedVoos, IdAirPartida,
                                                                IdAirChegada, hourPartida,
                                                                minutePartida);
    else
        printf("+ voo %s %s %.2hd:%.2hd inexistente\n", IdAirPartida, IdAirChegada, hourPartida, minutePartida);

}

void intrudVoo(char IdAirPartida[5], char IdAirChegada[5], short hPartida, short mPartida,
               short tempoDeVoo)//nesta função adicionamos novos voos aos aeroportos
{
    int hashIndex = search(IdAirPartida);//procuramos o aeroporto que contem o voo
    int hashIndex_chegada = search(IdAirChegada);// procuramos o aeroporto de chegada para garantimos que o voo existe sequer
    if (hashIndex != -1 && hashIndex_chegada != -1)// se existem estes aeroprotos então podemos tentar inserir os voos
        //vamos inserir o voo (na função add garantim os que nao inserimos voos iguais)
        hashArray[hashIndex]->linkedVoos = add(hashArray[hashIndex]->linkedVoos, IdAirPartida, IdAirChegada, hPartida,
                                               mPartida,
                                               tempoDeVoo);
    else if (hashIndex == -1)
        printf("+ aeroporto %s desconhecido\n", IdAirPartida);
    else
        printf("+ aeroporto %s desconhecido\n", IdAirChegada);

}

void intrudAir(char key[5])//esta função insere um aeroporto na hashtable
{
    bool check;
    struct air *novoAir = (struct air *) malloc(sizeof(struct air));//criamos o novo aeroporto
    strcpy(novoAir->id, key);
    novoAir->linkedVoos = NULL;
    check = insert(novoAir);
    // se a inserção tiver sido feita com sucesso devolve valor boleano verdadeiro caso contrario devolve false
    if (check) {
        printf("+ novo aeroporto %s\n", novoAir->id);
    } else {
        printf("+ aeroporto %s existe\n", novoAir->id);
    }
        
}

int main(void)
{
    char cod[5] = "";//Declara e inicializa o array de chars a ""
    openTable_FMTTM();// inicia os ficheiros
    enter_FMTTM();// carrega dados anteriores em disco par a memoria
    char idAir[ID_AIR_SIZE] = "";//Declara e inicializa o array de chars a ""
    char idAirPartida[ID_AIR_SIZE] = "";//Declara e inicializa o array de chars a ""
    char idAirDestino[ID_AIR_SIZE] = "";//Declara e inicializa o array de chars a ""
    short hLocal = 0;//Declara e inicializa o short para o valor 0
    short mLocal = 0;//Declara e inicializa o short para o valor 0
    short duracaoVoo = 0;//Declara e inicializa o short para o valor 0
    

    while (scanf("%s", cod) != EOF)// enquanto houver mais linhas // le strings
    {
        if (strcmp(cod, "X") == 0)//
        {
            exit_FMTTM();// termina execução mas antes mete tudo em memoria secundaria
            //Termina o programa
            return 0;
        } else if (strcmp(cod, "AI") == 0) 
        {
            scanf("%s", idAir);
            intrudAir(idAir);
        } else if (strcmp(cod, "FI") == 0) 
        {
            scanf("%s %s %hd:%hd %hd", idAirPartida, idAirDestino, &hLocal, &mLocal, &duracaoVoo);
            intrudVoo(idAirPartida, idAirDestino, hLocal, mLocal, duracaoVoo);
        } else if (strcmp(cod, "FD") == 0) 
        {
            scanf("%s %s %hd:%hd", idAirPartida, idAirDestino, &hLocal, &mLocal);

            delVoo(idAirPartida, idAirDestino, hLocal, mLocal);
        } else if (strcmp(cod, "TR") == 0) 
        {
            scanf("%s %s %hd:%hd", idAirPartida, idAirDestino, &hLocal, &mLocal);
            calcViagem(idAirPartida, idAirDestino, hLocal, mLocal);
        }

    }
    return 0;
}
