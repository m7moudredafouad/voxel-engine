#include "Game.h"

using Cubes = Chunkmesh<Cube, sCubeIndex>;

//static glm::vec4 player_color    = { 0.2, 1.0, 0.5, 1 };
static glm::vec4 player_color    = { 0, 0, 0, 0 };
static glm::vec4 sky_color       = { 0.6, 0.6, 1.0, 1 };
static glm::vec4 enemy_color	 = { 1.0, 0.3, 0.3, 1 };

static Window* window = static_cast<Window*>(&Window::getInstance());
static std::shared_ptr<Cubes> block;

void Game::_handle_key() {
    auto& keyboard = Window::keyboard.keys;

    if (keyboard[GLFW_KEY_W].down) {
        Camera::handle_keys(GLFW_KEY_W, keyboard[GLFW_KEY_W].delta);
    }

    if (keyboard[GLFW_KEY_S].down) {
        Camera::handle_keys(GLFW_KEY_S, keyboard[GLFW_KEY_S].delta);
    }

    if (keyboard[GLFW_KEY_A].down) {
        Camera::handle_keys(GLFW_KEY_A, keyboard[GLFW_KEY_A].delta);
    }

    if (keyboard[GLFW_KEY_D].down) {
        Camera::handle_keys(GLFW_KEY_D, keyboard[GLFW_KEY_D].delta);
    }

    if (keyboard[GLFW_KEY_SPACE].down) {
    }
}

void Game::_handle_mouse() {
    auto& mouse = Window::mouse;
    Camera::handle_mouse(mouse.dx, mouse.dy, mouse.delta_time);
    mouse.dx = 0;
    mouse.dy = 0;
}

void Game::startup() {
    /***WORLD******************************************/
    block = std::shared_ptr<Cubes>(new Cubes(VERTEX_SIZE, INDEX_SIZE));
    block->layout({
        {3, GL_FLOAT, true},
        {4, GL_FLOAT, true},
        });

    block->shader(ShaderEnum::BASIC);

    /***LEVEL*********************************/
}

void Game::shutdown() {

}

void Game::Init() {
    /***Blocks****************************************/

    block->push(Model(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, player_color));
    for (int x = 0; x < GAME_WIDTH; x++) {
        for (int y = 1; y <= GAME_HEIGHT; y++) {
            for (int z = 0; z < GAME_DEPTH; z++) {
                block->push(Model(x * BLOCK_SIZE, -y * BLOCK_SIZE, z * BLOCK_SIZE, BLOCK_SIZE, enemy_color));
            }
        }
    }
}

void Game::Update() {
    /***Player****************************************/
    auto& player = block->object(0);


    /***Events****************************************/
    _handle_key();
    _handle_mouse();
    
    /***Camera****************************************/
     Camera::Update();
     player.set_position(Camera::Position());
     block->translate(0);
    /***DRAW*********************/
    block->Render();
}
