#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashtable.h"
//Esta hashtabkle foi implementada com base neste site :
// https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.html

unsigned int hashCode(char key[5])
{
    unsigned int res=0;
    for (int i = 0; i < strlen(key); i++)
    {
        
        res=res + (int) key[i];
        
    }
    res=res *HASH;

    return res % SIZE;
}

struct air* searchAir(char key[5]) {
    //get the hash
    unsigned int hashIndex = hashCode(key);

    //move in array until an empty
    while(hashArray[hashIndex] != NULL) {

        if(strcmp (hashArray[hashIndex]->Id,key)==0)
        {
            return hashArray[hashIndex];
        }

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }
    puts("NÃO ENCONTREI O  AIR NO SERACH AIR\n");
    return NULL;
}


unsigned int search(char key[5]) {
    //get the hash
    unsigned int hashIndex = hashCode(key);

    //move in array until an empty
    while(hashArray[hashIndex] != NULL) {

        if(strcmp (hashArray[hashIndex]->Id,key)==0)
        {
            return hashIndex;
        }

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }
    puts("NÃO ENCONTREI O INDEX NA hash\n");
    return -1;
}

bool insert(struct air* novoAir) {

    //struct air *item = (struct air*) malloc(sizeof(struct air));
    char key[5];
    strcpy(key,novoAir->Id);
    //get the hash
    unsigned int hashIndex = hashCode(key);

    //move in array until an empty or deleted cel
    while(hashArray[hashIndex] != NULL)
    {
        if (strcmp(hashArray[hashIndex]->Id, novoAir->Id)==0)//Para não deixar que haja dois aeroportos iguais na hastable
        {
            return false;
        }

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    hashArray[hashIndex] = novoAir;
    return true;

}

struct air* delete(struct air* item) {
    char key[5];
    strcpy(key,item->Id);

    //get the hash
    unsigned int hashIndex = hashCode(key);

    //move in array until an empty
    while(hashArray[hashIndex] != NULL) {

        if(strcmp (hashArray[hashIndex]->Id,key)==0) {
            struct air* temp = hashArray[hashIndex];

            //assign a dummy item at deleted position
            hashArray[hashIndex] = dummyItem;
            return temp;
        }

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE;
    }

    return NULL;
}

void display() {
    unsigned int i = 0;

    for(i = 0; i<SIZE; i++)
    {

        if(hashArray[i] != NULL)
        {
            printf(" (%s)",hashArray[i]->Id);
        }
        else
        {
            //printf(" ; ");
        }

    }

    printf("\n");
}


