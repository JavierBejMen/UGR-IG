#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "objetos_B.h"

//Chasis
class Chasis: _triangulos3D{
public:
  Chasis();
  void 	draw(_modo modo, float r1, float g1, float b1,
    float r2, float g2, float b2, float grosor) override;

private:
  _rotacion lower;
  _esfera upper;
};

//Vertical support
class Vsupport: _triangulos3D{
public:
  Vsupport();
  void 	draw(_modo modo, float r1, float g1, float b1,
    float r2, float g2, float b2, float grosor) override;

private:
  _rotacion rod;
  _cubo v_support;
};

//Robot
class Robot: public _triangulos3D{
public:
  Robot();
  void 	draw(_modo modo, float r1, float g1, float b1,
    float r2, float g2, float b2, float grosor) override;

  _vertex3f position;
  float velocity, wheel_angle_z, wheel_angle_x, chasis_angle, chasis_velocity;
  float h_dplcmnt, string_length, ball_angle;

private:
  _esfera wheel;
  Chasis chasis;
  _cubo h_support;
  Vsupport v_support;
  _esfera ball;
  _rotacion string;
  float h_s_lenght;

};

#endif
