#include "../include/dbllist.h"
#include "../munit/munit.h"
#include <stdio.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

void printNode(const Node* node){
    munit_logf(MUNIT_LOG_INFO,"\n%sNode%s: %p\n\tData: %s\n\tPrev: %p\n\tNext: %p\n",BLUE, RESET, node,node->data,node->prev,node->next);
}

void printList(const List* list){
    munit_logf(MUNIT_LOG_INFO,"\n%sList%s: %p\n\tLength: %u\n\tHead: %p\n\tTail: %p\n", GREEN, RESET, list, list->length,list->head,list->tail);
}

void printFullList(const List* list){
    printList(list);
    if(list->length>0){
        Node* node = list->head;
        for(int i = 0; i<list->length; i++){
            printNode(node);
            node = node->next;
        }
    }
}

MunitResult getTest(const MunitParameter params[], void* fixture) {
    List* list = createListWithSep("0,1,2,3,4",",");

    Node* node = getItem(list, 0);
    munit_assert_not_null(node);
    munit_assert_string_equal(node->data,"0");
    munit_log(MUNIT_LOG_INFO, "Found head");

    node = getItem(list,4);
    munit_assert_not_null(node);
    munit_assert_string_equal(node->data,"4");
    munit_log(MUNIT_LOG_INFO, "Found tail");

    node = getItem(list,2);
    munit_assert_not_null(node);
    munit_assert_string_equal(node->data,"2");
    munit_log(MUNIT_LOG_INFO, "Found middle");

    node = getItem(list,10);
    munit_assert_null(node);
    node = getItem(list, -2);
    munit_assert_null(node);
    munit_log(MUNIT_LOG_INFO, "Looked for nonexistent data");

    deleteList(list);
    return MUNIT_OK;
}

MunitResult findTest(const MunitParameter params[], void* fixture) {
    List* list = createListWithSep("0,1,2,3,4",",");
    int pos = -1;
    Node* node = findItem(list, "0", &pos);
    munit_assert_not_null(node);
    munit_log(MUNIT_LOG_INFO, "Found head");
    munit_assert_string_equal(node->data, "0");
    munit_assert_int(pos, ==, 0);

    node = findItem(list,"4",&pos);
    munit_assert_not_null(node);
    munit_log(MUNIT_LOG_INFO, "Found tail");
    munit_assert_string_equal(node->data, "4");
    munit_assert_int(pos, ==, 4);

    node = findItem(list,"2",&pos);
    munit_assert_not_null(node);
    munit_log(MUNIT_LOG_INFO, "Found middle");
    munit_assert_string_equal(node->data, "2");
    munit_assert_int(pos, ==, 2);

    node = findItem(list,"wahhh",&pos);
    munit_log(MUNIT_LOG_INFO, "Looked for nonexistent data");
    munit_assert_null(node);
    munit_assert_int(pos, ==, -1);

    deleteList(list);
    return MUNIT_OK;
}

MunitResult insertAtTest(const MunitParameter params[], void* fixture){
    List* list = createListWithSep("0,1,2,3,4",",");
    printFullList(list);

    munit_log(MUNIT_LOG_INFO, "Inserting new head...");
    Node* oldHead = list->head;
    Node* node = insertItemAt(list, "x", 0);
    munit_assert_not_null(node);
    munit_assert_ptr_equal(node, list->head);
    munit_assert_ptr_equal(node->next, oldHead);
    munit_assert_ptr_equal(node, oldHead->prev);
    munit_assert_int(list->length,==,6);
    munit_log(MUNIT_LOG_INFO, "Successfully inserted head.");
    printFullList(list);

    munit_log(MUNIT_LOG_INFO, "Inserting new tail...");
    Node* oldTail = list->tail;
    node = insertItemAt(list, "y", 6);
    munit_assert_not_null(node);
    munit_assert_ptr_equal(node, list->tail);
    munit_assert_ptr_equal(node->prev, oldTail);
    munit_assert_ptr_equal(node, oldTail->next);
    munit_assert_int(list->length,==,7);
    munit_log(MUNIT_LOG_INFO, "Successfully inserted tail.");
    printFullList(list);

    munit_log(MUNIT_LOG_INFO, "Inserting new pre-tail...");
    Node* existing = getItem(list, 6);
    Node* prev = existing->prev;
    node = insertItemAt(list, "z", 6);
    munit_assert_not_null(node);
    munit_assert_ptr_equal(node, prev->next);
    munit_assert_ptr_equal(node, existing->prev);
    munit_assert_ptr_equal(node->prev, prev);
    munit_assert_ptr_equal(node->next, existing);
    munit_assert_int(list->length,==,8);
    munit_log(MUNIT_LOG_INFO, "Successfully inserted pre-tail.");
    printFullList(list);

    deleteList(list);
    return MUNIT_OK;
}

