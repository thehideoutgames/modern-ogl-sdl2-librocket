#ifndef _ROCKET_INTERFACES_H_
#define _ROCKET_INTERFACES_H_

#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/RenderInterface.h>
#include <Rocket/Core/Platform.h>
#include <Rocket/Core.h>
#include <Rocket/Controls.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <SDL2/SDL.h>

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

class RocketSDL2SystemInterface : public Rocket::Core::SystemInterface
{
public:
	RocketSDL2SystemInterface();

	Rocket::Core::Input::KeyIdentifier TranslateKey(SDL_Keycode sdlkey);
    int TranslateMouseButton(Uint8 button);
	int GetKeyModifiers();

	// Get the number of seconds elapsed since the start of the application.
	virtual float GetElapsedTime();

	//not required:
	// Translate the input string into the translated string.
	//virtual int TranslateString(Rocket::Core::String& translated, const Rocket::Core::String& input);

	// Log the specified message.
	//virtual bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);
};

class RocketSDL2ModernOpenglRenderInterface : public Rocket::Core::RenderInterface
{
private:
	GLuint _program;
	SDL_Window * _window;

public:
	RocketSDL2ModernOpenglRenderInterface(SDL_Window * window);
	virtual ~RocketSDL2ModernOpenglRenderInterface();

	// Called by Rocket when it wants to render geometry that the application does not wish to optimise.
	virtual void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);

	// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
	virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);

	// Called by Rocket when it wants to render application-compiled geometry.
	virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);

	// Called by Rocket when it wants to release application-compiled geometry.
	virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);

	// Called by Rocket when it wants to enable or disable scissoring to clip content.
	virtual void EnableScissorRegion(bool enable);

	// Called by Rocket when it wants to change the scissor region.
	virtual void SetScissorRegion(int x, int y, int width, int height);

	// Called by Rocket when a texture is required by the library.
	virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);

	// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
	virtual bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);

	// Called by Rocket when a loaded texture is no longer required.
	virtual void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);
};

#endif _ROCKET_INTERFACES_H_