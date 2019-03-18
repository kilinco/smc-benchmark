
// initial amount for input data:
#define ALLOC 64 
// doubled when needed in load_data()

double lap;
int cp;

typedef struct {
    char *src; // filename for data read
    int client_id;
    int  *arr; // array
    int n; // number of data points
} protocolIO;

// TODO - Implement Heaps
// class Heap
// {
//     int *Data;
//     int Parent(int);
//     int RightChild(int);
//     int LeftChild(int);
//     void maxheapify(int);
//     int heap_size;
// 	Heap(int m){heap_size = 0; Data = new int[m];}
	
// 	void heap_increase_key(int, int);
//     void insert(int);
//     int  extractmaximum();
// 	int  Maximum(){return Data[0];}
//    	int get_data(int index) { return Data[index]; }
// 	void set_heap_size(int size){ heap_size = size; }
// 	int get_heap_size(){ return heap_size; }
// };

double wallClock();
void bubblesort(void* args);
void load_dummy(protocolIO *io, int **x, int **y, int party);
void load_data_int(protocolIO *io, int **x, int **y, int party);
