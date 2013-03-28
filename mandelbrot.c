#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

#define MAX_ITER 50
#define WIDTH 1500
#define HEIGHT 1000
#define R_MAX 25.0
#define G_MAX 255.0
#define B_MAX 75.0

int main() {
	float x_min = -1.8;
	float y_min = -1.1;

	float x_max = 1.0;
	float y_max = 1.1;

	int w = WIDTH;
	int h = HEIGHT;

	Canvas * canv = new_canvas(w, h);
	int i;
	int j;
	float x0;
	float y0;
	float x;
	float y;
	int iter;
	float x_temp;
	Byte r;
	Byte g;
	Byte b;
	for(i = 0; i < h; i++) {
		for(j = 0; j < w; j++) {
			x0 = (float) j * (x_max - x_min) / w + x_min;
			y0 = (float) i * (y_max - y_min) / h + y_min;
			
			x = 0;
			y = 0;

			iter = 0;
			while((x * x + y * y < 2 * 2) && (iter < MAX_ITER)) {
				x_temp = x * x - y * y + x0;
				y = 2 * x * y + y0;
				x= x_temp;
				++iter;
			}
			r = (Byte) (iter * R_MAX / MAX_ITER);
			g = (Byte) (iter * G_MAX / MAX_ITER);
			b = (Byte) (iter * B_MAX / MAX_ITER);
			set_pixel(j, i, rgb(r, g, b), canv);
		}
	}
	write_bmp("m.bmp", canv);

	release(canv);
	return 0;
}
