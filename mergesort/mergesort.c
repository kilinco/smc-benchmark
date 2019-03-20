#include <obliv.h>
#include "../../common/util.h"
#include "../utils.h"

void mergesort(void* args);

int main(int argc, char *argv[]) 
{
	printf("Merge Sort\n");
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
		execYaoProtocol(&pd, mergesort, &io);
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
	dummy_size = 6;
	dummy = malloc(sizeof(int) * dummy_size); 
	if(party == 1){
		int arr[] = {5,2,1,6,11,14}; //4,7,8,9,0,3
		for(int i=0; i < dummy_size; i++){			
				dummy[i]=arr[i];
		}
	}
	else if (party == 2){
		int arr[] = {23,62,10,12,9,20};
		for(int i=0; i < dummy_size; i++){			
				dummy[i]=arr[i];
		}
	}

	int memsize = ALLOC;
	for(int i = 0; i < dummy_size; i++){
		// Assign the value to the corresponding party
		if (party == 1) {
			io->n += 1;
			*(*x + io->n - 1) =  dummy[i];
		}
		else if (party == 2) {
			io->n += 1;
			*(*y + io->n - 1) =  dummy[i];
		}
		printf("Party %d element %d = %d\n", party, i, dummy[i]);
	}
	free(dummy);
}