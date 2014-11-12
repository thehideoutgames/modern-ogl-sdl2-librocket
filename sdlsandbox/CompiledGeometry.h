#ifndef _COMPILED_GEOMETRY_H_
#define _COMPILED_GEOMETRY_H_

#include <Rocket/Core/RenderInterface.h>
//#include <Rocket/Core/Platform.h>
//#include <Rocket/Core.h>
//#include <Rocket/Controls.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>


#include "CTexture.h"

class CompiledGeometry
{
private:
	unsigned int _elementBuffer;
	unsigned int _vertexBuffer;
	unsigned int _uvBuffer;
	CTexture * _texture;
	GLuint _program;
	int _num_indices;

public:
	CompiledGeometry(Rocket::Core::Vertex* vertices, 
	int num_vertices, 
	int* indices, 
	int num_indices, 
	Rocket::Core::TextureHandle texture,
	GLuint program);

	~CompiledGeometry();

	void render(const Rocket::Core::Vector2f& translation, int w_width, int w_height);
};

#endif // _COMPILED_GEOMETRY_H_
