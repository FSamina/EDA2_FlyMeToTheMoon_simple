#include "disk.h"
#define HEAP_SIZE 200000 // tamanho da heap

struct Heap{
    struct air *arr;
    int count;
};
struct Heap *h; 


int parent(int i);
void decreaseKey(int i, int new_val);
void createHeap();
void freeHeap();
bool popCheck();
void insert_Heap(struct air air);
void printH();
void heapify_bottom_top(int index);
void heapify_top_bottom(int parent_node);
struct air popMin();