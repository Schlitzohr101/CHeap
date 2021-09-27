#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// using namespace std;

//Custom Structures
//----------------------------------------------------------------
struct Block {

    int blockSize;// of bytes in the data section
    struct Block *next_block; // pointer to next block --> holds an address
};
//global variables
//----------------------------------------------------------------
const int OVRHDSIZE = sizeof(struct Block); //value is in bytes
const int PTRSIZE = sizeof(void*);
struct Block* FRHD = NULL;

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
 * return: pointer to newly allocated block data, pointer plus overhead
 * will allocate space for a given size for the list of space attached to the FREE LIST
*/
void * myAlloc(int size);


void myFree(void * data) ;



int main() {
    myInitializeHeap(1000);
    printf("freehead at %p \n",FRHD);
    printf("overhead: %d, and pointer: %d  sizes\n",OVRHDSIZE, PTRSIZE);
    printBlock(FRHD);
    printf("TEST 1\n");
    int *a = myAlloc(sizeof(int)); // gimme an int.
    printf("a is at address %p\n", a); // %p prints the memory address of a pointer in hexadecimal.
    printBlock(FRHD);
    myFree(a);
    printf("after free of a \n");
    printBlock(FRHD);
    int *b = myAlloc(sizeof(int));
    printf("b is at address %p\n", b);
    //should be at the same location if done right
    printf("TEST 2\n");
    myInitializeHeap(1000);
    printf("freehead at %p \n",FRHD);
    printBlock(FRHD);
    a = myAlloc(sizeof(int));
    b = myAlloc(sizeof(int));
    printf("a is at address %p and b is at address %p \n",a,b);
    printf("TEST 3\n");
    myInitializeHeap(1000);
    printf("freehead at %p \n",FRHD);
    printBlock(FRHD);
    a = myAlloc(sizeof(int));
    b = myAlloc(sizeof(int));
    printf("middle int at %p \n",b);
    int * c = myAlloc(sizeof(int));
    myFree(b);
    printf("freed b \n");
    double * d = myAlloc(sizeof(double) * 2);
    printf("double array is at address %p\n", d);
    myFree(d);
    printf("freed d \n");
    b = myAlloc(sizeof(int));
    printf("new int at pos :%p \n",b);
    return 0;
}

