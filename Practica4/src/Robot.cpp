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
// clase Vsupport
//*************************************************************************
Vsupport::Vsupport(){
  rod.parametros("data/cilindro", 20);
}

void Vsupport::draw(_modo modo, float r1, float g1, float b1,
  float r2, float g2, float b2, float grosor)
{
  glPushMatrix();
    glTranslatef(0,1.38,0);
    glScalef(0.3,0.25,0.25);
    glRotatef(90,0,0,1);
    rod.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
    glScalef(0.25,1,0.25);
    glTranslatef(0,0.9,0);
    v_support.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

}
//*************************************************************************
// clase Robot
//*************************************************************************
Robot::Robot(){
  wheel.parametros(0.8, 20, 2*M_PI);
  string.parametros("data/cilindro", 10);
  ball.parametros(0.125, 10, 2*M_PI);
  h_dplcmnt=1;
  h_s_lenght = 1.9;
  string_length = 0.5;

  position.x=0;position.y=0;position.z=0;
  velocity=0.01;
  wheel_angle_z=0;
  wheel_angle_x=0;
  chasis_angle=0;
  chasis_velocity=1;
}

void Robot::draw(_modo modo, float r1, float g1, float b1,
  float r2, float g2, float b2, float grosor)
  {
    glPushMatrix();
      //x,z movement
      glTranslatef(position.x, 0, position.z);

      glPushMatrix();
        glTranslatef(0,-1,0);
        //Wheel rotation on x,z movement
        glRotatef(wheel_angle_z, 0,0,1);
        glRotatef(wheel_angle_x, 1,0,0);
        wheel.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
      glPopMatrix();

      glPushMatrix();

        //Chasis rotation
        glRotatef(chasis_angle,0,1,0);

        chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
        v_support.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

        glPushMatrix();
          //H support displacement
          glTranslatef(0,0,h_dplcmnt);
          glPushMatrix();
            glTranslatef(0,1.52,0);
            glScalef(0.25,0.25,5);
            h_support.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
          glPopMatrix();

          glPushMatrix();
            glTranslatef(0, 1.5, 2.4);
            //String length
            glScalef(0.1,string_length,0.1);
            glTranslatef(0,-0.5,0);
            string.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
          glPopMatrix();


          glPushMatrix();
            //Rotate ball
            glTranslatef(0, 1.5-string_length, 2.4);
            glRotatef(ball_angle,0,1,0);
            ball.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
          glPopMatrix();

        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  }
