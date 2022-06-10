#ifndef _CLEAR_H_
#define _CLEAR_H_

#include <stdlib.h>

#ifdef __WIN32__
    #define CLEAR() { system("cls"); }
#elif __linux__
    #define CLEAR() { system("clear"); }
#endif

#endif