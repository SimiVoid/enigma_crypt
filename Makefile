PROJECT_NAME = enygma_crypt
INC_DIR = ./include
GCC_PARAMS = -O3 -I$(INC_DIR) -g

src_files = $(shell find -name "*.c")

all:
	gcc $(GCC_PARAMS) -o enygma_crypt $(src_files)
