// Implementação adaptada de  https://gist.github.com/sudhanshuptl/d86da25da46aa3d060e7be876bbdb343
// e de https://www.geeksforgeeks.org/binary-heap/
/*
Min Heap implementation in c
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bHeap.h"
/*
 Array Implementation of MinHeap data Structure
*/






void createHeap()// incializamos a heap
{
    h = (struct Heap * ) malloc(sizeof(struct Heap)); //one is number of heap
    h->count=0;   
    h->arr = (struct air *) malloc(HEAP_SIZE*sizeof(struct air)); //size in bytes    
}

void freeHeap()// libertamos o espaço da heap
{
    free(h->arr);
    free(h);
}

void insert_Heap(struct air air)// inserimos o aeroporto na heap
{
    int temp = search(air.id);// pocuramos o aeroporto na hashtable
    if( h->count < HEAP_SIZE)//se  houver espaço na heap
    {
        hashArray[temp]->indexNaHeap=h->count;// marcamos o indice da heap em que o aeroporto esta
        h->arr[h->count] = air;// metemos o aeroporto na heap
        heapify_bottom_top(h->count);// reoganiza a heap de baixo para cima
        h->count++;
    }
}

void heapify_bottom_top(int index)// função que reorganiza a heap depois de cada inserção
{
    struct air temp;
    int parent_node = (index-1)/2;

    if(h->arr[parent_node].tempoTotalDijkstra > h->arr[index].tempoTotalDijkstra)
    // se o pai for mais pessado que o filho troca-os
    {
        //swap and recursive call
        temp = h->arr[parent_node];
        h->arr[parent_node] = h->arr[index];
        h->arr[index] = temp;
        heapify_bottom_top(parent_node);
    }
}

int parent(int i) //procura o pai
{ 
    return (i-1)/2; 
} 
void swap(struct air x,int i,struct air y, int parent) //faz swap das posições dos aeroportos
{ 
    unsigned int indexX = search(x.id);//para sabermos onde esta o aeroporto na hashtable
    unsigned int indexY =search(y.id);//para sabermos onde esta o aeroporto na hashtable
    struct air temp = x; 
    x = y;
    h->arr[i]=y;//o aeroporto onde esta o x passa a ficar com o y
    hashArray[indexY]->indexNaHeap=i; // actualiamos o novo indice da heap no aeroporto
    h->arr[parent] = temp;// o aerpoto onde estava o Y fica com ox
    hashArray[indexX]->indexNaHeap=parent;// actualiamos o novo indice da heap no aeroporto

} 
void decreaseKey(int i, int new_val)// esta função vai reorganizar o aeroporto cujo o peso foi alterado
{ 
    h->arr[i].tempoTotalDijkstra= new_val; 
    while (i != 0 && h->arr[parent(i)].tempoTotalDijkstra > h->arr[i].tempoTotalDijkstra) 
    // enquanto o api tiver mais peso que o filho fazemos swap dos nos
    { 
       swap(h->arr[i],i, h->arr[parent(i)],parent(i)); 
       i = parent(i); 
    }
} 

void heapify_top_bottom(int parent_node)//esta função reorganiza deste o topo até ao fim da heap
{
    int left = parent_node*2+1;//indice do filho da esquerda
    int right = parent_node*2+2;//indice do filho da direita
    int min;//
    struct air temp;
    if(left >= h->count || left <0)
    // se o filho estiver depois do fim ou antes do incio então fica com indice a -1 temporarioamente
        left = -1;
    if(right >= h->count || right <0)
    // se o filho estiver depois do fim ou antes do incio então fica com indice a -1 temporarioamente
        right = -1;

    if(left != -1 && h->arr[left].tempoTotalDijkstra < h->arr[parent_node].tempoTotalDijkstra)
    //Vemos se o filho esquerdo é mais "leve" que o pai
        
        min=left;
    else//O pai é mais "leve" que o pai
        min =parent_node;
    if(right != -1 && h->arr[right].tempoTotalDijkstra < h->arr[min].tempoTotalDijkstra)
    //Vemos se o filho direito é mais "leve" que o min ate agora encontrado
        min = right;

    if(min != parent_node)// se o indice do menor for diferente  do pai então trocamo-los
    {
        temp = h->arr[min];
        h->arr[min] = h->arr[parent_node];
        h->arr[parent_node] = temp;

        // recursive  call
        heapify_top_bottom(min);
    }
}
bool  popCheck()//verifica se podemos retirar alguma coisa da heap
{
    if(h->count!=0)
    {
       return true;
        
    }else
    {
        printf("\n__Heap is Empty__\n");
        return false;
    }
    
    
}

struct air popMin()//esta função retira o aeroproto na raiz da heap
{
    struct air pop;
  
    // replace first node by last and delete last
    pop = h->arr[0];
    h->arr[0] = h->arr[h->count-1];
    h->count--;
    heapify_top_bottom(0);// reorganizamos para ir prencher o a nova raiz da heap
    return *hashArray[search(pop.id)];

}
void printH()//esta função so server para mostrar o conteudo da heap
{
    int i;
    printf("____________Print Heap_____________\n");
    for(i=0;i< h->count;i++){
        printf("-> %s D= %d ",h->arr[i].id,h->arr[i].tempoTotalDijkstra);
    }
    printf("\n");
}