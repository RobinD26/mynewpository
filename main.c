#include <stddef.h>     // pour size_t

//#define HEAP_SIZE   0x0007FFFF   // taille 512Ko -1
#define HEAP_SIZE   0x00001000     // taille 4Ko
#define HEAP_START  0x00000000

// prototypes
void* malloc(size_t size);
void free(void* ptr);

void test_lifo();
void test_fifo();
void test_random();


typedef struct block_header {
    struct block_header* next;      // prochain bloc dans la liste
    size_t size;                    // taille des donnees du bloc
} block_header;                     // attention l'espace reel occuppe par un bloc
// est size + sizeof(block_header)

// bloc de memoire pour simuler l'environnement de la question.
unsigned char mem[HEAP_SIZE];

// premier noeud, variable globale (serait géré par l'OS si on en avait un...)
block_header* first = (block_header*) mem;


int main(void)
{
    first->next = first;
    first->size = HEAP_SIZE-sizeof(block_header);

    test_lifo();
    //test_fifo();
    //test_random();
    return 0;
}

void free(void* ptr){

    block_header* block;

    block = (block_header*)((char*)ptr - sizeof(block_header));

    void* nextBlockEnd = (char*)first + first->size;

    if(block == nextBlockEnd){
        //next block is before allocated memory
        first->size += sizeof(block_header) + block->size;
    }
    else{
        //create a new block
        block->next = first;
        first = block;
    }
}

void* malloc(size_t size){

    block_header* block = first;

    while(block->size < size && block->next != first){
        block = block->next;
    }
    if(block == first && block->size < size){
        return NULL;
    }

    block_header* tmp = (block_header*)((char*)block + block->size - size);
    block->size = (size_t)tmp - (size_t)block - sizeof(block_header);

    return (block_header*)((char*)tmp+sizeof(block_header));
}

void test_lifo(){

    //Allocations de la memoire
    int *alloc_1 = (int*)malloc(sizeof(int));
    float *alloc_2 = (float*)malloc(sizeof(float));
    int *alloc_3 = (int*)malloc(sizeof(int));
    double *alloc_4 = (double*)malloc(sizeof(double));
    short *alloc_5 = (short*)malloc(sizeof(short));
    long *alloc_6 = (long*)malloc(sizeof(long));

    //Liberation de la memoire selon le principe LIFO
    free(alloc_6);
    free(alloc_5);
    free(alloc_4);
    free(alloc_3);
    free(alloc_2);
    free(alloc_1);
}
void test_fifo(){
    //Allocations de la memoire
    int *alloc_1 = (int*)malloc(sizeof(int));
    float *alloc_2 = (float*)malloc(sizeof(float));
    int *alloc_3 = (int*)malloc(sizeof(int));
    double *alloc_4 = (double*)malloc(sizeof(double));
    short *alloc_5 = (short*)malloc(sizeof(short));
    long *alloc_6 = (long*)malloc(sizeof(long));

    //Liberation de la memoire selon le principe FIFO
    free(alloc_1);
    free(alloc_2);
    free(alloc_3);
    free(alloc_4);
    free(alloc_5);
    free(alloc_6);
}

void test_random(){

    int *alloc_1 = (int*)malloc(sizeof(int));
    float *alloc_2 = (float*)malloc(sizeof(float));

    free(alloc_2);

    long *alloc_6 = (long*)malloc(sizeof(long));

    free(alloc_1);

    int *alloc_3 = (int*)malloc(sizeof(int));
    double *alloc_4 = (double*)malloc(sizeof(double));
    short *alloc_5 = (short*)malloc(sizeof(short));

    free(alloc_5);
    free(alloc_3);

    double *alloc_7 = (double*)malloc(sizeof(double));

    free(alloc_4);

    int *alloc_8 = (int*)malloc(sizeof(int));

    free(alloc_6);
    free(alloc_8);
    free(alloc_7);
}