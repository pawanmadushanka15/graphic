#include <glut.h>
#include <math.h>

int xi=400;
int yi=400;
int r=200;

int ww = 800, wh = 800;

void display()
{
	glClearColor(0.0,0.0,1.0,1.0);
	glColor3f(0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void putPixel(int x,int y,float a,float b,float c)
{
	if(((x-xi)*(x-xi)+(y-yi)*(y-yi)-(r+1)*(r+1))<=0)
	{
		glPointSize(2.0);
		glColor3f(a,b,c);
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
		glFlush();
	}
}

void plotCircle(int h,int k,int x,int y,float a,float b,float c)
{
	putPixel(x+h,y+k,a,b,c);
	putPixel(y+h,x+k,a,b,c);
	putPixel(y+h,-x+k,a,b,c);
	putPixel(x+h,-y+k,a,b,c);
	putPixel(-x+h,-y+k,a,b,c);
	putPixel(-y+h,-x+k,a,b,c);
	putPixel(-y+h,x+k,a,b,c);
	putPixel(-x+h,y+k,a,b,c);
}

void bresenhamCircle(int h,int k,float a,float b,float c)
{
	int x=0,y=r,p=1-r;
	while(x<=y)
	{
		plotCircle(h,k,x,y,a,b,c);
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

void mouse(int btn,int state,int x,int y)
{
	const double PI=3.14;
	double cos60=cos((60*PI)/180);
	double sin60=sin((60*PI)/180);

	bresenhamCircle(xi,yi,0.0,0.0,0.0);
	bresenhamCircle((int)xi+r*cos60,(int)yi+r*sin60,1.0,0.0,0.0);
	bresenhamCircle((int)xi+r*cos60,(int)yi-r*sin60,1.0,0.0,0.0);
	bresenhamCircle((int)xi-r*cos60,(int)yi-r*sin60,0.0,1.0,0.0);
	bresenhamCircle((int)xi-r*cos60,(int)yi+r*sin60,0.0,1.0,0.0);
	bresenhamCircle(xi+r,yi,0.0,1.0,0.0);
	bresenhamCircle(xi-r,yi,1.0,0.0,0.0);
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
    glutCreateWindow("Bresenham Line Algorithm");
    glutDisplayFunc(display);
    myinit();
	glutMouseFunc(mouse); 
    glutMainLoop();
    return 0;
}
