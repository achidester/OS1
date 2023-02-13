#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "llist.h"


struct node *node_alloc(int value){
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void llist_insert_head(struct node **head, struct node *n){
    if(*head == NULL){
        printf("Succesfully replaced NULL head");
       *head = n;
    }

    return;
}


void node_free(struct node *n){
    free(n);
}


int main(int argc, char *argv[]){
    struct node *head = NULL;


    for(int i = 1; i < argc; i++){

        if(strcmp(argv[i], "ih") == 0){ 
            struct node *n = node_alloc(atoi(argv[i+1]));
            llist_insert_head(&head, n);

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



