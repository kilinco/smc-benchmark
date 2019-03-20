#include "utils.h"

void load_data_int(protocolIO *io, int **x, int **y, int party)
{
	FILE *inputFile = fopen(io->src, "r");
	if (inputFile == NULL) {
		log_err("File '%s' not found\n", io->src);
		clean_errno();
		exit(1); // causes TCP error for non-null party
	}
  	
	io->n = 0;
	int memsize = ALLOC;
	int a;

	while (!feof(inputFile)) {
		int dataPoints = fscanf(inputFile, "%d", &a);

		// Input Control
		if (dataPoints != 1) {
			if (dataPoints < 0) {
				if (feof(inputFile)) {
					break;
				} 
				else {
					log_err("Input from '%s' does not match file format. Check input file.\n\t" 
						"File format exception found at Line %d or %d in file.\n", 
						io->src, io->n, io->n + 1); // prints to both parties if filename is same
					clean_errno();
					exit(1);
				}
			} 
			else {
				log_err("Input from '%s' does not match file format. Check input file.\n\t" 
						"File format exception found at Line %d or %d in file.\n", 
						io->src, io->n, io->n + 1); // prints to both parties if filename is same
				clean_errno();
				exit(1);
			}
		}

		// Increment the array size
		io->n += 1;
		if (io->n > memsize) {
			memsize *= 2;
			*x = realloc(*x, sizeof(int) * memsize);
			*y = realloc(*y, sizeof(int) * memsize);
		}
		
		// Assign the value to the corresponding party
		if (party == 1) {
			*(*x + io->n - 1) =  a; // messy, but needed for dereferencing 
		} 
		else if (party == 2) {
			*(*y + io->n - 1) =  a;
		}
	}

	log_info("Loading %d data points ...\n", io->n);
	fclose(inputFile);
}

