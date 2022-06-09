PROJECT_NAME = enygma_crypt
INC_DIR = ./include
GCC_PARAMS = -I$(INC_DIR) -Wl,--allow-multiple-definition -g

src_files = $(shell find -name "*.c")
src_files += $(shell find -name "*.s")

all:
	@echo "Scaning projects files..."
	@sleep 1
	@echo "\033[0;32mFile to build:\033[0;m"
	@echo $(src_files)
	@echo "\033[0;32mBuilding\033[1;34m enygma_crypt\033[0;32m project...\033[0;m"
	@gcc $(GCC_PARAMS) -o enygma_crypt $(src_files)
	@echo "\033[0;33mFinished\033[0;m"
