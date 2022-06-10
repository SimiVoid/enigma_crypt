PROJECT_NAME = enygma_crypt
INC_DIR = ./include
GCC_PARAMS = -I$(INC_DIR)

src_files = $(shell find -name "*.c")
src_files += $(shell find -name "*.s")

all: build

debug: GCC_PARAMS += -g -DDEBUG
debug: build
	
build:
	@echo "Scaning projects files..."
	@sleep 1
	@echo "\033[0;32mFile to build:\033[0;m"
	@echo $(src_files)
	@echo "\033[0;32mBuilding\033[1;34m " $(PROJECT_NAME)"\033[0;32m project...\033[0;m"
	@gcc $(GCC_PARAMS) -o $(PROJECT_NAME) $(src_files)
	@echo "\033[0;33mFinished\033[0;m"

clean:
	@echo "\033[0;32mRemoving\033[0;m" $(PROJECT_NAME)
	@rm $(PROJECT_NAME)