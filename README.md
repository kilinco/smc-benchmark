# smpc-benchmark
## Introduction to Secure Multiparty Computation
Secure Multiparty Computation is a field within cryptography that aims to solve a difficult problem; the calculation of a function over several participants’ inputs without revealing any of their inputs to the other participants. While traditional cryptography aims to conceal information from an adversary outside of the system, here we assume the adversary actually controls actual participants. 

SMC was formally introduced as the Millionaires’ Problem by Andrew Yao in 1982, where two millionaires (Alice and Bob) wish to find out which of them is richer without revealing their actual wealth. The protocol consists of 6 steps as follows:
The underlying function (e.g., in the millionaires' problem, comparison function) is described as a Boolean circuit with 2-input gates. The circuit is known to both parties. This step can be done beforehand by a third-party, and is mainly being investigated here.

1. Alice garbles (encrypts) the circuit. We call Alice the garbler.
2. Alice sends the garbled circuit to Bob along with her encrypted input.
3. Bob through oblivious transfer receives his encrypted inputs from Alice.
4. Bob evaluates (decrypts) the circuit and obtains the encrypted outputs. We call Bob the evaluator.
5. Alice and Bob communicate to learn the output.

## Testing Secure Multiparty Computation frameworks with three different benchmarks

In this project, we aim to compare 3 different SMC frameworks: TinyGarble, Frigate and Obliv-C. We will do so with the implementation of three benchmarks: Bubblesort, Mergesort and Dijkstra’s Shortest Path Algorithm. Additionally, we will be attempting to reduce the number of AND gates needed to implement these algorithms as much as possible, and through this or by other means reduce the runtime required. The implementation of these algorithms are also of concern to us as these applications are not straightforward, and require workarounds to deal with the inherent limitations of these systems.

### Benchmarks
Benchmarks tested were bubblesort, mergesort and Dijkstra's algorithm. 

### TinyGarble
TinyGarble views circuit generation for GC as an atypical logic synthesis task addressable by conventional hardware synthesis tools. By posing the circuit generation for Yao’s protocol as a hardware synthesis problem, it benefits from the algorithms and techniques already incorporated in existing logic synthesis solutions. TinyGarble’s libraries aim to reduce the cost of building these circuits by optimizing and using as many XOR gates instead of traditional AND gates as possible.

Folder contains instructions to compile TinyGarble, .v verilog files for benchmarks, as well as .scd files to run with TinyGarble.

### Frigate
Frigate was created to address the issues that authors have encountered in the previous frameworks, namely integrity and efficiency. It includes the optimizations that were proposed after the creation of these frameworks.

Folder contains instructions to compile Frigate, and .wir files to be run in Frigate.

### Obliv-C
Obliv-C is a gcc wrapper that guarantees secure computation if the underlying protocol is secure. It is more extensible and the language is very similar to C, but includes a new obliv datatype. It is written to be practical and the programmer does not need to be an expert in cryptography. It provides a higher-level programming abstractions, which simplifies the developing process. 

Folder contains .c and .oc files to be run in Obliv-C.

### Data
generate_input.py can be used to generate input and sample output files for each framework and for each benchmark like so:
```
python generate_input.py tinygarble mergesort alice.txt bob.txt 32 1000
````
The code above, for example, generates two text files with random positive integers up to 1000, as well as a tinygarble_trueoutput.txt file that contains the sorted version of the two files.
