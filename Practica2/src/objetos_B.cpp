//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B.h"
#include "file_ply_stl.hpp"



//*************************************************************************
// _puntos3D
//*************************************************************************


_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}



//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}



//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
	for (int i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i=0;i<caras.size();i++){
		if(i%2 == 0){
			glColor3f(r1, g1, b1);
		}else{
			glColor3f(r2, g2, b2);
		}
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}



//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
vertices.resize(8);
vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
vertices[2].x=-tam;vertices[2].y=-tam;vertices[2].z=-tam;
vertices[3].x=tam;vertices[3].y=-tam;vertices[3].z=-tam;
vertices[4].x=-tam;vertices[4].y=tam;vertices[4].z=tam;
vertices[5].x=tam;vertices[5].y=tam;vertices[5].z=tam;
vertices[6].x=-tam;vertices[6].y=tam;vertices[6].z=-tam;
vertices[7].x=tam;vertices[7].y=tam;vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=2;
caras[1]._0=2;caras[1]._1=1;caras[1]._2=3;

caras[2]._0=4;caras[2]._1=5;caras[2]._2=6;
caras[3]._0=6;caras[3]._1=5;caras[3]._2=7;

caras[4]._0=0;caras[4]._1=1;caras[4]._2=4;
caras[5]._0=4;caras[5]._1=1;caras[5]._2=5;

caras[6]._0=3;caras[6]._1=2;caras[6]._2=7;
caras[7]._0=7;caras[7]._1=2;caras[7]._2=6;

caras[8]._0=2;caras[8]._1=0;caras[8]._2=6;
caras[9]._0=6;caras[9]._1=0;caras[9]._2=4;

caras[10]._0=1;caras[10]._1=3;caras[10]._2=5;
caras[11]._0=5;caras[11]._1=3;caras[11]._2=7;
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices
vertices.resize(5);
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply()
{
   // leer lista de coordenadas de vértices y lista de indices de vértices

}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;

_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);
caras.resize(n_car);

// Copy vertexes to local vertices
int j=0, i;
for(i=0; i < n_ver; ++i){
	vertices[i].x = ver_ply[j++];
	vertices[i].y = ver_ply[j++];
	vertices[i].z = ver_ply[j++];
}

// Copy faces to local caras
j = 0;
for(i=0; i < n_car; ++i){
	caras[i]._0 = car_ply[j++];
	caras[i]._1 = car_ply[j++];
	caras[i]._2 = car_ply[j++];
}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}

int _rotacion::parametros(
	char *archivo,
	int num,
	eje_rot eje,
	float rad
){

	_objeto_ply::parametros(archivo);
	_rotacion::parametros(this->vertices, num, eje, rad);

	return 0;
}


