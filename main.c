/*
项目: 数码相框特效
创建者:嵌入式141 张静
导师:李建华
日期:2015 12 26
版本 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "fb.h"
#include "jpeg.h"
	struct fb_info fb;
	struct color c;
	struct img m;
	int ret = -1;
	int location;
	int fd = -1;
	int x, y,x1;
	char buf[3];
void SX(void); //上下向两边合
void X_S(void); //从上而下
void S_X(void);	//从下而上
void Left_R(void); //从左向右
void Right_L(void); //从右向左
void L_R(void); //左右向两边
void HS(void); // 四边游走
void HS2(void); //四边倒游走
void BYC_SP(void);//百页窗 水平
void BYC_CZ(void); //百叶窗 垂直
void move(void); // 移动 
int main()
{
	bzero(&fb,sizeof(fb));
	ret = init_fb("/dev/fb0",&fb);
	if(ret == -1)
	{
		printf("init framebuffer error!\n");
	}	
					bzero(&c,sizeof(c));
	bzero(&m,sizeof(m));
	m.buffer = (char *)malloc(fb.size);
	clear_fb(&fb);
	 open_img("./6.jpg", &m);
	S_X();//调用上下向中间的效果
	open_img("./1.jpg", &m);
	X_S();//调用
	open_img("./2.jpg", &m);
	L_R();//调用
	open_img("./3.jpg", &m);
	Right_L();//调用
	open_img("./4.jpg", &m);
	Left_R();
	open_img("./5.jpg", &m);
	SX();
	open_img("./7.jpg", &m);
	HS();
	open_img("./8.jpg", &m);
	HS2();
	open_img("./9.jpg", &m);
	BYC_SP();
	open_img("./10.jpg",&m);
	BYC_CZ();
	open_img("./11.jpg",&m);
	move();
	free(m.buffer);
	m.buffer = NULL;
	free_fb(&fb);
	
	return 0;
}
//----------------------------------------------------
void SX(void) //从上下向中间
{
	for(y = 0; y < m.high/2; y++)
	{	
		usleep(5000);	
		for(x = 0; x < m.width; x++)
		{
			location = (x + (y * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y, &c, &fb);
			location = (x + ((m.high-y-1) * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, (m.high-y-1), &c, &fb);
		}
	}
}
void X_S(void)//由下而上
{
	for(y = m.high-1; y >= 0; y--)
	{
		usleep(5000);	
		for(x = 0; x < m.width; x++)
		{
			location = (x + y * m.width)*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y, &c, &fb);
		}
	}
}
void S_X(void)//由上而下
{
	for(y = 0; y<=m.high; y++)
	{
		usleep(5000);	
		for(x = 0; x < m.width; x++)
		{
			location = (x + y * m.width)*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y, &c, &fb);
		}
	}
	
}
void Left_R(void) //从左向右
{
	for(x = 0; x < m.width; x++)
	{
		usleep(3000);	
		for(y = 0; y < m.high; y++)
		{
			location = (x + (y * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y, &c, &fb);
		}
	}
}
void Right_L(void) //从右向左
{
	for(x = m.width-1; x >=0; x--)
	{
		usleep(3000);	
		for(y = 0; y < m.high; y++)
		{
			location = (x + (y * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y, &c, &fb);
		}
	}
}
void L_R(void) //左右向中间
{
	for(x = 0; x < m.width/2+1; x++)
	{	x1=x;	
		usleep(5000);	
		for(y = 0; y < m.high; y++)
		{
			location = (x + (y * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y, &c, &fb);
		}
		x=m.width-x;
		
			for(y = 0; y < m.high; y++)
				{
				location = (x + (y * m.width))*3;
				c.blue = m.buffer[location + 2];
				c.green = m.buffer[location+1];
				c.red = m.buffer[location];
				set_p(x, y, &c, &fb);
				}
		x=x1;
}
}
void HS(void)
{
	for(y=0;y<=m.high;y++)
	{
	usleep(3000);
	for(x=0;x<=250;x++)
		{
			location=(x+(y*m.width))*3;
			c.blue=m.buffer[location+2];
			c.green=m.buffer[location+1];
			c.red=m.buffer[location];
			set_p(x,y,&c,&fb);
		}
	}
	for(x=250;x<=m.width;x++)
	{
usleep(1000);
		for(y=300;y<=m.high;y++)
			{
				location=(x+(y*m.width))*3;
				c.blue=m.buffer[location+2];
				c.green=m.buffer[location+1];
				c.red=m.buffer[location];
				set_p(x,y,&c,&fb);
			}	
	} 
	for(y = 300; y >= 0; y--)
	{
		usleep(5000);	
		for(x = 774; x < m.width; x++)
		{
			location = (x + y * m.width)*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y, &c, &fb);
		}
	}
	for(x =774; x >=0; x--)
	{
		usleep(3000);	
		for(y = 0; y < 300; y++)
		{
			location = (x + (y * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y, &c, &fb);
		}
	}
}
void HS2(void)
{
	for(x =250; x <=m.width; x++)
	{
		usleep(3000);	
		for(y = 0; y < 300; y++)
		{
			location = (x + (y * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y, &c, &fb);
		}
	}
	for(y = 300; y <= m.high; y++)
	{
		usleep(5000);	
		for(x = 774; x < m.width; x++)
		{
			location = (x + y * m.width)*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y, &c, &fb);
		}
	}
	for(x=774;x>=0;x--)
	{
		usleep(1000);
		for(y=300;y<=m.high;y++)
			{
				location=(x+(y*m.width))*3;
				c.blue=m.buffer[location+2];
				c.green=m.buffer[location+1];
				c.red=m.buffer[location];
				set_p(x,y,&c,&fb);
			}	
	} 
	for(y=300;y>=0;y--)
	{
	usleep(3000);
	for(x=0;x<=250;x++)
		{
			location=(x+(y*m.width))*3;
			c.blue=m.buffer[location+2];
			c.green=m.buffer[location+1];
			c.red=m.buffer[location];
			set_p(x,y,&c,&fb);
		}
	}
}
void BYC_SP(void)
{
	for(y = m.high/4; y >=0; y--)
	{	
		usleep(5000);	
		for(x = 0; x < m.width; x++)
		{
			location = (x + (y * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y, &c, &fb);
			location = (x + ((m.high-y-1) * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, (m.high-y-1), &c, &fb);
		
			
			location = (x + ((y+m.high/4) * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x,(y+m.high/4), &c, &fb);
			location = (x + ((m.high-(y+m.high/4)-1) * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, (m.high-(y+m.high/4)-1), &c, &fb);
		}
	}	
}
void BYC_CZ(void)
{
	for(x = m.width/8; x >=0; x--)
	{	
		usleep(5000);	
		for(y = 0; y < m.high; y++)
		{
			location = (x + (y * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y, &c, &fb);

			location = ((m.width-x-1) + y * m.width)*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p((m.width-x-1), y, &c, &fb);
		
			location = ((x+m.width/8) + y * m.width)*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p((x+m.width/8), y, &c, &fb);
			
			location = ((m.width-(x+m.width/8)-1) + (y * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p((m.width-(x+m.width/8)-1), y, &c, &fb);
		
			location = ((x+m.width/4) + y * m.width)*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p((x+m.width/4), y, &c, &fb);
			
			location = ((m.width-(x+m.width/4)-1) + (y * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p((m.width-(x+m.width/4)-1), y, &c, &fb);
		
			location = ((x+m.width/2) + y * m.width)*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p((x+m.width/2), y, &c, &fb);
			
			location = ((m.width-(x+m.width/2)-1) + (y * m.width))*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p((m.width-(x+m.width/2)-1), y, &c, &fb);
		}
	}	
}

void move(void)
{
	int i;
	int num=10;
	for(i=0; i < fb.y_size; i=i+num)
	{
		usleep(50);	
	for(y = m.high-i-1; y < m.high; y++)
	{
		for(x = 0; x < m.width; x++)
		{
			location = (x + y * m.width)*3;
			c.blue = m.buffer[location + 2];
			c.green = m.buffer[location+1];
			c.red = m.buffer[location];
			set_p(x, y - (fb.y_size-i-1), &c, &fb);
		}
	}
	if(i > 500)
	num = 5;
	if(i >550)
	num = 2;
	if(i > 590)
	num = 1;
	}
	
}











