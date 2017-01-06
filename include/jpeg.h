#ifndef __JPEG_H__
#define __JPEG_H__

struct img {
int width;
int high;
char * buffer;
};

int open_img(const char * path, struct img * img);
	
#endif
