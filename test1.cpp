#include <glut.h>  
#include <math.h>  
int ww = 600, wh = 400;    
int xi, yi, xf, yf;  

void putPixel(int x,int y)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}
 
void display()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void dda(int x0,int y0,int x1,int y1)
{
	int dx=(x1-x0),dy=(y1-y0),k,steps;
	float xincrement,yincrement,x=x0,y=y0;

	if (abs(dx)>abs(dy))
	{
		steps=abs(dx);
	}
	else
	{
		steps=abs(dy);
	}
	xincrement=dx/float(steps);
	yincrement=dy/float(steps);
	putPixel((int)x,(int)y);

	for (k=0;k<steps;k++)
	{
		x+=xincrement;
		y+=yincrement;
		putPixel((int)x,(int)y);
	}
}

void mouse(int btn,int state,int x,int y)
{
	if (btn==GLUT_LEFT_BUTTON)
	{
		if (state==GLUT_DOWN)
		{
			xi=x;
			yi=(wh-y);
		}
		else if(state==GLUT_UP)
		{
			xf=x;
			yf=(wh-y);
		}
		dda(xi,yi,xf,yf);
	}

	if (btn==GLUT_RIGHT_BUTTON)
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
     glutCreateWindow("dda Line Algorithm");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
     glutMainLoop();  
     return 0;  
}  