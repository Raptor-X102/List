#include "List_funcs.h"
#include "List_debug.h"
#include "List_graph_debug.h"
#include "Check_r_w_flags.h"

void Print_double(void* data, FILE* file);

int main(int argc, char* argv[]) {

    char* write_files[1] = {};
    file_types files = {};
    files.write_files = write_files;
    if(!Check_r_w_flags(CHECK_W, argv, argc, &files)) {

        DEBUG_PRINTF("ERROR: flags verification failed");
        return 0;
    }

    List list = {};
    double list_value = 10;

    List_Ctor(&list, 3);

    List_insert(&list, 0, &list_value, sizeof(double));
    list_value = 20;

    List_insert(&list, 1, &list_value, sizeof(double));
    List_erase(&list, 1);

    List_insert(&list, 0, &list_value, sizeof(double));
    list_value = 30;

    List_insert(&list, 2, &list_value, sizeof(double));
    list_value = 40;

    List_erase(&list, 1);
    List_erase(&list, 2);
    List_erase(&list, 3);
    List_erase(&list, 4);
    List_erase(&list, 4);

    List_insert(&list, 3, &list_value, sizeof(double));
    list_value = 50;

    List_insert(&list, 4, &list_value, sizeof(double));
    list_value = 60;

    List_insert(&list, 5, &list_value, sizeof(double));
    list_value = 70;

    List_insert(&list, 6, &list_value, sizeof(double));
    list_value = 80;

    /*List_erase(&list, 1);
    List_erase(&list, 2);
    List_erase(&list, 3);
    List_erase(&list, 4);
    List_erase(&list, 4); */

    List_insert(&list, 0, &list_value, sizeof(double));
    list_value = 90;

    List_insert(&list, 4, &list_value, sizeof(double));
    list_value = 80;

    List_insert(&list, 3, &list_value, sizeof(double));
    list_value = 70;

    List_insert(&list, 2, &list_value, sizeof(double));

    List_graph_debug(&list, files.write_files[0], Print_double);
    List_Dtor(&list);
}

void Print_double(void* data, FILE* file) {

    double tmp_double = 0;
    memcpy(&tmp_double, data, sizeof(double));
    fprintf(file, "%.2lg", tmp_double);
}
