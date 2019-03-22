# smpc-benchmark

## Testing Secure Multiparty Computation frameworks with three different benchmarks

### Benchmarks
Benchmarks tested were bubblesort, mergesort and Dijkstra's algorithm.


### TinyGarble
Folder contains .v verilog files, as well as .scd files to run with TinyGarble

### Frigate
Folder contains .wir files to be run in Frigate

### Obliv-C
Folder contains .c and .oc files to be run in Obliv-C

### Data
generate_input.py can be used to generate input and sample output files for each framework and for each benchmark like so:
```
python generate_input.py tinygarble mergesort alice.txt bob.txt 32 1000
````
The code above, for example, generates two text files with random positive integers up to 1000, as well as a tinygarble_trueoutput.txt file that contains the sorted version of the two files.
