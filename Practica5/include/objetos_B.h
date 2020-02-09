//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************
#ifndef __OBJETOS_H__
#define __OBJETOS_H__
#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

using namespace std;

const float AXIS_SIZE=5000;

enum eje_rot{X=0,Y,Z};

typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,FLAT,SMOOTH,SELECT} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:


	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
	void 	draw_aristas(float r, float g, float b, int grosor);
	void    draw_solido(float r, float g, float b);
	void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
	void 	virtual draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	void 	draw_iluminacion_plana( );
	void 	draw_iluminacion_suave( );

	void draw_selection();
	vector<bool> alt_triangle_color;

	void	calcular_normales_caras();
	void 	calcular_normales_vertices();

	vector<_vertex3i> caras;
	vector<_vertex3f> normales_caras;
	vector<_vertex3f> normales_vertices;

	bool b_normales_caras;
	bool b_normales_vertices;

	_vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
	_vertex4f especular;           //coeficiente especular
	float brillo;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _objeto_ply
{
public:
       _rotacion();
void  parametros(
	vector<_vertex3f> perfil1,
	int num,
	eje_rot eje = Y,
	float rad=2*M_PI
);

int   parametros(
	char *archivo,
	int num,
	eje_rot eje = Y,
	float rad=2*M_PI
);

vector<_vertex3f> perfil;
int num;

protected:
	bool is_in_eje(_vertex3f point, eje_rot eje);
	_vertex3f rotate_point(_vertex3f point, eje_rot eje, float theta);
};

//************************************************************************
// esfera
//************************************************************************

class _esfera: public _rotacion{
public:
	_esfera();
	void parametros(float r, int num, float rad=2*M_PI);
};

#endif
