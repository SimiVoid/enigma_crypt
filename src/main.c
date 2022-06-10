#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <enigma_encoding.h>
#include <enigma_decoding.h>
#include <operation_type.h>

char* input_file_path;
char* output_file_path;

enum operation_t parse_args(int argc, char **argv);

char* read_input_file(void);
char* read_stdin(void);
int write_output_file(char* output_file_content);

void print_help();
enum operation_t gui();

int main(int argc, char *argv[]) {
    enum operation_t operation_type = parse_args(argc, argv);

    if(operation_type == HELP)
        print_help();
    else if(operation_type == GUI)
        operation_type = gui();

    if(operation_type == ENCODING_FILEIN_STDOUT) {
        char* input_file_content = read_input_file();
        if(input_file_content == NULL)
            return EXIT_FAILURE;

        char* encoded = enigma_encoding(input_file_content);
        
        if(encoded == NULL)
            return EXIT_FAILURE;

        printf("%s", encoded);
    }
    else if(operation_type == DECODING_FILEIN_STDOUT) {
        char* input_file_content = read_input_file();
        if(input_file_content == NULL)
            return EXIT_FAILURE;

        char* decoded = enigma_decoding(input_file_content);

        if(decoded == NULL)
            return EXIT_FAILURE;

        printf("%s", decoded);
    }
    else if(operation_type == ENCODING_STDIN_FILEOUT) {
        char* input_text_content = read_stdin();
        char* encoded = enigma_encoding(input_text_content);

        if(encoded == NULL)
            return EXIT_FAILURE;

        write_output_file(encoded);
    }
    else if(operation_type == DECODING_STDIN_FILEOUT) {
        char* input_text_content = read_stdin();
        char* decoded = enigma_decoding(input_text_content);

        if(decoded == NULL)
            return EXIT_FAILURE;
        
        write_output_file(decoded);
    }
    else if(operation_type == ENCODING_STDIO) {
        char* input_text_content = read_stdin();
        char* encoded = enigma_encoding(input_text_content);

        if(encoded == NULL)
            return EXIT_FAILURE;

        printf("%s", encoded);
    }
    else if(operation_type == DECODING_STDIO) {
        char* input_text_content = read_stdin();
        char* decoded = enigma_decoding(input_text_content);

        if(decoded == NULL)
            return EXIT_FAILURE;

        printf("%s", decoded);
    }
    else if(operation_type == ENCODING_FILE) {
        char* input_file_content = read_input_file();
        if(input_file_content == NULL)
            return EXIT_FAILURE;

        char* encoded = enigma_encoding(input_file_content);
        if(encoded == NULL)
            return EXIT_FAILURE;

        write_output_file(encoded);
    }
    else if(operation_type == DECODING_FILE) {
        char* input_file_content = read_input_file();
        if(input_file_content == NULL)
            return EXIT_FAILURE;

        char* decoded = enigma_decoding(input_file_content);
        if(decoded == NULL)
            return EXIT_FAILURE;

        write_output_file(decoded);
    }
    else return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

#pragma GCC optimize ("O3")

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

        if(strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) return HELP;
        else if(strcmp(arg, "-g") == 0 || strcmp(arg, "--gui") == 0) return GUI;
        else if(strcmp(arg, "-e") == 0 || strcmp(arg, "--encoding") == 0) encoding = true;
        else if(strcmp(arg, "-d") == 0 || strcmp(arg, "--decoding") == 0) decoding = true;
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
    if(file_input && file_output && encoding) return ENCODING_FILE;
    if(file_input && file_output && decoding) return DECODING_FILE;
    if(file_input && std_output && encoding) return ENCODING_FILEIN_STDOUT;
    if(file_input && std_output && decoding) return DECODING_FILEIN_STDOUT;
    if(std_input && std_output && encoding) return ENCODING_STDIO;
    if(std_input && std_output && decoding) return DECODING_STDIO;
    if(std_input && file_output && encoding) return ENCODING_STDIN_FILEOUT;
    if(std_input && file_output && decoding) return DECODING_STDIN_FILEOUT;

    return HELP;
}

