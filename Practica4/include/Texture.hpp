#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "CImg.h"
#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

class Texture{
public:
  void prepara_textura (char *file, GLuint *tex_id );
  void libera_textura (GLuint *tex_id);

private:

};

#endif
