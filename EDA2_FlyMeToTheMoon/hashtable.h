#include "aeroportoVoo.h"

#define SIZE 400009 
#define HASH 8721
struct air * hashArray[SIZE];
struct air* dummyItem;
struct air* item;

unsigned int hashCode(char key[5]);

struct air* searchAir(char key[5]);

unsigned int  search(char key[5]);

bool insert(struct air* novoAir);

struct air* delete(struct air* item);

void display();