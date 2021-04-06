gameoflife.out: main.o list.o one_cycle.o output_to_file.o sparse_matrix.o
	gcc -o gameoflife.out main.o list.o one_cycle.o output_to_file.o sparse_matrix.o -lpng

list.o: list.h one_cycle.h output_to_file.h sparse_matrix.h
	gcc -c list.c

one_cycle.o: list.h one_cycle.h output_to_file.h sparse_matrix.h
	gcc -c one_cycle.c

output_to_file.o: list.h one_cycle.h output_to_file.h sparse_matrix.h
	gcc -c output_to_file.c -lpng

sparse_matrix.o: list.h one_cycle.h output_to_file.h sparse_matrix.h
	gcc -c sparse_matrix.c

.PHONY: clean-o clean-png clean-txt test25 test50 test400

clean-o:
	-rm *.o *.out

clean-png:
	-rm outputPNG/* 

clean-txt:
	-rm outputTXT/* 

test25:
	./gameoflife.out -f ../init_boards/ut_25_25.txt -n 30

test50:
	./gameoflife.out -f ../init_boards/ut_50_50.txt -n 30

test400:
	./gameoflife.out -f ../init_boards/ut_400_400.txt -n 30
