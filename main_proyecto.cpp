//Semestre 2020-1	Proyecto Final Laboratorio		Grupo: 4
//************************************************************//
//************************************************************//
//************** Alumno (s): CONTRERAS PERALTA MARCO ISAAC****//
//*************											******//
//*************											******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


//NEW// Keyframes
//Variables de dibujo y manipulacion
float posX =0, posY = 2.5, posZ =-3.5, rotRodIzq = 0, rotRodDer = 0,rotBDer=0,rotBizq=0;
float giroMonito = 0;

#define MAX_FRAMES 10
int i_max_steps = 90;
int i_curr_steps = 0;
bool f_tiro = false;
float v = 10;
float angulo = 45;
float gravedad = 9.81;
float tiempo = 1;
float xin = 0.0f;
float yin = 4.0f;
float x;
float y;
float movKit = 0.0;
float movkit2 = 0.0;
float giroLlanta = 0.0;
bool g_fanimacion = false;
bool g_fanimacion2 = false;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodDer;
	float rotRodIzq;
	float rotBder;
	float rotBizq;
	float rotIncbd;
	float rotIncbi;
	float rotInc2;
	float rotInc;
	float giroMonito;
	float giroMonitoInc;
	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=0;			//introducir datos
bool play=false;
int playIndex=0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01



CTexture textGrass;



//para proy
CTexture tpuerta;
CTexture ttecho;
CTexture tpared;
CTexture tfachada;
CTexture tpiso;
CTexture tdulces;
CTexture tpdulces;
CTexture tpantalla;
CTexture tred;
CTexture tmadera;
CTexture tsilla;
CTexture ttubo;
CTexture tpelota1;
CTexture tbote2;
CTexture tcolchoneta;

CFiguras fig1;
CFiguras fig3;
CFiguras cubo;
CFiguras sky;


float abrirPuerta = 0;

CFiguras fclubhouse;
CFiguras fmaq_dulces;
CFiguras fsilla;
CFiguras fbote;
CFiguras fpingpong;
CFiguras fpantalla;
CFiguras fropero;
CFiguras fmaqgym;
CFiguras fpelota;




void saveFrame ( void )
{
	
	printf("frameindex %d\n",FrameIndex);			

	KeyFrame[FrameIndex].posX=posX;
	KeyFrame[FrameIndex].posY=posY;
	KeyFrame[FrameIndex].posZ=posZ;

	KeyFrame[FrameIndex].rotRodIzq=rotRodIzq;
	KeyFrame[FrameIndex].giroMonito=giroMonito;
	KeyFrame[FrameIndex].rotRodDer = rotRodDer;
	KeyFrame[FrameIndex].rotBder= rotBDer;
	KeyFrame[FrameIndex].rotBizq = rotBizq;
	FrameIndex++;
}

void resetElements( void )
{
	posX=KeyFrame[0].posX;
	posY=KeyFrame[0].posY;
	posZ=KeyFrame[0].posZ;

	rotRodIzq=KeyFrame[0].rotRodIzq;
	rotRodDer = KeyFrame[0].rotRodDer;
	rotBDer = KeyFrame[0].rotBder;
	rotBizq = KeyFrame[0].rotBizq;
	giroMonito=KeyFrame[0].giroMonito;

}

void interpolation ( void )
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;	
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;	
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;	

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;	
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;
	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].rotIncbd = (KeyFrame[playIndex + 1].rotBder - KeyFrame[playIndex].rotBder) / i_max_steps;
	KeyFrame[playIndex].rotIncbi = (KeyFrame[playIndex + 1].rotBizq - KeyFrame[playIndex].rotBizq) / i_max_steps;
}

