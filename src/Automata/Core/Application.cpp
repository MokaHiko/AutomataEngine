#include "Application.h"

// Available ELelmentsa
#include "Elements/Solids/Sand.h"
#include "Elements/Liquids/Water.h"
#include "Elements/Gases/Smoke.h"

namespace Automata
{
	Application* Application::s_Instance = nullptr;

	// time
	float Application::t;
	float Application::lastTime;
	float Application::deltaTime;
	float Application::totalTime;
	float Application::fps;

	// inputs
	bool Application::Keys[1024];
	Vector2 Application::MousePos;
	bool Application::MouseButtons[7];

	// Temporary Event Handler
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
    void close_callback(GLFWwindow* window)
    {
        std::cout << window << std::endl;
    }
    void mouse_callback(GLFWwindow* window, double xPos, double yPos)
    {
		Application::MousePos = glm::vec2(xPos, yPos);
    }
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button >= 0 && button <= 7)
		{
			if (action == GLFW_PRESS)
			{
				Application::MouseButtons[button] = true;
			}
			else if (action == GLFW_RELEASE)
			{
				Application::MouseButtons[button] = false;
			}
		}
	}
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		if (key >= 0 && key < 1024)
		{
			if (action == GLFW_PRESS)
				Application::Keys[key] = true;
			else if (action == GLFW_RELEASE)
				Application::Keys[key] = false;
		}
	}
	
	Application::Application() 
	{
		s_Instance = this;
		CreateWindow();
		InitSystems();
	}
	
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttatch();
	}
	
	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
		layer->OnDetatch();
	}
	void Application::ProcessInput()
	{
		// --- Input Events ---
		// Mouse Inputs
		if(MouseButtons[GLFW_MOUSE_BUTTON_LEFT])
			m_CellMatrix.AddElement<Sand>(MousePos);
		else if(MouseButtons[GLFW_MOUSE_BUTTON_RIGHT])
			m_CellMatrix.AddElement<Water>(MousePos);
		else if(MouseButtons[GLFW_MOUSE_BUTTON_3])
			m_CellMatrix.AddElement<Smoke>(MousePos);

		if (Keys[GLFW_KEY_LEFT_SHIFT])
		{
		 if(MouseButtons[GLFW_MOUSE_BUTTON_LEFT])
		 	m_CellMatrix.AddElementSquare<Sand>(MousePos, 3);
		 else if(MouseButtons[GLFW_MOUSE_BUTTON_RIGHT])
		 	m_CellMatrix.AddElementSquare<Water>(MousePos, 3);
		 else if(MouseButtons[GLFW_MOUSE_BUTTON_3])
		 	m_CellMatrix.AddElementSquare<Smoke>(MousePos, 3);
		}

		if(Keys[GLFW_KEY_LEFT_CONTROL])
		{
		 if(MouseButtons[GLFW_MOUSE_BUTTON_LEFT])
		 	m_CellMatrix.RemoveElementSquare(MousePos, 3);
		}
			
		// KeyBoard Inputs
		if(Keys[GLFW_KEY_SPACE] && m_state == APPLICATION_STATE::RUNNING)
			m_state = APPLICATION_STATE::PAUSED;
		else if(Keys[GLFW_KEY_SPACE] && m_state == APPLICATION_STATE::PAUSED)
			m_state = APPLICATION_STATE::RUNNING;
	}
	void Application::Run()
	{
		while(m_Running)
		{
			glClearColor(0.1, 0.1, 0.1, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			ProcessTime();
			ProcessInput();

			for(Layer* layer : m_LayerStack)
				layer->OnUpdate();
		
			if(m_state == APPLICATION_STATE::RUNNING)
				m_CellMatrix.Update(deltaTime);

			m_CellMatrix.DrawElements();

			m_ImGuiLayer->Begin();
			for(Layer* layer : m_LayerStack)
				layer->OnImguiRender();
			m_ImGuiLayer->End();

			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}
		m_state = APPLICATION_STATE::STOPPED;
	}

	Application::~Application() { }
	
	void Application::ShutDown()
	{
		std::cout << "AUTOMATA ENGINE SHUT DOWN..." << std::endl; 
		glfwTerminate();
	}
	
	void Application::CreateWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(RESOLUTION_X, RESOLUTION_Y, "Automata Engine", NULL, NULL);

		if (m_Window == NULL)
		{
			std::runtime_error("Failed to create glfw window");
			glfwTerminate();
		}
		
		glfwMakeContextCurrent(m_Window);

		// init glad after making window current context
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::runtime_error("Failed to load glad");
		}
		glViewport(0, 0, RESOLUTION_X, RESOLUTION_Y); // where openGL draws in the window
		glfwSwapInterval(0);
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		// set callbacks
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		glfwSetWindowCloseCallback(m_Window, close_callback);
		glfwSetCursorPosCallback(m_Window, mouse_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetKeyCallback(m_Window, key_callback);
	}
	
	void Application::InitSystems()
	{
		// time
		t = glfwGetTime();
		lastTime = t;
		deltaTime = 0;

		//  ImGui Ui
		m_ImGuiLayer = new ImGuiLayer("Engine UI");
		PushLayer(m_ImGuiLayer);

		// cell matrix
		m_CellMatrix.InitMatrix(Vector2{RESOLUTION_X, RESOLUTION_Y});
		m_state = APPLICATION_STATE::RUNNING;
	}

	void Application::ProcessTime()
	{
		t = glfwGetTime();
		deltaTime = t - lastTime;
		lastTime = t;
		fps = 1.0f / deltaTime;

		totalTime += deltaTime;
		// if(totalTime >= 0.25f)
		// {
		// 	std::string fpsDescriptor = "FrameTime: " + std::to_string(deltaTime * 1000) + "ms" + " , FPS: " + std::to_string(fps) + "fps at (" + std::to_string(m_CellMatrix.m_nElements()) + ") particles.";
		// 	glfwSetWindowTitle(m_Window, fpsDescriptor.c_str());
		// 	if (fps < 40.0f)
		// 		std::cout << "Performance Drop: " << fps << std::endl;

		// 	totalTime = 0;
		// }
	}
}