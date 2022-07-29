#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#pragma once
#include "Layer.h"

namespace Automata {
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer(const std::string& name);
        ~ImGuiLayer();

        void OnAttatch() override;
        void OnDetatch() override;
        void OnUpdate() override;

        virtual void OnImguiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0f;

		bool show_demo_window = true;
		bool show_another_window = false;
    };
}

#endif