OBLIVCC=../../../../bin/oblivcc
RUNTIME=../../../../_build/libobliv.a
PORT=1234
REMOTE_HOST=localhost
CONNECTION = $(REMOTE_HOST):$(PORT)
CILPATH=../../../../
CFLAGS=-g -Wall
LOADLIBES=-lm
testName=bubblesort
TX=tx.dat
TY=ty.dat

./a.out: $(testName).oc $(testName).c ../../common/util.c ../utils.c ../utils.oc $(RUNTIME)
	$(OBLIVCC) $(CFLAGS) -I .  ../utils.c $(testName).oc $(testName).c  ../../common/util.c ../utils.oc $(LOADLIBES)

clean:
	rm -f a.out $(testName).oc.cil.i $(testName).oc.i $(testName).oc.cil.c

# Run tests quickly
t1:
	$(./a.out)
	./a.out $(CONNECTION) 1 $(TX)

t2:
	$(./a.out) 
	./a.out $(CONNECTION) 2 $(TY)
