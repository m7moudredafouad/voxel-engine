#pragma once

#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>


#include <gfx/gfx.h>
#include <gfx/Resource.h>
#include <gfx/Window.h>
#include <gfx/Shader.h>
#include <gfx/Buffers.h>


#include <control/Camera.h>

#include <models/Model.h>

#include <world/Geometric.h>
#include <world/Chunkmesh.h>
#include "Settings.h"

class Game {
private:
	Game();
	static void _handle_key();
	static void _handle_mouse();
public:
	static void startup();
	static void shutdown();
	static void Init();
	static void Update();
};