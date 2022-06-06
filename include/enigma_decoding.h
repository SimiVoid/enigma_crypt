#ifndef _ENIGMA_DECODING_H_
#define _ENIGMA_DECODING_H_

inline char* enigma_decoding(char* input) {
    extern char* enigma_encoding(char* input);
    
    return enigma_encoding(input);
}

#endif