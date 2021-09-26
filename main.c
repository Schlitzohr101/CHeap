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
    FRHD = (struct Block *)malloc(size);

    // The -> operator accesses the field of an object that we have
    // a pointer to.
    FRHD->next_block = NULL;
    // struct Block * temp = (struct Block*) malloc(OVRHDSIZE*size);
    // temp->blockSize = OVRHDSIZE*(size-1); //this may be wrong, not sure if i say i have the whole size when this block occupys space
    // temp->next_block = NULL;
    // FRHD = temp;
}
void printBlock(const struct Block* block) {
    printf("printing block\nblock size:%d and has pointer:",block->blockSize);
    printf("%s \n", block->next_block == NULL ? "false" : "true");
}
void * myAlloc(int size) {
    // TODO: if size is not a multiple of POINTER_SIZE, you
    // must round it *UP* to the next multiple.



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
        if (temp->blockSize >= size) {
            // This block is big enough!
            // If we were doing FIRST FIT, we would definitely break here.
            // But this project uses BEST FIT, so you might NOT want
            // to break on the next line. You may need to make a copy
            // of temp to remember this block if it's the best fit that
            // you've found so far!

            chosen_block = temp; // this is FIRST FIT!
            break;
        }
    }

    // 4. If we get here and chosen_block is NULL, that means we could not
    // find a block. A real heap allocator would throw an exception;
    // we will just return NULL;
    if (chosen_block == NULL) {
        return NULL;
    }

    // Otherwise, we must decide:
    // a) Do we split the block? yes/no
    // b) Is this block the head node? yes/no

    // The four possible answers to a) and b) will give you four branches
    // to code.

    // Branch 1: we are not splitting the head node.
    // if (....) 

    // Branch 2: we are splitting the head node.
    // else if (....)

    // Branch 3: we are not splitting an interior node.
    // else if (....)

    // Branch 4: we are splitting an interior node.
    // else {}

    // To reassign chosen_block's next_block pointer, just give it a new value.
    // FOR EXAMPLE, to make chosen_block point AROUND the block that follows 
    // (you don't necessarily actually want to do this, just an example)
    // we would write
    // chosen_block->next_block = chosen_block->next_block->next_block
    // just like you did in 274.

    // If you need to "create" a new block, perhaps to split chosen_block itself,
    // you will simply create a new struct Block* variable and point it
    // to an address of where you want the new block object to be.
    // FOR EXAMPLE, if I wanted a new Block to exist exactly 100 bytes 
    // after where chosen_block currently is, I would write

    // struct Block *new_block = (struct Block*)((char*)chosen_block->nextBlock + 100);

    // and then initialize its fields:
    // new_block->size = ...;
    // new_block->next_block = ...;

    // This might mean that chosen_block is now smaller, and I might have
    // to change its size field...

    // See the PDF for the explanation for all the casting.
}