#include <obliv.h>
#include "obliv.oh"

#include "../utils.h"
#include "../../common/util.h"

#define row(i, n_nodes) (i/n_nodes)
#define col(j, n_nodes) (j%n_nodes)
void dijkstra(void* args);

int main(int argc, char *argv[]) 
{
	printf("Dijkstra\n");
	printf("=================\n\n");
	// Check args
	if (argc == 4) {
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
		io.src = argv[3]; // filename
		lap = wallClock();
		io.n = 0;

		// Execute Yao's protocol and cleanup
		execYaoProtocol(&pd, dijkstra, &io);
		cleanupProtocol(&pd);
		double runtime = wallClock() - lap; // stop clock here 
		for(int i = 0; i < io.n; i++){
			printf("%d ", io.arr[i]);
		}
		printf("\n");
		// Print results and gate count
		log_info("Total time: %lf seconds\n", runtime);
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
	int n_nodes = 6;
	int **dummy = (int **)malloc(n_nodes * sizeof(int *)); 
	if(party == 1){
		printf("Party 1 Dummy Loader - Creating Array\n");
		int arr[6][6] = { 
			{0,3,1,0,0,0},
			{3,0,2,0,0,3},
			{1,2,0,0,1,0},
			{0,0,0,0,1,2},
			{0,0,1,1,0,0},
			{0,3,0,2,0,0}
		};
		printf("Party 1 Dummy Loader - Array Created\n");
		for(int i=0; i < n_nodes; i++){
			printf("Party 1 Dummy Loader - Allocating Memory for Row\n");
			dummy[i] = (int *)malloc(sizeof(int) * n_nodes); 
			for(int j=0; j < n_nodes; j++){
				printf("Assigning element[%d][%d]\n", i, j);
				dummy[i][j]=arr[i][j];
			}
		}
	}
	else if (party == 2){
		printf("Party 2 Dummy Loader - Creating Array\n");
		int arr[6][6] = { 
			{1,0,0,0,0,1},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0}, 
			{1,0,0,0,0,1}
		};
		printf("Party 2 Dummy Loader - Array Created\n");
		for(int i=0; i < n_nodes; i++){
			printf("Party 2 Dummy Loader - Allocating Memory for Row\n");
			dummy[i] = (int *)malloc(sizeof(int) * n_nodes); 
			for(int j=0; j < n_nodes; j++){
				printf("Assigning element[%d][%d]\n", i, j);
				dummy[i][j]=arr[i][j];
			}
		}
	}

	int memsize = ALLOC;
	for(int i = 0; i < n_nodes*n_nodes; i++){
		// Assign the value to the corresponding party
		if (party == 1) {
			io->n += 1;
			*(*x + io->n - 1) =  dummy[row(i,n_nodes)][col(i,n_nodes)];
		}
		else if (party == 2) {
			io->n += 1;
			*(*y + io->n - 1) = dummy[row(i,n_nodes)][col(i,n_nodes)];
		}
		printf("Party %d element [%d][%d] = %d\n", party, row(i,n_nodes), col(i,n_nodes), 
			dummy[row(i, n_nodes)][col(i,n_nodes)]);
	}
	for(int i=0; i < n_nodes; i++){
		free(dummy[i]);
	}
	free(dummy);
}
