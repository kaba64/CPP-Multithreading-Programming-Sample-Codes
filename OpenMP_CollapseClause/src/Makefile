CC := g++ -std=c++23
TARGET_EXEC := myprogram
CFLAGS1  := -Wall -O3 -m64 -mavx2 -march=native
SRC_DIR := .
OBJ_DIR := obj
LIBS := -lopenblas -fopenmp

LIBIN_LTBB = /usr/include/x86_64-linux-gnu
LIBD_ltbb = /usr/lib/x86_64-linux-gnu
LIB_ltbb = -ltbb

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXECUTABLE = myprogram

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $^ -o $@ -L$(LIBD_ltbb) $(LIB_ltbb) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if [ ! -d $(dir $@) ];then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS1) -c $< -o $@ -I$(LIBIN_LTBB) $(LIBS)

$(OBJ_FILES): common.h

clean:
	rm -r $(OBJ_DIR) $(EXECUTABLE) *~
run:
	@./$(EXECUTABLE)
