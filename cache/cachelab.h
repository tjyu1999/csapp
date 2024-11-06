/* 
 * cachelab.h - Prototypes for Cache Lab helper functions
 */

#ifndef _CACHELAB
#define _CACHELAB

#define MAX_TRANS_FUNCS 100

typedef struct trans_func {
    void(*func_ptr)(int M, int N, int[N][M], int[M][N]);
    char* description;
    char correct;
    unsigned int num_hits;
    unsigned int num_misses;
    unsigned int num_evictions;
} trans_func_t;

void printSummary(int hits, int misses, int evictions);

// fill the matrix with data
void initMatrix(int M, int N, int A[N][M], int B[M][N]);

// the baseline trans function that produces correct results
void correctTrans(int M, int N, int A[N][M], int B[M][N]);

// add the given function to the function list
void registerTransFunction(void(*trans)(int M, int N, int[N][M], int[M][N]), char *desc);

#endif
