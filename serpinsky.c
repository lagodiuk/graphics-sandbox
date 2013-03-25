#include "bmp.h"

int main() {
	Canvas * canv = new_canvas(115, 20);
	set_pixel(10, 10, rgb(255, 0, 0), canv);
	set_pixel(11, 10, rgb(0, 255, 0), canv);
	set_pixel(12, 10, rgb(0, 0, 255), canv);
	set_pixel(0, 0, rgb(255, 255, 255), canv);
	write_bmp("test.bmp", canv);
	return 0;
}