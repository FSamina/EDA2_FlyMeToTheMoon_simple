/* 
 * C Program to Implement Priority Queue to Add and Delete Elements
 * From:
 * https://www.sanfoundry.com/c-program-priority-queue/
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queueP.h"

 

 
// int  main(void)
// {
//     struct air *novoAir = (struct air*) malloc(sizeof(struct air));//criamos o novo aeroporto
//     strcpy(novoAir->Id,"LIS");
//     novoAir->tempoTotalDiskt=10;
//     struct air *novoAir2 = (struct air*) malloc(sizeof(struct air));//criamos o novo aeroporto
//     strcpy(novoAir2->Id,"MASD");
//     novoAir2->tempoTotalDiskt=5;
//     struct air *novoAir3 = (struct air*) malloc(sizeof(struct air));//criamos o novo aeroporto
//     strcpy(novoAir3->Id,"ABCD");
//     novoAir3->tempoTotalDiskt=2;
   
 
//     create();

//     insert_by_priority(novoAir);
//     insert_by_priority(novoAir2);
//     insert_by_priority(novoAir3);
//     display_pqueue();

//     delete_element();
//     puts("________\n");

//     display_pqueue();

//     return -1;
// }


/* Function to create an empty priority queue */
void create()
{
    front = rear = -1;
}
 
/* Function to insert value into priority queue */
void insert_by_priority(struct air* data)
{

  
    if (rear >= MAX - 1)
    {
        printf("\nQueue overflow no more elements can be inserted");
        return;
    }
    if ((front == -1) && (rear == -1))
    {
        front++;
        rear++;
        pri_que[rear] = data;
        return;
    }    
    else
        check(data);
    rear++;
}
 
/* Function to check priority and place element */
void check(struct air* data)
{
    int i,j;
    
 
    for (i = 0; i <= rear; i++)
    {
        if (data->tempoTotalDiskt <= pri_que[i]->tempoTotalDiskt)
        {
            for (j = rear + 1; j > i; j--)
            {
                pri_que[j] = pri_que[j - 1];
            }

            pri_que[i] = data;
            return;
        }
    }
    
    pri_que[i] = data;
}
 
/* Function to delete an element from queue */
struct air* delete_element()
{
    int n=-1;
    if ((front==-1) && (rear==-1))
    {
        printf("\nQueue is empty no elements to delete");
        return NULL;
    }
    n=front;
    front++;
    return pri_que[n];
}
 
/* Function to display queue elements */
void display_pqueue()
{
    if ((front == -1) && (rear == -1))
    {
        printf("\nQueue is empty");
        return;
    }
 
    for (; front <= rear; front++)
    {
        printf("I=%d %s \n",front, pri_que[front]->Id);
    }
 
    front = 0;
}