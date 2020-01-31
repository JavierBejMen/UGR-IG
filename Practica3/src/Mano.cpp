//Mano.cpp
#include "Mano.hpp"

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//************************************************************************
// class Falange_3
//************************************************************************

Falange_3::Falange_3(){

  _vertex3f aux_point = {0.,0.25,0.};
  vertices.push_back(aux_point);

  for(int i=0; i<5; ++i){
		vertices.push_back(_rotacion::rotate_point(aux_point, Z, M_PI/2*(i+1)/(1.*6)));
	}

  aux_point = _vertex3f {-0.25,0.,0.};
	vertices.push_back(aux_point);

  for(int i=0; i<vertices.size(); ++i){
    vertices[i].x*=(-1);vertices[i].y+=0.25;
  }

  aux_point = _vertex3f {0.25, -0.5, 0.};
  vertices.push_back(aux_point);

  sort(vertices.begin(), vertices.end(),
    [](const _vertex3f & a, const _vertex3f & b) -> bool{
      return a.y < b.y;
    });

  _rotacion::parametros(this->vertices, 20, Y, 2*M_PI);
}

//************************************************************************
// class Dedo
//************************************************************************
Dedo::Dedo(){
  vector<_vertex3f> perfil={-0.5,0.5};
  falange_1.parametros(perfil, 20);
  falange_2.parametros(perfil, 20);
  articulacion_1.parametros(0.5, 20);
  articulacion_2.parametros(0.5, 20);
}

void Dedo::draw_puntos(float r, float g, float b, int grosor){
  cout << "HOLAAAAAAAAA"<<endl;
  falange_1.draw_puntos(r,g,b,grosor);
  falange_2.draw_puntos(r,g,b,grosor);
  falange_3.draw_puntos(r,g,b,grosor);
  articulacion_1.draw_puntos(r,g,b,grosor);
  articulacion_2.draw_puntos(r,g,b,grosor);
}
void Dedo::draw_aristas(float r, float g, float b, int grosor){
  falange_1.draw_aristas(r,g,b,grosor);
  falange_2.draw_aristas(r,g,b,grosor);
  falange_3.draw_aristas(r,g,b,grosor);
  articulacion_1.draw_aristas(r,g,b,grosor);
  articulacion_2.draw_aristas(r,g,b,grosor);
}
void Dedo::draw_solido(float r, float g, float b){
  falange_1.draw_solido(r,g,b);
  falange_2.draw_solido(r,g,b);
  falange_3.draw_solido(r,g,b);
  articulacion_1.draw_solido(r,g,b);
  articulacion_2.draw_solido(r,g,b);
}
void Dedo::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2){
  falange_1.draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
  falange_2.draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
  falange_3.draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
  articulacion_1.draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
  articulacion_2.draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
}

void Dedo::compose(){

}
