//Mano.hpp
#ifndef __MANO_H__
#define __MANO_H__
#include "objetos_B.h"
#include "vertex.h"

class Falange_3: public _rotacion{
public:
  Falange_3();

};

class Dedo: public _triangulos3D{
public:
  Dedo();
  void draw_puntos(float r, float g, float b, int grosor);
  void draw_aristas(float r, float g, float b, int grosor);
  void draw_solido(float r, float g, float b);
  void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

  void compose();
protected:
  _rotacion falange_1, falange_2;
  Falange_3 falange_3;
  _esfera articulacion_1, articulacion_2;
};

#endif
