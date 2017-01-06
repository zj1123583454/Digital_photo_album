#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "fb.h"

int init_fb(const char * fb_path, struct fb_info * fb)
{
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
	fb->fb_fd = open(fb_path, O_RDWR);
	if(fb->fb_fd == -1)
	{
		perror("Error: cannot open framebuffer device");
        return -1;
    }
    // Get fixed screen information
    if(ioctl(fb->fb_fd, FBIOGET_FSCREENINFO, &finfo) == -1)
	{
        perror("Error reading fixed information");
        return -1;
 	}

    // Get variable screen information
    if (ioctl(fb->fb_fd, FBIOGET_VSCREENINFO, &vinfo) == -1)
	{
        perror("Error reading variable information");
        return -1;
    }
	fb->x_size = vinfo.xres;
	fb->y_size = vinfo.yres;
 	fb->bpp = vinfo.bits_per_pixel;
	fb->xoffset = vinfo.xoffset;
	fb->yoffset = vinfo.yoffset;
	fb->size = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
	fb->line_length = finfo.line_length;
	fb->fb_mem = (char *)mmap(0, fb->size, PROT_READ | PROT_WRITE, MAP_SHARED,fb->fb_fd, 0);
    if ((int)fb->fb_mem == -1) {
        perror("Error: failed to map framebuffer device to memory");
        return -1;
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

	return 0;
}

int set_p(int x, int y, struct color * c, struct fb_info * fb)
{
	int location = (x+fb->xoffset) * (fb->bpp/8) +
                       (y+fb->yoffset) * fb->line_length;
	
	if(location < fb->size)
	{
		*(fb->fb_mem + location) = c->blue;
		*(fb->fb_mem + location + 1) = c->green;
		*(fb->fb_mem + location + 2) = c->red;
		*(fb->fb_mem + location + 3) = c->tou;  
	}
	
	return 0;
}


int clear_fb(struct fb_info * fb){

	bzero(fb->fb_mem,fb->size);
	return 0;
} 
int free_fb(struct fb_info * fb)
{
	munmap(fb->fb_mem, fb->size);	
	close(fb->fb_fd);
	bzero(fb,sizeof(struct fb_info));

	return 0;
}

