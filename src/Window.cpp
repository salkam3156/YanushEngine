#include "Window.h"

void Window::ClearScreen() {


}

void Window::InitWindow(const std::string& windowTitle) {
	_windowScreen = SDL_CreateWindow(windowTitle.c_str(),
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (_windowScreen == nullptr) {
		throw WindowException(SDL_GetError());
	}
}

Window::Window(const std::string& windowTitle) :
		_windowScreen(nullptr), _glContext(nullptr) {
	InitWindow(windowTitle);
	InitContext();
}

void Window::Update() {
	SDL_GL_SwapWindow(_windowScreen);
	ClearScreen();
}

Window::~Window() {
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_windowScreen);
}

void Window::InitContext() {
	//TODO: initialize glew here after context creation and handle accordingly , should it fail
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,0);

	_glContext = SDL_GL_CreateContext(_windowScreen);
	if (_glContext == nullptr) {
		throw WindowException(SDL_GetError());
	}
	try {
		if (SDL_GL_SetSwapInterval(1) < 0) {
			throw WindowException(SDL_GetError());
		}
	} catch (WindowException& exception) {
		std::cout << "SetSwapInterval [Enable V-Sync]: " << SDL_GetError()
				<< std::endl;
	}
}
