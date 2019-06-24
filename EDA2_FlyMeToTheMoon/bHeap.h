//#include "hashtable.h"
#include "aeroportoVoo.h"
#define HEAP_SIZE 200000

struct Heap{
    struct air *arr;
    int count;
};
typedef struct Heap Heap;



Heap *CreateHeap();
void insert(Heap *h, struct air key);
void print(Heap *h);
void heapify_bottom_top(Heap *h,int index);
void heapify_top_bottom(Heap *h, int parent_node);
struct air PopMin(Heap *h);