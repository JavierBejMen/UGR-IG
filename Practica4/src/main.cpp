//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "objetos_B.h"
#include <iostream>
#include <algorithm>
#include "vertex.h"
#include "Robot.hpp"
#include <stdlib.h>

using namespace std;
// tamaño de los ejes



// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=920,UI_window_height=920;

// Objetos
_piramide piramide(0.85,1.3);
_cubo cubo(0.2);
_objeto_ply  ply;
_rotacion cono, cilindro, prueba;
_esfera esfera;
Robot robot;

// Variables de control
_triangulos3D *current_object = &piramide;
_modo draw_mode = POINTS;
bool animation = false;
bool ball_dir=true, h_dir=true, x_dir=true, z_dir=true;
int x_max,x_min,z_max,z_min;

//Animation function
void funcion_idle(){

  if(ball_dir){
    robot.ball_angle+=0.1;
    if(robot.ball_angle>75)ball_dir=false;
  }else{
    robot.ball_angle-=0.1;
    if(robot.ball_angle<-75)ball_dir=true;
  }

  if(h_dir){
    robot.h_dplcmnt+=0.0001;
    if(robot.h_dplcmnt>=2)h_dir=false;
  }else{
    robot.h_dplcmnt-=0.001;
    if(robot.h_dplcmnt<=-1.1)h_dir=true;
  }

  if(x_dir){
    robot.position.x-=0.001;
    robot.wheel_angle_z+=0.03;
    if(robot.position.x<=x_min)x_dir=false;
  }else{
    robot.position.x+=0.001;
    robot.wheel_angle_z-=0.03;
    if(robot.position.x>=x_max)x_dir=true;
  }

  if(z_dir){
    robot.position.z-=0.001;
    robot.wheel_angle_x-=0.03;
    if(robot.position.z<=z_min)z_dir=false;
  }else{
    robot.position.z+=0.001;
    robot.wheel_angle_x+=0.03;
    if(robot.position.z>=z_max)z_dir=true;
  }


  glutPostRedisplay();
}

//**************************************************************************
//  Lights
//***************************************************************************
float light1_angle = 0;
GLfloat light1_position[] = { 3.0, 3.0, 0.0, 1.0 };
bool rotation = false;

void rotating_light(){
  light1_angle+=0.1;
  glPushMatrix();
    glRotated(light1_angle, 0, 1, 0);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glPopMatrix();

  glutPostRedisplay();
}

void EnableLights(){
  //Parallel on y axe white light
  GLfloat light0_position[] = { 0.0, 1.0, 0.0, 0.0 };
  GLfloat light0_ambient[] = { .2, .2, .2, 1.0 };
	GLfloat light0_diffuse[] = { .2, .2, .2, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  glEnable(GL_LIGHT0);

  // Rotating magenta light
  GLfloat light1_ambient[] = { 0., .0, 0., 1.0 };
	GLfloat light1_diffuse[] = { 1., .0, 1., 1.0 };
	GLfloat light1_specular[] = { 1., .0, 1., 1.0 };

  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

  glEnable(GL_LIGHT1);
}

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{
  // Solucion para el ratio al maximizar
	const GLfloat ratio = GLfloat(UI_window_height) / GLfloat(UI_window_width);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	// glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
	glFrustum(-Window_width,Window_width,-Window_height * ratio,Window_height * ratio,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
  current_object->draw(draw_mode, .8,.8,.8,.0,.5,1.,1);
}



//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
  UI_window_width = Ancho1;
	UI_window_height = Alto1;

  change_projection();

  glViewport(0,0,Ancho1,Alto1);
  glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

if (toupper(Tecla1)=='Q') exit(0);
if (toupper(Tecla1)=='P') draw_mode=POINTS;
if (toupper(Tecla1)=='L') draw_mode=EDGES;
if (toupper(Tecla1)=='F') draw_mode=SOLID;
if (toupper(Tecla1)=='C') draw_mode=SOLID_CHESS;
if (Tecla1=='1') current_object = &piramide;
if (Tecla1=='2') current_object = &cubo;
if (Tecla1=='3') current_object = &cono;
if (Tecla1=='4') current_object = &cilindro;
if (Tecla1=='5') current_object = &esfera;
if (Tecla1=='6') current_object = &ply;
if (Tecla1=='7') current_object = &robot;
if(toupper(Tecla1)=='A'){
  if(!animation){
    //idle function
    glutIdleFunc(funcion_idle);
    animation=true;
  }else{
    animation=false;
    glutIdleFunc(NULL);
  }
}
if(toupper(Tecla1)=='W'){
  robot.position.x-=robot.velocity;
  robot.wheel_angle_z+=robot.velocity*30;
}
if(toupper(Tecla1)=='E'){
  robot.position.x+=robot.velocity;
  robot.wheel_angle_z-=robot.velocity*30;
}
if(toupper(Tecla1)=='R'){
  robot.position.z-=robot.velocity;
  robot.wheel_angle_x-=robot.velocity*30;
}
if(toupper(Tecla1)=='T'){
  robot.position.z+=robot.velocity;
  robot.wheel_angle_x+=robot.velocity*30;
}
if(toupper(Tecla1)=='Y') robot.chasis_angle+=robot.chasis_velocity;
if(toupper(Tecla1)=='U') robot.chasis_angle-=robot.chasis_velocity;
if(toupper(Tecla1)=='I') robot.h_dplcmnt=min(robot.h_dplcmnt+0.1,2.);
if(toupper(Tecla1)=='O') robot.h_dplcmnt=max(robot.h_dplcmnt-0.1,-1.1);
if(toupper(Tecla1)=='G') robot.string_length=min(robot.string_length+0.1,3.);
if(toupper(Tecla1)=='H') robot.string_length=max(robot.string_length-0.1,0.5);
if(toupper(Tecla1)=='J') robot.ball_angle+=0.5;
if(toupper(Tecla1)=='K') robot.ball_angle-=0.5;
if(toupper(Tecla1)=='Z') robot.velocity=min(robot.velocity+0.01, 0.2);
if(toupper(Tecla1)=='X') robot.velocity=max(robot.velocity-0.01, 0.01);
if(toupper(Tecla1)=='B') robot.chasis_velocity=min(robot.chasis_velocity+1, (float)5);
if(toupper(Tecla1)=='N') robot.chasis_velocity=max(robot.chasis_velocity-1, (float)1);

glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
  case GLUT_KEY_F1: draw_mode=FLAT;break;
  case GLUT_KEY_F2: draw_mode=SMOOTH;break;
  case GLUT_KEY_F3:
    if(!rotation){
      //idle function
      glutIdleFunc(rotating_light);
      rotation=true;
    }else{
      rotation=false;
      glutIdleFunc(NULL);
    }
  }
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************


void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=.5;
Window_height=.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=3*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
EnableLights();
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    srand (time(NULL));

    x_max=rand()%10;
    x_min=-(rand()%10);
    z_max=rand()%10;
    z_min=-(rand()%10);
    // se llama a la inicialización de glut

    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Práctica 1");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // funcion de inicialización
    initialize();

    // creación de objetos ply
    ply.parametros(argv[1]);
    cono.parametros("data/cono", 40);
    cilindro.parametros("data/cilindro", 40);
    prueba.parametros("data/prueba", 20, Z, 2*M_PI*0.75);
    esfera.parametros(0.5, 40);

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
