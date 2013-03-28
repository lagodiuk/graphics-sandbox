#include <stdint.h>

typedef
uint8_t
Byte;

typedef
struct {
	Byte r;
	Byte g;
	Byte b;
}
Color;

typedef
struct {
	int w;
	int h;
	Color * data;
}
Canvas;

inline Color rgb(Byte r, Byte g, Byte b);

Canvas * new_canvas(int width, int height);

void release(Canvas * canv);

inline void set_pixel(int x, int y, Color c, Canvas * canv);

inline Color get_pixel(int x, int y, Canvas * canv);

int write_bmp(char file_name[], Canvas * canv);
