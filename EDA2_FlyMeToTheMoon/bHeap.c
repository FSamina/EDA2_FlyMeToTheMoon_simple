/* Sudhanshu Patel sudhanshuptl13@gmail.com */
/*
Min Heap implementation in c
*/
#include<stdio.h>
#include<stdlib.h>
#include "bHeap.h"
/*
 Array Implementation of MinHeap data Structure
*/



int main(){
    int i;
    Heap *heap = CreateHeap(); //Min Heap
    struct air *novoAir = (struct air*) malloc(sizeof(struct air));//criamos o novo aeroporto
    strcpy(novoAir->Id,"LIS");
    novoAir->tempoTotalDiskt=10;
    struct air *novoAir2 = (struct air*) malloc(sizeof(struct air));//criamos o novo aeroporto
    strcpy(novoAir2->Id,"MASD");
    novoAir2->tempoTotalDiskt=5;
    struct air *novoAir3 = (struct air*) malloc(sizeof(struct air));//criamos o novo aeroporto
    strcpy(novoAir3->Id,"ABCD");
    novoAir3->tempoTotalDiskt=2;
    if( heap == NULL ){
        printf("__Memory Issue____\n");
        return -1;
    }


    insert(heap, *novoAir);
    insert(heap, *novoAir2);
    insert(heap, *novoAir3);

    print(heap);

    for(i=9;i>=0;i--){
        printf(" Pop Minima : %d\n", PopMin(heap));
        print(heap);
    }
    return 0;
}

Heap *CreateHeap(){
    Heap *h = (Heap * ) malloc(sizeof(Heap)); //one is number of heap

    //check if memory allocation is fails
    if(h == NULL){
        printf("Memory Error!");
        return NULL;
    }
    h->count=0;   
    h->arr = (struct air *) malloc(HEAP_SIZE*sizeof(struct air)); //size in bytes

    //check if allocation succeed
    if ( h->arr == NULL){
        printf("Memory Error!");
        return NULL;
    }
    return h;
}

void insert(Heap *h, struct air air){
    if( h->count < HEAP_SIZE){
        h->arr[h->count] = air;
        heapify_bottom_top(h, h->count);
        h->count++;
    }
}

void heapify_bottom_top(Heap *h,int index){
    struct air temp;
    int parent_node = (index-1)/2;

    if(h->arr[parent_node].tempoTotalDiskt > h->arr[index].tempoTotalDiskt){
        //swap and recursive call
        temp = h->arr[parent_node];
        h->arr[parent_node] = h->arr[index];
        h->arr[index] = temp;
        heapify_bottom_top(h,parent_node);
    }
}

void heapify_top_bottom(Heap *h, int parent_node){
    int left = parent_node*2+1;
    int right = parent_node*2+2;
    int min;
    struct air temp;

    if(left >= h->count || left <0)
        left = -1;
    if(right >= h->count || right <0)
        right = -1;

    if(left != -1 && h->arr[left].tempoTotalDiskt < h->arr[parent_node].tempoTotalDiskt)
        min=left;
    else
        min =parent_node;
    if(right != -1 && h->arr[right].tempoTotalDiskt < h->arr[min].tempoTotalDiskt)
        min = right;

    if(min != parent_node){
        temp = h->arr[min];
        h->arr[min] = h->arr[parent_node];
        h->arr[parent_node] = temp;

        // recursive  call
        heapify_top_bottom(h, min);
    }
}

struct air* PopMin(Heap *h){
    struct air* pop;
    if(h->count==0){
        printf("\n__Heap is Empty__\n");
        return NULL;
    }
    // replace first node by last and delete last
    pop = h->arr[0];
    h->arr[0] = h->arr[h->count-1];
    h->count--;
    heapify_top_bottom(h, 0);
    return pop;
}
void print(Heap *h){
    int i;
    printf("____________Print Heap_____________\n");
    for(i=0;i< h->count;i++){
        printf("-> %d ",h->arr[i]);
    }
    printf("->__/\\__\n");
}