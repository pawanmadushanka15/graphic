#include <glut.h>
#include <math.h>
int ww = 600, wh = 400;
int xi=200;
int yi=200;
int r=100;

void putPixel1(int x,int y)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();
}

void putPixel2(int x,int y)
{
	if((int)((x-xi)*(x-xi)+(y-yi)*(y-yi)-(r+1)*(r+1))<=0)
	{
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
		glFlush();
	}
}

void plotCircle(int h,int k,int x,int y)
{
	putPixel2(x+h,y+k);
	putPixel2(y+h,x+k);
	putPixel2(y+h,-x+k);
	putPixel2(x+h,-y+k);
	putPixel2(-x+h,-y+k);
	putPixel2(-y+h,-x+k);
	putPixel2(-y+h,x+k);
	putPixel2(-x+h,y+k);
}



void bresenhamLine(int x0,int y0,int x1,int y1)
{
	int dx=abs(x1-x0);
	int dy=abs(y1-y0);
	int x,y;
	if(dx>dy)
	{
		int d=2*dy-dx;
		int ds=2*dy;
		int dt=2*(dy-dx);

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
		putPixel1(x,y);
		
		while(x<x1)
		{
			if(d<0)
			{
				d+=ds;;
			}
			else
			{
				if(y<y1)
				{
					y++;
				}
				else
				{
					y--;
				}
				d+=dt;
			}
			x++;
			putPixel1(x,y);
		}
	}
	else{
		int d=2*dx-dy;
		int ds=2*dx;
		int dt=2*(dx-dy);
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
		putPixel1(x,y);
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
				}
				else
				{
					x--;
				}
				d+=dt;
			}
			y++;
			putPixel1(x,y);
		}
	}
}

void bresenhamCircle(int h,int k)
{
	int x=0,y=r,p=1-r;
	while(x<=y)
	{
		plotCircle(h,k,x,y);
		if(p<0)
		{
			p=p+2*x+3;
		}
		else
		{
			p=p+2*(x-y)+5;
			y--;
		}
		x++;
	}
}

void display()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	bresenhamLine(300,200,250,287);
	bresenhamLine(250,287,150,287);
	bresenhamLine(150,287,100,200);
	bresenhamLine(100,200,150,113);
	bresenhamLine(150,113,250,113);
	bresenhamLine(250,113,300,200);

	bresenhamCircle(300,200);
	bresenhamCircle(250,287);
	bresenhamCircle(150,287);
	bresenhamCircle(100,200);
	bresenhamCircle(150,113);
	bresenhamCircle(250,113);


}



void myinit() {
    glViewport(0, 0, ww, wh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww, wh);
    glutCreateWindow("Bresenham Line Algorithm And Mid Point");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}
