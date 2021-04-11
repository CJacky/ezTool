PRJ_DIR     = .

INC_DIR = $(PRJ_DIR)/inc
SRC_DIR = $(PRJ_DIR)/src
TEST_DIR= $(PRJ_DIR)/test
INC     = $(wildcard $(INC_DIR)/*.h)
SRC     = $(wildcard $(SRC_DIR)/*.c)
EXE     = $(notdir $(SRC:%.c=%))

CC          = gcc
LD          = gcc
CCFLAGS     = -Wall -I$(INC_DIR)
LDFLAGS     =
DEPLIBS     =

all: $(EXE)
	./ezQueue.exe

$(EXE) : % : $(INC_DIR)/%.h $(SRC_DIR)/%.c $(TEST_DIR)/%.c
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $@ $(SRC_DIR)/$@.c $(TEST_DIR)/$@.c

clean:
	rm -f $(EXE)