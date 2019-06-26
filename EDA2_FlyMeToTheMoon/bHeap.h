// //#include "hashtable.h"
// //#include "disk.h"
// #include "aeroportoVoo.h"
// #define HEAP_SIZE 200000

// struct Heap{
//     struct air *arr;
//     int count;
// };
// struct Heap *h; 



// void CreateHeap();
// bool  popCheck();
// void insertHeap(struct air* key);
// void print();
// void heapify_bottom_top(int index);
// void heapify_top_bottom(int parent_node);
// struct air PopMin();


//#include "hashtable.h"
#include "aeroportoVoo.h"
#define HEAP_SIZE 200000

struct Heap{
    struct air *arr;
    int count;
};
struct Heap *h; 


int indexfinder(struct air* air);
int parent(int i);
void decreaseKey(int i, int new_val);
void CreateHeap();
bool  popCheck();
void insert(struct air key);
void print();
void heapify_bottom_top(int index);
void heapify_top_bottom(int parent_node);
struct air PopMin();