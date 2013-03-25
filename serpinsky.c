#include <stdlib.h>
#include "bmp.h"

int main() {
	int x0 = 1;
	int y0 = 1;
	
	int x1 = 199;
	int y1 = 1;

	int x2 = 1;
	int y2 = 199;

	int x = 10;
	int y = 10;
	
	Canvas * canv = new_canvas(200, 200);

	int i;
	int r;

	for(i = 0; i < 10000; i++) {
		set_pixel(x, y, rgb(255, 255, 0), canv);
		r = rand() % 3;
		switch(r) {
			case 0:
				x = (x0 + x) / 2;
				y = (y0 + y) / 2;
				break;
			case 1:
				x = (x1 + x) / 2;
                                y = (y1 + y) / 2;
				break;
			case 2:
				x = (x2 + x) / 2;
                                y = (y2 + y) / 2;
				break;
		}
	}

	write_bmp("fract.bmp", canv);
	return 0;
}
