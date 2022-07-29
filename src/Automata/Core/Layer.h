#ifndef LAYER_H
#define LAYER_H

#pragma once

namespace Automata{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        ~Layer();

        virtual void OnAttatch() = 0;
        virtual void OnDetatch() = 0;
        virtual void OnUpdate() = 0;

        virtual void OnImguiRender(){};

        inline const std::string& GetName() const {return m_Name;}
    protected:
        std::string m_Name;
    };
}

#endif