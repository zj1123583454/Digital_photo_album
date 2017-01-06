#ifndef __FB_H__
#define __FB_H__

struct fb_info{
int x_size;
int xoffset;
int y_size;
int yoffset;
int line_length;
int bpp;
int size;
int fb_fd;
char * fb_mem;
};

struct color{
char blue;
char green;
char red;
char tou;
};

int init_fb(const char *, struct fb_info * );
int free_fb(struct fb_info *);
int clear_fb(struct fb_info *);
int set_p(int x, int y, struct color * c, struct fb_info *);

#endif








