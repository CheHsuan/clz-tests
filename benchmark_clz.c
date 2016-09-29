#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "clz.h"

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

int main(int argc, char *argv[])
{
    struct timespec start = {0, 0};
    struct timespec end = {0, 0};

    uint32_t num = 0;
    uint32_t max = 0XFFFFFFFF;

    // clz recursive version
    clock_gettime(CLOCK_ID, &start);
    for(num = 0; num < max; num++){
        clz_recursive(num);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // clz binary recursive version
    clock_gettime(CLOCK_ID, &start);
    for(num = 0; num < max; num++){
        clz_binary_recursive(num, 16);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);


    // clz iteration version
    clock_gettime(CLOCK_ID, &start);
    for(num = 0; num < max; num++){
        clz_iteration(num);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // clz byte-shift version
    clock_gettime(CLOCK_ID, &start);
    for(num = 0; num < max; num++){
        clz_byteshift(num);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // clz binary search technique version
    clock_gettime(CLOCK_ID, &start);
    for(num = 0; num < max; num++){
        clz_binarysearch(num);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    // clz harley version
    clock_gettime(CLOCK_ID, &start);
    for(num = 0; num < max; num++){
        clz_harley(num);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf\n", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);

    return 0;
}
