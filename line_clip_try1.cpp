#include<iostream>
#include<GL/freeglut.h>
#include<math.h>
using namespace std;
# define w 500
#define h 500
int flag=0,flag1=0,win[4][2],win1[4][2],k=0,m=0,n=0,xmin,xmax,ymin,ymax;
void setpixel(int x, int y)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
		glVertex2f(x,y);
	glEnd();
	glFlush();
}
class edge
{
public:
	int x,y;
	int code[4];
};
edge e[10];
void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-w/2,w/2,-h/2,h/2);
	for(int i=-500;i<500;i++)
	{
		setpixel(i,0);

	}

}
class clip
{
public:
	int zero_check(edge e)
	{
		if(e.code[0]==0&&e.code[1]==0&&e.code[2]==0&&e.code[3]==0)
		{
			return 1;
		}
		else return 0;
	}
	int a_check(int a[])
	{
		if(a[0]!=0||a[1]!=0||a[2]!=0||a[3]!=0)
		{
			return 0;
		}
		else return 1;
	}
	void hand(edge e1,edge e2,int a[4])
	{
		for(int i=0;i<4;i++)
		{
			if(e1.code[i]==1&&e2.code[i]==1)
			{
				a[i]=1;
			}
			else
				a[i]=0;
		}
	}


	edge outcode(edge e)
	{
		if(win[0][0]<win[2][0])
		{
			xmin=win[0][0];
			xmax=win[2][0];
		}
		else
		if(win[0][0]<win[2][0])
		{
			xmin=win[0][0];
			xmax=win[2][0];
		}
		else
		{
			xmin=win[2][0];
			xmax=win[0][0];
		}


		if(win[0][1]<win[2][1])
		{
			ymin=win[0][1];
			ymax=win[2][1];
		}
		else
		{
			ymin=win[2][1];
			ymax=win[0][1];
		}
		if(e.x<xmin)
			e.code[0]=1;
		else
			e.code[0]=0;
		if(e.x>xmax)
			e.code[1]=1;
		else
			e.code[1]=0;

		if(e.y<ymin)
			e.code[2]=1;
		else
			e.code[2]=0;
		if(e.y>ymax)
			e.code[3]=1;
		else
			e.code[3]=0;
		return e;

	}
	void cohensuth()
	{
		int a[4],flag=0;
		float s;
		for(int i=0;i<n;i=i+2)
		{
			do{
				flag=0;
				if((zero_check(e[i]))&&(zero_check(e[i+1])))
				{
					break;
				}
				else
				{
					hand(e[i],e[i+1],a);
					if(!a_check(a))
					{
						e[i].y=900;
						e[i+1].y=900;
						break;
					}
					else
					{
						s=(float)(e[i+1].y-e[i].y)/(e[i+1].x-e[i].x);
						if(e[i].code[0]==0&&e[i+1].code[0]==1)
						{
							e[i+1].y+=(int)(s*(xmin-e[i].x));
							e[i+1].x=xmin;
							e[i+1]=outcode(e[i+1]);
							flag=1;
						}
						if(e[i].code[0]==1&&e[i+1].code[0]==0)
						{
							e[i].y+=(int)(s*(xmin-e[i].x));
							e[i].x=xmin;
							e[i]=outcode(e[i]);

							flag=1;
						}
						if(e[i].code[1]==0&&e[i+1].code[1]==1&&flag==0)
						{
							e[i+1].y+=(int)(s*(xmax-e[i].x));
							e[i+1].x=xmax;
							e[i+1]=outcode(e[i+1]);
							flag=1;
						}
						if(e[i].code[1]==1&&e[i+1].code[1]==0&&flag==0)
						{
							e[i].y+=(int)(s*(xmax-e[i].x));
							e[i].x=xmax;
							e[i]=outcode(e[i]);
							flag=1;


						}
						if(e[i].code[2]==0&&e[i+1].code[2]==1&&flag==0)
						{
							e[i+1].x+=(int)((ymin-e[i+1].y)/s);
							e[i+1].y=ymin;
							e[i+1]=outcode(e[i+1]);
							flag=1;
						}
						if(e[i].code[2]==1&&e[i+1].code[2]==0&&flag==0)
						{
							e[i].x+=(int)((ymin-e[i].y)/s);
							e[i].y=ymin;
							e[i]=outcode(e[i]);
							flag=1;
						}
						if(e[i].code[3]==0&&e[i+1].code[3]==1&&flag==0)
						{
							e[i+1].x+=(int)((ymax-e[i+1].y)/s);
							e[i+1].y=ymax;
							e[i+1]=outcode(e[i+1]);

							flag=1;
						}
						if(e[i].code[3]==1&&e[i+1].code[3]==0&&flag==0)
						{
							e[i].x+=(int)((ymax-e[i].y)/s);
							e[i].y=ymax;
							e[i]=outcode(e[i]);
							flag=1;
						}



					}

				}

			}while(a_check(a));
			e[i].y=e[i].y-250;
			e[i+1].y=e[i+1].y-250;
			glColor3f(0.0,1.0,0.0);
			glBegin(GL_LINES);
				glVertex2i(e[i].x,e[i].y);
				glVertex2i(e[i+1].x,e[i+1].y);
			glEnd();
			glFlush();

		}


	}

};
clip c;
void draw_outwin()
{
	win1[0][0]=win[0][0];
	win1[1][0]=win[1][0];
	win1[2][0]=win[2][0];
	win1[3][0]=win[3][0];
	win1[0][1]=win[0][1]-250;
	win1[1][1]=win[1][1]-250;
	win1[2][1]=win[2][1]-250;
	win1[3][1]=win[3][1]-250;
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<4;i++)
			glVertex2f(win1[i][0],win1[i][1]);
		glEnd();
		glFlush();
}
void menu(int item)
{
	if(item==1)
	{
		draw_outwin();
		c.cohensuth();
	}
}
void draw_win()
{

	win[1][0]=win[0][0];
	win[1][1]=win[2][1];
	win[3][0]=win[2][0];
	win[3][1]=win[0][1];
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<4;i++)
		glVertex2f(win[i][0],win[i][1]);
	glEnd();
	glFlush();
}
void mymouse(int button,int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		if(flag==1)
		{
			e[m].x= x-250;
			e[m].y= 250-y;
			e[m]=c.outcode(e[m]);
			glColor3f(1.0,0.0,0.0);
			glPointSize(2.0);
			glBegin(GL_POINTS);
					glVertex2f(e[m].x,e[m].y);
				glEnd();
				glFlush();
			m++;

			flag1=1;
		}
		else
		{
			win[k][0]=x-250;
			win[k][1]=250-y;
			k=k+2;
		}
	}
	if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
	{
		flag=1;
		if(flag1==1)
		{
			glBegin(GL_LINES);
				glVertex2f(e[n].x,e[n].y);
				n++;
				glVertex2f(e[n].x,e[n].y);
			glEnd();
			glFlush();
			n++;

		}
		else
		{
			draw_win();
		}
	}
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(w,h);
	glutCreateWindow("line clipping");
	init();
	glutMouseFunc(mymouse);
	glutCreateMenu(menu);
	glutAddMenuEntry("clip line",1);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutMainLoop();

	return 0;
}
