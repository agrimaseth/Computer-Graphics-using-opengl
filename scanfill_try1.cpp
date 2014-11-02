#include<iostream>
#include<GL/freeglut.h>
#include<math.h>
using namespace std;
int MAX=10;
int i,n,flag,count,ymax,ymin;

void init()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.7,0.7,0.7,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0,500,500,0);

}

class Polygon
{
public:
	GLint edges[10][2];
	Polygon()
	{
		for(int a=0;a<10;a++)
			for(int b=0;b<2;b++)
				edges[a][b]=0;
	}
	void drawpoly();
	void scanline(int arr[][2]);
}poly;
void Polygon::drawpoly()
{
	glColor3f(0.0,1.0,0.0);
	if(flag)
	{
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<n;i++)
		glVertex3f(edges[i][0],edges[i][1],0.0);
	glEnd();
	}
}

void Polygon::scanline(int arr[][2])
{
	ymax=0;
	ymin=500;
	float m[10],dx,dy,intx[10];
	glColor3f(0,1,0);
	glBegin(GL_LINES);
	for(int j=0;j<n;j++)
	{
	/*	if(arr[j][1]>ymax)
		{
			ymax=arr[j][1];
		}
		if(arr[j][1]<ymin)
		{
			ymin=arr[j][1];
		}
		dx=arr[j+1][0]-arr[j][0];
		dy=arr[j+1][1]-arr[j][1];
		if(dx==0)
			m[j]=0;
		if(dy==0)
			m[j]=1;
		if(dx!=0&&dy!=0)
		{
			m[j]=(float)dx/dy;
		}*/
		if(arr[j][1]>=ymax)ymax=arr[j][1];
			    if(arr[j][1]<=ymin)ymin=arr[j][1];

				dx=arr[j+1][0]-arr[j][0];
				dy=arr[j+1][1]-arr[j][1];

				if(dx==0)m[j]=0;
				if(dy==0)m[j]=1;

				if(dx!=0&&dy!=0)
					m[j]=(float)dx/dy;

	}
		int count;
		for(int y=ymax;y>=ymin;y++)
		{
			/*count=0;
			for(int k=0;k<n;k++)
			{
				if((arr[k][1]<y&&arr[k+1][1]>y)||(arr[k][1]<y&&arr[k+1][1]>y))
				{
					intx[count]=arr[k][0]+(m[k]*(y-arr[k][1]));
					count++;

				}

			}*/
			int cnt=0;
						for(int k=0;k<n;k++)
						{
								if((arr[k][1]>y&&arr[k+1][1]<=y)||(arr[k][1]<=y&&arr[k+1][1]>y))
								{
									intx[cnt]=(arr[k][0]+(m[k]*(y-arr[k][1])));
									cnt++;
								}
						}

		/*	for(int k=0;k<cnt-1;k++)
			{
				for(int j=0;j<cnt-1;j++)
				{
					if(intx[j]>intx[j+1])
					{
						int temp;
						temp=intx[j];
						intx[j]=intx[j+1];
						intx[j+1]=temp;

					}
				}
				for(int j=0;j<cnt-1;j=j+2)
				{
					glVertex3f(intx[j],y,0.0);
					glVertex3f(intx[j+1],y,0.0);
					glutPostRedisplay();

				}
			}*/
						int temp;

						for(int k=0;k<cnt-1;k++)
									{
										for(int j=0;j<cnt-1;j++)
										{
												if(intx[j]>intx[j+1])
												{
													temp=intx[j];
													intx[j]=intx[j+1];
													intx[j+1]=temp;
												}
										}

										for(int j=0;j<cnt-1;j+=2)
										{
											glVertex3f(intx[j],y,0.0);
										    glVertex3f(intx[j+1]+1,y,0.0);
											glutPostRedisplay();

										}
									}




		}

		glEnd();
					//glFlush();

}

void mouse(int button,int state,int x,int y)
{
	switch(button)
	{
	    case GLUT_LEFT_BUTTON:if(state==GLUT_DOWN)
							     {
									  poly.edges[i][0]=x;
									  poly.edges[i][1]=y;
									  glPointSize(8);
									  glColor3f(1,1,1);
									  glBegin(GL_POINTS);
									  glVertex3f(x,y,0.0);
									  glEnd();
									  if(i>0)
									  {
									  glBegin(GL_LINES);
									  glVertex3f(poly.edges[i-1][0],poly.edges[i-1][1],0);
									  glVertex3f(poly.edges[i][0],poly.edges[i][1],0);
									  glEnd();
									  glFlush();
									  }
									  cout<<i<<","<<poly.edges[i][0]<<","<<poly.edges[i][1];
									  cout<<endl;
									  i++;
									  //glutPostRedisplay();
								  }


								break;
		case GLUT_RIGHT_BUTTON:if(state==GLUT_DOWN)
								   {
									   poly.edges[i][0]=poly.edges[0][0];
									   poly.edges[i][1]=poly.edges[0][1];
									   flag=1;
									   n=i;
									   count++;
							       }

				break;

	}
	glutPostRedisplay();
}
void renderscene()
{
	poly.drawpoly();
	if(count>1)
		{
			poly.scanline(poly.edges);
			glutPostRedisplay();
		}
	glFlush();
}





int main(int argc,char **argv)
{

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("POLYGON FILLING");
	init();
	glutMouseFunc(mouse);
	glutDisplayFunc(renderscene);
	glutMainLoop();
}
