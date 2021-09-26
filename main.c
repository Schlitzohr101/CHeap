#include <stdio.h>

// using namespace std;

struct Block {
    int blockSize;// of bytes in the data section
    struct Block *next_block; // pointer to next block --> holds an address
};

int main() {
    const int overheadSize = sizeof(struct Block);
    const int pointerSize = sizeof(void*);
    printf("overhead: %d, and pointer: %d  sizes\n",overheadSize, pointerSize);
    return 0;
}