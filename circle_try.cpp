#include<iostream>
#include<GL/freeglut.h>
#include<math.h>
#define w 500
#define h 500
int x1[2],y2[2],i=0,r;
using namespace std;
void setpixel(int x,int y)
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
	glFlush();

}

void initialise()
{
	int i;
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-w/2,w/2,-h/2,h/2);
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0.0,0.0,1.0)
	for(i=-500;i<500;i++)
	{
		setpixel(i,0);
		setpixel(0,i);
	}
}
class circle{
public:
	void dda()
	{
		int x,y;
		x=0;
		y=r;
		glPointSize(1.0);

		for(int i=0;i<360;i++)
		{
		 x=x1[0]+r*cos(i);
		 y=y2[0]+r*sin(i);
		 setpixel(x,y);
		}

	}
	void mid_point()
	{
		int x,y;
		int p;
		p=1-r;
		x=0;
		y=r;
		setpixel(x,y);
		while(x<y)
		{
			if(p<0)
			{
				p=p+2*x+1;
				x++;
			}
			else{
				p=p+2*(x-y)+1;
				x++;
				y--;
			}
			setpixel(x1[0]+x,y2[0]+y);
			setpixel(x1[0]+x,y2[0]-y);
			setpixel(x1[0]+y,y2[0]+x);
			setpixel(x1[0]+y,y2[0]-x);
			setpixel(x1[0]-x,y2[0]+y);
			setpixel(x1[0]-x,y2[0]-y);
			setpixel(x1[0]-y,y2[0]+x);
			setpixel(x1[0]-y,y2[0]-x);
		}

	}
	void bresenham()
	{
		int x,y,p;
		p=3-2*r;
		x=0;
		y=r;
		setpixel(x,y);
		while(x<y)
		{
			if(p<0)
			{
				p=p+4*(x)+6;
				x++;
			}
			else
			{
				p=p+4*(x-y)+10;
				x++;
				y--;
			}
			setpixel(x1[0]+x,y2[0]+y);
			setpixel(x1[0]+x,y2[0]-y);
			setpixel(x1[0]+y,y2[0]+x);
			setpixel(x1[0]+y,y2[0]-x);
			setpixel(x1[0]-x,y2[0]+y);
			setpixel(x1[0]-x,y2[0]-y);
			setpixel(x1[0]-y,y2[0]+x);
			setpixel(x1[0]-y,y2[0]-x);
		}

	}
};
void mymouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		x1[i]=x-250;
		y2[i]=250-y;

		setpixel(x1[i],y2[i]);
		i++;
	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		r=sqrt(((x1[1]-x1[0])*(x1[1]-x1[0]))+((y2[1]-y2[0])*(y2[1]-y2[0])));
	}
}
void menu(int item)
{	circle c;
	if(item==1)
	{
		c.dda();
	}
	if(item==2)
	{
		c.mid_point();
	}
	if(item==3)
	{
		c.bresenham();
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(500,300);
	glutInitWindowSize(w,h);
	glutCreateWindow("circle_try");
	initialise();
	glutMouseFunc(mymouse);
	glutCreateMenu(menu);
	glutAddMenuEntry("dda",1);
	glutAddMenuEntry("midpoint",2);
	glutAddMenuEntry("bresenham",3);
	glutAddMenuEntry("exit",4);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutMainLoop();
}
