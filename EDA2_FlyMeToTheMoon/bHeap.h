#include "disk.h"
#define HEAP_SIZE 200000

struct Heap{
    struct air *arr;
    int count;
    bool firstpop;
};
struct Heap *h; 


int indexfinder(struct air* air);
int parent(int i);
void decreaseKey(int i, int new_val);
void CreateHeap();
bool popCheck();
void insert_Heap(struct air air);
void print();
void heapify_bottom_top(int index);
void heapify_top_bottom(int parent_node);
struct air PopMin();