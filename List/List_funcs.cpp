#include "List_funcs.h"
#include "List_debug.h"

void List_Ctor(List* list, size_t list_size) {

    List_data* tmp_ptr = (List_data*) calloc(list_size, sizeof(List_data));
    if(tmp_ptr) {

        list->list_data = tmp_ptr;
        tmp_ptr = NULL;
        list->list_size = list_size;
    }

    else {

        DEBUG_PRINTF("ERROR: memory was not allocated\n");
        return;
    }

    for(int64_t i = 0; i < list->list_size; i++) {

        list->list_data[i].next = (i + 1) % list->list_size;
        list->list_data[i].prev = -1;
    }

    list->list_data[0].next = 0;
    list->list_data[0].prev = 1;
    list->free_element = 1;
}

void List_Dtor(List* list) {

    if(list && list->list_data)
        free(list->list_data);

    else
        DEBUG_PRINTF("ERROR: null pointer\n");
}

void List_insert(List* list, int64_t index, void* value, size_t value_size) {

    if(!list->free_element) {

        DEBUG_PRINTF("ERROR: list is full, can't insert\n");
        return;
    }

    if(list->list_data[index].prev == -1) {

        DEBUG_PRINTF("ERROR: can't insert after element out of list\n");
        return;
    }

    int64_t free_index_copy = list->list_data[list->free_element].next;

    memcpy(&list->list_data[list->free_element].element, value, value_size);

    list->list_data[list->list_data[index].next].prev = list->free_element;
    list->list_data[list->free_element].next = list->list_data[index].next;
    list->list_data[list->free_element].prev = index;
    list->list_data[index].next = list->free_element;
    list->free_element = free_index_copy;

    List_debug_console(list);
}

void List_erase(List* list, int64_t index) {

    if(list->list_data[index].prev == -1) {

        DEBUG_PRINTF("ERROR: cant' erase element out of list\n");
        return;
    }

    memset(&list->list_data[index].element, 0, sizeof(int64_t));

    if(list->list_data[index].prev == 0 && list->list_data[index].next == 0)
        list->list_data[list->list_data[index].next].prev = list->free_element;

    else
        list->list_data[list->list_data[index].next].prev = list->list_data[index].prev;

    list->list_data[list->list_data[index].prev].next = list->list_data[index].next;
    list->list_data[index].prev = -1;
    list->list_data[index].next = list->free_element;
    list->free_element = index;

    List_debug_console(list);
}
