#include<iostream>
#include<GL/freeglut.h>
#include<math.h>
using namespace std;
#define w 640
# define	h 480
# define	step 0.0001
int numpoint=0,q=0;
class point
{public:
	float x,y;
};
point *ctrl,*aux;
void disp()

{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
void init()
{
	glClearColor(1.0,1.0,1.0,0.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluOrtho2D(0,(float)w,0,(float)h);

}
void setpixel(int x, int y)
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POINTS);
		glVertex2f(x,y);
	glEnd();
	glFlush();
}
void drawline(point p1,point p2)
{
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
		glVertex2f(p1.x,p1.y);
		glVertex2f(p2.x,p2.y);
	glEnd();
	glFlush();

}
void drawcurve(point p1,point p2,float t)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
		glVertex2f(p1.x,p1.y);
		glVertex2f(p2.x,p2.y);
	glEnd();
	glFlush();

}
long double factorial(int n)
{
	long double fact=1;
	int p=1;
	if(n==0||n==1)
	{
		return 1;
	}
	else
	{
		while(p<n)
		{
			fact=fact*p;
			p++;
		}

	}
	return fact;
}

long double binomial(int f, int n)
{
	double com=factorial(n)/(factorial(f)*factorial(n-f));
return com;

}
/*point bernstein(point *ctrl,float t,int n)
{
	point m;

		m.x=m.y=0;
	/*for(int i=0;i<=n;i++)
	{
		m.x=m.x+ctrl[i].x*binomial(i,n)*pow(t,i)*pow((1-t),(n-i));
		m.x=m.x+ctrl[i].x*binomial(i,n)*pow(t,i)*pow((1-t),(n-i));
		m.y=m.y+ctrl[i].y*binomial(i,n)*pow(t,i)*pow((1-t),(n-i));
	}*/
		//for(int i=0;i<=n;i++)
			//{
				//m.x=m.x+ctrl[i].x*binomial(i,n)*pow(t,i)*pow((1-t),(n-i));

				//m.y=m.y+ctrl[i].y*binomial(i,n)*pow(t,i)*pow((1-t),(n-i));

			//}
	//return m;

//}
point bernstein(point *ctrl,float t, int n)
{
	point m;

	m.x=m.y=0;



	for(int i=0;i<=n;i++)
	{
		m.x=m.x+ctrl[i].x*binomial(i,n)*pow(t,i)*pow((1-t),(n-i));

		m.y=m.y+ctrl[i].y*binomial(i,n)*pow(t,i)*pow((1-t),(n-i));

	}
	return m;

}
void mymouse(int button, int state, int x,int y)
{
	point m,p=ctrl[0];
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		ctrl[numpoint].x=x;
		ctrl[numpoint].y=480-y;
		setpixel(ctrl[numpoint].x,ctrl[numpoint].y);
		numpoint++;
	}
	if(button==GLUT_MIDDLE_BUTTON&&state==GLUT_DOWN)
	{
		for(float t=0;t<1;t+=step)
		{
		m=bernstein(ctrl,t,numpoint-1);
		drawcurve(p,m,t);
		p=m;
		}
	}
	if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
	{
		for(int i=0;i<numpoint-1;i++)
		{
			drawline(ctrl[i],ctrl[i+1]);
		}
	}
}
void processKeys(unsigned char key,int x, int y)
{
	if(key==27)
		exit(0);
	else if(key=='c')
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		numpoint=0;
	}
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(w,h);
	glutInitWindowPosition(0,0);
	glutCreateWindow("bezeir curve");
	ctrl=(point*)malloc(q*sizeof(point));
	if(!ctrl)
	{
		cout<<"allocation failed";
	}
	else
	{	q++;
		aux=(point*)realloc(ctrl,q*sizeof(point));
		if(!aux)
		{
			cout<<"allocation failed";
		}
		else
		{
			ctrl=aux;
			glutMouseFunc(mymouse);
		}
	}

	glutDisplayFunc(disp);
	glutKeyboardFunc(processKeys);
	init();
	glutMainLoop();
	free(ctrl);
	free(aux);
	return 0;

}
