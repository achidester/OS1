#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define ALIGNMENT 16   // Must be power of 2
#define MIN_FREE_SIZE 16
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))
#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))

struct block *head = NULL;  // Head of the list, empty

struct block{
    struct block *next;
    int size;     // Bytes
    int in_use;   // Boolean
};

void split_space(struct block *current_node, int requested_size){
    int available_space = current_node->size;
    int required_space = PADDED_SIZE(requested_size) + PADDED_SIZE(sizeof(struct block));

    if(available_space >= required_space + MIN_FREE_SIZE){
        struct block *split = PTR_OFFSET(current_node, required_space);
        split->next = current_node->next;
        split->size = available_space - required_space;
        current_node->next = split;
        current_node->size = PADDED_SIZE(requested_size);
    }
}   

void myfree(void *p){
    // Assume valid initial pass; no need for magic number
    struct block *node = PTR_OFFSET(p, - PADDED_SIZE(sizeof(p)));
    node->in_use = 0;

}

void *myalloc(int byte_size){
    if (head == NULL) {
        head = mmap(NULL, 1024, PROT_READ|PROT_WRITE,
                    MAP_ANON|MAP_PRIVATE, -1, 0);
        head->next = NULL;
        head->size = 1024 - PADDED_SIZE(sizeof(struct block));
        head->in_use = 0;
    }
    struct block *pointer = head;
    int padded_bytes = PADDED_SIZE(byte_size);

    while(pointer != NULL){
        if(pointer->in_use == 0 && pointer->size >= padded_bytes){
            split_space(pointer, byte_size);

            pointer->in_use = 1;
            int padded_block_size = PADDED_SIZE(sizeof(struct block));

            return PTR_OFFSET(pointer, padded_block_size);
        }
        pointer = pointer->next;
    }
    return NULL;
}


void print_data(){
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        // printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}

int main(){
    //example1

    // void *p;
    // p = myalloc(512);
    // print_data();
    // myfree(p);
    // print_data();

    //example2

    // myalloc(10); print_data();
    // myalloc(20); print_data();
    // myalloc(30); print_data();
    // myalloc(40); print_data();
    // myalloc(50); print_data();

    //example3

    void *p;
    myalloc(10);     print_data();
    p = myalloc(20); print_data();
    myalloc(30);     print_data();
    myfree(p);       print_data();
    myalloc(40);     print_data();
    myalloc(10);     print_data();

    return 0;
}