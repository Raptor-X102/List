#ifndef LIST_FUNCS
#define LIST_FUNCS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "DEBUG_PRINTF.h"
#include "List_definitions.h"

void List_Ctor(List* list, size_t list_size);
void List_Dtor(List* list);
void List_insert(List* list, int64_t index, void* value, size_t value_size);
void List_erase(List* list, int64_t index);

#endif
