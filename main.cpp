#include <gl/glut.h>
#include <gl/glext.h>
#include <gl/gltools.h>
#include <math.h>
#include <gl/math3d.h>
#include <stdio.h>
#include <windows.h>

#define  PI 3.14159265358979323846264

float RotX = 272;
float RotY = 0;
float RotZ = 0;
GLuint fangzhu = NULL;
GLuint ground = NULL;
GLuint taijie = NULL;
GLuint ganzi = NULL;
GLuint yuanqiu = NULL;
M3DVector3f vNormal;

bool LoadTexture(LPSTR szFileName, GLuint &texid) ;

void SetupRC()
{
	// Bluish background
	glClearColor(0.5f, 0.5f, 0.50f, 1.0f );
	glEnable(GL_TEXTURE_2D);   // ���ö�ά����
	glEnable(GL_DEPTH_TEST);   //��Ȳ���
	glEnable(GL_LIGHTING);
	glEnable(GL_FOG);
	LoadTexture("b.bmp", ground);
	LoadTexture("a.bmp", taijie);
	LoadTexture("c.bmp", fangzhu);
	LoadTexture("d.bmp", ganzi);
	LoadTexture("e.bmp", yuanqiu);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//����
	GLfloat ambientLight[] = {0.9, 0.9, 0.9, 1.0};
	GLfloat diffuseLight[] = {0.7, 0.7, 0.7, 1.0};
	GLfloat specular[]     = {0.1, 0.1, 0.1, .1};
	GLfloat lightPos[] = {-3000.00,-2000,700,1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT ,ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	//��
	GLfloat color[] = {0.7f ,0.7f, 0.7f,0.5f };
	glFogfv(GL_FOG_COLOR, color);
	glFogf(GL_FOG_START, -100);
	glFogf(GL_FOG_END, 100);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	//glDisable(GL_FOG);
}

bool LoadTexture(LPSTR szFileName, GLuint &texid)      // Creates Texture From A Bitmap File
{
	HBITMAP hBMP;              // Handle Of The Bitmap
	BITMAP BMP;              // Bitmap Structure
	glGenTextures(1, &texid);           // Create The Texture
	hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );
	if (!hBMP)               // Does The Bitmap Exist?
		return FALSE;             // If Not Return False

	GetObject(hBMP, sizeof(BMP), &BMP);         // Get The Object
	// hBMP:        Handle To Graphics Object
	// sizeof(BMP): Size Of Buffer For Object Information
	// &BMP:        Buffer For Object Information

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);        // Pixel Storage Mode (Word Alignment / 4 Bytes)

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texid);         // Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);             // Delete The Object

	return TRUE;              // Loading Was Successful
}

void DrawGround()
{
	//����200 ��ש�� 1��һ�����
	glBindTexture(GL_TEXTURE_2D, ground);
	for(int i=-10;i< 10;i++){
		for(int j=-10;j<10;j++){
			glBegin(GL_QUADS);

			M3DVector3f vPoints[3] = {{ i * 30, j * 30,  -1.0f},
			{ i * 30, (j+1) * 30, -1.0f},
			{ (i+1)* 30, (j+1)*30, -1.0f}};
			m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
			glNormal3fv(vNormal);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(i * 30, j * 30,  -1.0f); // ������ı��ε�����
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i * 30, (j+1) * 30, -1.0f); // ������ı��ε�����
			glTexCoord2f(1.0f, 1.0f); glVertex3f((i+1)* 30, (j+1)*30, -1.0f); // ������ı��ε�����
			glTexCoord2f(1.0f, 0.0f); glVertex3f((i+1)*30, j*30 ,  -1.0f); // ������ı��ε�����	
			glEnd();
		}
	}
	
}

//���ƿ���Բ�� Ҳ����̨�� �� ʹ�� a.bmp ����ͼ
void drawYuanZhu(GLfloat ground, GLfloat height, GLfloat out, GLfloat inner){
	
	//��Բ
	glBindTexture(GL_TEXTURE_2D, taijie);
	for (GLfloat j = 0; j <= 2*PI + 0.01; j+= 0.01f)
	{
		glBegin(GL_QUADS);
	
		M3DVector3f vPoints[3] = {{out * cos(j), out * sin(j), ground + height},
		{out * cos(j+1), out * sin(j+1), ground + height},
		{out * cos(j+1), out * sin(j+1), ground}};
		m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
		glNormal3fv(vNormal);

		glTexCoord2f(0.0f, 0.0f);glVertex3f(out * cos(j), out * sin(j), ground + height);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(out * cos(j+1), out * sin(j+1), ground + height);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(out * cos(j+1), out * sin(j+1), ground);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(out * cos(j), out * sin(j), ground);
		glEnd();
	}

	//��Բ
	for (GLfloat j = 0; j < 2*PI; j+= 0.01f)
	{
		glBegin(GL_QUADS);
		M3DVector3f vPoints[3] = {{inner * cos(j), inner * sin(j), ground + height},
		{inner * cos(j+1), inner * sin(j+1), ground + height},
		{inner * cos(j), inner * sin(j), ground}};
		m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
		glNormal3fv(vNormal);


		glVertex3f(inner * cos(j), inner * sin(j), ground + height);
		glVertex3f(inner * cos(j+1), inner * sin(j+1), ground + height);
		glVertex3f(inner * cos(j+1), inner * sin(j+1), ground);
		glVertex3f(inner * cos(j), inner * sin(j), ground);
		glEnd();
	}

	//����
	for (GLfloat j = 0; j < 2*PI; j += 0.01f)
	{
		glBegin(GL_QUADS);
		M3DVector3f vPoints[3] = {{inner * cos(j), inner * sin(j), ground + height},
		{inner * cos(j+1), inner * sin(j+1), ground + height},
		{out * cos(j), out * sin(j), ground + height}};
		m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
		glNormal3fv(vNormal);

		
		glVertex3f(inner * cos(j), inner * sin(j), ground + height);
		glVertex3f(inner * cos(j+1), inner * sin(j+1), ground + height);
		glVertex3f(out * cos(j), out * sin(j), ground + height);
		glVertex3f(out * cos(j+1), out * sin(j+1), ground + height);
		glEnd();
	}
}

