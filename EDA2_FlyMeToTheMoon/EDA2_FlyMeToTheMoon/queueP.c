#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroportoVoo.h"//alterar depois para compliar

 
#define MAX 200000
 
typedef struct pqueue
{
    struct air* data[MAX];
    int rear,front;
}pqueue;
 
void initialize(pqueue *p);
int empty(pqueue *p);
int full(pqueue *p);
void enqueue(pqueue *p, struct air* x);
struct air* dequeue(pqueue *p);
void print(pqueue *p);
 
int main(void)
{
    
    struct air *novoAir = (struct air*) malloc(sizeof(struct air));//criamos o novo aeroporto
    strcpy(novoAir->Id,"LISB");
    novoAir->hour=4;
    novoAir->minute=2;
    novoAir->tempoTotalDiskt=5;
    struct air *novoAir2 = (struct air*) malloc(sizeof(struct air));//criamos o novo aeroporto
    strcpy(novoAir->Id,"ASH");
    novoAir->hour=2;
    novoAir->minute=1;
    novoAir->tempoTotalDiskt=10;
    pqueue q;
    initialize(&q);
 

    if(full(&q))
    {
        printf("\nQueue is Full..");
        exit(0);
    }
    enqueue(&q,novoAir);
    
    if(full(&q))
    {
        printf("\nQueue is Full");
        exit(0);
    }
    enqueue(&q,novoAir2);
    

    

    //dequeue(&q);
    

    print(&q);

        

    return -1;
}
 
void initialize(pqueue *p)
{
    p->rear=-1;
    p->front=-1;
}
 
int empty(pqueue *p)
{
    if(p->rear==-1)
        return(1);
 
    return(0);
}
 
int full(pqueue *p)
{
    if((p->rear+1)%MAX==p->front)
        return(1);
 
    return(0);
}
 
void enqueue(pqueue *p,struct air*  x)
{
    int i;
    if(full(p))
        printf("\nOverflow");
    else
    {
        if(empty(p))
        {
            p->rear=p->front=0;
            p->data[0]=x;
        }
        else
        {
            i=p->rear;
 
            while(x->tempoTotalDiskt > p->data[i]->tempoTotalDiskt)
            {
                p->data[(i+1)%MAX]=p->data[i];
                i=(i-1+MAX)%MAX; //anticlockwise movement inside the queue
                if((i+1)%MAX==p->front)
                    break;
            }
 
            //insert x
            i=(i+1)%MAX;
            p->data[i]=x;
 
            //re-adjust rear
            p->rear=(p->rear+1)%MAX;
        }
    }
}
 
struct air* dequeue(pqueue *p)
{
    
    struct air *deletedAir = (struct air*) malloc(sizeof(struct air));
 
    if(empty(p))
    {
        printf("\nUnderflow..");
    }
    else
    {
        deletedAir=p->data[p->front];
        if(p->rear==p->front)   //delete the last element
            initialize(p);
        else
            p->front=(p->front +1)%MAX;
    }
 
    return(deletedAir);
}
 
void print(pqueue *p)
{
    int i;
    struct air * x = (struct air*) malloc(sizeof(struct air));


 
    if(empty(p))
    {
        printf("\nQueue is empty..");
    }
    else
    {
        i=p->front;
 
        while(i!=p->rear)
        {
            x=p->data[i];
            printf("\nAQUI %s",x->Id);
            i=(i+1)%MAX;
        }
 
        //prints the last element
        x=p->data[i];
        printf("\nUltimo %s\n",x->Id);
    }
}
