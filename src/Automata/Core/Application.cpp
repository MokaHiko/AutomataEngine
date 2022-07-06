#include "Application.h"

namespace Automata
{
	float Application::t;
	float Application::lastTime;
	float Application::deltaTime;
	float Application::totalTime;
	float Application::fps;

    Shader* automataShader; // Main Program Shader

	// inputs
	bool Application::Keys[1024];
	Vector2 Application::MousePos;
	bool Application::MouseButtons[7];

	// GLFW callbacks
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

	Application::Application() {}
	void Application::Init()
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
		
		// init systems
		t = glfwGetTime();
		lastTime = t;
		deltaTime = 0;

		// Init Renderer
		automataShader = new Shader("resources/shaders/automata_instanced_vertex.shader", "resources/shaders/automata_instanced_fragment.shader");
		m_Renderer = new SpriteRenderer(*automataShader, Vector2(RESOLUTION_X, RESOLUTION_Y));

		// Init Cell Matrix
		m_CellMatrix.InitMatrix(Vector2{RESOLUTION_X, RESOLUTION_Y});
	}
	void Application::ProcessInput()
	{
		if(MouseButtons[GLFW_MOUSE_BUTTON_LEFT])
			m_CellMatrix.AddElement<Sand>(MousePos);
	}
	void Application::Run()
	{
		while(m_Running)
		{
			glClearColor(0.1, 0.1, 0.1, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			ProcessTime();
			ProcessInput();
		
			m_CellMatrix.Update(deltaTime);
			m_CellMatrix.DrawElements(m_Renderer);

			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
	}

	Application::~Application() 
	{
		delete m_Renderer;
		delete automataShader;
	}
	void Application::ShutDown()
	{
		glfwTerminate();
	}
	void Application::ProcessTime()
	{
		t = glfwGetTime();
		deltaTime = t - lastTime;
		lastTime = t;
		fps = 1.0f / deltaTime;

		totalTime += deltaTime;
		if(totalTime >= 0.25f)
		{
			std::string fpsDescriptor = "FPS: " + std::to_string(fps) + " at" + std::to_string(m_CellMatrix.m_nElements());
			glfwSetWindowTitle(m_Window, fpsDescriptor.c_str());
			if (fps < 40.0f)
				std::cout << "Performance Drop: " << fps << std::endl;

			totalTime = 0;
		}
	}
}