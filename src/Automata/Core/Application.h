#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Core.h"
#include "CellMatrix.h"

namespace Automata {
    class Application
    {
    public:
        Application();
        virtual ~Application();

        enum class APPLICATION_STATE {
            PAUSED,
            RUNNING,
            STOPPED
        };

        static inline Application& GetInstance()  {return *s_Instance;}

        inline GLFWwindow& NativeWindow() { return *m_Window; }
        inline float GetWidth() {return 55;}
        inline float GetHeight() {return 55;}
    public:
        void Run();
        void ShutDown();

        inline float FPS() {return fps;}
        inline float dt() {return deltaTime;}
    public:
        inline CellMatrix* GetCellMatrix() {return &m_CellMatrix;}
    private:
        LayerStack m_LayerStack;
        CellMatrix m_CellMatrix;

        static Application* s_Instance;
    private:
        GLFWwindow* m_Window;
        bool m_Running = true;
        APPLICATION_STATE m_state = APPLICATION_STATE::PAUSED;
        
        float RESOLUTION_X = 852;
        float RESOLUTION_Y = 480;

        static float t;
        static float lastTime;
        static float deltaTime;
        static float totalTime;
        static float fps;

        void CreateWindow();
        void InitSystems();
        void ProcessTime();

    private:

        ImGuiLayer* m_ImGuiLayer;
        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);
    public:
        // input state
        void ProcessInput();
        static bool Keys[1024];
        static Vector2 MousePos;
        static bool MouseButtons[7];
    };
}
#endif
