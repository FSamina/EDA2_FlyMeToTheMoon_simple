#include "hashtable.h"
#define MAX 200000

void create();
void insert_by_priority(struct air* data);
struct air* delete_element();
void check(struct air* data);
void display_pqueue();
struct air* pri_que[MAX];
int front, rear;