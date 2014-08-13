#include <iostream>

#include "CTexture.h"

CTexture::CTexture()
{
	_gl_handle = 0;
	_w = 0;
	_h = 0;
}

CTexture::~CTexture()
{
	Release();
}

void CTexture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, _gl_handle);
}

void CTexture::LoadTexture(std::string filename)
{
	_filename = filename;
	
	std::cout << "Loading Texture:" << _filename.c_str() << std::endl;
	SDL_Surface *tex_img = IMG_Load(_filename.c_str());
	
	glGenTextures(1, &_gl_handle);
	BindTexture();
	glTexImage2D(GL_TEXTURE_2D,	0, GL_RGBA, tex_img->w, tex_img->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_img->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(tex_img);
}


void CTexture::LoadTextureAlpha(std::string filename)
{
	_filename = filename;
	
	std::cout << "Loading Texture:" << _filename.c_str() <<std::endl;
	SDL_Surface *tex_img = IMG_Load(_filename.c_str());
	
	glGenTextures(1, &_gl_handle);
	BindTexture();
	glTexImage2D(GL_TEXTURE_2D,	0, GL_RGBA, tex_img->w, tex_img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_img->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	_w = tex_img->w;
	_h = tex_img->h;

	SDL_FreeSurface(tex_img);
}

void CTexture::CreateTexture(unsigned char * data, unsigned int w, unsigned int h)
{
	_filename = "(generated texture)";
	glGenTextures(1, &_gl_handle);
	BindTexture();
	glTexImage2D(GL_TEXTURE_2D,	0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	_w = w;
	_h = h;
}


void CTexture::Release()
{
	printf("Releasing Texture: %s\n", _filename.c_str());
	glDeleteTextures(1, &_gl_handle);

}

const unsigned int & CTexture::get_w()
{
	return _w;
}

const unsigned int & CTexture::get_h()
{
	return _h;
}
