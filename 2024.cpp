#define _USE_MATH_DEFINES
#include <glut.h>  
#include <math.h>  
#include <cmath>
#include <iostream>
int ww = 800, wh = 800;  
  
int xi,yi,xf,yf;
int h=300,k=300,r=100;


void putPixel1(int x,int y)
{
	glPointSize(2.0);
	if(((x-h)*(x-h)+(y-k)*(y-k)-(r+1)*(r+1))<=0)
	{
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
		glFlush();
	}
	else
	{
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
		glFlush();
	}
	
}

void putPixel(int x,int y)
{
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();
}



void plotCircle(int x,int y)
{
	putPixel(x+h,y+k);
	putPixel(y+h,x+k);
	putPixel(y+h,-x+k);
	putPixel(x+h,-y+k);
	putPixel(-x+h,-y+k);
	putPixel(-y+h,-x+k);
	putPixel(-y+h,x+k);
	putPixel(-x+h,y+k);
}

void midpoint()
{
	 int x=0,y=r,p=1-r;
	 while(x<=y)
	 {
		 plotCircle(x,y);
		 if(p<0)
		 {
			 p=p+2*x+3;
		 }
		 else
		 {
			 y--;
			 p=p+2*(x-y)+5;
		 }
		 x++;
	 }

}

void bresenhamLine(int x0, int y0, int x1, int y1)  
{  
  int dx = abs (x1 - x0);  
  int dy = abs (y1 - y0);  
  int x, y;  
  if (dx >= dy)  
  {  
   int d = 2*dy-dx;  
   int ds = 2*dy;  
   int dt = 2*(dy-dx);  
       if (x0 < x1)   
       {  
            x = x0;  
            y = y0;  
        }  
        else  
        {   
            x = x1;  
            y = y1;  
            x1 = x0;  
            y1 = y0;  
        }  
	  putPixel1(x, y);  
	  while (x < x1)  
	  {  
		if (d < 0)  
			d += ds;  
			else {  
				 if (y < y1) {  
				   y++;  
				   d += dt;  
					}   
				 else {  
					y--;  
					d += dt;             
				 }  
			}  
			x++;  
			putPixel1(x, y);  
		}  
	}  
   else 
   {   
	   int d = 2*dx-dy;  
		 int ds = 2*dx;  
		 int dt = 2*(dx-dy);  
		 if (y0 < y1) 
		 {  
			 x = x0;  
			 y = y0;  
		 }  
		 else 
		 {   
			 x = x1;  
			 y = y1;  
			 y1 = y0;  
			 x1 = x0;  
		 }  
		putPixel1(x, y);   
		while (y < y1)  
		{  
			  if (d < 0)  
				 d += ds;  
			 else {  
				   if (x > x1)
				   {  
						x--;  
						d += dt;  
					} else 
					{  
						x++;  
						d += dt;  
					}                
				}  
			y++;  
			 putPixel1(x, y);
			 
	   }        
	}  
} 

void bresenhamLine1(int x0, int y0, int x1, int y1)  
{  
  int dx = abs (x1 - x0);  
  int dy = abs (y1 - y0);  
  int x, y;  
  if (dx >= dy)  
  {  
   int d = 2*dy-dx;  
   int ds = 2*dy;  
   int dt = 2*(dy-dx);  
       if (x0 < x1)   
       {  
            x = x0;  
            y = y0;  
        }  
        else  
        {   
            x = x1;  
            y = y1;  
            x1 = x0;  
            y1 = y0;  
        }  
	  putPixel(x, y);  
	  while (x < x1)  
	  {  
		if (d < 0)  
			d += ds;  
			else {  
				 if (y < y1) {  
				   y++;  
				   d += dt;  
					}   
				 else {  
					y--;  
					d += dt;             
				 }  
			}  
			x++;  
			putPixel(x, y);  
		}  
	}  
   else 
   {   
	   int d = 2*dx-dy;  
		 int ds = 2*dx;  
		 int dt = 2*(dx-dy);  
		 if (y0 < y1) 
		 {  
			 x = x0;  
			 y = y0;  
		 }  
		 else 
		 {   
			 x = x1;  
			 y = y1;  
			 y1 = y0;  
			 x1 = x0;  
		 }  
		putPixel(x, y);   
		while (y < y1)  
		{  
			  if (d < 0)  
				 d += ds;  
			 else {  
				   if (x > x1)
				   {  
						x--;  
						d += dt;  
					} else 
					{  
						x++;  
						d += dt;  
					}                
				}  
			y++;  
			 putPixel(x, y);
			 
	   }        
	}  
}

void lianbarsky(int xi,int yi,int xf,int yf)
{
	float t0=0,t1=1;
	float dx=xf-xi,dy=yf-yi;
	float p,q,r;
	float top=500,bottom=100,left=100,right=500;

	for(int edge=0;edge<4;edge++)
	{
		if(edge==0)
		{
			p=-dx;
			q=xi-left;
		}
		else if(edge==1)
		{
			p=dx;
			q=right-xi;
		}
		else if(edge==2)
		{
			p=-dy;
			q=yi-bottom;
		}
		else
		{
			p=dy;
			q=top-yi;
		}


	if(p==0)
	{
		if(q<0)
			return;
		else
			continue;
	}

	r=q/p;
	if(p<0)
	{
		if(r>t1)
			return;
		else if(r>t0)
			t0=r;
	}
	else if(p>0)
	{
		if(r<t0)
			return;
		else if(r<t1)
			t1=r;
	}

	}
	float x0=xi+t0*dx;
	float y0=yi+t0*dy;
	float x1=xi+t1*dx;
	float y1=yi+t1*dy;
	glColor3f(0.0,0.0,1.0);
	bresenhamLine(x0,y0,x1,y1);
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
			lianbarsky(xi,yi,xf,yf);
		}
	}

}

void keyboard(unsigned char key,int x,int y)
{
	if(key=='Q'|| key=='q')
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}

}

void activity()
{
	glColor3f(0.0,0.0,0.0);
	bresenhamLine1(100,500,500,500);
	bresenhamLine1(500,500,500,100);
	bresenhamLine1(500,100,100,100);
	bresenhamLine1(100,100,100,500);
	glColor3f(0.0,1.0,0.0);
	midpoint();
}


void display()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	activity();
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
     glutCreateWindow("Exam");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);
	 glutKeyboardFunc(keyboard);
     glutMainLoop();  
     return 0;  
}  