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

void deleteList(List* list);

Node* findItem(List* list, const char* data, int* pos);
Node* getItem(List* list, int pos);
Node* insertItemAt(List* list, const char* data, int pos);
Node* insertItemBefore(List* list, const char* data, Node* node);
Node* insertItemAfter(List* list, const char* data, Node* node);
Node* appendItem(List* list, const char* data);

#endif


