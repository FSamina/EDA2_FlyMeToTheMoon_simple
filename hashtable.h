#include "aeroportoVoo.h"

#define SIZE_HASH_TABLE 400009 // Tamanho da hashTable
#define HASH 8721 // Hash para evitar muitas colisões
struct air * hashArray[SIZE_HASH_TABLE];//array da hashtable que recebe endereços de aeroportos


unsigned int hashCode(char key[5]);

struct air* searchAir(char key[5]);

unsigned int  search(char key[5]);

bool insert(struct air* novoAir);

void display();