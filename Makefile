all:
	gcc -Wall -o prog main.c sudoku.c

test:
	@echo "*** TESTING : ***\n"
	./prog
