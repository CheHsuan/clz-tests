#include <stdio.h>
#include <stdint.h>
#include "clz.h"

int main(int argc, char *argv[])
{
    __attribute__((unused)) uint32_t start = 0X0;
    __attribute__((unused)) uint32_t end = 0XFFFF;
    __attribute__((unused)) uint32_t num = 0;
    __attribute__((unused)) uint8_t ret;

#if defined(RECURSIVE)
    for(num = start; num < end; num++){
        ret = clz_recursive(num);
#if defined(DEBUG)
        printf("%u ",ret);
#endif
    }
#endif

#if defined(ITERATION)
    for(num = start; num < end; num++){
        ret = clz_iteration(num);
#if defined(DEBUG)
        printf("%u ",ret);
#endif
    }
#endif

#if defined(BYTESHIFT)
    for(num = start; num < end; num++){
        ret = clz_byteshift(num);
#if defined(DEBUG)
        printf("%u ",ret);
#endif
    }
#endif

#if defined(BINARYSEARCH)
    for(num = start; num < end; num++){
        ret = clz_binarysearch(num);
#if defined(DEBUG)
        printf("%u ",ret);
#endif
    }
#endif

#if defined(DEBUG)
        printf("\n");
#endif

    return 0;
}