char* read_input_file(void) {
    FILE* input_file = fopen(input_file_path, "rb");
    if(input_file == NULL) {
        fprintf(stderr, "Error: cannot open input file\n");
        return NULL;
    }

    fseek(input_file, 0, SEEK_END);
    long input_file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    char* input_file_buffer = malloc(input_file_size + 1);
    if(input_file_buffer == NULL) {
        fprintf(stderr, "Error: cannot allocate memory for input file buffer\n");
        return NULL;
    }

    if(fread(input_file_buffer, input_file_size, 1, input_file) != 1) {
        fprintf(stderr, "Error: cannot read input file\n");
        return NULL;
    }
    fclose(input_file);

    input_file_buffer[input_file_size] = 0;

    return input_file_buffer;
}

char* read_stdin(void) {
    printf("Insert input text: ");

    char* input_buffer = NULL;
    size_t len = 0;
    ssize_t line_size = getline(&input_buffer, &len, stdin);

    return input_buffer;
}

int write_output_file(char* output_file_content) {
    FILE* output_file = fopen(output_file_path, "wb");
    if(output_file == NULL) {
        fprintf(stderr, "Error: cannot open output file\n");
        return -1;
    }

    fwrite(output_file_content, strlen(output_file_content), 1, output_file);
    fclose(output_file);

    return 0;
}

void print_help() {
    printf("    HELP\n\n\
        \n\
        -e - encoding\n\
        -d - decoding\n\
        -o str - output file name\n\
        -i str - input file name\n\
        -g - GUI (in cli)\n\
        \n\
        1) Encoding\n\
            1) From file\n\
                1) To file\n\
                2) To console\n\
            2) From console\n\
                1) To file\n\
                2) To console\n\
        2) Decoding\n\
            1) From file\n\
                1) To file\n\
                2) To console\n\
            2) From console\n\
                1) To file\n\
                2) To console\n\
        \n\n\
        For example\n\
        If you want to Encode your text in file and print it in console, you choose -> 1) -> 1) -> 2)\n\n");
}

enum operation_t gui() {
    int lev1 = 0;
    int lev2 = 0;
    int lev3 = 0;

    printf("    MENU\n\
    \n\
    1) Encoding\n\
    2) Decoding\n\
    To print HELP press 3");
    fflush(stdin);
    scanf("%d", &lev1);
    if (lev1 == 1) {
        printf("\n\n\
        1) From file\n\
        2) From console\n");
        fflush(stdin);
        scanf("%d", &lev2);
        if (lev2 == 1) {
            printf("\n\n\
            1) To file\n\
            2) To console\n");
            fflush(stdin);
            scanf("%d", &lev3);
            if (lev3 == 1) return ENCODING_FILE;
            else if (lev3 == 2) return ENCODING_FILEIN_STDOUT;
            else printf("Invalid input.\n\n");
        }
        else if (lev2 == 2) {
            printf("\n\n\
            1) To file\n\
            2) To console\n");
            fflush(stdin);
            scanf("%d", &lev3);
            if (lev3 == 1) return ENCODING_STDIN_FILEOUT;
            else if (lev3 == 2) return ENCODING_STDIO;
            else printf("Invalid input.\n\n");
        }
        else printf("Invalid input.\n\n");
    }
    else if (lev1 == 2) {
        printf("\n\n\
        1) From file\n\
        2) From console\n");
        fflush(stdin);
        scanf("%d", &lev2);
        if (lev2 == 1) {
            printf("\n\n\
            1) To file\n\
            2) To console\n");

            fflush(stdin);
            scanf("%d", &lev3);
            if (lev3 == 1) return DECODING_FILE;
            else if (lev3 == 2) return DECODING_FILEIN_STDOUT;
            else printf("Invalid input.\n\n");
        }
        else if (lev2 == 2) {
            printf("\n\n\
            1) To file\n\
            2) To console\n");
            fflush(stdin);
            scanf("%d", &lev3);
            if (lev3 == 1) return DECODING_STDIN_FILEOUT;
            else if (lev3 == 2) return DECODING_STDIO;
            else printf("Invalid input.\n\n");
        }
        else printf("Invalid input.\n\n");
    }
    else if(lev1 == 3) return HELP;
    else printf("Invalid input.\n\n");
    
    return UNKNOWN;
}

#pragma GCC optimize("O0")