GCC  = gcc
FLAGS = -ansi -pedantic -Wall -std=c99 
C_FLAGS = -fopenmp
PROGRAMAS = matrices

matrices:
	$(GCC) $(FLAGS) funcionesMatrices.c -c $(C_FLAGS)
	$(GCC) $(FLAGS) funcionesTime.c -c $(C_FLAGS)
	$(GCC) $(FLAGS) $@.c -c $(C_FLAGS)
	$(GCC) $(FLAGS) -o $@ $@.o funcionesMatrices.o funcionesTime.o $(C_FLAGS)

clean:
	$(RM) $(PROGRAMAS) *.o