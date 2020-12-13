all:
	gcc -g -Wall -o servidor servidor.c
	gcc -g -Wall -o clififo clififo.c

servidor:
	gcc -c servidor.c
clififo:
	gcc -c clififo.c

clean:
	$(RM) servidor servidor.o
	$(RM) clififo clififo.o
