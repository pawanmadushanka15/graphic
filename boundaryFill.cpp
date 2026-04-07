#include <glut.h>
#include <math.h> 
#include <stdio.h>
#include<iostream>
#include <windows.h>

int ww = 800, wh = 600;
int xi,xf,yi,yf,r;

struct Color
{
	float r,g,b;
};

struct Color interiorColor={1.0,1.0,1.0};
struct Color borderColor={0.0,0.0,0.0};
struct Color fillColor={1.0,0.0,1.0};

void putPixel(int x,int y)
{
	glColor3f(borderColor.r,borderColor.g,borderColor.b);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();
}

struct Color getPixelColor(int x,int y)
{
	struct Color color;
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,&color);
	return color;
}

void setPixelColor(int x,int y,struct Color color)
{
	glColor3f(color.r,color.g,color.b);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();
}

void boundaryFill4(int x,int y,struct Color fill_color,struct Color border_color)
{
	struct Color color=getPixelColor(x,y);
	
	if(border_color.r!=color.r && border_color.g!=color.g && border_color.b!=color.b)
	{
		setPixelColor(x,y,fill_color);
		boundaryFill4(x,y+1,fill_color,border_color);
		boundaryFill4(x,y-1,fill_color,border_color);
		boundaryFill4(x-1,y,fill_color,border_color);
		boundaryFill4(x+1,y,fill_color,border_color);
	}
}

void plotCircle(int h, int k, int x, int y)
{
	putPixel((x+h), (y+k));
	putPixel((y+h), (x+k));
	putPixel((-y+h), (x+k));
	putPixel((-x+h), (y+k));
	putPixel((-x+h), (-y+k));
	putPixel((-y+h), (-x+k));
	putPixel((y+h), (-x+k));
	putPixel((x+h), (-y+k));

}

void bresenhamCircle(int h, int k, int r)
{
	int x=0, y=r, d= 3-2*r;
	while(x <= y)
	{
		 plotCircle(h, k, x, y);
		if(d<0)
		{
			d = d + 4*x + 6; 
		}
		else
		{
			d = d + 4*(x-y) + 10;
			y--;
		}
		x++;
	}
}

void keyboard(unsigned char key,int x,int y)
{
	if (key=='q' || key=='Q')
	{
		exit(0);
	}
	else if (key=='f' || key=='F')
	{
		boundaryFill4(xi,yi,fillColor,borderColor);
	}
}

void mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON)
	{
		if(state==GLUT_DOWN)
		{
			xi=x;
			yi=(wh-y);
		}
		else if(state==GLUT_UP)
		{
			xf=x;
			yf=(wh-y);
			r=(int)sqrt((float)((xi-xf)*(xi-xf)+(yi-yf)*(yi-yf)));
			bresenhamCircle(xi,yi,r);
		}
	}
}

void display()  
{  
   glClearColor(interiorColor.r, interiorColor.g, interiorColor.b, 1.0);  
   glColor3f(0.2, 0.3, 0.3);  
   glClear(GL_COLOR_BUFFER_BIT);  

   glFlush();  
} 





void myinit()  
{        
    glClearColor(1.0,1.0,1.0,0);
  	glColor3f(0.0,0.0,0.0);
  	glPointSize(1.0);
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	gluOrtho2D(0 , ww , 0 , wh);  
}  
int main(int argc, char** argv)  
{  
     glutInit(&argc,argv);  
     glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  
     glutInitWindowSize(ww,wh);  
     glutCreateWindow("Bresenham Circle Algorithm");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
	 glutKeyboardFunc(keyboard);
     glutMainLoop();  
     return 0;  
} 