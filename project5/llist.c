#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int value;
    struct Node* next;
}Node;

Node* node_alloc(int value){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void node_free(Node* node){
    free(node);

}

int main(int argc, char *argv[]){
    Node *head = NULL;
    Node *tail = NULL;

    int n;

    for(int i = 1; i < argc; i++){

        if(strcmp(argv[i], "ih") == 0){ 
            Node* node_pointer = node_alloc(atoi(argv[i+1]));
            head = node_pointer;
            printf("%s stored as node struct %p", argv[i], node_pointer);
        }

        if(strcmp(argv[i], "p") == 0){ 
            printf("\n%d is the head", head->value);
        }


        //low priority: add check for isdigit (note:atoi will convert char to 0)
        int input_num = atoi(argv[i]);
        printf("\narg %d is %d", i, input_num);
        
    }
    
    return 0;
}



