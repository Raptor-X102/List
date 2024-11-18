#include "Check_r_w_flags.h"

bool Check_r_w_flags(int check_option, char** argv, int argc, file_types* files) {

    bool rf_flag_found = false;
    bool wf_flag_found = false;
    bool flags_check_succsess = false;

    for(int i = 0; i < argc; i++) {

        if(!strcmp(argv[i], "-rf")) {

            files->read_file = argv[i+1];
            rf_flag_found = true;
        }

        if(!strcmp(argv[i], "-wf")) {

            files->write_file = argv[i+1];
            wf_flag_found = true;
        }
    }

    if(check_option & CHECK_R)
        if(rf_flag_found)
            flags_check_succsess = true;

    if(check_option & CHECK_W)
        if(wf_flag_found)
            flags_check_succsess = true;

        else
           flags_check_succsess = false;

    return flags_check_succsess;
}
