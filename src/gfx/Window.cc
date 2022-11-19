#include "Window.h"
#include <iostream>
#include <utils/cmath.h>


GLFWwindow * Window::m_window = nullptr;
uint32_t Window::m_width = 800, Window::m_height = 600;
double Window::m_delta_time = 0, Window::m_last_time = 0;
bool Window::m_window_resized = true;
Keyboard Window::keyboard;
Mouse Window::mouse;  // TODO: Move from here

Window::Window() {}
Window::~Window() {
	glfwTerminate();
}
	

Window & Window::getInstance() {
    static Window new_window;
    return new_window;
}

void Window::create(const char * name, uint32_t width, uint32_t height) {
    glfwInit();
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed

	Window::m_width = width;
	Window::m_height = height;
    m_window = glfwCreateWindow(width, height, name, NULL, NULL);

	ASSERT_CB(m_window, glfwTerminate(), "WINDOW::Failed to create GLFW window");
    
	glfwMakeContextCurrent(m_window);

	ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "WINDOW::Failed to initialize GLAD");

    glViewport(0, 0, width, height);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(m_window, _handle_resize);
	glfwSetKeyCallback(m_window, _handle_key);
	glfwSetCursorPosCallback(m_window, _handle_mouse_pos);

}

void Window::loop(void (*init)(void), void (*render)(void), void (*destroy)(void)) {
	ASSERT(init && render && destroy, "WINDOW::Functions are not intialized");

	init();
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));
	GLCall(glEnable(GL_PROGRAM_POINT_SIZE));

	// GLCall(glEnable(GL_BLEND));
	// GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	
    while(!glfwWindowShouldClose(m_window)){
		float current_time = glfwGetTime();
		Window::m_delta_time = current_time - Window::m_last_time;

		if (m_delta_time < 0.002f) continue;

		Window::m_last_time = current_time;

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		render();
		Window::m_window_resized = false;

		GLCall(glfwSwapBuffers(m_window));
		GLCall(glfwPollEvents());
	    GLClearError();
	}

	destroy();
}

void Window::_handle_resize(GLFWwindow* window, int width, int height) {
	Window::m_width = width;
	Window::m_height = height;
	Window::m_window_resized = true;
    glViewport(0, 0, width, height);
}

void Window::_handle_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key== GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(Window::m_window, true);

	switch (action) {
	case GLFW_PRESS:
		Window::keyboard.keys[key] = { m_delta_time, true };
		break;
	case GLFW_RELEASE:
		Window::keyboard.keys[key] = { m_delta_time, false };
		break;
	default:
		Window::keyboard.keys[key] = { m_delta_time, Window::keyboard.keys[key].down };

		break;
	}
}

void Window::_handle_mouse_pos(GLFWwindow* handle, double x, double y) {
	mouse.delta_time = m_delta_time;
	mouse.dx = mouse.x - x;
	mouse.dy = mouse.y - y;
	
	mouse.dx = saturate(mouse.dx, -100.0f, 100.0f);
	mouse.dy = saturate(mouse.dy, -100.0f, 100.0f);

	mouse.x = x;
	mouse.y = y;
}