void myInitializeHeap(int size) {
    FRHD = (struct Block *)malloc(size);

    // The -> operator accesses the field of an object that we have
    // a pointer to.
    FRHD->next_block = NULL;
    FRHD->blockSize = size-OVRHDSIZE;
    // struct Block * temp = (struct Block*) malloc(OVRHDSIZE*size);
    // temp->blockSize = OVRHDSIZE*(size-1); //this may be wrong, not sure if i say i have the whole size when this block occupys space
    // temp->next_block = NULL;
    // FRHD = temp;
}
void printBlock(const struct Block* block) {
    printf("printing block\nblock size:%d and has pointer:",block->blockSize);
    printf("%s ", block->next_block == NULL ? "false\n" : "true");
    if (block->next_block != NULL) {
        printf(" at %p \n ",block->next_block);
    }
}
void * myAlloc(int size) {
    // TODO: if size is not a multiple of POINTER_SIZE, you
    // must round it *UP* to the next multiple.
    if (size%PTRSIZE != 0) {
        size = (int) ceil(size/(double)PTRSIZE); //get the largest int back from the division and case back into int for size
        size = size * PTRSIZE;
        //printf("size %d \n",size);
    }


    // From now on, we will assume that "size" has been adjusted
    // as per above.

    // Next, walk through the nodes that are linked together starting
    // at free_head. Look for a node whose whose block_size is sufficient
    // to fit this request size.

    // 1. Declare a temporary pointer to use for the "walking". A second
    // pointer will point to the block we choose in the end.
    struct Block *temp;
    struct Block *chosen_block = NULL;

    // 2. Start the pointer at free_head.
    temp = FRHD;

    // 3. Perform the "walk through a linked list" logic that you
    // learned in 274.
    while (temp != NULL) { // keep going until we walk off the end of the list.
        printf("temp block size: %d\n", temp->blockSize);
        if (temp->blockSize >= size) { //block is big enough
            if (chosen_block == NULL || temp->blockSize <= chosen_block->blockSize) {//but is it smaller than the current block
                chosen_block = temp;
                if (chosen_block->blockSize == size) {
                    printf("size %d \n",size);
                    printf("chosen size: %d \n",chosen_block->blockSize);
                    printf("perfect fit\n");
                    break;} //stop loop if exact fit
            }
        }
        //move temp to next
        temp = temp->next_block;
    }
    // 4. If we get here and chosen_block is NULL, that means we could not
    // find a block. A real heap allocator would throw an exception;
    // we will just return NULL;
    if (chosen_block == NULL) {
        return NULL;
    }

    //should split if the size leftover is bigger than overhead size
    printf("chosen block size: %d\n", chosen_block->blockSize);
    if (chosen_block->blockSize - size > OVRHDSIZE) {

    
        // new_block->next_block = chosen_block->next_block;
        if (chosen_block == FRHD) //case splitting head
        {
            printf("split chose head \n");
            //block is the head block 
            //we can make a new pointer struct to a size + overhead address and say its holding a difference of the selected block's att blcksz - ovrhd
            struct Block *new_block = (struct Block*)((char*)chosen_block + (OVRHDSIZE + size));
            new_block->blockSize = chosen_block->blockSize - OVRHDSIZE - size;
            chosen_block->blockSize = size;
            new_block->next_block = chosen_block->next_block; //new_block will be head so have it point to other free mem
            FRHD = new_block;
            chosen_block->next_block = NULL;

            //make new pointer from the chosen_block address plus overhead and size
            //then adjust values for both new blocks
            //set head to the new block
        } else { //case splitting middle block
            printf("split chose mid\n");
            //block found is not the head, so there is pointer chain to chosen_block 
            //need to make the new block be the one that is going to be allocated...
            struct Block *new_block = (struct Block*)((char*)chosen_block->next_block + chosen_block->blockSize - size - OVRHDSIZE);
            new_block->blockSize = size;
            new_block->next_block = NULL;
            chosen_block->blockSize = chosen_block->blockSize - size - OVRHDSIZE;
            //no need to change where chosen block points to as it is still the 
            //need to set chosen_block to be the new block
            chosen_block = new_block;
        }
        
    } else {
        //can't split due to block not having enough space, so have the full space be occupied aka removed from the list
        if (chosen_block== FRHD) {
            printf("all chose head\n");
            //block is head block but needs to be removed, normall this requires us to skip
            chosen_block->blockSize = size;
            FRHD = chosen_block->next_block;
            //this could make FRHD point to nothing but that would mean there is no more space to allocate with
        } else {
            printf("all chose mid\n");
            // need to remove a block from the middle of the list and
            //would be super nice if there was a prev option in the list but here we are, creating a loop to get it
            struct Block * prev;
            struct Block * temp = FRHD;
            while (temp != NULL) {
                if (temp == chosen_block) {
                    break;
                }
                prev = temp;
                temp = temp->next_block;
            }
            //after getting previous, point the next pointer to chosen's next
            prev->next_block = chosen_block->next_block;
        }  
    }
    return (void *)((char*) chosen_block+OVRHDSIZE);
}

void myFree(void * data) {
    printf("doing free \n");
    struct Block * block = (struct Block*) ((char*)data - OVRHDSIZE);
    struct Block * prev;
    struct Block * temp = FRHD;
    while (temp != NULL) {
        prev = temp;
        temp = temp->next_block;
    } //again no prev so no easy way to find anything so go through list and find last block in free list then set the next pointer to block pointer
    printf("prev size: %d\n", prev->blockSize);
    prev->next_block = block;
    block->next_block = NULL;
    //add pointer to the end
}