/* Sudhanshu Patel sudhanshuptl13@gmail.com */
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




// int main(){
//     int i;
//     CreateHeap(); //Min Heap
//     struct air *novoAir = (struct air*) malloc(sizeof(struct air));//criamos o novo aeroporto
//     strcpy(novoAir->Id,"LIS");
//     novoAir->tempoTotalDiskt=7;
//     struct air *novoAir2 = (struct air*) malloc(sizeof(struct air));//criamos o novo aeroporto
//     strcpy(novoAir2->Id,"MASD");
//     novoAir2->tempoTotalDiskt=8;
//     struct air *novoAir3 = (struct air*) malloc(sizeof(struct air));//criamos o novo aeroporto
//     strcpy(novoAir3->Id,"ABCD");
//     novoAir3->tempoTotalDiskt=3;
//     struct air *novoAir4 = (struct air*) malloc(sizeof(struct air));//criamos o novo aeroporto
//     strcpy(novoAir4->Id,"OPOA");
//     novoAir4->tempoTotalDiskt=1;
//     if( h == NULL ){
//         printf("__Memory Issue____\n");
//         return -1;
//     }


//     insert(*novoAir);
//     insert(*novoAir2);
//     insert(*novoAir3);
//     insert(*novoAir4);

//     print();
//     bool flag = false;
//     for(i=0;i<4;i++){
        
//         if (popCheck())
//         {
            
//             struct air min = PopMin();
//             printf(" Pop Minima : %s\n", min.Id);
//             if (!flag)
//             {
//                 decreaseKey(indexfinder(novoAir2),1);
//                 printf("DISKTRA NOVO %d \n",h->arr[indexfinder(novoAir2)].tempoTotalDiskt);
                

//                 flag=true;
//             }
            
        
//         }
        
//         print();
//     }
//     printf("DISKTRA NOVO %d \n",h->arr[indexfinder(novoAir2)].tempoTotalDiskt);


//     return 0;
// }

void CreateHeap(){
    h = (struct Heap * ) malloc(sizeof(struct Heap)); //one is number of heap
    h->count=0;   
    h->arr = (struct air *) malloc(HEAP_SIZE*sizeof(struct air)); //size in bytes    
}

void freeHeap()
{
    free(h->arr);
    free(h);
}

void insert_Heap(struct air air){
    if( h->count < HEAP_SIZE){
        h->arr[h->count] = air;
        heapify_bottom_top(h->count);
        h->count++;
    }
}

void heapify_bottom_top(int index){
    struct air temp;
    int parent_node = (index-1)/2;

    if(h->arr[parent_node].tempoTotalDiskt > h->arr[index].tempoTotalDiskt){
        //swap and recursive call
        temp = h->arr[parent_node];
        h->arr[parent_node] = h->arr[index];
        h->arr[index] = temp;
        heapify_bottom_top(parent_node);
    }
}
int indexfinder(struct air* air)
{
    for(int i =0; i < h->count;i++)
    {
        if (strcmp(h->arr[i].Id,air->Id)==0)
        {
            //printf(" NO array esta %s  que é igual a %s\n",h->arr[i].Id,air->Id);
            return i;
        }
    }
    puts("NÃO ENCONTREI O INDEX\n");
    return -1;
}
int parent(int i) 
{ 
    return (i-1)/2; 
} 
void swap(struct air x,int i,struct air y, int parent) 
{ 
    struct air temp = x; 
    x = y;
    h->arr[i]=y; 
    h->arr[parent] = temp; 
} 
void decreaseKey(int i, int new_val) 
{ 
    h->arr[i].tempoTotalDiskt = new_val; 
    while (i != 0 && h->arr[parent(i)].tempoTotalDiskt > h->arr[i].tempoTotalDiskt) 
    { 
       swap(h->arr[i],i, h->arr[parent(i)],parent(i)); 
       i = parent(i); 
    }
   
     
} 

void heapify_top_bottom(int parent_node){
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
        heapify_top_bottom(min);
    }
}
bool  popCheck()
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

struct air PopMin(){
    struct air pop;
  
      
    
    // replace first node by last and delete last
    pop = h->arr[0];
    h->arr[0] = h->arr[h->count-1];
    h->count--;
    

    heapify_top_bottom(0);
    return *hashArray[search(pop.Id)];

}
void print(){
    int i;
    printf("____________Print Heap_____________\n");
    for(i=0;i< h->count;i++){
        printf("-> %s D= %d ",h->arr[i].Id,h->arr[i].tempoTotalDiskt);
    }
    printf("\n");
}