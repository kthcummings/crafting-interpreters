#ifndef DOUBLE_LINK_LIST
#define DOUBLE_LINK_LIST

typedef struct Node{
    char* data;
    struct Node* next;
    struct Node* prev;
} Node;

#endif