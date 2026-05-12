#ifndef TSVC_COMMON_HDR
#define TSVC_COMMON_HDR

#define iterations 10
#define LEN_1D 256
#define LEN_2D 256

#include <sys/time.h>

struct args_t {
    struct timeval t1;
    struct timeval t2;
    void * __restrict__ arg_info;
};

#if 0
typedef double real_t;
#define ABS fabs
#else
typedef float real_t;
#define ABS fabsf
#endif

__attribute__((pure))
int dummy(real_t[LEN_1D], real_t[LEN_1D], real_t[LEN_1D], real_t[LEN_1D], real_t[LEN_1D], real_t[LEN_2D][LEN_2D], real_t[LEN_2D][LEN_2D], real_t[LEN_2D][LEN_2D], real_t);

void init1(int** ip, real_t* s1, real_t* s2);

int initialise_arrays(const char* name);
real_t calc_checksum(const char * name);

// Malloc for baremetal
#define ALIGNMENT (NR_LANES * NR_CLUSTERS * 4)

#define ALIGN_UP(x, a)  (((x) + (a) - 1) & ~((a) - 1))

inline void * baremetal_malloc(int incr)
{
    extern char l2_alloc_base;   /* Set by linker */
    static char *heap_end = 0;

    uintptr_t aligned;
    char *result;

    /* First call: initialize heap */
    if (!heap_end)
        heap_end = &l2_alloc_base;

    /* Align current heap pointer */
    aligned = ALIGN_UP((uintptr_t)heap_end, ALIGNMENT);

    result = (char *)aligned;

    /* Move heap past allocated block */
    heap_end = result + incr;

    return (void *)result;
}

#endif
