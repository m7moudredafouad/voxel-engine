#pragma once

#include "world/geometric_utils.h"

#define GAME_WIDTH		(16)
#define GAME_HEIGHT		(2)
//#define GAME_HEIGHT		(16)
#define GAME_DEPTH		(16)

#define BLOCK_SIZE		(16)
#define BLOCK_WIDTH		(16)
#define BLOCK_HEIGHT	(16)
#define BLOCK_DEPTH		(16)

#define WINDOW_WIDTH	(20.0f * BLOCK_HEIGHT)
#define WINDOW_HEIGHT	(20.0f * BLOCK_HEIGHT)

#define GRAVITY			(-0.15f)
#define JUMP_HEIGHT		(BLOCK_HEIGHT * 2)
#define SPEED			(BLOCK_WIDTH*3)


#define MAX_CUBES		(GAME_WIDTH * GAME_HEIGHT * GAME_DEPTH)

#define CUBE_VERTEX_SIZE		(VERTEX_PER_CUBE * sizeof(sSpaceVertex))
#define CUBE_INDEX_SIZE			(INDEX_PER_CUBE * sizeof(uint32_t))
