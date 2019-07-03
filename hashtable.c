#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashtable.h"
//Esta hashtabkle foi implementada com base neste site :
// https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.html

unsigned int hashCode(char key[5])// calcula o hashcode com base no id do aeroporto 
{
    unsigned int res=0;

    for (int i = 0;key[i]!='\0'; i++)
    {
        
        res=res + (int) key[i];
        
    }
    res=res *HASH;

    return res % SIZE_HASH_TABLE;
}

struct air* searchAir(char key[5]) // este metodo é responsavel por procurar um aeroporto e devolve-o
{
    //get the hash
    unsigned int hashIndex = hashCode(key);// encontra a possição na hashtable do aeroporto que procuramos

    //move in array until an empty
    while(hashArray[hashIndex] != NULL) //por cada posição diferente de NULL vamos confirmar se é a que nos enteressa
    {

        if(strcmp (hashArray[hashIndex]->id,key)==0)//se for o que procuramos devolvemos esse aeroporto
        {
            return hashArray[hashIndex];
        }

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE_HASH_TABLE;
    }
    return NULL;
}


unsigned int search(char key[5]) // este metodo é responsavel por procurar um aeroporto e devolve o seu index na hashtable
{
    //get the hash
    unsigned int hashIndex = hashCode(key);// encontra a possição na hashtable do aeroporto que procuramos

    //move in array until an empty
    while(hashArray[hashIndex] != NULL)
    {

        if(strcmp (hashArray[hashIndex]->id,key)==0)//se for o que procuramos devolvemos esso seu index
        {
            return hashIndex;
        }

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE_HASH_TABLE;
    }
    return -1;
}

bool insert(struct air* novoAir) //este metodo insere um aeroporto na hashtable
{

    char key[5];
    strcpy(key,novoAir->id);
    //get the hash
    unsigned int hashIndex = hashCode(key);// encontra a possição na hashtable do aeroporto que queremos inserir
    
    while(hashArray[hashIndex] != NULL)// percorremos o array ate encontrarmos uma posição NULL onde possamos inserir
    {
        if (strcmp(hashArray[hashIndex]->id, novoAir->id)==0)//Para não deixar que haja dois aeroportos iguais na hastable
        {
            return false;
        }

        //go to next cell
        ++hashIndex;

        //wrap around the table
        hashIndex %= SIZE_HASH_TABLE;
    }

    hashArray[hashIndex] = novoAir;
    return true;

}

void display() //esta função so serve para mostrar a hashtable
{
    unsigned int i = 0;

    for(i = 0; i<SIZE_HASH_TABLE; i++)
    {

        if(hashArray[i] != NULL)
        {
            printf(" (%s)",hashArray[i]->id);
        }
        else
        {
            printf(" ; ");
        }

    }

    printf("\n");
}


