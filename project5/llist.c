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
    if(*head == NULL)*head = n;                  // if no head, set head to this node
    else{
        struct node *temp = *head;               // set head to new node, make old head the next of new head.
        n->next = temp;
        *head = n;
    }
    return;
}


struct node *llist_delete_head(struct node **head){
    if(*head == NULL) return NULL;           // if the head is NULL, do nothing.
        
    struct node *prev_head = *head;
    *head = (*head)->next;
    return prev_head;
}

void llist_insert_tail(struct node **head, struct node *n){
    if(*head == NULL){
        *head = n;}
    else{
        struct node *pointer = *head;
        while(pointer->next !=NULL) 
            pointer = pointer->next;
        pointer->next = n;
    }
}

void llist_print(struct node *head){
    struct node *pointer = head;
    if(pointer == NULL) printf("[empty]");
    
    while(pointer !=NULL){
        int value = pointer->value;
        printf("%d", value);
        if(pointer->next !=NULL) printf("->");
        pointer = pointer->next;
    }
    printf("\n");

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
        } else if(strcmp(argv[i], "it") == 0){   
            struct node *n = node_alloc(atoi(argv[i+1]));
            llist_insert_tail(&head, n);
        } else if(strcmp(argv[i], "dh") == 0){
            llist_delete_head(&head);
        } else if(strcmp(argv[i], "p") == 0){ 
            llist_print(head);
        }else if(strcmp(argv[i], "f") == 0){ 
            node_free(atoi(argv[i+1]));
        }
    }
    return 0;
}



