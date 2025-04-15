#ifndef LIST_FUNCS
#define LIST_FUNCS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "Debug_printf.h"
#include "List_definitions.h"

const size_t Realloc_shrink_limit = 4;
const size_t Realloc_coeff = 2;

bool List_Ctor(List* list, size_t list_size);
static void List_connector(List* list, int64_t start_index);
void List_Dtor(List* list);
bool List_insert(List* list, int64_t index, void* value, size_t value_size);
bool List_erase(List* list, int64_t index);
bool List_expand(List* list, unsigned int coeff);
int64_t List_get_first(List* list);
int64_t List_get_last(List* list);

#endif