//Proyecto inicia
void clubhousem() {	
	glPushMatrix();
	glTranslatef(0.0, 0, -5);
	fclubhouse.prisma(10, 15, 0.8, tpuerta.GLindex);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 3.0, -5.0);
	fclubhouse.prisma(15, 60, 0.5, tfachada.GLindex);	
	glTranslatef(0.0, 0.0, -25.0);
	fclubhouse.prisma(15, 60, 0.5, tpared.GLindex);
	glTranslatef(30.0, 0.0, 12.5);
	fclubhouse.prisma(15, 0.5, 25, tpared.GLindex);
	glTranslatef(-60.0, 0.0, 0.0);
	fclubhouse.prisma(15, 0.5, 25, tpared.GLindex);
	glTranslatef(30.0, 7.3, 0.0);
	fclubhouse.prisma(0.5, 60, 25, ttecho.GLindex);
	glTranslatef(0.0, -14.6, 0.0);
	fclubhouse.prisma(0.5, 60, 25, tpiso.GLindex);
	glTranslatef(0.0, 7.5, 0.0);
	fclubhouse.prisma(14, 5, 3, NULL);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, -5.0, -25.0);
	fclubhouse.prisma(0.2, 130, 80, text5.GLindex);
	glPopMatrix();
}
void silla() {
	glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(0, 2, 15);
		fsilla.prisma(0.3,1,1, tsilla.GLindex);
		glTranslatef(0, 0.5, 0.36);
		fsilla.prisma(1, 1, 0.3, tsilla.GLindex);
		glTranslatef(0, -1.2, -0.3);
		fsilla.cilindro(0.05, 0.7,24, ttubo.GLindex);
		glTranslatef(-0.45, 1, -0.3);
		fsilla.prisma(0.5, 0.1, 0.14, ttubo.GLindex);
		glTranslatef(0.9, 0, 0.0);
		fsilla.prisma(0.5, 0.1, 0.1, ttubo.GLindex);
		glTranslatef(0.0, 0.2, 0.3);
		fsilla.prisma(0.1, 0.1, 0.5, ttubo.GLindex);
		glTranslatef(-0.9, 0.0, 0.0);
		fsilla.prisma(0.1, 0.1, 0.5, ttubo.GLindex);
	glPopMatrix();
}
void pingpong() {
	fpingpong.prisma(0.3, 10, 3, NULL);
	glColor3f(0, 0, 1);
	glTranslatef(0, 0.0, 0);	
	fpingpong.prisma(0.3, 10, 3, NULL);
	glColor3f(1, 1, 1);
	glTranslatef(0, 0.12, 0);
	fpingpong.prisma(0.1, 10, 0.2, NULL);
	glColor3f(1, 0, 0);
	glTranslatef(-3.5, -1.7, 1);
	fpingpong.prisma(3, 0.3, 0.3, NULL);
	glTranslatef(7.5, 0, 0);
	fpingpong.prisma(3, 0.3, 0.3, NULL);
	glTranslatef(0, 0, -2.0);
	fpingpong.prisma(3, 0.3, 0.3, NULL);
	glTranslatef(-7, 0, 0.0);
	fpingpong.prisma(3, 0.3, 0.3, NULL);
	glColor3f(1, 1, 1);
	glTranslatef(3.3, 2.2, 1.0);
	glEnable(GL_ALPHA_TEST);
	fpingpong.prisma(1, 0.2, 3, tred.GLindex);
	glDisable(GL_ALPHA_TEST);
}
void guardaropa() {
	glColor3f(1, 1, 1);
	fropero.prisma(13, 10, 0.3, tmadera.GLindex);
	glTranslatef(0, 2.5, 1.3);
	fropero.prisma(0.5, 10, 2.5, tmadera.GLindex);
	glTranslatef(0, 1.8, 0);
	fropero.prisma(0.5, 10, 2.5, tmadera.GLindex);
	glTranslatef(0, 2.3, 0);
	fropero.prisma(0.3, 10, 2.5, tmadera.GLindex);
	glTranslatef(0, -10, 0);
	fropero.prisma(0.3, 10, 2.5, tmadera.GLindex);
	glTranslatef(-1, 8, 0);
	fropero.prisma(4, 0.4, 2.5, tmadera.GLindex);
	glTranslatef(3, 0, 0);
	fropero.prisma(4, 0.4, 2.5, tmadera.GLindex);
	glTranslatef(3, -4.5, 0);
	fropero.prisma(13, 0.4, 2.5, tmadera.GLindex);
	glTranslatef(-10, 0, 0);
	fropero.prisma(13, 0.4, 2.5, tmadera.GLindex);
}
void m_gym() {
	glColor3f(1, 1, 1);
	fmaqgym.prisma(0.3, 5, 2, tcolchoneta.GLindex);
	glTranslatef(-2.0, -0.6, 0.0);
	fmaqgym.prisma(1, 0.2,0.2, NULL);
	glTranslatef(4.0, 0.0, 0.0);
	fmaqgym.prisma(1, 0.2, 0.2, NULL);
	glTranslatef(0.0, 0.7, 0.7);
	fmaqgym.cilindro(0.1, 2, 24, NULL);
	glTranslatef(0.0, 0.0, -1.4);
	fmaqgym.cilindro(0.1, 2, 24, NULL);
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glTranslatef(-0.2, -2, -1.5);
		fmaqgym.cilindro(0.1, 5, 24, NULL);
		glPushMatrix();
		glColor3f(0, 0, 0);
;		glTranslatef(0, 1.2, 0);
		fmaqgym.cilindro(0.8, 0.3, 24, NULL);
		glTranslatef(0,2.8, 0);
		fmaqgym.cilindro(0.8, 0.3, 24, NULL);
		glPopMatrix();
	glPopMatrix();
}
void pantalla() {
	glColor3f(1, 1, 1);
	fpantalla.prisma(2, 5, 0.2, tpantalla.GLindex);
	glTranslatef(0.0, 0.0, -0.05);
	glColor3f(0.0, 0.0, 0.0);
	fpantalla.prisma(2.5, 6, 0.2, NULL);
	glTranslatef(0.0, 1, -0.9);
	fpantalla.prisma(0.3, 0.3, 2, NULL);
	glTranslatef(0.0, 0.9, -1);
	fpantalla.prisma(3.0, 0.3, 0.3, NULL);
}
void m_dulces() {	
	fmaq_dulces.prisma(8, 3, 3, tdulces.GLindex);
	glTranslatef(0.0, 0.0, -1.5);
	fmaq_dulces.prisma(8, 3, 0.3, tpdulces.GLindex);
	glTranslatef(-1.5, 0.0, 1.5);
	fmaq_dulces.prisma(8, 0.3, 3.0, tpdulces.GLindex);
	glTranslatef(3.0, 0.0, 0.0);
	fmaq_dulces.prisma(8, 0.3, 3.0, tpdulces.GLindex);
	glTranslatef(-1.5, 3.8, 0.0);
	fmaq_dulces.prisma(0.3, 3, 3.0, tpdulces.GLindex);
}
void pelota() {
	//glColor3f(1, 1, 1);
	fpelota.esfera(0.5, 15, 15, tpelota1.GLindex);
}
void botebasura() {
	glColor3f(1,1,1);
	fbote.cilindro(0.5, 1.5, 24, tbote2.GLindex);
	glTranslatef(0.0, 1.4, 0);
	fbote.cilindro(0.6, 0.15, 24, tbote2.GLindex);
	glColor3f(0, 0, 0);
	glTranslatef(0.0, -0.05, 0);
	fbote.torus(0.6, 0.2, 24, 24);
}
//proyecto termina


GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	//para proy
	tpuerta.LoadTGA("puerta.tga");
	tpuerta.BuildGLTexture();
	tpuerta.ReleaseImage();

	ttecho.LoadTGA("techo.tga");
	ttecho.BuildGLTexture();
	ttecho.ReleaseImage();

	tpared.LoadTGA("metalp.tga");
	tpared.BuildGLTexture();
	tpared.ReleaseImage();

	tfachada.LoadTGA("fachada.tga");
	tfachada.BuildGLTexture();
	tfachada.ReleaseImage();

	tpiso.LoadTGA("piso1.tga");
	tpiso.BuildGLTexture();
	tpiso.ReleaseImage();

	tdulces.LoadTGA("dulces.tga");
	tdulces.BuildGLTexture();
	tdulces.ReleaseImage();

	tpdulces.LoadTGA("pdulces.tga");
	tpdulces.BuildGLTexture();
	tpdulces.ReleaseImage();

	tpantalla.LoadTGA("tv.tga");
	tpantalla.BuildGLTexture();
	tpantalla.ReleaseImage();

	tred.LoadTGA("red.tga");
	tred.BuildGLTexture();
	tred.ReleaseImage();

	tmadera.LoadTGA("madera.tga");
	tmadera.BuildGLTexture();
	tmadera.ReleaseImage();

	tsilla.LoadTGA("silla.tga");
	tsilla.BuildGLTexture();
	tsilla.ReleaseImage();

	ttubo.LoadTGA("tubo.tga");
	ttubo.BuildGLTexture();
	ttubo.ReleaseImage();

	tpelota1.LoadTGA("pelota3.tga");
	tpelota1.BuildGLTexture();
	tpelota1.ReleaseImage();

	tbote2.LoadTGA("bote.tga");
	tbote2.BuildGLTexture();
	tbote2.ReleaseImage();

	tcolchoneta.LoadTGA("colchoneta.tga");
	tcolchoneta.BuildGLTexture();
	tcolchoneta.ReleaseImage();
	//
    text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	

	text5.LoadTGA("pasto.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();


	
	
	

	objCamera.Position_Camera(0,2.5f,22, 0,2.5f,0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;
		KeyFrame[i].rotBder = 0;
		KeyFrame[i].rotBizq = 0;
		KeyFrame[i].rotRodIzq =0;
		KeyFrame[i].rotRodDer = 0;
		KeyFrame[i].rotInc =0;
		KeyFrame[i].rotInc2 = 0;
		KeyFrame[i].rotBder = 0;
		KeyFrame[i].rotBizq = 0;
		KeyFrame[i].giroMonito =0;
		KeyFrame[i].giroMonitoInc =0;
	}
	//NEW//////////////////NEW//////////////////NEW///////////

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glPushMatrix();
	

	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				fig1.skybox(130.0, 130.0, 130.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glEnable ( GL_COLOR_MATERIAL );
					glColor3f(1, 1, 1);
					glTranslatef(posX, posY, posZ);
					glRotatef(giroMonito, 0, 1, 0);


					//mostrando clubhouse
					clubhousem();
					
					glTranslatef(4.6, 0, -18);
					glRotatef(90,0,1,0);
					m_dulces();
					glTranslatef(0, -4, -9);
					glRotatef(-180, 0, 1, 0);
					m_dulces();
					glRotatef(90, 0, 1, 0);
					glTranslatef(18, 3, -6);
					pantalla();
					glTranslatef(-30, -2, 2);
					pantalla();
					glRotatef(-180, 0, 1, 0);
					glTranslatef(0, -1.5, -15);
					pantalla();
					glTranslatef(-35, -2.5, 3);
					pantalla();
					glRotatef(180, 0, 1, 0);
					glTranslatef(-40, -6.5, -19);
					guardaropa();
					glTranslatef(16, 0, -2.0);
					guardaropa();
					glTranslatef(16, 0, -1.0);
					guardaropa();
					glTranslatef(16, 0, -1.3);
					guardaropa();
					glTranslatef(16.5, 0, -1.2);
					guardaropa();
					glRotatef(-180, 0, 1, 0);
					glTranslatef(-6, 0, -22.5);
					guardaropa();
					glTranslatef(16, 0, -1.5);
					guardaropa();
					glTranslatef(32, 0, -1);
					guardaropa();
					glTranslatef(16, 0, -1);
					guardaropa();
					glRotatef(-90, 0, 1, 0);
					glTranslatef(8, -0.5, -9);
					guardaropa();
					glRotatef(180, 0, 1, 0);
					glTranslatef(-7, -0.5, -57);
					guardaropa();
					glRotatef(90, 0, 1, 0);
					glTranslatef(-15, -2.5, 0);
					pingpong();
					glTranslatef(-27, -1, 7);
					pingpong();
					glRotatef(0, 0, 1, 0);					
					glTranslatef(-4, -2.3, -7);
					glRotatef(180, 0, 1, 0);
					m_gym();
					glTranslatef(15, -0.5, -18);
					glRotatef(-90, 0, 1, 0);
					glRotatef(90, 0, 1, 0);
					m_gym();
					glScaled(4, 4, 4);
					glTranslatef(1.5, -2, -17.5);
					silla();
					glTranslatef(-6, 0, 0);
					silla();
					glTranslatef(-2.5, 0, 0);
					silla();
					glTranslatef(-2.8, 0, 0);
					silla();
					glTranslatef(-0.4, 0, 3.2);
					silla();
					glTranslatef(2.8, 0, 0);
					silla();
					glTranslatef(9, 0, 0);
					silla();
					
					glTranslatef(0, 8, 15);
					glPushMatrix();
					glTranslatef(movKit, y, movKit);
					if (movKit > 15) {
						movKit -= 1;
					}
					pelota();
					glPopMatrix();
					glTranslatef(-6, -7, -0.5);
					botebasura();
					//termina proyecto



				glDisable ( GL_COLOR_MATERIAL );
			glPopMatrix();			

	glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-11,12.0,-14.0,(void *)font,"Proyecto final Lab");
			pintaTexto(-11,8.5,-14,(void *)font,s);
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	fig3.text_izq-= 0.001;
	fig3.text_der-= 0.001;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;
	if (g_fanimacion)
	{
		movKit += 0.1;
		giroLlanta += 2;
		tiempo += 0.1;
		x = v * tiempo + cos(angulo);
		y = v * tiempo * sin(angulo) - (0.5 * gravedad * tiempo * tiempo);

	}

	if (g_fanimacion2)
	{
		movKit -= 0.1;
		giroLlanta -= 2;

	}
	if (f_tiro) {
		//movkit += 0.1;
		tiempo += 0.1;
		x = v * tiempo + cos(angulo);
		y = v * tiempo * sin(angulo) - (0.5 * gravedad * tiempo * tiempo);
	}
	//Movimiento del monito
	if(play)
	{		
		
		if(	i_curr_steps >= i_max_steps) //end of animation between frames?
		{			
			playIndex++;		
			if(playIndex>FrameIndex-2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex=0;
				play=false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			posX+=KeyFrame[playIndex].incX;
			posY+=KeyFrame[playIndex].incY;
			posZ+=KeyFrame[playIndex].incZ;

			rotBDer += KeyFrame[playIndex].rotIncbd;
			rotBizq += KeyFrame[playIndex].rotIncbi;
			rotRodIzq+=KeyFrame[playIndex].rotInc;
			rotRodDer += KeyFrame[playIndex].rotInc2;
			giroMonito+=KeyFrame[playIndex].giroMonitoInc;

			i_curr_steps++;
		}
		
	}


	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;
		case 't':
		case 'T':
			f_tiro = true;
			movKit = 0;
			break;
		case 'k':		//
		case 'K':
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}

			break;

		case ' ':		//Poner algo en movimiento
			g_fanimacion ^= true; //Activamos/desactivamos la animacíon
			movKit = 0;
			break;
		case 'l':						
		case 'L':
			if(play==false && (FrameIndex>1))
			{

				resetElements();
				//First Interpolation				
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;

		case 'y':						
		case 'Y':
			posZ++;
			printf("%f \n", posZ);
			break;

		case 'g':						
		case 'G':
			posX--;
			printf("%f \n", posX);
			break;

		case 'h':						
		case 'H':
			posZ--;
			printf("%f \n", posZ);
			break;

		case 'j':						
		case 'J':
			posX++;
			printf("%f \n", posX);
			break;

		case 'b':						
			rotRodIzq++;
			printf("%f \n", rotRodIzq);
			break;

		case 'B':						
			rotRodIzq--;
			printf("%f \n", rotRodIzq);
			break;

		case 'p':						
			giroMonito++;
			break;

		case 'P':						
			giroMonito--;
			break;

		case 'm':
			rotRodDer++;
			break;

		case 'M':
			rotRodDer--;
			break;

		case 'o':
			rotBDer++;
			break;

		case 'O':
			rotBDer--;
			break;

		case 'i':
			rotBizq++;
			break;

		case 'I':
			rotBizq--;
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

void menuKeyFrame( int id)
{
	switch (id)
	{
		case 0:	//Save KeyFrame
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}
			break;

		case 1:	//Play animation
			if(play==false && FrameIndex >1)
			{

				resetElements();
				//First Interpolation
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;


	}
}


void menu( int id)
{
	
}



int main ( int argc, char** argv )   // Main Function
{
  int submenu;
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto 2"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  submenu = glutCreateMenu	  ( menuKeyFrame );
  glutAddMenuEntry	  ("Guardar KeyFrame", 0);
  glutAddMenuEntry	  ("Reproducir Animacion", 1);
  glutCreateMenu	  ( menu );
  glutAddSubMenu	  ("Animacion Monito", submenu);
 
  glutAttachMenu	  (GLUT_RIGHT_BUTTON);


  glutMainLoop        ( );          // 

  return 0;
}