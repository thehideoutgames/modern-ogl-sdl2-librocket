#include "RocketInterfaces.h"
#include "load_shader.h"
#include "CTexture.h"

#include <iostream>

RocketSDL2SystemInterface::RocketSDL2SystemInterface()
{

}

float RocketSDL2SystemInterface::GetElapsedTime()
{
	return SDL_GetTicks() / 1000.f;
}

Rocket::Core::Input::KeyIdentifier RocketSDL2SystemInterface::TranslateKey(SDL_Keycode sdlkey)
{
    using namespace Rocket::Core::Input;


    switch(sdlkey) {
        case SDLK_UNKNOWN:
            return KI_UNKNOWN;
            break;
        case SDLK_SPACE:
            return KI_SPACE;
            break;
        case SDLK_0:
            return KI_0;
            break;
        case SDLK_1:
            return KI_1;
            break;
        case SDLK_2:
            return KI_2;
            break;
        case SDLK_3:
            return KI_3;
            break;
        case SDLK_4:
            return KI_4;
            break;
        case SDLK_5:
            return KI_5;
            break;
        case SDLK_6:
            return KI_6;
            break;
        case SDLK_7:
            return KI_7;
            break;
        case SDLK_8:
            return KI_8;
            break;
        case SDLK_9:
            return KI_9;
            break;
        case SDLK_a:
            return KI_A;
            break;
        case SDLK_b:
            return KI_B;
            break;
        case SDLK_c:
            return KI_C;
            break;
        case SDLK_d:
            return KI_D;
            break;
        case SDLK_e:
            return KI_E;
            break;
        case SDLK_f:
            return KI_F;
            break;
        case SDLK_g:
            return KI_G;
            break;
        case SDLK_h:
            return KI_H;
            break;
        case SDLK_i:
            return KI_I;
            break;
        case SDLK_j:
            return KI_J;
            break;
        case SDLK_k:
            return KI_K;
            break;
        case SDLK_l:
            return KI_L;
            break;
        case SDLK_m:
            return KI_M;
            break;
        case SDLK_n:
            return KI_N;
            break;
        case SDLK_o:
            return KI_O;
            break;
        case SDLK_p:
            return KI_P;
            break;
        case SDLK_q:
            return KI_Q;
            break;
        case SDLK_r:
            return KI_R;
            break;
        case SDLK_s:
            return KI_S;
            break;
        case SDLK_t:
            return KI_T;
            break;
        case SDLK_u:
            return KI_U;
            break;
        case SDLK_v:
            return KI_V;
            break;
        case SDLK_w:
            return KI_W;
            break;
        case SDLK_x:
            return KI_X;
            break;
        case SDLK_y:
            return KI_Y;
            break;
        case SDLK_z:
            return KI_Z;
            break;
        case SDLK_SEMICOLON:
            return KI_OEM_1;
            break;
        case SDLK_PLUS:
            return KI_OEM_PLUS;
            break;
        case SDLK_COMMA:
            return KI_OEM_COMMA;
            break;
        case SDLK_MINUS:
            return KI_OEM_MINUS;
            break;
        case SDLK_PERIOD:
            return KI_OEM_PERIOD;
            break;
        case SDLK_SLASH:
            return KI_OEM_2;
            break;
        case SDLK_BACKQUOTE:
            return KI_OEM_3;
            break;
        case SDLK_LEFTBRACKET:
            return KI_OEM_4;
            break;
        case SDLK_BACKSLASH:
            return KI_OEM_5;
            break;
        case SDLK_RIGHTBRACKET:
            return KI_OEM_6;
            break;
        case SDLK_QUOTEDBL:
            return KI_OEM_7;
            break;
        case SDLK_KP_0:
            return KI_NUMPAD0;
            break;
        case SDLK_KP_1:
            return KI_NUMPAD1;
            break;
        case SDLK_KP_2:
            return KI_NUMPAD2;
            break;
        case SDLK_KP_3:
            return KI_NUMPAD3;
            break;
        case SDLK_KP_4:
            return KI_NUMPAD4;
            break;
        case SDLK_KP_5:
            return KI_NUMPAD5;
            break;
        case SDLK_KP_6:
            return KI_NUMPAD6;
            break;
        case SDLK_KP_7:
            return KI_NUMPAD7;
            break;
        case SDLK_KP_8:
            return KI_NUMPAD8;
            break;
        case SDLK_KP_9:
            return KI_NUMPAD9;
            break;
        case SDLK_KP_ENTER:
            return KI_NUMPADENTER;
            break;
        case SDLK_KP_MULTIPLY:
            return KI_MULTIPLY;
            break;
        case SDLK_KP_PLUS:
            return KI_ADD;
            break;
        case SDLK_KP_MINUS:
            return KI_SUBTRACT;
            break;
        case SDLK_KP_PERIOD:
            return KI_DECIMAL;
            break;
        case SDLK_KP_DIVIDE:
            return KI_DIVIDE;
            break;
        case SDLK_KP_EQUALS:
            return KI_OEM_NEC_EQUAL;
            break;
        case SDLK_BACKSPACE:
            return KI_BACK;
            break;
        case SDLK_TAB:
            return KI_TAB;
            break;
        case SDLK_CLEAR:
            return KI_CLEAR;
            break;
        case SDLK_RETURN:
            return KI_RETURN;
            break;
        case SDLK_PAUSE:
            return KI_PAUSE;
            break;
        case SDLK_CAPSLOCK:
            return KI_CAPITAL;
            break;
        case SDLK_PAGEUP:
            return KI_PRIOR;
            break;
        case SDLK_PAGEDOWN:
            return KI_NEXT;
            break;
        case SDLK_END:
            return KI_END;
            break;
        case SDLK_HOME:
            return KI_HOME;
            break;
        case SDLK_LEFT:
            return KI_LEFT;
            break;
        case SDLK_UP:
            return KI_UP;
            break;
        case SDLK_RIGHT:
            return KI_RIGHT;
            break;
        case SDLK_DOWN:
            return KI_DOWN;
            break;
        case SDLK_INSERT:
            return KI_INSERT;
            break;
        case SDLK_DELETE:
            return KI_DELETE;
            break;
        case SDLK_HELP:
            return KI_HELP;
            break;
        case SDLK_F1:
            return KI_F1;
            break;
        case SDLK_F2:
            return KI_F2;
            break;
        case SDLK_F3:
            return KI_F3;
            break;
        case SDLK_F4:
            return KI_F4;
            break;
        case SDLK_F5:
            return KI_F5;
            break;
        case SDLK_F6:
            return KI_F6;
            break;
        case SDLK_F7:
            return KI_F7;
            break;
        case SDLK_F8:
            return KI_F8;
            break;
        case SDLK_F9:
            return KI_F9;
            break;
        case SDLK_F10:
            return KI_F10;
            break;
        case SDLK_F11:
            return KI_F11;
            break;
        case SDLK_F12:
            return KI_F12;
            break;
        case SDLK_F13:
            return KI_F13;
            break;
        case SDLK_F14:
            return KI_F14;
            break;
        case SDLK_F15:
            return KI_F15;
            break;
        case SDLK_NUMLOCKCLEAR:
            return KI_NUMLOCK;
            break;
        case SDLK_SCROLLLOCK:
            return KI_SCROLL;
            break;
        case SDLK_LSHIFT:
            return KI_LSHIFT;
            break;
        case SDLK_RSHIFT:
            return KI_RSHIFT;
            break;
        case SDLK_LCTRL:
            return KI_LCONTROL;
            break;
        case SDLK_RCTRL:
            return KI_RCONTROL;
            break;
        case SDLK_LALT:
            return KI_LMENU;
            break;
        case SDLK_RALT:
            return KI_RMENU;
            break;
        case SDLK_LGUI:
            return KI_LMETA;
            break;
        case SDLK_RGUI:
            return KI_RMETA;
            break;
        /*case SDLK_LSUPER:
            return KI_LWIN;
            break;
        case SDLK_RSUPER:
            return KI_RWIN;
            break;*/
        default:
            return KI_UNKNOWN;
            break;
    }
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




RocketSDL2ModernOpenglRenderInterface::RocketSDL2ModernOpenglRenderInterface(SDL_Window * window)
{
	//_program = LoadShaders("ui.vert", "ui.frag");
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
	glEnable(GL_BLEND);

	auto c_texture = (CTexture*)texture;
	std::vector<unsigned int> indexData;
	for (unsigned int i = 0; i < num_indices; i++)
	{
		indexData.push_back(indices[i]);
	}
	
	glDisable(GL_CULL_FACE);

	unsigned int elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int), &indexData[0], GL_STATIC_DRAW);


	std::vector<float> vertexData;

	for (unsigned int i = 0; i < num_vertices; i++)
	{
		vertexData.push_back(vertices[i].position.x);
		vertexData.push_back(vertices[i].position.y);
		vertexData.push_back(0);
	}

	std::vector<float> uvData;

	for (unsigned int i = 0; i < num_vertices; i++)
	{
		uvData.push_back(vertices[i].tex_coord.x);
		uvData.push_back(vertices[i].tex_coord.y);
	}

	unsigned int vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), &vertexData[0], GL_STATIC_DRAW);

	unsigned int uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvData.size() * sizeof(float), &uvData[0], GL_STATIC_DRAW);

	glUseProgram(_program);

	GLuint matrix_uniform = glGetUniformLocation(_program, "MVP");

	int w_width, w_height;
	SDL_GetWindowSize(_window, &w_width, &w_height);

	glm::mat4 MVP = glm::mat4(1.0f);
	MVP = glm::translate(MVP, glm::vec3(-1, 1, 0));
	//MVP = glm::translate(MVP, glm::vec3(-1 + translation.x/w_width, 1+translation.y/w_height, 0));
	MVP = glm::scale(MVP, glm::vec3(1.0f / (w_width/2), -1.0f / (w_height/2), 0.0f));
	MVP = glm::translate(MVP, glm::vec3(translation.x, translation.y,0));
	
	glUniformMatrix4fv(matrix_uniform, 1, GL_FALSE, &MVP[0][0]);

	GLuint texture_uniform = glGetUniformLocation(_program, "texSampler");

	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, (GLuint) ((CTexture*)texture)->BindTexture());
	c_texture->BindTexture();
    glUniform1i(texture_uniform, 0);


	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

	glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(
            1,                  // attribute
            2,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );


	//glDrawArrays(GL_TRIANGLES, 0, 3);
    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
    glDrawElements(
            GL_TRIANGLES,      // mode
            num_indices,    // count
            GL_UNSIGNED_INT,   // type
            (void*)0           // element array buffer offset
    );

	glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &elementbuffer);
    
	glDisable(GL_BLEND);
}


// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
Rocket::Core::CompiledGeometryHandle RocketSDL2ModernOpenglRenderInterface::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture)
{
	return NULL;
}

// Called by Rocket when it wants to render application-compiled geometry.
void RocketSDL2ModernOpenglRenderInterface::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
{
	return;
}

// Called by Rocket when it wants to release application-compiled geometry.
void RocketSDL2ModernOpenglRenderInterface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
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