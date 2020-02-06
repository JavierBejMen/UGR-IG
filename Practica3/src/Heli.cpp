//Helicopter Model
#include "Heli.hpp"

using namespace std;

//*************************************************************************
// clase HeliBody
//*************************************************************************

HeliBody::HeliBody(){
  back.parametros("data/cilindro", 40);
}

void 	HeliBody::draw(_modo modo, float r1, float g1, float b1,
  float r2, float g2, float b2, float grosor){
    glPushMatrix();
      glTranslatef(-1, 0, 0);
      glRotatef(90, 0, 0, 1);
      cabin.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
      glScalef(2, 1, 1);
      body.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(3, 0, 0);
      glScalef(4, 0.2, 0.2);
      glRotatef(90, 0, 0, 1);
      back.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
}
//*************************************************************************
// clase HeliHelix
//*************************************************************************
HeliHelix::HeliHelix(){
  cilinder.parametros("data/cilindro", 40);
}

void 	HeliHelix::draw(_modo modo, float r1, float g1, float b1,
  float r2, float g2, float b2, float grosor){
    glPushMatrix();
    glTranslatef(0,0.48,0);
    glPushMatrix();
      glScalef(6, 0.005, 0.15);
      helix_1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,0.007,0);
      glRotatef(90,0,1,0);
      glScalef(6, 0.005, 0.15);
      helix_2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,0.25,0);
      glScalef(0.1,0.5,0.1);
      cilinder.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();


}
//*************************************************************************
// clase HeliHook
//*************************************************************************
HeliHook::HeliHook(){
  string.parametros("data/cilindro", 40);
  hook_0.parametros("data/cilindro", 40);
  hook_1.parametros("data/cilindro", 40);
  hook_2.parametros("data/cilindro", 40);
}

void 	HeliHook::draw(_modo modo, float r1, float g1, float b1,
  float r2, float g2, float b2, float grosor){
    glPushMatrix();
      glTranslatef(0, 0.05, 0);
      glScalef(0.015,0.1,0.015);
      string.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
      glScalef(0.03, 0.1, 0.03);
      hook_0.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-0.05,-0.02,0);
      glScalef(0.03, 0.05, 0.03);
      hook_1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-(0.03),-0.04,0);
      glRotatef(90,0,0,1);
      glScalef(0.03, 0.05, 0.03);
      hook_2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();


}

//*************************************************************************
// clase Heli
//*************************************************************************
Heli::Heli(){}

void Heli::draw(_modo modo, float r1, float g1,
  float b1, float r2, float g2, float b2, float grosor){

    body.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPushMatrix();
      glTranslatef(0,0.5,0);
      helix_up.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(4.9,0,0);
      glRotatef(90, 1,0,0);
      glScalef(0.2,0.5,0.2);
      helix_back.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,-0.6,0);
      hook.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
  }
