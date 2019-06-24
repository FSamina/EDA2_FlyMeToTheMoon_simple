//#include "hashtable.h"
#include "disk.h"
#define HEAP_SIZE 200000

struct Heap{
    struct air *arr;
    int count;
};
struct Heap *h; 



void CreateHeap();
bool  popCheck();
void insert(struct air key);
void print();
void heapify_bottom_top(int index);
void heapify_top_bottom(int parent_node);
struct air PopMin();