void _rotacion::parametros(
	vector<_vertex3f> perfil,
	int num,
	eje_rot eje,
	float rad
){
	int n_perfil = perfil.size();

	// Calcular numero de puntos en el eje y anotar cuales
	bool point_eje[n_perfil]{false};
	int n_point_eje = 0;

	for(int i=0; i < n_perfil; ++i){
		if(_rotacion::is_in_eje(perfil[i], eje)){
			point_eje[i]=true;
			n_point_eje++;
		}
	}

	// Generar puntos
	vertices.resize(n_perfil + (n_perfil-n_point_eje)*(num-1));
	for(int i = 0; i<n_perfil; ++i){
		vertices[i] = perfil[i];
	}
	int n_point_eje_below;
	for(int i=0; i<num-1; ++i){
		n_point_eje_below=0;
		for(int j=0; j<n_perfil; ++j){
			if(!point_eje[j]){
				vertices[n_perfil + j-n_point_eje_below + i*(n_perfil-n_point_eje)] = _rotacion::rotate_point(vertices[j], eje, rad*(i+1)/(1.*num));
			}else{
				++n_point_eje_below;
			}
		}
	}

	//Generar triangulos
	int n_cara = 0;
	int n_cara_perf = (n_perfil-1)*2;
	if(point_eje[0]){
		--n_cara_perf;
	}else{
		n_cara+=num;
	}
	if(point_eje[n_perfil-1]){
		--n_cara_perf;
	}else{
		n_cara+=num;
	}
	for(int i=1; i<n_perfil-1; ++i){
		if(point_eje[i]) n_cara_perf-=2;
	}
	n_cara += (num)*n_cara_perf;

	//caras.resize(n_cara);

	// Generamos perfiles intermedios
	_vertex3i aux_cara;

	for(int i=1; i<num-1; ++i){
		n_point_eje_below = 0;
		for(int j=0; j<n_perfil-1; ++j){
			// Primer triangulo
			if(!point_eje[j]){
				aux_cara._0=i*(n_perfil-n_point_eje)+j-n_point_eje_below+n_point_eje;
				aux_cara._1=(i+1)*(n_perfil-n_point_eje)+j-n_point_eje_below+n_point_eje;
				aux_cara._2=point_eje[j+1] ? j+1 : i*(n_perfil-n_point_eje)+j-n_point_eje_below+1+n_point_eje;
				caras.push_back(aux_cara);
			}else{
				++n_point_eje_below;
			}

			// Segundo triangulo
			if(!point_eje[j+1]){
				aux_cara._0=i*(n_perfil-n_point_eje)+j-n_point_eje_below+1+n_point_eje;
				aux_cara._1=point_eje[j] ? j : (i+1)*(n_perfil-n_point_eje)+j-n_point_eje_below+n_point_eje;
				aux_cara._2=(i+1)*(n_perfil-n_point_eje	)+j-n_point_eje_below+1+n_point_eje;
				caras.push_back(aux_cara);
			}
		}
	}

	// Primer y ultimo Perfil
	n_point_eje_below=0;
	for(int j=0; j<n_perfil-1; ++j){
		if(!point_eje[j]){
			aux_cara._0=(num-1)*(n_perfil-n_point_eje)+j-n_point_eje_below+n_point_eje;
			aux_cara._1=j;
			aux_cara._2=point_eje[j+1] ? j+1 : (num-1)*(n_perfil-n_point_eje)+j-n_point_eje_below+1+n_point_eje;
			caras.push_back(aux_cara);
		}else{
			++n_point_eje_below;
		}
		if(!point_eje[j+1]){
			aux_cara._0=(num-1)*(n_perfil-n_point_eje)+j-n_point_eje_below+1+n_point_eje;
			aux_cara._1=j;
			aux_cara._2=j+1;
			caras.push_back(aux_cara);
		}
	}
	n_point_eje_below=0;
	for(int j=0; j<n_perfil-1; ++j){
		if(!point_eje[j]){
			aux_cara._0=j;
			aux_cara._1=(n_perfil)+j-n_point_eje_below;
			aux_cara._2=j+1;
			caras.push_back(aux_cara);
		}else{
			n_point_eje_below++;
		}
		if(!point_eje[j+1]){
			aux_cara._0=j+1;
			aux_cara._1=point_eje[j] ? j : (n_perfil)+j-n_point_eje_below;
			aux_cara._2=(n_perfil)+j-n_point_eje_below+1;
			caras.push_back(aux_cara);
		}
	}

	// Tapas
	if(!point_eje[0]){
		for(int i=1; i<num-2; ++i){
			aux_cara._0=0;
			aux_cara._1=n_perfil+(i-1)*(n_perfil-n_point_eje);
			aux_cara._2=n_perfil+(i)*(n_perfil-n_point_eje);
			caras.push_back(aux_cara);
		}
	}

	if(!point_eje[n_perfil-1]){
		for(int i=1; i<num-2; ++i){
			aux_cara._0=n_perfil-1;
			aux_cara._1=2*n_perfil-1+(i-1)*(n_perfil-n_point_eje);
			aux_cara._2=2*n_perfil-1+(i)*(n_perfil-n_point_eje);
			caras.push_back(aux_cara);
		}
	}
}

bool _rotacion::is_in_eje(_vertex3f point, eje_rot eje){
	switch(eje){
		case X:
			return point.y==0;
		case Y:
			return point.x==0;
		case Z:
			return point.x==0 && point.y==0;
		default:
			return false;
	}
}

_vertex3f _rotacion::rotate_point(_vertex3f point, eje_rot eje, float theta){
	_vertex3f r_point;
	switch (eje) {
		case X:
			r_point.x = point.x;
			r_point.y = point.y*cos(theta)-point.z*sin(theta);
			r_point.z = point.y*sin(theta)+point.z*cos(theta);
			return r_point;
		case Y:
			r_point.x = point.x*cos(theta)+point.z*sin(theta);
			r_point.y=point.y;
			r_point.z = -1*(point.x*sin(theta))+point.z*cos(theta);
			return r_point;
		case Z:
			r_point.x=point.x*cos(theta)-point.y*sin(theta);
			r_point.y=point.x*sin(theta)+point.y*cos(theta);
			r_point.z = point.z;
			return r_point;
		default:
			return {.0,.0,.0};
	}
}

//************************************************************************
// esfera
//************************************************************************

_esfera::_esfera(){}

void _esfera::parametros(float r, int num, float rad){
	// Generamos perfil
	_vertex3f point = {0.,-r,0.};
	vertices.resize(30);
	vertices[0]=point;
	for(int i=0; i<28; ++i){
		vertices[i+1]=rotate_point(point, Z, M_PI*(i+1)/(1.*28));
	}
	_vertex3f last_point= {0.,r,0.};
	vertices[29] = last_point;

	for(int i=0; i<vertices.size(); ++i){
		cout<<vertices[i].x<<","<<vertices[i].y<<","<<vertices[i].z<<endl;
	}

	// Generamos esfera por rotacion
	_rotacion::parametros(this->vertices, num, Y, rad);
}
