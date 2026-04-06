#include <glut.h>
#include <math.h> 

int ww = 800, wh = 600;
int xi, yi, xf, yf; 

void putPixel(int x,int y)
{
	glBegin(GL_POINTS);
	glColor3f(1.0,0.0,0.0);
	glVertex2i(x,y);
	glEnd();
	glFlush();
}

void plotCircle(int h,int k,int x,int y)
{
	putPixel((x+h),(y+k));
	putPixel((y+h),(x+k));
	putPixel((y+h),(-x+k));
	putPixel((x+h),(-y+k));
	putPixel((-x+h),(-y+k));
	putPixel((-y+h),(-x+k));
	putPixel((-y+h),(x+k));
	putPixel((-x+h),(y+k));
}

void bresenhamCircle(int h,int k,int r)
{
	int x=0,y=r,d=3-2*r;
	while(x<=y)
	{
		plotCircle(h,k,x,y);
		if(d<0)
		{
			d=d+4*x+6;
		}
		else
		{
			d=d+4*(x-y)+10;
			y--;
		}
		x++;
	}
}

void display()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
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
			int r=(int)sqrt((double)(xi-xf)*(xi-xf)+(yi-yf)*(yi-yf));
			bresenhamCircle(xi,yi,r);
		}
	}
	if(btn==GLUT_RIGHT_BUTTON)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}



void myinit()  
{        
     glViewport(0,0,ww,wh);  
     glMatrixMode(GL_PROJECTION);  
     glLoadIdentity();  
     gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);  
     glMatrixMode(GL_MODELVIEW);  
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
     glutMainLoop();  
     return 0;  
} 