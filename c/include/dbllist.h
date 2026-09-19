#ifndef DOUBLE_LINK_LIST
#define DOUBLE_LINK_LIST

typedef unsigned int uint;

typedef struct Node{
    char* data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct List{
    struct Node* head;
    struct Node* tail;
    uint length;
} List;

Node* createNode(const char* data);
List* createList(const char* data);
List* createListWithSep(const char* data, char* sep);
List* createEmptyList();

Node* findItem(List* list, const char* data, int* pos);
Node* getItem(List* list, int pos);
Node* insertItem(List* list, const char* data, int pos);
Node* appendItem(List* list, const char* data);

#endif
