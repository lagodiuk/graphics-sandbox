typedef
unsigned char
Byte;

typedef
struct color {
	Byte r;
	Byte g;
	Byte b;
}
Color;

typedef
struct canvas {
	int w;
	int h;
	Color * data;
}
Canvas;

Color rgb(Byte r, Byte g, Byte b);

Canvas * new_canvas(int width, int height);

void set_pixel(int x, int y, Color c, Canvas * canv);

Color get_pixel(int x, int y, Canvas * canv);

void write_bmp(char file_name[], Canvas * canv);