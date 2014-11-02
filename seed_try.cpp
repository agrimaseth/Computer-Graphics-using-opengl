#include<iostream>
#include<GL/freeglut.h>
#include<math.h>
using namespace std;
int xs,ys;

class queue{
public:
	int c[2];
	queue *next;
	friend void insert(int element);
	friend int *del();
};
queue *front=NULL;
queue *rear=NULL;
void insert(int x, int y)
{	queue *p;
	if(front==NULL&& rear==NULL)
	{
		front=new queue;
		front->c[0]=x;
		front->c[1]=y;
		front->next=NULL;
		rear=front;
	}
	else{

		p=rear;
		rear=new queue;
		rear->c[0]=x;
		rear->c[1]=y;
		p->next=rear;
		rear->next=NULL;

	}
}
void del(int *temp)
{
	queue *p;
	temp[0]=999;
	temp[1]=999;
	if(front==NULL&&rear==NULL)
	{
		cout<<"queue is empty";
	}
	else{
		temp[0]=front->c[0];
		temp[1]=front->c[1];
		p=front;
		if(front==rear)
		{
			front=NULL;
			rear=NULL;

		}
		else{
			front=front->next;
		}
		delete p;
	}
}
struct pColor{
	GLubyte red,green,blue;
};
class polygon{
public:
	int point[10][2],n;
	float color;
	polygon()
	{
		for(int i=0;i<10;i++)
		{
			for(int j=0;j<2;j++)
			{
				point[i][j]=0;
			}
		}
		n = 0;
		color = 0.0;
	}
	void draw()
	{
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		for(int i=0;i<n;i++)
		{
			glVertex2f(point[i][0],point[i][1]);
		}
		glEnd();
		glFlush();
		glColor3f(1.0, 1.0, 1.0);
	}
};
polygon p;
void setpixel(int x, int y)
{
	//glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}
void seedfill(int xs,int ys)
{
	pColor seedc;
	insert(xs,ys);
	int t[2];
	t[0]=99;
	t[1]=99;
	while(t[0]!=999)
	{
		cout<<"inside while";
		del(t);
		glReadPixels(t[0],t[1],1,1,GL_RGB,GL_UNSIGNED_BYTE,&seedc);
		if(seedc.red!=255)
		{
			setpixel(t[0],t[1]);
			insert(t[0]-1,t[1]);
			insert(t[0]+1,t[1]);
			insert(t[0],t[1]-1);
			insert(t[0],t[1]+1);
		}
	}
}
void mouse1(int button,int state, int x,int y)
{
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		p.point[p.n][0]=x;
		p.point[p.n][1]=500-y;
		setpixel(p.point[p.n][0],p.point[p.n][1]);
		p.n++;
	}
}
void mouse2(int button,int state, int x,int y)
{
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		xs=x;
		ys=500-y;
	}

}
void mykey(unsigned char key,int x,int y)
{

	if(key=='f')
		p.draw();
	if(key=='s')
		seedfill(xs,ys);
}
void menu(int item)
{
	if(item==1)
	{
		glutMouseFunc(mouse1);
	}
	if(item==2)
	{
		p.draw();
		glutMouseFunc(mouse2);
	}
}
void init()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.4,0.6,0.6,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);

}
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}





int main(int argc, char ** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(640,480);
	glutCreateWindow("seed try");
	init();
	glutCreateMenu(menu);
	glutAddMenuEntry("draw polygon",1);
	glutAddMenuEntry("seed fill",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(mykey);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;

}
