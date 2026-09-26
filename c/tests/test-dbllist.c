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
    munit_logf(MUNIT_LOG_INFO,"%sNode%s: %p\n\tData: %s\n\tPrev: %p\n\tNext: %p\n",BLUE, RESET, node,node->data,node->prev,node->next);
}

void printList(const List* list){
    munit_logf(MUNIT_LOG_INFO,"%sList%s: %p\n\tLength: %u\n\tHead: %p\n\tTail: %p\n", GREEN, RESET, list, list->length,list->head,list->tail);
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

static void* appendSetup(const MunitParameter params[], void* user_data){
    const char* unlist;
    List* newList;

    unlist = munit_parameters_get(params, "list");
    if(strlen(unlist) > 0)
    {
        newList = createListWithSep(unlist,",");
    }
    else{
        newList = createEmptyList();
    }
    return newList;
}

static void appendTeardown(void* fixture) {
    List* list = (List*)fixture;
    deleteList(list);
}

MunitResult appendTest(const MunitParameter params[], void* fixture) {
    //const char* insertion = munit_parameters_get(params,"insertion");
    return MUNIT_OK;
}

int main(int argc, char* argv[]){

    // munit only allows us to make params that are char* lists
    // so we have to smash things together and use our setup function to break them apart
    static char* lists[] = {
        "", "int,main", "apple,0,true,{carrot},null,ls -l", NULL
    };
    static char* insertions[] = {
        "","0","star**",";-"," ","banana","The only way out is through.\n-Anon",NULL
    };
    static MunitParameterEnum list_params[] = {
        {"list", lists},
        {"insertion",insertions},
        { NULL, NULL},
    };


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
/*     {
        "/append",
        appendTest,
        appendSetup,
        appendTeardown,
        MUNIT_TEST_OPTION_NONE,
        list_params
    }, */
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