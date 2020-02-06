//Helicopter Model
#include "objetos_B.h"


class HeliBody : _triangulos3D{
public:
  HeliBody();
  void 	draw(_modo modo, float r1, float g1, float b1,
    float r2, float g2, float b2, float grosor) override;

private:
  _piramide cabin;
  _cubo body;
  _rotacion back;
};


class HeliHelix: _triangulos3D{
public:
  HeliHelix();
  void 	draw(_modo modo, float r1, float g1, float b1,
    float r2, float g2, float b2, float grosor) override;

private:
  _cubo helix_1, helix_2;
  _rotacion cilinder;
};

class HeliHook: _triangulos3D{
public:
  HeliHook();
  void 	draw(_modo modo, float r1, float g1, float b1,
    float r2, float g2, float b2, float grosor) override;

private:
  _rotacion string, hook_0, hook_1, hook_2;
};

class Heli: public _triangulos3D {
public:
  Heli();
  void 	draw(_modo modo, float r1, float g1, float b1,
    float r2, float g2, float b2, float grosor) override;

private:
  HeliBody body;
  HeliHelix helix_up, helix_back;
  HeliHook hook;
};
