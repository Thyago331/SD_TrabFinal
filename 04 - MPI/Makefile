FLAGS = -Wall -lm

all:
	mpicc mpi.c -o mpi $(FLAGS)

serial:
	mpicc serial.c -o serial $(FLAGS)

run:
	mpirun --oversubscribe -np $(np) ./mpi

clean:
	@echo "Limpando projeto"
	@rm -f mpi serial *.o

.PHONY: clean
