# TinyGarble

## How to run


1. Follow instructions on [TinyGarble](https://github.com/esonghori/TinyGarble) to compile and install TinyGarble
2. Copy *.scd files to ~/TinyGarble/bin/netlists
3. Generate an input file using the generate_input.py tool
4. Save the input to ~/TinyGarble/bin/alice.txt & bob.txt
5. Navigate to ~/TinyGarble/bin
6. Run ./garbled_circuit/TinyGarble --alice --scd_file netlists/*benchmark.scd* -input alice.txt
