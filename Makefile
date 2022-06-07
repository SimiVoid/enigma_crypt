PROJECT_NAME = enygma_crypt
INC_DIR = ./include
GCC_PARAMS = -I$(INC_DIR) -g

src_files = $(shell find -name "*.c")
src_files += $(shell find -name "*.s")

all:
	gcc $(GCC_PARAMS) -o enygma_crypt $(src_files)