void drawFangzhu(GLfloat height, GLfloat width, GLfloat halfheight){
	//���������棬����ֻ����5��
	
	glBindTexture(GL_TEXTURE_2D, fangzhu);
	
	//ǰ��
	glBegin(GL_QUADS);{
		M3DVector3f vPoints[3] = {{-width/ 2, width/ 2, 0},
		{width/ 2, width/ 2, 0},
		{width/ 2, width/ 2, height}};
		m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
		glNormal3fv(vNormal);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-width/ 2, width/ 2, 0);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(width/ 2, width/ 2, 0);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(width/ 2, width/ 2, height);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-width/ 2, width/ 2, height);
	}
	
	glEnd();

	//����
	glBegin(GL_QUADS);{
		M3DVector3f vPoints[3] = {{width/ 2, width/ 2, 0},
		{width/ 2, -width/ 2, 0},
		{width/ 2, -width/ 2, height}};
		m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
		glNormal3fv(vNormal);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(width/ 2, width/ 2, 0);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(width/ 2, -width/ 2, 0);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(width/ 2, -width/ 2, height);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(width/ 2, width/ 2, height);

	}
	glEnd();

	//����
	glBegin(GL_QUADS);{
		M3DVector3f vPoints[3] = {{-width/ 2, width/ 2, 0},
		{-width/ 2, -width/ 2, 0},
		{-width/ 2, -width/ 2, height}};
		m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
		glNormal3fv(vNormal);

		glTexCoord2f(0.0f, 0.0f);glVertex3f(-width/ 2, width/ 2, 0);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(-width/ 2, -width/ 2, 0);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(-width/ 2, -width/ 2, height);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-width/ 2, width/ 2, height);

	}
	glEnd();

	//����
	glBegin(GL_QUADS);{
		M3DVector3f vPoints[3] = {{-width/ 2, -width/ 2, 0},
		{width/ 2, -width/ 2, 0},
		{width/ 2, -width/ 2, height}};
		m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
		glNormal3fv(vNormal);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-width/ 2, -width/ 2, 0);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(width/ 2, -width/ 2, 0);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(width/ 2, -width/ 2, height);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-width/ 2, -width/ 2, height);

	}
	glEnd();

	//����
	glBegin(GL_QUADS);{
		M3DVector3f vPoints[3] = {{-width/ 2, width/ 2, 0},
		{width/ 2, width/ 2, 0},
		{width/ 2, width/ 2, 0}};
		m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
		glNormal3fv(vNormal);

		glVertex3f(width/ 2, width/ 2, height);
		glVertex3f(width/ 2, -width/ 2, height);
		glVertex3f(-width/ 2, -width/ 2, height);
		glVertex3f(-width/ 2, width/ 2, height);

	}
	glEnd();
	
	//��������ӻ������ĸ��棬 �Ȳ�д
	//TODO:
	//������Ķ�����һ�£��Ͳ�д��
	//TODO:
}

//����ͼ�εĵ���
void drawDizuo(){
	GLfloat step = 5;
	GLfloat inner = 50;
	GLfloat out = 150;
	GLfloat height = 10;
	for(int i=0;i< 10;i++){
		drawYuanZhu(0, height, out, inner);
		height = height + 3;
		out = out - step * 2;
	}
}

//����3�������� �������
void drawThreeXiang(GLfloat width, GLfloat height, GLfloat pos){
	pos = pos + width / 2;
	//glRotatef(2*PI / 3, 0, 0, 1.0);
	glTranslatef(pos * sin(0.0), pos * cos(0.0), 0);
	drawFangzhu(height,width, 0);
	
	glTranslatef(-pos * sin(0.0), -pos * cos(0.0), 0);
	glTranslatef( pos * sin(2*PI / 3), pos * cos(2*PI / 3), 0);
	drawFangzhu(height,width, 0);
	
	glTranslatef(-pos * sin(2*PI / 3), -pos * cos(2*PI / 3), 0);
	glTranslatef(pos * sin(4*PI / 3), pos * cos(4*PI / 3), 0);
	drawFangzhu(height,width, 0);

	glTranslatef(-pos * sin(4*PI / 3), -pos * cos(4*PI / 3), 0);
}

