#include <stdio.h>
#include <stdlib.h>
#include <obliv.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "dbg.h"
#include<time.h>
#include "../common/util.h"

#include "bubblesort.h"


int main(int argc, char *argv[]) 
{
	printf("Bubble Sort\n");
	printf("=================\n\n");
	// Check args
	if (argc == 3) {
		// Initialize protocols and obtain connection information
		const char *remote_host = strtok(argv[1], ":");
		const char *port = strtok(NULL, ":");
		ProtocolDesc pd;
		protocolIO io;

		// Make connection between two shells
		// Modified ocTestUtilTcpOrDie() function from obliv-c/test/oblivc/common/util.c
		log_info("Connecting to %s on port %s ...\n", remote_host, port);
		if(argv[2][0] == '1') {
			if(protocolAcceptTcp2P(&pd, port)!=0) {
				log_err("TCP accept from %s failed\n", remote_host);
				exit(1);
			}
		} else {
			if(protocolConnectTcp2P(&pd,remote_host, port)!=0) {
				log_err("TCP connect to %s failed\n", remote_host);
				exit(1);
			}
		}

		// Final initializations before entering protocol
		cp = (argv[2][0]=='1'? 1 : 2);
		io.client_id = (argv[2][0]=='1'? 1 : 2);
		setCurrentParty(&pd, cp); // only checks for a '1'
		// io.src = argv[3]; // filename
		lap = wallClock();

		// Execute Yao's protocol and cleanup
		execYaoProtocol(&pd, bubblesort, &io);
		cleanupProtocol(&pd);
		double runtime = wallClock() - lap; // stop clock here 

		// Print results and gate count
		log_info("Total time: %lf seconds\n", runtime);
		// log_info("Yao Gate Count: %u\n", yaoGateCount());
		printf("\n");
		for(int i = 0; i < io.n; i++){
			printf("%d ", io.arr[i]);
		}
		printf("\n");
	} 
	else {
		log_info("Usage: %s <hostname:port> <1|2> <filename>\n" 
				 "\tHostname usage:\n" 
				 "\tlocal -> 'localhost' remote -> IP address or DNS name\n", argv[0]);
	}
	return 0;
}

void load_dummy(protocolIO *io, int **x, int **y, int party){
	printf("Dummy Loading...\n");
	int *dummy;
	int dummy_size;
	if(party == 1){
		dummy_size = 4;
		int arr[] = {5,2,1,6}; //4,7,8,9,0,3
		dummy = malloc(sizeof(int) * dummy_size); 
		for(int i=0; i < dummy_size; i++){			
				dummy[i]=arr[i];
				// printf("Party %d element %d = %d\n", party, i, dummy[i]);
		}
	}
	else if (party == 2){
		dummy_size = 4;
		int arr[] = {23,62,10,12};
		dummy = malloc(sizeof(int) * dummy_size);
		for(int i=0; i < dummy_size; i++){			
				dummy[i]=arr[i];
				// printf("Party %d element %d = %d\n", party, i, dummy[i]);
		}
	}

	io->n = 0;
	int memsize = ALLOC;
	int a;

	for(int i = 0; i < dummy_size; i++){
		a = dummy[i];
		// Increment the array size
		io->n += 1;
		if (io->n > memsize){
			memsize *= 2;
			*x = realloc(*x, sizeof(int) * memsize);
			*y = realloc(*y, sizeof(int) * memsize);
		}
		
		// Assign the value to the corresponding party
		if (party == 1) {
			*(*x + io->n - 1) =  a;
		}

		else if (party == 2) {
			*(*y + io->n - 1) =  a;
		}
		printf("Party %d element %d = %d\n", party, i, a);
	}
	free(dummy);
}

// void load_data_int(protocolIO *io, int* x, int *y, int party) 
// {
// 	FILE *inputFile = fopen(io->src, "r");
// 	if (inputFile == NULL) {
// 		log_err("File '%s' not found\n", io->src);
// 		clean_errno();
// 		exit(1); // causes TCP error for non-null party
// 	}
  	
// 	io->n = 0;
// 	int memsize = ALLOC;
// 	int a;

// 	while (!feof(inputFile)) {
// 		int dataPoints = fscanf(inputFile, "%d", &a);

// 		// Input Control
// 		if (dataPoints != 1) {
// 			if (dataPoints < 0) {
// 				if (feof(inputFile)) {
// 					break;
// 				} 
// 				else {
// 					log_err("Input from '%s' does not match file format. Check input file.\n\t" 
// 						"File format exception found at Line %d or %d in file.\n", 
// 						io->src, io->n, io->n + 1); // prints to both parties if filename is same
// 					clean_errno();
// 					exit(1);
// 				}
// 			} 
// 			else {
// 				log_err("Input from '%s' does not match file format. Check input file.\n\t" 
// 						"File format exception found at Line %d or %d in file.\n", 
// 						io->src, io->n, io->n + 1); // prints to both parties if filename is same
// 				clean_errno();
// 				exit(1);
// 			}
// 		}

