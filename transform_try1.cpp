#include<GL/freeglut.h>
#include<iostream>
#include<math.h>
using namespace std;
#define w 500
#define h 500
int xc[10],yc[10],i=0,n=0;

void setpixel(GLint x,GLint y)
	{
		glColor3f(0,0,1);
		glBegin(GL_POINTS);
		glVertex2f(x,y);
		glEnd();
		glFlush();

	}
void myMouse(int button,int state,int x,int y)
{

	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		xc[i]=x-250;
		yc[i]=250-y;
		setpixel(xc[i],yc[i]);
		i++;
		n++;

	}

	if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
	{
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_LINE_LOOP);
			for(int i=0;i<n;i++)
			glVertex2f(xc[i],yc[i]);
		glEnd();
		glFlush();


	}
}
class transform{
public:
	void translate()
	{
		float tx,ty;
		cout<<"enter the x translation value";
		cin>>tx;
		cout<<"enter the y translation value";
		cin>>ty;
		for(int j=0;j<n;j++)
		{
			xc[j]=xc[j]+tx;
			yc[j]=yc[j]+ty;
		}
		glColor3f(1.0,0.0,0.0);
				glBegin(GL_LINE_LOOP);
					for(int i=0;i<n;i++)
					glVertex2f(xc[i],yc[i]);
				glEnd();
				glFlush();

	}
	void rotate()
	{
		float theta,a[n],tx,ty;
		cout<<"enter the angle of rotation";
		cin>>theta;
		tx=xc[0];
		ty=yc[0];
		for(int j=0;j<n;j++)
		{
				xc[j]=xc[j]-tx;
				yc[j]=yc[j]-ty;
		}
		for(int i=0;i<n;i++)
		{
			a[i]=xc[i];
			xc[i]=(xc[i]*cos(theta))+(yc[i]*sin(+theta));
			yc[i]=(a[i]*sin(-theta))+(yc[i]*cos(theta));
		}
		for(int j=0;j<n;j++)
				{
						xc[j]=xc[j]+tx;
						yc[j]=yc[j]+ty;
				}

		glColor3f(0.0,0.0,1.0);
			glBegin (GL_LINE_LOOP);
			for(int i=0;i<n;i++)
			{
						glVertex3f (xc[i],yc[i],0.0);//display the polygon
			}
			glEnd ();
			glFlush();



	}
	void drawline(int m,int c)
	{
		int y;
		for(int i=-500;i<500;i++)
		{
			y=(m*i)+c;
			setpixel(i,y);
		}
	}
	void translate1(int x,int y)
	{
		for(int i=0;i<n;i++)
		{
			xc[i]=xc[i]+x;
			yc[i]=yc[i]+y;
		}
	}
	void rotate1(float theta)
	{
		int i;
		int a[n];
		for(i=0;i<n;i++)
		{
			a[i]=xc[i];
			xc[i]=(xc[i]*cos(theta))+(yc[i]*sin(theta));
			yc[i]=(a[i]*sin(-theta))+(yc[i]*cos(theta));
		}
}
	void refx()
	{
		int i;

				for(i=0;i<n;i++)
				{
					yc[i]=yc[i]*(-1);

				}
	}
	void plot()
	{
		glColor3f(0.0,0.0,1.0);
					glBegin (GL_LINE_LOOP);
					for(int i=0;i<n;i++)
					{
								glVertex3f (xc[i],yc[i],0.0);//display the polygon
					}
					glEnd ();
					glFlush();
	}

	void reflect()
	{
		int m,c;
		float theta1;
		cout<<"enter the slope of the line about which reflection is to be carried out";
		cin>>m;
		cout<<"enter the intercept";
		cin>>c;
		drawline(m,c);
		translate1(0,-c);
		theta1=atan(m);
		rotate1(theta1);
		refx();
		rotate1(-theta1);
		translate1(0,c);
		plot();

	}
};

void menu(int item)
{
	transform t;
	if(item==1)
	{
		t.translate();
	}
	if(item==2)
	{
		t.rotate();
	}
	if(item==3)
	{
		t.reflect();
	}
}


void initialise()
{
	int i;
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-w/2,w/2,-h/2,h/2);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
		glPointSize(2.0);
		for(i=-500;i<500;i++)
		{
			setpixel(i,0);
			setpixel(0,i);
		}
}


int main(int argc, char ** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(500,300);
	glutInitWindowSize(w,h);
	glutCreateWindow("transform_try1");
	initialise();
	glutMouseFunc(myMouse);

	glutCreateMenu(menu);
	glutAddMenuEntry("scaling",1);
	glutAddMenuEntry("rotation",2);
	glutAddMenuEntry("reflection about arbitary point",3);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutMainLoop();
	return(0);
}
