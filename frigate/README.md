# Frigate

## How to run


1. Follow instructions on [frigaterelease](https://bitbucket.org/bmood/frigaterelease/src/master/src/README.txt) to compile and install frigate
2. Copy *.wir files to ~/frigaterelease/src/tests
3. Generate an input file using the generate_input.py tool
4. Save the input to ~/frigaterelease/src/inputs.txt
5. Navigate to ~/frigaterelease
6. Run ./frigate *benchmark.wir* -i -i_io

**NOTE:** Frigate requires Ubuntu 14.04
