#include "Instance.h"

Instance::Instance() :
		_running(true), _window(nullptr), _gameState(nullptr) {
	try {
			_window = new Window(std::string("Core.App"));
		}
	catch (InstanceException& exception) {
		std::cout << "Application error: " << exception.what() << std::endl;
	}
	catch (WindowException& exception) {
		std::cout << "Application error: " << exception.what() << std::endl;
	}

}

Instance* Instance::_applicationInstance = nullptr;

template<typename T>
void Instance::SetState() {
	if (_gameState != nullptr) {
		_gameState->Destroy();
	}
	_gameState = new T();
	_gameState->Init();
}

Instance* Instance::GetInstance() {
	if (_applicationInstance == nullptr) {
		_applicationInstance = new Instance();
	}

	return _applicationInstance;
}

void Instance::UpdateWindow()
{
	_window->Update();
}

void Instance::Update() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			Stop();
			break;
		case SDL_KEYDOWN:
			if (_gameState != nullptr) {
				//_gameState->Update(event.key.keysym.sym);
			}
			break;
		default:
			break;
		}
	}

	_window->Update();
}

bool Instance::Running() const {
	return _running;
}

void Instance::Stop() {
	_running = false;
}

Instance::~Instance() {
	SDL_Quit();
}
