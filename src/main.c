#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <operation_type.h>

char* input_file_path;
char* output_file_path;

enum operation_t parse_args(int argc, char **argv);

int main(int argc, char *argv[]) {
    enum operation_t operation_type = parse_args(argc, argv);

    

    return 0;
}

enum operation_t parse_args(int argc, char** argv) {
    char* arg;
    size_t it = 1;

    bool encoding = false;
    bool decoding = false;
    bool file_input = false;
    bool file_output = false;
    bool std_output = false;
    bool std_input = false;

    while(it < argc) {
        arg = argv[it++];

        if(strcmp(arg, "-e") == 0 || strcmp(arg, "--encoding") == 0) {
            encoding = true;
        }
        else if(strcmp(arg, "-d") == 0 || strcmp(arg, "--decoding") == 0) {
            decoding = true;
        }
        else if(strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
            return HELP;
        }
        else if(strcmp(arg, "-g") == 0 || strcmp(arg, "--gui") == 0) {
            return GUI;
        }
        else if(strcmp(arg, "-i") == 0) {
            if(it < argc) {
                arg = argv[it++];

                if(strcmp(arg, "stdin") == 0) {
                    std_input = true;
                }
                else {
                    input_file_path = arg;
                    file_input = true;
                }
            }
            else {
                printf("Missing argument for -i\n");
                return UNKNOWN;
            }
        }
        else if(strcmp(arg, "-o") == 0) {
            if(it < argc) {
                arg = argv[it++];

                if(strcmp(arg, "stdout") == 0) {
                    std_output = true;
                }
                else {
                    output_file_path = arg;
                    file_output = true;
                }
            }
            else {
                printf("Missing argument for -o\n");
                return UNKNOWN;
            }
        }
        else {
            printf("Unknown argument: %s\n", arg);
            return UNKNOWN;
        }
    }

    if(encoding == decoding) {
        printf("You must specify either -e or -d\n");
        return UNKNOWN;
    }
    if(file_input == std_input) {
        printf("You must specify either -i stdin or -i file\n");
        return UNKNOWN;
    }
    if(file_output == std_output) {
        printf("You must specify either -o stdout or -o file\n");
        return UNKNOWN;
    }
    if(file_input && file_output && encoding) {
        return ENCODING_FILE;
    }
    if(file_input && file_output && decoding) {
        return DECODING_FILE;
    }
    if(file_input && std_output && encoding) {
        return ENCODING_FILEIN_STDOUT;
    }
    if(file_input && std_output && decoding) {
        return DECODING_FILEIN_STDOUT;
    }
    if(std_input && std_output && encoding) {
        return ENCODING_STDIO;
    }
    if(std_input && std_output && decoding) {
        return DECODING_STDIO;
    }
    if(std_input && file_output && encoding) {
        return ENCODING_STDIN_FILEOUT;
    }
    if(std_input && file_output && decoding) {
        return DECODING_STDIN_FILEOUT;
    }

    return HELP;
}