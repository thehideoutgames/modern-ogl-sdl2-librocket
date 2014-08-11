#ifndef CTEXTURE_H
#define CTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <GL/GL.h>

#include <string>
//#include "CSDLApp.h"
//#include "CResource.h"


class CTexture//: public CResource
{
private:
	GLuint _gl_handle;
	std::string _filename;
	unsigned int _w;
	unsigned int _h;
public:
	CTexture();
	~CTexture();
	
	void BindTexture();
	void LoadTexture(std::string filename);
	void LoadTextureAlpha(std::string filename);
	void CreateTexture(unsigned char * data, unsigned int w, unsigned int h);
	void Release();

	const unsigned int & get_w();
	const unsigned int & get_h();
};


#endif
