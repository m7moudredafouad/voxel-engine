#include "Game.h"
#include <noise/Perlin.h>

using Cubes = Chunkmesh<Cube, sCubeIndex>;

static sColor player_color(255, 77, 77, 0);
static sColor colors[] = {
    sColor(154, 154, 154, 255), // brick_color
    sColor(200, 50, 50, 255),    // red_color
    sColor(86, 125, 70, 255),    // grass_color
    sColor(255, 215, 0, 255),    // gold_color
};

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

    if (keyboard[GLFW_MOUSE_BUTTON_LEFT].down) {
        auto b = Model(new_pos.x, new_pos.y, new_pos.z, 1, colors[3]);
        auto dir = Camera::Direction();
        dir *= 10;
        b.set_delta(dir);
        player_mesh->push(b);

        keyboard[GLFW_MOUSE_BUTTON_LEFT].down = false;
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
    block_mesh = std::shared_ptr<Cubes>(new Cubes(MAX_CUBES, { GAME_WIDTH, GAME_DEPTH, GAME_HEIGHT }));
    block_mesh->layout({
        {3, GL_FLOAT, true},
        {4, GL_FLOAT, true},
        {1, GL_FLOAT, true},
    });

    block_mesh->shader(ShaderEnum::BASIC);

    player_mesh = std::shared_ptr<Cubes>(new Cubes(2, {2}));
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
    srand(time(0));
    PerlinNoise p(rand());

    for (int x = 0; x < GAME_WIDTH; x++) {
        for (int z = 0; z < GAME_DEPTH; z++) {
            int maxHeight = p.noise(10 * (double)x/GAME_WIDTH, 10 * (double)z/GAME_DEPTH, 0.8) * GAME_HEIGHT;
            for (int y = 0; y < GAME_HEIGHT; y++) {
                bool isActive = y < maxHeight;
                sColor & color = y < 2 ? colors[0] : (y < 6 ? colors[1] : colors[2]);
                block_mesh->push(Model(x * BLOCK_SIZE, y * BLOCK_SIZE, z * BLOCK_SIZE, BLOCK_SIZE, isActive, color));
            }
        }
    }
    /***Player****************************************/
    player_mesh->push(Model(BLOCK_SIZE, (GAME_HEIGHT + 10) *BLOCK_SIZE, BLOCK_SIZE*1.1, BLOCK_SIZE, player_color));
}

void Game::Update() {
    /***Player****************************************/
    auto& player = player_mesh->object(0);

    player.handle_jump(block_mesh->check_collision(player, TOP), 
                        block_mesh->check_collision(player, BOTTOM));

    // Bullet handler
    if (player_mesh->exist(1)) {
        auto& bullet = player_mesh->object(1);
        bullet.translate();
        int in_bound = block_mesh->in_bound(bullet);
        if (!in_bound || in_bound && block_mesh->deactivate_if_contains(bullet)) {
            player_mesh->remove(1);
        }
    }

    /***Events****************************************/
    _handle_mouse();
    _handle_key();

    /***Camera****************************************/
     Camera::Update(player.get_position());
    /***DRAW*********************/
     player_mesh->Render();
     block_mesh->Render();
}
