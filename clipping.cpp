#include <glut.h>  
#include <math.h>  
int ww = 600, wh = 400;    
int xi,yi,xf,yf;

const int INSIDE=0;
const int TOP=8;
const int BOTTOM=4;
const int RIGHT=2;
const int LEFT=1;

const int xmin=50,xmax=250,ymin=50,ymax=250;

void putPixel(int x,int y)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();
}

void brehensam(int x0,int y0,int x1,int y1)
{
	int dx=abs(x0-x1);
	int dy=abs(y0-y1);
	int ds,dt,d,x,y;

	if(dx>=dy)
	{
		d=2*dy-dx;
		ds=2*dy;
		dt=2*(dy-dx);

		if(x0<x1)
		{
			x=x0;
			y=y0;
		}
		else
		{
			x=x1;
			y=y1;
			x1=x0;
			y1=y0;
		}
		while(x<x1)
		{
			if(d<0)
			{
				d+=ds;
			}
			else
			{
				if(y<y1)
				{
					y++;
					d+=dt;
				}
				else
				{
					y--;
					d+=dt;
				}
			}
			x++;
			putPixel(x,y);
		}
	}
	else
	{
		d=2*dx-dy;
		ds=2*dx;
		dt=2*(dx-dy);

		if(y0<y1)
		{
			x=x0;
			y=y0;
		}
		else
		{
			x=x1;
			y=y1;
			x1=x0;
			y1=y0;
		}
		while(y<y1)
		{
			if(d<0)
			{
				d+=ds;
			}
			else
			{
				if(x<x1)
				{
					x++;
					d+=dt;
				}
				else
				{
					x--;
					d+=dt;
				}
			}
			y++;
			putPixel(x,y);
		}
	}
}

int computeOutcode(int x,int y)
{
	int outCode=INSIDE;
	if(x<xmin)
		outCode|=LEFT;
	if(x>xmax)
		outCode|=RIGHT;
	if(y>ymax)
		outCode|=TOP;
	if(y<ymin)
		outCode|=BOTTOM;
	return outCode;
}

void clipping(int x0,int y0,int x1,int y1)
{
	int outCode0,outCode1,outCode;
	bool accept=false,done=false;
	do{
		outCode0=computeOutcode(x0,y0);
		outCode1=computeOutcode(x1,y1);

		if(!(outCode0 | outCode1))
		{
			accept=true;
			done=true;
		}
		else if(outCode0 & outCode1)
		{
			done=true;
		}
		else
		{
			int x,y;
			outCode=outCode0?outCode0:outCode1;
			
			if(outCode & TOP)
			{
				x=x0+(ymax-y0)*(x1-x0)/(y1-y0);
				y=ymax;
			}
			else if(outCode & BOTTOM)
			{
				x=x0+(ymin-y0)*(x1-x0)/(y1-y0);
				y=ymin;
			}
			else if(outCode & LEFT)
			{
				y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
				x=xmin;
			}
			else if(outCode & RIGHT)
			{
				y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
				x=xmax;
			}

			if(outCode==outCode0)
			{
				x0=x;
				y0=y;
			}
			else{
				x1=x;
				y1=y;
			}

		}
	}while(!(done));

	if(accept)
	{
		brehensam(x0,y0,x1,y1);
	}
}

void display()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	glVertex2i(xmin,ymax);
	glVertex2i(xmax,ymax);
	glVertex2i(xmax,ymin);
	glVertex2i(xmin,ymin);
	glEnd();
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
			clipping(xi,yi,xf,yf);
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
     glutCreateWindow("Bresenham Line Algorithm");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
     glutMainLoop();  
     return 0;  
}  