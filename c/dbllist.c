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

Node* getItem(List* list, int pos){
    if(pos >= list->length){
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
    Node* prev;
    for(int i = 0; i<list->length; ++i){
        prev = node;
        if(i == pos){
            return node;
        }
        node = node->next;
    }
}

Node* insertItem(List* list, const char* data, int pos){
    Node* newNode;
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
        // new tail
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    else{
        // middle insert

    }

    list->length++;
    return newNode;
}

