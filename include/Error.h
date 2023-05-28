#ifndef _ERROR_H_
#define _ERROR_H_

#include <setjmp.h>

typedef enum error
{
    Error_Malloc,
    Error_Realloc,
    Error_Output
} Error;

#endif // _ERROR_H_