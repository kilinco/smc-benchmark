#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h> 
#include<time.h>

#include "dbg.h"

// initial amount for input data:
#define ALLOC 64 
// doubled when needed in load_data()

double lap;
int cp;

typedef struct {
    char *src; // filename for data read
    int client_id;
    int *arr; 
    int n; // number of nodes

} protocolIO;

double wallClock();
void load_dummy(protocolIO *io, int **x, int **y, int party);
void load_data_int(protocolIO *io, int **x, int **y, int party);
