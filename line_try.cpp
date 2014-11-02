#include<iostream>
#include<GL/freeglut.h>
#include<math.h>
#define w 500
#define h 500
int x1[2][2];
int flag=0;
int i=0;
using namespace std;

class circle
{
public:
	void setPixel(GLint x,GLint y)
	{
		glColor3f(0,0,1);
		glBegin(GL_POINTS);
		glVertex2f(x,y);
		glEnd();
		glFlush();

	}
	void dda()
	{
		GLint dy = x1[1][1] - x1[0][1];
		    GLint dx = x1[1][0] - x1[0][0];
		    GLint steps,i;
		    GLfloat xinc,yinc,x=x1[0][0],y=x1[0][1];
		    if( abs(dx) >= abs(dy)){
		        steps=abs(dx);
		    }else{
		          steps=abs(dy);
		    }
		    xinc=(float) dx/ (float) steps;
		    yinc=(float) dy/ (float) steps;
		    setPixel(x,y);
		    for(i=0;i<steps;i++){
		         x+=xinc;
		         y+=yinc;
		        // glLineWidth (100.0 );
		        // glPointSize(10.0);
		        // glEnable(GL_LINE_STIPPLE);
		         	 //  glLineStipple ( 1.0, 0x0F0F );
		        // if(i%9==0)
		        	// 	 int flag=0;
		         //else
		        	// flag=1;
		         //if(i%9!=0&&flag==1 )
		        {
		        	 setPixel(x,y);

		         }



		    }}
	void bres()
	{
		GLint dx,dy,steps,i=0,x,y,g;
			if(x1[0][0]>x1[1][0]&&x1[0][1]>x1[1][1])
			{
				x=x1[1][0];
				y=x1[1][1];
			}
			else
			{
			x=x1[0][0];
			y=x1[0][1];
			}
			dx=abs(x1[1][0]-x1[0][0]);
			dy=abs(x1[1][1]-x1[0][1]);
		if(x1[0][0]>x1[1][0]&&x1[0][1]<x1[1][1])
		{

			if(dx>=dy)
			{	g=2*dy-dx;
				steps=dx;
				while(i<=steps)
				{
				if(g>0)
				{
					y--;
					g+=2*(dy-dx);
				}
				else
				{
					g+=2*dy;
				}
				x++;
				i++;
				setPixel(x,y);
				}


			}
			else
			{
				i=0;
				g=2*dx-dy;
				steps=dy;
			while(i<=steps)
				{
				if(g>0)
				{
					x--;
					g+=2*(dy-dx);
				}
				else
				{
					g+=2*dx;
				}
				y++;
				i++;
				setPixel(x,y);
				}
			}
		}

		else if(x1[0][0]<x1[1][0]&&x1[0][1]>x1[1][1])
		{
			if(dx>=dy)
			{	g=dx-2*dy;
				steps=dx;
				while(i<=steps)
				{
				if(g>0)
				{
					y--;
					g+=2*(dx-dy);
				}
				else
				{
					g+=2*dy;
				}
				x++;
				i++;
				setPixel(x,y);
				}


			}
			else
			{
				i=0;
				g=2*dy-dx;
				steps=dy;
			while(i<=steps)
				{
				if(g>0)
				{
					x--;
					g+=2*(dx-dy);
				}
				else
				{
					g+=2*dx;
				}
				y++;
				i++;
				setPixel(x,y);
				}
			}
		}
		else
		{if(dx>=dy)
			{	g=2*dy-dx;
				steps=dx;
				while(i<=steps)
				{
				if(g>0)
				{
					y++;
					g+=2*(dy-dx);
				}
				else
				{
					g+=2*dy;
				}
				x++;
				i++;
				setPixel(x,y);
				}


			}
			else
			{
				i=0;
				g=2*dx-dy;
				steps=dy;
			while(i<=steps)
				{
				if(g>0)
				{
					x++;
					g+=2*(dy-dx);
				}
				else
				{
					g+=2*dx;
				}
				y++;
				i++;
				setPixel(x,y);
				}
			}

		}
		}
	void exit()
	{
		//glPushAttrib(GL_ENABLE_BIT);
		//glLineStipple(1, 0xAAAA);
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 0x1C47);
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINE_STRIP);
		//glVertex3f(-.5,.5,-.5);
		//glVertex3f(.5,.5,-.5);
		for(int k=0;k<2;k++)
		{
			glVertex2f(x1[k][0],x1[k][1]);
		}
		glFlush();
		glEnd();
		//glPopAttrib();
	}



};

void initialise()
{
	circle c;
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-w/2,w/2,-h/2,h/2);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
		glPointSize(2.0);
		for(i=-500;i<500;i++)
		{
			c.setPixel(i,0);
			c.setPixel(0,i);
		}
}

void myMouse(int button,int state,int x,int y)
{

	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		glColor3f(1.0,0.0,0.0);
		if(flag==0)
		{
			x1[0][0]=x-250;
			x1[0][1]=250-y;
			cout<<"the x cordinate is"<<x1[0][0];
			cout<<"\n the y cordinate is"<<x1[0][1];
			//y1[i][]=y-250;
			glBegin(GL_POINTS);//in built functions
			glVertex2f(x1[0][0],x1[0][1]);//to pass coordinates
			glEnd();
			glFlush();
			i++;
			flag++;

		}
		else
		{
					x1[1][0]=x-250;
					x1[1][1]=250-y;
					cout<<"the x cordinate is"<<x1[1][0];
					cout<<"\n the y cordinate is"<<x1[1][1];
					//y1[i][]=y-250;
					glBegin(GL_POINTS);//in built functions
					glVertex2f(x1[1][0],x1[1][1]);//to pass coordinates
					glEnd();
					glFlush();
					i++;

				}
	}
	if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)
		{


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
		c.bres();
	}
	if(item==3)
	{
		c.exit();
	}
}
void initialize()
{circle c;
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor( 0.0, 0.0, 0.0, 0.0);//sets background color
	glMatrixMode(GL_MODELVIEW);//viewing angle
	glLoadIdentity();//to load identity matrix
	gluOrtho2D(-w/2, w/2,-h/2,h/2);//camera properties
						for(i=-500;i<500;i++)
				{
					c.setPixel(i,0);
					c.setPixel(0,i);
				}
}

int main(int argc, char ** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(500,300);
	glutInitWindowSize(w,h);
	glutCreateWindow("line_try");
	initialise();
	glutMouseFunc(myMouse);

	glutCreateMenu(menu);
	glutAddMenuEntry("dda",1);
	glutAddMenuEntry("breshenham",2);
	glutAddMenuEntry("exit",3);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutMainLoop();
	return(0);
}
