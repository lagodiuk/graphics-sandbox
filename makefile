bmp.o: bmp.c bmp.h
	gcc -c bmp.c

serpinsky.o: serpinsky.c bmp.h
	gcc -c serpinsky.c

serpinsky: bmp.o serpinsky.o
	gcc bmp.o serpinsky.o -o serpinsky
