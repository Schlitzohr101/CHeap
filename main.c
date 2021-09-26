#include <stdio.h>
#include <stdlib.h>
// using namespace std;

//Custom Structures
//----------------------------------------------------------------
struct Block {

    int blockSize;// of bytes in the data section
    struct Block *next_block; // pointer to next block --> holds an address
};
//global variables
//----------------------------------------------------------------
const int OVRHDSIZE = sizeof(struct Block);
const int PTRSIZE = sizeof(void*);
const struct Block* FRHD = NULL;

//function definitions
/****************************************************************
 * myintializeHeap
 * sets the global variable freeHead to a free portion of space allocated
 * inputs:
 * size - total size of buffer space to be allocated
 * outputs:
 * FRHD points to a new heap with a size based on entered
*/
void myInitializeHeap(int size);
/****************************************************************
 * printBlock
 * prints all aspects of a block
 * inputs:
 * block - pointer to block in question on heap
 * outputs:
 * the block's attributes to the console
*/
void printBlock(const struct Block *block) ;
/****************************************************************
 * myAlloc
 * creates a new allocation of data within a heap already allocated, based off a given size
 * considers most optimal location by walking through current list of blocks in heap
 * inputs:
 * size - pointer to block in question on heap
 * outputs:
 * return: pointer to newly allocated block
 * creates a heap within the heap at correct location
*/
void * myAlloc(int size);




int main() {
    myInitializeHeap(2);
    printf("overhead: %d, and pointer: %d  sizes\n",OVRHDSIZE, PTRSIZE);
    printBlock(FRHD);
    return 0;
}

void myInitializeHeap(int size) {
    struct Block * temp = (struct Block*) malloc(OVRHDSIZE*size);
    temp->blockSize = OVRHDSIZE*(size-1); //this may be wrong, not sure if i say i have the whole size when this block occupys space
    temp->next_block = NULL;
    FRHD = temp;
}
void printBlock(const struct Block* block) {
    printf("printing block\nblock size:%d and has pointer:",block->blockSize);
    printf("%s \n", block->next_block == NULL ? "false" : "true");
}
void myAlloc(int size) {
    
}