bmp.o: bmp.c bmp.h
	gcc -c bmp.c

serpinsky.o: serpinsky.c bmp.h
	gcc -c serpinsky.c

mandelbrot.o: mandelbrot.c bmp.h
	gcc -c mandelbrot.c

serpinsky: bmp.o serpinsky.o
	gcc bmp.o serpinsky.o -o serpinsky

mandelbrot: bmp.o mandelbrot.o
	gcc bmp.o mandelbrot.o -o mandelbrot

serpinsky_bmp: serpinsky
	./serpinsky

mandelbrot_bmp: mandelbrot
	./mandelbrot
