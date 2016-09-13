/* 
 * File:   Window.h
 * Author: ANTOINE
 *
 * Created on 15 février 2016, 13:15
 */
#pragma once

#ifndef WINDOW_H
#define	WINDOW_H

#ifndef TYPES_H
#include "Types.h"
#endif

// Classe

class Window {
public:
    Window(std::string title, int width, int height);
    Window();
    ~Window();

    bool initWindow(int flags);

    // getter
    int getWidth() const;
    int getHeight() const;
    float getRatio() const;
    SDL_Window* getWindow() const;
    SDL_GLContext getContext() const;

    // setter
    void setWindowTitle(std::string title);
    void setResolution(int width, int height);

private:
    std::string m_title;

    int m_width;
    int m_height;

    SDL_Window* m_window;
    SDL_GLContext m_context;
};

#endif	/* WINDOW_H */

