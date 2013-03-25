#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

Color rgb(Byte r, Byte g, Byte b) {
	Color c;
	c.r = r;
	c.g = g;
	c.b = b;
	return c;
}

Canvas * new_canvas(int width, int height) {
	Canvas * c = (Canvas *) malloc(sizeof(Canvas));
	c->w = width;
	c->h = height;
	c->data = (Color *) calloc(width * height, sizeof(Color));
	return c;
}

void set_pixel(int x, int y, Color c, Canvas * canv) {
	int offs = y * canv->w + x;
	canv->data[offs] = c;
}

Color get_pixel(int x, int y, Canvas * canv) {
	int offs = y * canv->w + x;
	return canv->data[offs];
}

void set_bfType(Byte bmp_file_header[]) {
	bmp_file_header[0] = 'B';
	bmp_file_header[1] = 'M';
}

void set_bfSize(int size, Byte bmp_file_header[]) {
	bmp_file_header[2] = (Byte) size;
	bmp_file_header[3] = (Byte) (size >> 8);
	bmp_file_header[4] = (Byte) (size >> 16);
	bmp_file_header[5] = (Byte) (size >> 24);
}

void set_bfReserved1(Byte bmp_file_header[]) {
	bmp_file_header[6] = 0;
	bmp_file_header[7] = 0;
}

void set_bfReserved2(Byte bmp_file_header[]) {
        bmp_file_header[8] = 0;
        bmp_file_header[9] = 0;
}

void set_bfOffBits(Byte bmp_file_header[]) {
	bmp_file_header[10] = 54;
        bmp_file_header[11] = 0;
	bmp_file_header[12] = 0;
        bmp_file_header[13] = 0;
}

int get_padding(int w) {
	int padding = 4 - (w - (w / 4) * 4);
	return (padding < 4) ? padding : 0;
}

void set_biSize(Byte bmp_info_header[]) {
	bmp_info_header[0] = 40;
	bmp_info_header[1] = 0;
	bmp_info_header[2] = 0;
	bmp_info_header[3] = 0;
}

void set_biWidth(int w, Byte bmp_info_header[]) {
	bmp_info_header[4] = (Byte) w;
	bmp_info_header[5] = (Byte) (w >> 8);
	bmp_info_header[6] = (Byte) (w >> 16);
	bmp_info_header[7] = (Byte) (w >> 24);
}

void set_biHeight(int h, Byte bmp_info_header[]) {
        bmp_info_header[8] = (Byte) h;
        bmp_info_header[9] = (Byte) (h >> 8);
        bmp_info_header[10] = (Byte) (h >> 16);
        bmp_info_header[11] = (Byte) (h >> 24);
}


void set_biPlanes(Byte bmp_info_header[]) {
	bmp_info_header[12] = 1;
        bmp_info_header[13] = 0;
}

void set_biBitCount(Byte bmp_info_header[]) {
        bmp_info_header[14] = 24;
        bmp_info_header[15] = 0;
}

void set_biCompression(Byte bmp_info_header[]) {
        bmp_info_header[16] = 0;
        bmp_info_header[17] = 0;
	bmp_info_header[18] = 0;
        bmp_info_header[19] = 0;
}

void set_biSizeImage(int s, Byte bmp_info_header[]) {
        bmp_info_header[20] = (Byte) s;
        bmp_info_header[21] = (Byte) (s >> 8);
        bmp_info_header[22] = (Byte) (s >> 16);
        bmp_info_header[23] = (Byte) (s >> 24);
}

void set_biXPixelsPerMeter(Byte bmp_info_header[]) {
        bmp_info_header[24] = 0;
        bmp_info_header[25] = 0;
        bmp_info_header[26] = 0;
        bmp_info_header[27] = 0;
}

void set_biYPixelsPerMeter(Byte bmp_info_header[]) {
        bmp_info_header[28] = 0;
        bmp_info_header[29] = 0;
        bmp_info_header[30] = 0;
        bmp_info_header[31] = 0;
}

void set_biClrUsed(Byte bmp_info_header[]) {
        bmp_info_header[32] = 0;
        bmp_info_header[33] = 0;
        bmp_info_header[34] = 0;
        bmp_info_header[35] = 0;
}

void set_biClrImportant(Byte bmp_info_header[]) {
        bmp_info_header[36] = 0;
        bmp_info_header[37] = 0;
        bmp_info_header[38] = 0;
        bmp_info_header[39] = 0;
}

int write_bmp(char file_name[], Canvas * canv) {
	int pad = get_padding(canv->w);
	int row_len = (canv->w + pad) * 3;
	int raster_size = row_len * canv->h;
	int file_size = raster_size + 54;

	Byte bmp_file_header[14];
	set_bfType(bmp_file_header);
	set_bfSize(file_size, bmp_file_header);
	set_bfReserved1(bmp_file_header);
	set_bfReserved2(bmp_file_header);
	set_bfOffBits(bmp_file_header);

	Byte bmp_info_header[40];
	set_biSize(bmp_info_header);
	set_biWidth(canv->w, bmp_info_header);
	set_biHeight(canv->h, bmp_info_header);
	set_biPlanes(bmp_info_header);
	set_biBitCount(bmp_info_header);
	set_biCompression(bmp_info_header);
	set_biSizeImage(raster_size, bmp_info_header);
	set_biXPixelsPerMeter(bmp_info_header);
	set_biYPixelsPerMeter(bmp_info_header);  
	set_biClrUsed(bmp_info_header);
	set_biClrImportant(bmp_info_header);

	FILE * f = fopen(file_name, "wb");
	if(f == NULL) {
		return 0;
	}

	fwrite(bmp_file_header, 1, 14, f);
	fwrite(bmp_info_header, 1, 40, f);

	int i;
	int j;
	Byte * row = (Byte *) calloc(row_len, 1);
	for(i = 0; i < canv->h; i++) {
		for(j = 0; j < canv->w; j++) {
			Color c = get_pixel(j, canv->h - i - 1, canv);
			row[j * 3] = c.b;
			row[j * 3 + 1] = c.g;
			row[j * 3 + 2] = c.r;
		}
		fwrite(row, 1, row_len, f);
	}

	fclose(f);
	free(row);

	return 1;
}
