CC = g++

CFLAGS = -Wformat=2 -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal \
-Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs \
-Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions \
-Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 \
-Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor \
-Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
-Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

SOURCES_DIR = src
SOURCES = $(wildcard $(SOURCES_DIR)/*.cpp)
HEADERS_DIR = headers

LIBS_CHECK_R_W_FLAGS = Check_flags
LIB_CHECK_R_W_FLAGS_SRC = $(wildcard $(LIBS_CHECK_R_W_FLAGS)/*.cpp)
BUILD_DIR = build
OBJ_DIR = obj
OBJECTS = $(wildcard $(OBJ_DIR)/*.o)
EXECUTABLE = list.exe

setup:
	mkdir $(BUILD_DIR)
	mkdir $(OBJ_DIR)
	mkdir $(SOURCES_DIR)
	mkdir $(HEADERS_DIR)

clean_exe:
	rm $(BUILD_DIR)/*.exe

clean_obj:
	rm $(OBJ_DIR)/*.o

clean_dump:
	rm dump/*.png
	rm dump/*.dot

clean:
	make clean_obj

create_obj:
	$(CC) $(SOURCES) $(LIB_CHECK_R_W_FLAGS_SRC) -c -I $(LIBS_CHECK_R_W_FLAGS) -I $(HEADERS_DIR) $(CFLAGS)
	mv *.o $(OBJ_DIR)

linkage:
	$(CC) $(OBJECTS) -o $(BUILD_DIR)/$(EXECUTABLE)

compile:
	make create_obj
	make linkage
