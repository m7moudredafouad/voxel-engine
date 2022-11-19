#pragma once

#include <gfx/Window.h>

#include "../Settings.h"

enum eCollisionDir {
    LEFT = 0b00000001,
    RIGHT = 0b00000010,
    TOP = 0b00000100,
    BOTTOM = 0b00001000,

    TOP_LEFT = 0b00010000,
    BOTTOM_LEFT = 0b00100000,
    TOP_RIGHT = 0b01000000,
    BOTTOM_RIGHT = 0b10000000,

    FLEFT = 0b00110001,
    FRIGHT = 0b11000010,
    FTOP = 0b01010100,
    FBOTTOM = 0b10101000,

    FVERTICAL = 0b11111100,
    FHORIZONAL = 0b11110011,
};

/*
bool is_in_mid_screen(Model& player) {
    return (player.x >= offsetX + (WINDOW_WIDTH / 2) - (BLOCK_WIDTH / 2))
        && (player.x <= offsetX + WINDOW_WIDTH - (WINDOW_WIDTH / 2) + (BLOCK_WIDTH / 2))
        || (player.y >= offsetY + (WINDOW_HEIGHT / 2) - (BLOCK_HEIGHT / 2))
        && (player.y <= offsetY + WINDOW_HEIGHT - (WINDOW_HEIGHT / 2) + (BLOCK_HEIGHT / 2));
}

static char getBlockType(int x, int y){
    y = GAME_HEIGHT - y - 1;
    if (x < 0 || y < 0 || x >= GAME_WIDTH || y >= GAME_HEIGHT) return ' ';

    return Level[y * GAME_WIDTH + x];
}

static int getBlockIndex(int x, int y) {
    char block_type = getBlockType(x, y);
    if (block_type == '.' || block_type == ' ') return -1;

    return 1 + y * GAME_WIDTH + x;
}

bool check_collision(Model player, eCollisionDir dir) {

    int x = std::round(player.x / BLOCK_WIDTH);
    int y = std::round(player.y / BLOCK_HEIGHT);

    player.translate();
    int idx = getBlockIndex(x, y);

    if (dir & eCollisionDir::LEFT) {
        idx = getBlockIndex(x - 1, y);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::RIGHT) {
        idx = getBlockIndex(x + 1, y);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::TOP) {
        idx = getBlockIndex(x, y + 1);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::BOTTOM) {
        idx = getBlockIndex(x, y - 1);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::BOTTOM_LEFT) {
        idx = getBlockIndex(x - 1, y - 1);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::TOP_LEFT) {
        idx = getBlockIndex(x - 1, y + 1);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::BOTTOM_RIGHT) {
        idx = getBlockIndex(x + 1, y - 1);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::TOP_RIGHT) {
        idx = getBlockIndex(x + 1, y + 1);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    return false;
};*/