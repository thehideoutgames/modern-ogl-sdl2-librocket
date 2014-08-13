#include "RocketInterfaces.h"
#include "load_shader.h"
#include "CTexture.h"
#include "CompiledGeometry.h"
#include <iostream>

//System Interface (also see RocketDefaultKeymapping.cpp)
RocketSDL2SystemInterface::RocketSDL2SystemInterface()
{

}

float RocketSDL2SystemInterface::GetElapsedTime()
{
	return SDL_GetTicks() / 1000.f;
}

int RocketSDL2SystemInterface::TranslateMouseButton(Uint8 button)
{
    switch(button)
    {
        case SDL_BUTTON_LEFT:
            return 0;
        case SDL_BUTTON_RIGHT:
            return 1;
        case SDL_BUTTON_MIDDLE:
            return 2;
        default:
            return 3;
    }
}

int RocketSDL2SystemInterface::GetKeyModifiers()
{
    SDL_Keymod sdlMods = SDL_GetModState();

    int retval = 0;

    if(sdlMods & KMOD_CTRL)
        retval |= Rocket::Core::Input::KM_CTRL;

    if(sdlMods & KMOD_SHIFT)
        retval |= Rocket::Core::Input::KM_SHIFT;

    if(sdlMods & KMOD_ALT)
        retval |= Rocket::Core::Input::KM_ALT;

    return retval;
}

//Render Interface
RocketSDL2ModernOpenglRenderInterface::RocketSDL2ModernOpenglRenderInterface(SDL_Window * window)
{
	_program = LoadShaders("test.vert", "test.frag");
	_window = window;
}

RocketSDL2ModernOpenglRenderInterface::~RocketSDL2ModernOpenglRenderInterface()
{
}

void RocketSDL2ModernOpenglRenderInterface::RenderGeometry(
	Rocket::Core::Vertex* vertices, 
	int num_vertices, 
	int* indices, 
	int num_indices, 
	Rocket::Core::TextureHandle texture, 
	const Rocket::Core::Vector2f& translation)
{
	int w_width, w_height;
	SDL_GetWindowSize(_window, &w_width, &w_height);

	CompiledGeometry geometry(vertices, num_vertices, indices, num_indices, texture, _program);
	geometry.render(translation, w_width, w_height);
}


// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
Rocket::Core::CompiledGeometryHandle RocketSDL2ModernOpenglRenderInterface::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture)
{
	auto geometry = new CompiledGeometry (vertices, num_vertices, indices, num_indices, texture, _program);
	return (Rocket::Core::CompiledGeometryHandle)geometry;
}

// Called by Rocket when it wants to render application-compiled geometry.
void RocketSDL2ModernOpenglRenderInterface::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
{
	int w_width, w_height;
	SDL_GetWindowSize(_window, &w_width, &w_height);
	((CompiledGeometry*)geometry)->render(translation, w_width, w_height);
	return;
}

// Called by Rocket when it wants to release application-compiled geometry.
void RocketSDL2ModernOpenglRenderInterface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
	delete ((CompiledGeometry*)geometry);
	return;
}

// Called by Rocket when it wants to enable or disable scissoring to clip content.
void RocketSDL2ModernOpenglRenderInterface::EnableScissorRegion(bool enable)
{

	if (enable)	{
		//std::cout << "enabling scissor region" << std::endl;
		glEnable(GL_SCISSOR_TEST);
	}else{
		//std::cout << "disabling scissor region" << std::endl;
		glDisable(GL_SCISSOR_TEST);
	}
}

// Called by Rocket when it wants to change the scissor region.
void RocketSDL2ModernOpenglRenderInterface::SetScissorRegion(int x, int y, int width, int height)
{
	//std::cout << "setting scissor region pos:" << x << "," << y << " size:" << width << "," << height << std::endl;
	int w_width, w_height;
	SDL_GetWindowSize(_window, &w_width, &w_height);
	glScissor(x, w_height - (y + height), width, height);
}

// Called by Rocket when a texture is required by the library.
bool RocketSDL2ModernOpenglRenderInterface::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
	std::cout << "loading texture:" << source.CString() << std::endl;
	auto tex = new CTexture();
	tex->LoadTextureAlpha(source.CString());
	texture_handle = (Rocket::Core::TextureHandle)tex;
	texture_dimensions.x = tex->get_w();
	texture_dimensions.y = tex->get_h();
	return true;
}

// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
bool RocketSDL2ModernOpenglRenderInterface::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
	std::cout << "generating " << source_dimensions.x << "x" << source_dimensions.y << " texture:" << std::endl;
	auto tex = new CTexture();
	tex->CreateTexture((unsigned char*)source, source_dimensions.x, source_dimensions.y);
	texture_handle = (Rocket::Core::TextureHandle)tex;
	return true;
}

// Called by Rocket when a loaded texture is no longer required.
void RocketSDL2ModernOpenglRenderInterface::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
	delete ((CTexture*)texture_handle);
}