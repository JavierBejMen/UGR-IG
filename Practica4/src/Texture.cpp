#include "Texture.hpp"

using namespace cimg_library;
using namespace std;

// ----------------------------------------------------------------------
void Texture::prepara_textura (char *file, GLuint *tex_id )
{
   vector<unsigned char> data;
   CImg<unsigned char> image;

   image.load(file);

   // empaquetamos bien los datos
   for (long y = 0; y < image.height(); y ++)
      for (long x = 0; x < image.width(); x ++)
      {
	 unsigned char *r = image.data(x, y, 0, 0);
	 unsigned char *g = image.data(x, y, 0, 1);
	 unsigned char *b = image.data(x, y, 0, 2);
	 data.push_back(*r);
	 data.push_back(*g);
	 data.push_back(*b);
      }

   glGenTextures(1, tex_id);
   glBindTexture(GL_TEXTURE_2D, *tex_id);

   //glActiveTexture(GL_TEXTURE0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // TRASFIERE LOS DATOS A GPU
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(),
		0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}

/*
void dibuja (void)
{
   glEnable(GL_TEXTURE_2D);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, textura_id);

   glVertexPointer(2, GL_FLOAT, 0, vertices);
   glTexCoordPointer(2, GL_FLOAT, 0, texVertices);
   glDrawArrays(GL_QUADS, 0, 4);

   glDisableClientState(GL_VERTEX_ARRAY);
   glBindTexture(GL_TEXTURE_2D, 0);
   glDisable(GL_TEXTURE_2D);
}*/

void Texture::libera_textura (GLuint *tex_id)
{
   glDeleteTextures(1, tex_id);
}