//���ƶ���Բ��, �Լ�дһ�¾ͺ���
void drawDingYuan(GLint lineCount,GLfloat height, GLfloat width, GLfloat ground){
	//Ĭ�ϵ�linePos �Ĵ�С�� 512�� Ҳ����˵ lineCount ���ܴ��� 255, ��Ҳ����С�� 2
	//������洢�ķֱ��� length �� height
	GLint pointCount = lineCount;
	float linePos[512][2];
	glBindTexture(GL_TEXTURE_2D, yuanqiu);
	for(int i=0;i<lineCount;i++){
		linePos[i][0] = (height/2) * cos(i* 2* PI / pointCount) + width;  // this is the length of it
		linePos[i][1] = (height/2) * sin(i* 2* PI / pointCount);      //this is the height of the tourds
	}
	linePos[lineCount][0] = linePos[0][0];
	linePos[lineCount][1] = linePos[0][1];
	for(int i=0;i < lineCount; i++){
		for(int j=0;j< pointCount; j++){
			glBegin(GL_QUADS);
			M3DVector3f vPoints[3] = {{linePos[i][0] * sin(2* PI* j / pointCount), linePos[i][0] * cos(2* PI* j / pointCount), linePos[i][1] + ground},
			{linePos[i][0] * sin(2* PI* (j+1) / pointCount), linePos[i][0] * cos(2* PI * (j+1) / pointCount), linePos[i][1] + ground},
			{linePos[i+1][0] * sin(2* PI* (j+1) / pointCount), linePos[i + 1][0] * cos(2* PI* (j+1) / pointCount), linePos[i+1][1] + ground}};
			m3dFindNormal(vNormal, vPoints[0], vPoints[1], vPoints[2]);
			glNormal3fv(vNormal);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(linePos[i][0] * sin(2* PI* j / pointCount), linePos[i][0] * cos(2* PI* j / pointCount), linePos[i][1] + ground);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(linePos[i][0] * sin(2* PI* (j+1) / pointCount), linePos[i][0] * cos(2* PI * (j+1) / pointCount), linePos[i][1] + ground);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(linePos[i+1][0] * sin(2* PI* (j+1) / pointCount), linePos[i + 1][0] * cos(2* PI* (j+1) / pointCount), linePos[i+1][1] + ground);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(linePos[i+1][0] * sin(2* PI* j / pointCount), linePos[i + 1][0] * cos(2* PI* j / pointCount), linePos[i+1][1] + ground);
			glEnd();
		}
	}
}

//�������������Ǹ���
void drawGan(GLfloat ground, GLfloat height, GLfloat width, GLfloat lineCount){
	glBindTexture(GL_TEXTURE_2D, ganzi);
	for(int i=0;i < lineCount; i++){
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0, height + ground);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0, height + ground);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(width * sin(2*PI*i/lineCount),width * cos(2*PI*i/lineCount), ground);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(width * sin(2*PI*(i+1)/lineCount),width * cos(2*PI*(i+1)/lineCount), ground);
		glEnd();
	}
}

//���ڲ��Ķ�����д��һ��
void drawMainGanYuan(){
	drawDingYuan(25, 12, 25,120);
	drawGan(0, 300, 5, 10);
	drawThreeXiang(15, 150,15);
}

// Called to draw scene
void RenderScene(void)
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0, -100,0);
	glRotatef(RotX, 1.0,0,0);
	glRotatef(RotY, 0,1.0,0);
	glRotatef(RotZ, 0,0,1.0);

	// Draw start to draw
	DrawGround();
	drawDizuo();
	drawMainGanYuan();

	// Do the buffer Swap
	glPopMatrix();
	glutSwapBuffers();
}


// Respond to arrow keys by moving the camera frame of reference
void SpecialKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		RotX = RotX + 1;
		break;
	case 'y':
		RotY = RotY + 1;
		break;
	case 'z':
		RotZ = RotZ + 1;
		break;
	default:
		break;
	}
	printf("\n the pos x: %f y: %f z: %f", RotX, RotY, RotZ);
	// Refresh the Window
	glutPostRedisplay();
}


///////////////////////////////////////////////////////////
// Called by GLUT library when idle (window not being
// resized or moved)
void TimerFunction(int value)
{
	// Redraw the scene with new coordinates
	glutPostRedisplay();
	glutTimerFunc(3,TimerFunction, 1);
}

void ChangeSize(int w, int h)
{
	GLfloat size = 150;
	GLfloat fAspect;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//gluPerspective(89.0f, fAspect, 10.0f, 2000.0f);

	if(w <= h){
		glOrtho(-size, size, -size / fAspect, size / fAspect, -size, size);
	}else{
		glOrtho(-size * fAspect, size * fAspect, -size, size, -size, size);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutCreateWindow("OpenGL SphereWorld Demo");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(SpecialKeys);
	SetupRC();
	glutTimerFunc(33, TimerFunction, 1);

	glutMainLoop();

	return 0;
}