MunitResult insertBeforeTest(const MunitParameter params[], void* fixture){
    List* list = createListWithSep("0,1,2,3,4",",");
    printFullList(list);

    munit_log(MUNIT_LOG_INFO, "Inserting before head...");
    Node* oldHead = list->head;
    Node* node = insertItemBefore(list, "head", oldHead);
    munit_assert_not_null(node);
    munit_assert_ptr_equal(node, list->head);
    munit_assert_ptr_equal(node->next, oldHead);
    munit_assert_ptr_equal(node, oldHead->prev);
    munit_assert_int(list->length,==,6);
    munit_log(MUNIT_LOG_INFO, "Successfully inserted before head.");
    printFullList(list);

    munit_log(MUNIT_LOG_INFO, "Inserting before tail...");
    Node* oldTail = list->tail;
    Node* prev = oldTail->prev;
    node = insertItemBefore(list, "pre-tail", oldTail);
    munit_assert_not_null(node);
    munit_assert_ptr_equal(list->tail, oldTail);
    munit_assert_ptr_equal(node, oldTail->prev);
    munit_assert_ptr_equal(node->next, oldTail);
    munit_assert_ptr_equal(node, prev->next);
    munit_assert_ptr_equal(node->prev, prev);
    munit_assert_int(list->length,==,7);
    munit_log(MUNIT_LOG_INFO, "Successfully inserted before tail.");
    printFullList(list);

    munit_log(MUNIT_LOG_INFO, "Inserting before a middle node...");
    int pos = 0;
    Node* two = findItem(list, "2", &pos);
    prev = two->prev;
    munit_assert_not_null(two);
    node = insertItemBefore(list, "middle", two);
    munit_assert_not_null(node);
    munit_assert_ptr_equal(node, two->prev);
    munit_assert_ptr_equal(node->next, two);
    munit_assert_ptr_equal(node, prev->next);
    munit_assert_ptr_equal(node->prev, prev);
    munit_assert_int(list->length,==,8);
    munit_log(MUNIT_LOG_INFO, "Successfully inserted before a middle node.");
    printFullList(list);
    
    deleteList(list);
    return MUNIT_OK;
}

MunitResult insertAfterTest(const MunitParameter params[], void* fixture){
    List* list = createListWithSep("0,1,2,3,4",",");
    printFullList(list);

    munit_log(MUNIT_LOG_INFO, "Inserting after head...");
    Node* head = list->head;
    Node* oldNext = head->next;
    Node* node = insertItemAfter(list, "after-head", head);
    munit_assert_not_null(node);
    munit_assert_ptr_equal(node, head->next);
    munit_assert_ptr_equal(node->prev, head);
    munit_assert_ptr_equal(node->next, oldNext);
    munit_assert_ptr_equal(node, oldNext->prev);
    munit_assert_int(list->length,==,6);
    munit_log(MUNIT_LOG_INFO, "Successfully inserted after head");
    printFullList(list);

    munit_log(MUNIT_LOG_INFO, "Inserting in middle...");
    Node* middle = getItem(list, 3);
    oldNext = middle->next;
    node = insertItemAfter(list, "after-middle", middle);
    munit_assert_not_null(node);
    munit_assert_ptr_equal(node, middle->next);
    munit_assert_ptr_equal(node->prev, middle);
    munit_assert_ptr_equal(node->next, oldNext);
    munit_assert_ptr_equal(node, oldNext->prev);
    munit_assert_int(list->length,==,7);
    munit_log(MUNIT_LOG_INFO, "Successfully inserted after middle");
    printFullList(list);

    munit_log(MUNIT_LOG_INFO, "Inserting after tail...");
    Node* oldTail = list->tail;
    node = insertItemAfter(list, "caboose", oldTail);
    munit_assert_not_null(node);
    munit_assert_ptr_equal(node, oldTail->next);
    munit_assert_ptr_equal(node->prev, oldTail);
    munit_assert_int(list->length,==,8);
    munit_log(MUNIT_LOG_INFO, "Successfully inserted after old tail");
    printFullList(list);

    return MUNIT_OK;
}

int main(int argc, char* argv[]){

    static MunitTest tests[] = {
    {
        "/get",
        getTest,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/find",
        findTest,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/insert/at",
        insertAtTest,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/insert/before",
        insertBeforeTest,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/insert/after",
        insertAfterTest,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    /* Mark the end of the array with an entry where the test
    * function is NULL */
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
    };

    MunitSuite suite = {
        "/linklist-tests",
        tests,
        NULL,
        1,
        MUNIT_SUITE_OPTION_NONE
    };
    // second arg is user_data
    return munit_suite_main(&suite, NULL, argc, argv);
}
