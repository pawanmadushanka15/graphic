#define _USE_MATH_DEFINES
#include <glut.h>  
#include <math.h>  
#include <cmath>
#include <iostream>
int ww = 800, wh = 800;  
  
float xi, yi, xf, yf;  
const int rows=3;
const int noofVertices=4;
float coordinates[rows][noofVertices];

void setCoordinates(int xi,int yi,int xf,int yf)
{
	coordinates[0][0]=xi;
	coordinates[1][0]=yi;
	coordinates[2][0]=1;
	coordinates[0][1]=(xi+xf-yf+yi)/2;
	coordinates[1][1]=(yi+yf+xf-xi)/2;
	coordinates[2][1]=1;
	coordinates[0][2]=xf;
	coordinates[1][2]=yf;
	coordinates[2][2]=1;
	coordinates[0][3]=(xi+xf+yf-yi)/2;
	coordinates[1][3]=(yi+yf-xf+xi)/2;
	coordinates[2][3]=1;
}

void setrotationMatrix(float teta,float rotationMatrix[rows][rows])
{
	rotationMatrix[0][0]=cos(teta);
	rotationMatrix[1][0]=sin(teta);
	rotationMatrix[2][0]=0;
	rotationMatrix[0][1]=-1*sin(teta);
	rotationMatrix[1][1]=cos(teta);
	rotationMatrix[2][1]=0;
	rotationMatrix[0][2]=0;
	rotationMatrix[1][2]=0;
	rotationMatrix[2][2]=1;
}

void settranslationMatrix(float dx,float dy,float translationMatrix[rows][rows])
{
	translationMatrix[0][0]=1;
	translationMatrix[1][0]=0;
	translationMatrix[2][0]=0;
	translationMatrix[0][1]=0;
	translationMatrix[1][1]=1;
	translationMatrix[2][1]=0;
	translationMatrix[0][2]=dx;
	translationMatrix[1][2]=dy;
	translationMatrix[2][2]=1;
}

void setscaleMatrix(float sx,float sy,float scaleMatrix[rows][rows])
{
	scaleMatrix[0][0]=sx;
	scaleMatrix[1][0]=0;
	scaleMatrix[2][0]=0;
	scaleMatrix[0][1]=0;
	scaleMatrix[1][1]=sy;
	scaleMatrix[2][1]=0;
	scaleMatrix[0][2]=0;
	scaleMatrix[1][2]=0;
	scaleMatrix[2][2]=1;
}

void putPixel (int x, int y)  
{  
 
	glPointSize(2.0f);
   glBegin (GL_POINTS);  
	   glVertex2i (x, y); 
	glEnd ();  
   glFlush ();   
} 
 
void display()  
{  
   glClearColor(1.0, 1.0, 1.0, 1.0);  
   glColor3f(1.0, 0.0, 0.0);  
   glClear(GL_COLOR_BUFFER_BIT);  
   glFlush();  
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
	  putPixel (x, y);  
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
			putPixel (x, y);  
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
		putPixel (x, y);   
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
			 putPixel (x, y);
			 
	   }        
	}  
} 

void multiplyArray(float A[rows][rows],float B[rows][noofVertices],float C[rows][noofVertices])
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<noofVertices;j++)
		{
			C[i][j]=0;
			for(int k=0;k<rows;k++)
			{
				C[i][j]+=A[i][k]*B[k][j];
			}
		}
	}
}

void drawObject(float points[rows][noofVertices])
{
	for(int i=1;i<noofVertices;i++)
	{
		bresenhamLine((int)(points[0][i-1]),(int)(points[1][i-1]),(int)(points[0][i]),(int)(points[1][i]));
	}
	bresenhamLine((int)(points[0][0]),(int)(points[1][0]),(int)(points[0][3]),(int)(points[1][3]));
	
}

void activity()
{
	float degree=45;
	float teta=degree*M_PI/180;
	float tx=(xi+xf)/2;
	float ty=(yi+yf)/2;

	float translationMatrix1[3][3];
	settranslationMatrix(-tx,-ty,translationMatrix1);
	float rotationMatrix1[3][3];
	setrotationMatrix(teta,rotationMatrix1);
	float translationMatrix2[3][3];
	settranslationMatrix(tx,ty,translationMatrix2);

	float temp1[rows][noofVertices];
	float temp2[rows][noofVertices];
	float temp3[rows][noofVertices];

	multiplyArray(translationMatrix1,coordinates,temp1);
	multiplyArray(rotationMatrix1,temp1,temp2);
	multiplyArray(translationMatrix2,temp2,temp3);
	glColor3f(0.0,1.0,0.0);
	drawObject(temp3);

}

void activity2()
{
	float sx=0.5;
	float sy=0.5;
	float tx=(xi+xf)/2;
	float ty=(yi+yf)/2;

	float translationMatrix1[3][3];
	settranslationMatrix(-tx,-ty,translationMatrix1);
	float scaleMatrix1[3][3];
	setscaleMatrix(sx,sy,scaleMatrix1);
	float translationMatrix2[3][3];
	settranslationMatrix(tx,ty,translationMatrix2);

	float temp1[rows][noofVertices];
	float temp2[rows][noofVertices];
	float temp3[rows][noofVertices];

	multiplyArray(translationMatrix1,coordinates,temp1);
	multiplyArray(scaleMatrix1,temp1,temp2);
	multiplyArray(translationMatrix2,temp2,temp3);
	glColor3f(0.0,0.0,1.0);
	drawObject(temp3);
	glColor3f(0.0,0.0,0.0);
	bresenhamLine((int)(temp3[0][0]),(int)(temp3[1][0]),(int)(temp3[0][2]),(int)(temp3[1][2]));
	bresenhamLine((int)(temp3[0][1]),(int)(temp3[1][1]),(int)(temp3[0][3]),(int)(temp3[1][3]));

}



  

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)
		{
			xi=x;
			yi=(wh-y);
		}
		else if (state == GLUT_UP) 
		{
			xf=x;
			yf=(wh-y);
			setCoordinates(xi,yi,xf,yf);
			bresenhamLine(xi,yi,(xi+xf-yf+yi)/2,(yi+yf+xf-xi)/2);
			bresenhamLine((xi+xf-yf+yi)/2,(yi+yf+xf-xi)/2,xf,yf);
			bresenhamLine(xf,yf,(xi+xf+yf-yi)/2,(yi+yf-xf+xi)/2);
			bresenhamLine((xi+xf+yf-yi)/2,(yi+yf-xf+xi)/2,xi,yi);

		}
	if (btn == GLUT_RIGHT_BUTTON) 
	{
		activity();
		activity2();
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
     glutCreateWindow("Exam");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
     glutMainLoop();  
     return 0;  
}  