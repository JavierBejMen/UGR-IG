#include "Robot.hpp"

using namespace std;

//*************************************************************************
// clase Chasis
//*************************************************************************
Chasis::Chasis(){
  lower.parametros("data/Robot_lower", 20);
  upper.parametros(0.5, 20, M_PI+0.17);
}

void Chasis::draw(_modo modo, float r1, float g1, float b1,
  float r2, float g2, float b2, float grosor)
{
  lower.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPushMatrix();
    glRotatef(90,1,0,0);
    upper.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}


//*************************************************************************
// clase Hsupport
//*************************************************************************
Hsupport::Hsupport(){
  rod.parametros("data/cilindro", 20);
}

void Hsupport::draw(_modo modo, float r1, float g1, float b1,
  float r2, float g2, float b2, float grosor)
{
  glPushMatrix();
    glScalef(0.3,0.25,0.25);
    glRotatef(90,0,0,1);
    rod.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,0.13,0.5);
    glRotatef(90,1,0,0);
    glScalef(0.25,3,0.25);
    h_support.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}
//*************************************************************************
// clase Robot
//*************************************************************************
Robot::Robot(){
  wheel.parametros(0.8, 20, 2*M_PI);
  string.parametros("data/cilindro", 10);
  ball.parametros(0.125, 10, 2*M_PI);
  v_s_height = 0.5+0.25+0.3;
  h_s_lenght = 1.9;
  string_length = 0.5;

  position.x=0;position.y=0;position.z=0;
  velocity=0.01;
}

void Robot::draw(_modo modo, float r1, float g1, float b1,
  float r2, float g2, float b2, float grosor)
  {
    glPushMatrix();
      //x,z movement
      glTranslatef(position.x, 0, position.z);

      chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
      glPushMatrix();
        glTranslatef(0,-1,0);
        glRotatef(wheel_angle_z, 0,0,1);
        glRotatef(wheel_angle_x, 1,0,0);
        wheel.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0,0.7,0);
        glScalef(0.25,0.5,0.25);
        v_support.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0,1,0);
        h_support.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0, v_s_height, h_s_lenght);
        glScalef(0.1,string_length-0.12,0.1);
        glTranslatef(0,-0.5,0);
        string.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0, v_s_height-string_length, h_s_lenght);
        ball.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
      glPopMatrix();
    glPopMatrix();
  }
