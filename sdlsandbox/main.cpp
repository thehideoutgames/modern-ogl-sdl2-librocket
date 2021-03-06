#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

#include <Rocket/Core.h>


#include "load_shader.h"
#include "RocketInterfaces.h"

#include "FileWatcherImpl.h"

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

class UpdateListener : public FW::FileWatchListener
{
private:
	std::list<std::string> _changed_files;
public:
    UpdateListener() {}
    void handleFileAction(FW::WatchID watchid, const std::string& dir, const std::string& filename,
                FW::Action action)
    {
        switch(action)
        {
        case FW::Actions::Add:
			std::cout << "File (" << dir + PATH_SEPARATOR + filename << ") Added! " <<  std::endl;
			break;
        case FW::Actions::Delete:
			std::cout << "File (" << dir + PATH_SEPARATOR + filename << ") Deleted! " << std::endl;
			break;
        case FW::Actions::Modified:
			std::cout << "File (" << dir + PATH_SEPARATOR + filename << ") Modified! " << std::endl;
			_changed_files.push_back(dir + PATH_SEPARATOR + filename);
			break;
        default:
            std::cout << "Should never happen!" << std::endl;
		}
    }

	bool has_changes()
	{
		return _changed_files.size() > 0;
	}

	std::list<std::string> changed_files()
	{
		std::list<std::string> changes = std::list<std::string>(_changed_files);
		_changed_files.clear();
		return changes;
	}
};

class RocketListener : public Rocket::Core::EventListener
{
public:

	virtual void ProcessEvent(Rocket::Core::Event& event)
	{
		std::cout << "type " << event.GetType().CString() << " element name " << event.GetTargetElement()->GetId().CString() << std::endl;
	}

};


int main(int argc, char *argv[])
{
	const int GAME_XRES = 1280;
	const int GAME_YRES = 720;

	std::cout << "Initializing SDL" << std::endl;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL init failed" << std::endl;
		return -1;
	}

	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	SDL_InitSubSystem(SDL_INIT_AUDIO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	auto window = SDL_CreateWindow("test window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_XRES, GAME_YRES, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); //SDL_WINDOW_FULLSCREEN_DESKTOP // SDL_WINDOW_OPENGL

	if (!window)
	{
		std::cout << "Create window failed" << std::endl;
		return -1;
	}

	auto glContext = SDL_GL_CreateContext(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew init failed" << std::endl;
		return -1;
	}

	glDisable(GL_CULL_FACE);

	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	RocketSDL2SystemInterface system_interface;
	Rocket::Core::SetSystemInterface(&system_interface);
	
	RocketSDL2ModernOpenglRenderInterface render_interface(window);
	Rocket::Core::SetRenderInterface(&render_interface);
	
	Rocket::Core::Initialise();
	
	Rocket::Core::FontDatabase::LoadFontFace("./assets/Delicious-Bold.otf");
	Rocket::Core::FontDatabase::LoadFontFace("./assets/Delicious-BoldItalic.otf");
	Rocket::Core::FontDatabase::LoadFontFace("./assets/Delicious-Italic.otf");
	Rocket::Core::FontDatabase::LoadFontFace("./assets/Delicious-Roman.otf");

	//Rocket::Core::FontDatabase::LoadFontFace("./assets/SourceCodePro-Black.ttf");
	Rocket::Core::FontDatabase::LoadFontFace("./assets/SourceCodePro-Bold.ttf"); //, "SourceCodePro", Rocket::Core::Font::Style::STYLE_NORMAL, Rocket::Core::Font::Weight::WEIGHT_BOLD);
	Rocket::Core::FontDatabase::LoadFontFace("./assets/SourceCodePro-Regular.ttf"); //, "SourceCodePro", Rocket::Core::Font::Style::STYLE_NORMAL, Rocket::Core::Font::Weight::WEIGHT_NORMAL);

	Rocket::Core::Context* context = Rocket::Core::CreateContext("default", Rocket::Core::Vector2i(GAME_XRES, GAME_YRES));

	Rocket::Core::ElementDocument* document = context->LoadDocument("./assets/demo.rml");

	if(document)
	{
		document->Show();
		document->RemoveReference();
		std::cout << "Document loaded" << std::endl;
	}
	else
	{
		std::cerr << "Document is NULL" << std::endl;
		return -1;
	}

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;	
	glGenBuffers(1, &vertexbuffer);	
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	SDL_GL_SetSwapInterval(1);

	if (SDL_NumJoysticks > 0)
	{
		auto joy = SDL_JoystickOpen(0);
		if (joy) std::cout << "Gamepad Detected" << std::endl;	
	}

	GLuint programID = LoadShaders( "test.vert", "test.frag" );

	// Create the object
    FW::FileWatcher* fileWatcher = new FW::FileWatcher();

	auto listener = new UpdateListener();

    // add a directory watch
	FW::WatchID watchid = fileWatcher->addWatch("assets", listener);

	RocketListener rocket_listener;
	//document->
	auto the_button = document->GetElementById("the_button");
	if(the_button != NULL)
	{
		std::cout << "found the button, registering for events" << std::endl;
		the_button->AddEventListener("click", &rocket_listener);
	}
	else
	{
		std::cout << "did not find the button!" << std::endl;
	}


	bool quit = false;
	while(!quit)
	{
		fileWatcher->update();

		if(listener->has_changes())
		{
			auto changes = listener->changed_files();

			for(auto it = changes.begin(); it != changes.end(); it++)
			{
				if( (*it).find(".rml") != std::string::npos || (*it).find(".rcss") != std::string::npos)
				{
					std::cout << "Reloading" << std::endl;
					Rocket::Core::Factory::ClearStyleSheetCache();
					Rocket::Core::Factory::ClearTemplateCache();
					document->Hide();
					document->Close();
					document = context->LoadDocument("./assets/demo.rml");	
					if (document != NULL)
					{
						document->Show();
						document->RemoveReference();
					}
				}
			}
		}
		
		SDL_Event evt;
		while(SDL_PollEvent(&evt))
		{
			if(evt.type == SDL_KEYUP) std::cout << evt.key.keysym.sym << std::endl;
			if(evt.type == SDL_KEYUP && evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				std::cout << "exiting" << std::endl;
				quit = true;
			}

			switch(evt.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_MOUSEMOTION:
                    context->ProcessMouseMove(evt.motion.x, evt.motion.y, system_interface.GetKeyModifiers());
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    context->ProcessMouseButtonDown(system_interface.TranslateMouseButton(evt.button.button), system_interface.GetKeyModifiers());
                    break;

                case SDL_MOUSEBUTTONUP:
                    context->ProcessMouseButtonUp(system_interface.TranslateMouseButton(evt.button.button), system_interface.GetKeyModifiers());
                    break;

                case SDL_MOUSEWHEEL:
                    context->ProcessMouseWheel(-evt.wheel.y, system_interface.GetKeyModifiers());
                    break;

                case SDL_KEYDOWN:
                    context->ProcessKeyDown(system_interface.TranslateKey(evt.key.keysym.sym), system_interface.GetKeyModifiers());
                    break;
                default:
                    break;
            }

		}


		context->Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		context->Render();
		
		SDL_GL_SwapWindow(window);
		SDL_Delay(16);
	}

	context->RemoveReference();
	Rocket::Core::Shutdown();

	SDL_DestroyWindow(window);

	SDL_Quit();

}
