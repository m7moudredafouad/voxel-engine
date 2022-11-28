#include "Game.h"

using Cubes = Chunkmesh<Cube, sCubeIndex>;

static sColor player_color(255, 77, 77, 0);
//static sColor player_color(0, 0, 0, 0);
static sColor sky_color(154, 154, 255, 255);
static sColor enemy_color(52, 255, 128, 255);

static Window* window = static_cast<Window*>(&Window::getInstance());
static std::shared_ptr<Cubes> block_mesh, player_mesh;

float jump_y = 0;


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

        if (!block_mesh->check_collision(player_copy, SAME)) {
            new_pos = old_pos;
        }
        
    }

    if (keyboard[GLFW_KEY_S].down) {
        old_pos -= Camera::Direction() * SPEED * (float)keyboard[GLFW_KEY_S].delta;
        old_pos.y = old_y;
        player_copy.set_position(old_pos);

        if (!block_mesh->check_collision(player_copy, SAME)) {
            new_pos = old_pos;
        }
    }

    if (keyboard[GLFW_KEY_A].down) {
        old_pos += Camera::Right() * SPEED * (float)keyboard[GLFW_KEY_A].delta;
        old_pos.y = old_y;
        player_copy.set_position(old_pos);

        if (!block_mesh->check_collision(player_copy, SAME)) {
            new_pos = old_pos;
        }
    }

    if (keyboard[GLFW_KEY_D].down) {
        old_pos -= Camera::Right() * SPEED * (float)keyboard[GLFW_KEY_D].delta;
        old_pos.y = old_y;
        player_copy.set_position(old_pos);

        if (!block_mesh->check_collision(player_copy, SAME)) {
            new_pos = old_pos;
        }
    }

    if (keyboard[GLFW_KEY_SPACE].down) {
        if (block_mesh->check_collision(player_copy, BOTTOM))
            player.jump();
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
    block_mesh = std::shared_ptr<Cubes>(new Cubes(MAX_CUBES, { GAME_WIDTH, GAME_HEIGHT, GAME_DEPTH }));
    block_mesh->layout({
        {3, GL_FLOAT, true},
        {4, GL_FLOAT, true},
        {1, GL_FLOAT, true},
    });

    block_mesh->shader(ShaderEnum::BASIC);

    player_mesh = std::shared_ptr<Cubes>(new Cubes(1, {1}));
    player_mesh->layout({
        {3, GL_FLOAT, true},
        {4, GL_FLOAT, true},
        {1, GL_FLOAT, true},
    });

    player_mesh->shader(ShaderEnum::BASIC);

}

void Game::shutdown() {

}

void Game::Init() {
    /***Blocks****************************************/
    for (int x = 0; x < GAME_WIDTH; x++) {
        for (int y = 0; y < GAME_HEIGHT; y++) {
            for (int z = 0; z < GAME_DEPTH; z++) {
                //bool isActive = (y == 0) || (x == 0) || (x == GAME_WIDTH - 1) || (z == 0) || (z == GAME_DEPTH - 1);
                bool isActive = (y == 0) || (x % 2 && z % 2);
                //isActive = true;
                if (y % 2 == 0) {
                    block_mesh->push(Model(x * BLOCK_SIZE, y * BLOCK_SIZE, z * BLOCK_SIZE, BLOCK_SIZE, isActive, enemy_color));
                }
                else {
                    block_mesh->push(Model(x * BLOCK_SIZE, y * BLOCK_SIZE, z * BLOCK_SIZE, BLOCK_SIZE, isActive, sky_color));

                }
            }
        }
    }
    /***Player****************************************/
    player_mesh->push(Model(BLOCK_SIZE, 10 *BLOCK_SIZE, BLOCK_SIZE*1.1, BLOCK_SIZE, player_color));
}

void Game::Update() {
    /***Player****************************************/
    auto& player = player_mesh->object(0);

    player.handle_jump(block_mesh->check_collision(player, TOP), 
                        block_mesh->check_collision(player, BOTTOM));

    bool x = block_mesh->check_collision(player, BOTTOM);


    /***Events****************************************/
    _handle_mouse();
    _handle_key();

    /***Camera****************************************/
     Camera::Update(player.get_position());
    /***DRAW*********************/
     player_mesh->Render();
     block_mesh->Render();
}
