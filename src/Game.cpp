#include "Game.h"

using Cubes = Chunkmesh<Cube, sCubeIndex>;

//static glm::vec4 player_color    = { 0.2, 1.0, 0.5, 1 };
static glm::vec4 player_color    = { 0, 0, 0, 0 };
static glm::vec4 sky_color       = { 0.6, 0.6, 1.0, 1 };
static glm::vec4 enemy_color	 = { 1.0, 0.3, 0.3, 1 };

static Window* window = static_cast<Window*>(&Window::getInstance());
static std::shared_ptr<Cubes> block_mesh, player_mesh;

void Game::_handle_key() {
    auto& keyboard = Window::keyboard.keys;
    auto& player = player_mesh->object(0);

    Model player_copy = player;

    glm::vec3 old_pos = player.get_position();
    glm::vec3 new_pos = player.get_position();
    auto old_y = old_pos.y;

    if (keyboard[GLFW_KEY_W].down) {
        old_pos += Camera::Direction() * SPEED * (float)keyboard[GLFW_KEY_W].delta;
        old_pos.y = old_y;
        player_copy.set_position(old_pos);

        if (!block_mesh->check_collision(player_copy, FLEFT)) {
            new_pos = old_pos;
        }
        
    }

    if (keyboard[GLFW_KEY_S].down) {
        old_pos -= Camera::Direction() * SPEED * (float)keyboard[GLFW_KEY_S].delta;
        old_pos.y = old_y;
    }

    if (keyboard[GLFW_KEY_A].down) {
        old_pos += Camera::Right() * SPEED * (float)keyboard[GLFW_KEY_A].delta;
        old_pos.y = old_y;
    }

    if (keyboard[GLFW_KEY_D].down) {
        old_pos -= Camera::Right() * SPEED * (float)keyboard[GLFW_KEY_D].delta;
        old_pos.y = old_y;
    }

    if (keyboard[GLFW_KEY_SPACE].down) {
    }

    player.set_position(new_pos);
}

void Game::_handle_mouse() {
    auto& mouse = Window::mouse;
    Camera::handle_mouse(mouse.dx, mouse.dy, mouse.delta_time);
    mouse.dx = 0;
    mouse.dy = 0;
}

void Game::startup() {
    /***WORLD******************************************/
    block_mesh = std::shared_ptr<Cubes>(new Cubes(MAX_CUBES));
    block_mesh->layout({
        {3, GL_FLOAT, true},
        {4, GL_FLOAT, true},
        });

    block_mesh->shape({ GAME_WIDTH, GAME_HEIGHT, GAME_DEPTH });
    block_mesh->shader(ShaderEnum::BASIC);

    player_mesh = std::shared_ptr<Cubes>(new Cubes(1));
    player_mesh->layout({
        {3, GL_FLOAT, true},
        {4, GL_FLOAT, true},
        });

    player_mesh->shape({ 1, 0, 0 });

    player_mesh->shader(ShaderEnum::BASIC);

}

void Game::shutdown() {

}

void Game::Init() {

    player_mesh->push(Model(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, player_color));

    /***Blocks****************************************/
    for (int x = 0; x < GAME_WIDTH; x++) {
        for (int y = 1; y <= GAME_HEIGHT; y++) {
            for (int z = 0; z < GAME_DEPTH; z++) {
                block_mesh->push(Model(x * BLOCK_SIZE, -y * BLOCK_SIZE, z * BLOCK_SIZE, BLOCK_SIZE, z%2&& x %2, enemy_color));
            }
        }
    }
}

void Game::Update() {
    /***Player****************************************/
    auto& player = player_mesh->object(0);


    /***Events****************************************/
    _handle_key();
    _handle_mouse();
    
    /***Camera****************************************/
     Camera::Update(player.get_position());
     player.translate();

    /***DRAW*********************/
     player_mesh->Render();
     block_mesh->Render();
}
