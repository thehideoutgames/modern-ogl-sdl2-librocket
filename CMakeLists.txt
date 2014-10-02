project(librocket-sdl2-sandbox)
cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig)

find_package(OpenGL REQUIRED)
list(APPEND LIBRARIES ${OPENGL_LIBRARIES})
include_directories(SYSTEM ${OPENGL_INCLUDE_DIR})

pkg_check_modules(GLEW glew)
list(APPEND LIBRARIES ${GLEW_LIBRARIES})
include_directories(SYSTEM ${GLEW_INCLUDE_DIRS})

pkg_check_modules(SDL2 sdl2)
list(APPEND LIBRARIES ${SDL2_LIBRARIES})
include_directories(SYSTEM ${SDL2_INCLUDE_DIRS})

find_package(SDL_image)
list(APPEND LIBRARIES ${SDLIMAGE_LIBRARY})
include_directories(SYSTEM ${SDLIMAGE_INCLUDE_DIR})

pkg_check_modules(FREETYPE REQUIRED freetype2)
list(APPEND LIBRARIES ${FREETYPE_LIBRARIES})
include_directories(SYSTEM ${FREETYPE_INCLUDE_DIRS})

#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wno-c++11-extensions")

set(SOURCES
	sdlsandbox/CTexture.cpp                
	sdlsandbox/FileWatcher.cpp             
	sdlsandbox/FileWatcherLinux.h          
	sdlsandbox/FileWatcherWin32.h          
	sdlsandbox/load_shader.cpp          
	sdlsandbox/CTexture.h
	sdlsandbox/FileWatcher.h               
	sdlsandbox/FileWatcherOSX.cpp          
	sdlsandbox/RocketDefaultKeymapping.cpp 
	sdlsandbox/load_shader.h               
	sdlsandbox/CompiledGeometry.cpp        
	sdlsandbox/FileWatcherImpl.h           
	sdlsandbox/FileWatcherOSX.h            
	sdlsandbox/RocketInterfaces.cpp        
	sdlsandbox/main.cpp
	sdlsandbox/CompiledGeometry.h          
	sdlsandbox/FileWatcherLinux.cpp        
	sdlsandbox/FileWatcherWin32.cpp        
	sdlsandbox/RocketInterfaces.h          	
	sdlsandbox/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