// 		// Increment the array size
// 		io->n += 1;
// 		if (io->n > memsize) {
// 			memsize *= 2;
// 			*x = realloc(*x, sizeof(int) * memsize);
// 			*y = realloc(*y, sizeof(int) * memsize);
// 			check_mem(*x, *y, party);
// 		}
		
// 		// Assign the value to the corresponding party
// 		if (party == 1) {
// 			*(*x + io->n - 1) =  a; // messy, but needed for dereferencing 
// 		} 
// 		else if (party == 2) {
// 			*(*y + io->n - 1) =  a;
// 		}
// 	}

// 	log_info("Loading %d data points ...\n", io->n);
// 	fclose(inputFile);
// }



/* Code from psi.oc

void batcherSwap(unsigned char* data,size_t n,size_t w,
                 void (*cmpswap)(void*,void*,void*),void* arg)
{
  size_t i;
  for(i=0;i+1<n;i+=2) cmpswap(data+w*i,data+w*(i+1),arg);
}

void batcherMerge(unsigned char* data,size_t n1,size_t n2,size_t w,
                  void (*cmpswap)(void*,void*,void*),void* arg)
{
  if(n1+n2<=1) return;
  int odd = n1%2;
  batcherMerge(data,(n1+1)/2,(n2+!odd)/2,w*2,cmpswap,arg);
  batcherMerge(data+w,n1/2,  (n2+odd)/2,  w*2,cmpswap,arg);
  batcherSwap(data+w*!odd,n1+n2-!odd,w,cmpswap,arg);
}

// w is width in bits
void batcherSort(void* data,size_t n,size_t w,
                 void (*cmpswap)(void*,void*,void*),void* arg)
{
  if(n<=1) return;
  batcherSort(data,n/2,w,cmpswap,arg);
  batcherSort((unsigned char*)data+w*(n/2),(n+1)/2,w,cmpswap,arg);
  batcherMerge(data,n/2,(n+1)/2,w,cmpswap,arg);
}

int intCompare(const void* a, const void* b) { return *(int*)a-*(int*)b; }

void swapInt(obliv int* a,obliv int* b) obliv
{
  ~obliv(en) {
    obliv int t = 0;
    obliv if(en) t=*a^*b;
    *a^=t;
    *b^=t;
  }
}

void cmpswapInt(void* va,void* vb,void* arg)
{
  obliv int *a=va,*b=vb;
  obliv if(*a>*b) swapInt(a,b);
}

*/

///// DIJKSTRA 
// float kruskal::dijkstra(int node_index){
// 	float temp_cost, distance_through_node; 
// 	int index,u,v;
// 	float infinity_var = numeric_limits<float>::infinity();
// 	queue <int> node_queue; 
// 	int *visited = new int [numnode]; 
// 	float *node_distance = new float[numnode];
// 	for(int j = 0; j < numnode; j++){
// 		node_distance[j] = infinity_var;
// 		visited[j] = -1;
// 	}
// 	node_queue.push(node_index);
// 	node_distance[node_index] = 0;
// 	visited[node_index] = 1;
// 	while(!node_queue.empty()){
// 		index = node_queue.front();
// 		node_queue.pop();
// 		for (int j = 0; j < numedges; j++){
// 			u = myedge[j].row;
// 			v = myedge[j].column;
// 			temp_cost = myedge[j].cost;
// 			distance_through_node = temp_cost + node_distance[index];
// 			//since myedge is already sorted, there is no need to look for the smallest edge.
// 			if(index == u && visited[v] == -1){
// 				visited[v] = 1;
// 				node_queue.push(v);
// 				if(distance_through_node < node_distance[v]){
// 					node_distance[v] = distance_through_node;
// 				}	
// 			}
// 			else if(index == v && visited[u] == -1){
// 				visited[u] = 1;
// 				node_queue.push(u);
// 				if(distance_through_node < node_distance[u]){
// 					node_distance[u] = distance_through_node;
// 				}	
// 			}
// 		}
// 	}
// 	temp_cost = 0;
// 	for(int j = 0; j < numnode; j++){
// 		temp_cost = temp_cost + node_distance[j];
// 	}
// 	delete [] node_distance; 
// 	delete [] visited;
// 	return temp_cost;
// }
