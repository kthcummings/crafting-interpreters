#include "dbllist.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Node* createNode(const char* data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(data);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

List* createList(const char* data){
    if( data == NULL)
    {
        return createEmptyList();
    }
    Node* loneNode = createNode(data);
    List* newList = (List*)malloc(sizeof(List));
    newList->head = loneNode;
    newList->tail = loneNode;
    newList->length = 1;
    return newList;
}

List* createListWithSep(const char* data, char* sep){
    List* newList = (List*)malloc(sizeof(List));
    newList->length = 0;
    newList->head = NULL;
    newList->tail = NULL;
    char* str = strdup(data);

    char* token = strtok(str, sep);
    Node* lastNode = NULL;

    while(token) {
        Node* newNode = createNode(strdup(token));
        if(newList->length == 0) {
            newList->head = newNode;
        }
        if(lastNode){
            newNode->prev = lastNode;
            lastNode->next = newNode;
        }
        lastNode = newNode;
        newList->length++;
        token = strtok(NULL,",");
    }

    if(lastNode){
        newList->tail = lastNode;
    }
}

List* createEmptyList(){
    List* newList = (List*)malloc(sizeof(List));
    newList->head = NULL;
    newList->tail = NULL;
    newList->length = 0;
    return newList;
}

void deleteList(List* list){
    if(list->length>0){
        Node* node = list->head;
        for(int i = 0; i<list->length; i++){
            Node* next = node->next;
            free(node->data);
            free(node);
            node = next;
        }
    }
    free(list);
}

Node* getItem(List* list, int pos){
    if(pos >= list->length || pos < 0){
        return NULL;
    }
    else if(pos == 0){
        return list->head;
    }
    else if(pos == (list->length-1)){
        return list->tail;
    }
    // traverse
    Node* node = list->head;
    for(int i = 0; i<list->length; ++i){
        if(i == pos){
            return node;
        }
        node = node->next;
    }
    return NULL;
}

// Note: This only finds the first item that matches
Node* findItem(List* list, const char* data, int* pos){
    Node* node = list-> head;
    for(int i = 0; i<(list->length+1); i++){
        if(strcmp(data, node->data) == 0){
            *pos = i;
            return node;
        }
        else{
            if(node->next)
            {
                node = node->next;
            }
        }
    }
    *pos = -1;
    return NULL;
}

// Note: this shifts down the node previously at this position
Node* insertItemAt(List* list, const char* data, int pos){
    Node* newNode = NULL;
    if(pos > list->length){
        return NULL; // out of bounds insert
    }
    newNode = createNode(data);
    if(pos == 0){
        // new head  
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    else if(pos == list->length){
        // new tail via append
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    else{
        // middle insert
        Node* existing = getItem(list, pos);
        Node* prev = existing->prev;
        newNode->next = existing;
        newNode->prev = prev;
        existing->prev = newNode;
        prev->next = newNode;
    }

    list->length++;
    return newNode;
}

Node* insertItemBefore(List* list, const char* data, Node* node){
    Node* newNode = createNode(data);
    newNode->next = node;
    if(node == list->head){
        node->prev = newNode;
        list->head = newNode;
    }
    else{
        Node* prevNode = node->prev;
        prevNode->next = newNode;
        newNode->prev = prevNode;
        node->prev = newNode;
    }

    list->length++;
    return newNode;
}

Node* insertItemAfter(List* list, const char* data, Node* node){
    if(node == list->tail){
        return appendItem(list,data);
    }
    else{
        Node* newNode = createNode(data);
        newNode->prev = node;

        Node* nextNode = node->next;
        nextNode->prev = newNode;
        newNode->next = nextNode;
        node->next = newNode;

        list->length++;
        return newNode;
    }   
}

Node* appendItem(List* list, const char* data){
    Node* newNode = createNode(data);
    Node* oldTail = list->tail;

    newNode->prev = oldTail;
    oldTail->next = newNode;
    list->tail = newNode;
    list->length++;
    return newNode;
}

