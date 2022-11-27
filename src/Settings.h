#pragma once

#define GAME_WIDTH		(16)
//#define GAME_WIDTH		(1)
#define GAME_HEIGHT		(2)
//#define GAME_HEIGHT		(16)
#define GAME_DEPTH		(16)

#define BLOCK_SIZE		(16)
#define BLOCK_WIDTH		(16)
#define BLOCK_HEIGHT	(16)
#define BLOCK_DEPTH		(16)

#define WINDOW_WIDTH	(20.0f * BLOCK_HEIGHT)
#define WINDOW_HEIGHT	(20.0f * BLOCK_HEIGHT)

#define GRAVITY			(-2.5f)
#define JUMP_HEIGHT		(BLOCK_HEIGHT*3.0f)
#define SPEED			(BLOCK_WIDTH*6.0f)

#define MOUSE_SENSE		(0.2f)

#define MAX_CUBES		(GAME_WIDTH * GAME_HEIGHT * GAME_DEPTH)
