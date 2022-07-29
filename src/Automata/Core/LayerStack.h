#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#pragma once
#include "Layer.h"

namespace Automata{
    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

        inline std::vector<Layer*>::iterator begin() {return m_Layers.begin();}
        inline std::vector<Layer*>::iterator end() {return m_Layers.end();}
    private:
        std::vector<Layer*> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };
}

#endif