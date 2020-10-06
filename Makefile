SHELL379: SHELL379.o helperFunction.o Calc_time.o
	gcc -ggdb -Wall  -o SHELL379 SHELL379.o helperFunction.o Calc_time.o

SHELL379.o: main.c main.h helperFunction.h Calc_time.h
	gcc -ggdb -Wall  -o SHELL379.o -c main.c

helperFunction.o: helperFunction.c helperFunction.h
	gcc -ggdb -Wall  -c helperFunction.c

Calc_time.o: Calc_time.c Calc_time.h
	gcc -ggdb -Wall  -c Calc_time.c

clean:
	rm SHELL379 SHELL379.o helperFunction.o Calc_time.o