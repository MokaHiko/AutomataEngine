#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include "Core.h"
#include "CellMatrix.h"

// Available ELelmentsa
#include "Elements/Solids/Sand.h"
#include "Elements/Liquids/Water.h"

namespace Automata
{
    class Application
    {
    public:
        static Application& GetInstance()
        {
            static Application app;
            return app;
        }

        Application(Application&) = delete;
    public:
        void Init();
        void Run();
        void ShutDown();

    private:
        CellMatrix m_CellMatrix;

    private:
        GLFWwindow* m_Window;
        bool m_Running = true;
        
        float RESOLUTION_X = 852;
        float RESOLUTION_Y = 480;

        static float t;
        static float lastTime;
        static float deltaTime;
        static float totalTime;
        static float fps;

    private:
        ~Application();
        Application();
        

        // helper functions
        void ProcessTime();

    public:

        // input state
        void ProcessInput();
        static bool Keys[1024];
        static Vector2 MousePos;
        static bool MouseButtons[7];
    };

    static Application& Core = Application::GetInstance();

}
#endif
