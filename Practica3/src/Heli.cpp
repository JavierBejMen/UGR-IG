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
HeliHelix::HeliHelix(){}

void 	HeliHelix::draw(_modo modo, float r1, float g1, float b1,
  float r2, float g2, float b2, float grosor){

}
//*************************************************************************
// clase HeliHook
//*************************************************************************
HeliHook::HeliHook(){}

void 	HeliHook::draw(_modo modo, float r1, float g1, float b1,
  float r2, float g2, float b2, float grosor){

}

//*************************************************************************
// clase Heli
//*************************************************************************
Heli::Heli(){}

void Heli::draw(_modo modo, float r1, float g1,
  float b1, float r2, float g2, float b2, float grosor){

    body.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  }
