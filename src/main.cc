#include <main.h>

Window * window = static_cast<Window *>(&Window::getInstance());

void init() {
    srand (time(NULL));
    
    /***Renderer**************************************/
    Resource::startup();

    /***Camera****************************************/
    Camera::startup(45);

    /***Game******************************************/
    Game::startup();
    Game::Init();

    /***Projection************************************/
    const Shader & basic_shader = Resource::getShader(ShaderEnum::BASIC);
    /*Resource::useShader(ShaderEnum::BASIC);
    basic_shader.setUniform("projection", glm::ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, 0.1f, 100.0f));*/
    // shader.setUniform("model", control::Camera::Model());
}

void render() {
    Game::Update();
}

void destroy() {
    Game::shutdown();
    Resource::shutdown();
}

int main() {
	window->create();
	window->loop(init, render, destroy);
	return 0;
}


