#include "Window.h"

Window::Window(std::string title, int width, int height){
    m_title=title;
    m_width=width;
    m_height=height;
}
Window::Window(){
    m_title="Default Window";
    m_width=800;
    m_height=600;
}
Window::~Window(){
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
bool Window::initWindow(int flags) {
    // Initialisation de la SDL
    if(SDL_Init(flags) < 0) {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
		
        return false;
    }
	
    // Version d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // core
	
    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	
    // Création de la fenêtre
    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_window == 0) {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Création du contexte OpenGL
    m_context = SDL_GL_CreateContext(m_window);

    if(m_context == 0) {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}
int Window::getWidth() const {
    return m_width;
}
int Window::getHeight() const {
    return m_height;
}
float Window::getRatio() const {
    return (float)m_width/(float)m_height;
}
SDL_Window* Window::getWindow() const {
    return m_window;
}
SDL_GLContext Window::getContext() const {
    return m_context;
}
// setter
void Window::setWindowTitle(std::string title) {
    m_title=title;
    SDL_SetWindowTitle(m_window,m_title.c_str());
}
void Window::setResolution(int width,int height) {
    m_width=width;
    m_height=height;
    SDL_SetWindowSize(m_window, m_width, m_height);
}