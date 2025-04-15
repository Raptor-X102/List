#include "List_funcs.h"
#include "List_debug.h"

bool List_Ctor(List* list, size_t list_size) {

    List_data* tmp_ptr = (List_data*) calloc(list_size, sizeof(List_data));
    if(tmp_ptr) {

        list->list_data = tmp_ptr;
        tmp_ptr = NULL;
        list->list_size = list_size;
    }

    else {

        DEBUG_PRINTF("ERROR: memory was not allocated\n");
        return false;
    }

    List_connector(list, 0);

    list->list_data[0].next = 0;
    list->list_data[0].prev = 0;
    list->free_element = 1;

    return true;
}

static void List_connector(List* list, int64_t start_index) {

    for(int64_t i = start_index; i < list->list_size; i++) {

        list->list_data[i].next = (i + 1) % list->list_size;
        list->list_data[i].prev = -1;
    }
}

void List_Dtor(List* list) {

    if(list && list->list_data)
        free(list->list_data);

    else
        DEBUG_PRINTF("ERROR: null pointer\n");
}

bool List_insert(List* list, int64_t index, void* value, size_t value_size) {

    if(list->list_data[index].prev == -1 || index >= list->list_size) {

        DEBUG_PRINTF("ERROR: can't insert after element out of list\n");
        return false;
    }

    DEBUG_PRINTF("list->list_data[index].prev = %d", list->list_data[index].prev);
    DEBUG_PRINTF(" index = %d list->list_data[index].next = ", index);
    DEBUG_PRINTF("%d\n", list->list_data[index].next);

    int64_t free_index_copy = list->list_data[list->free_element].next;

    memcpy(&list->list_data[list->free_element].element, value, value_size);

    list->list_data[list->list_data[index].next].prev = list->free_element;
    list->list_data[list->free_element].next = list->list_data[index].next;
    list->list_data[list->free_element].prev = index;
    list->list_data[index].next = list->free_element;
    list->free_element = free_index_copy;

    if(!list->free_element) {

        if(!List_expand(list, Realloc_coeff))
            return false;

        List_connector(list, list->list_size / 2);
        list->free_element = list->list_size / 2;
        DEBUG_PRINTF("List was expanded\n");
    }

    List_debug_console(list);

    return true;
}

bool List_erase(List* list, int64_t index) {

    if(list->list_data[index].prev == -1) {

        DEBUG_PRINTF("ERROR: cant' erase element out of list\n");
        return false;
    }

    memset(&list->list_data[index].element, 0, sizeof(int64_t));

    list->list_data[list->list_data[index].next].prev = list->list_data[index].prev;
    list->list_data[list->list_data[index].prev].next = list->list_data[index].next;
    list->list_data[index].prev = -1;
    list->list_data[index].next = list->free_element;
    list->free_element = index;

    List_debug_console(list);

    return true;
}

bool List_expand(List* list, unsigned int coeff) {

    if(!list) {

        DEBUG_PRINTF("ERROR: null pointer\n");
        return false;
    }

    if(coeff < 1) {

        DEBUG_PRINTF("ERROR: wrong expansion coefficient\n");
        return false;
    }

    List_data* tmp_struct_ptr = (List_data*) realloc(list->list_data, sizeof(List_data) * list->list_size * coeff);
    if(tmp_struct_ptr) {

        list->list_data = tmp_struct_ptr;
        tmp_struct_ptr = NULL;
        list->list_size *= coeff;
        return true;
    }

    else {

        DEBUG_PRINTF("ERROR: memory was not reallocated\n")
        return false;
    }
}

int64_t List_get_first(List* list) {

    return list->list_data[0].next;
}

int64_t List_get_last(List* list) {

    return list->list_data[0].prev;
}
