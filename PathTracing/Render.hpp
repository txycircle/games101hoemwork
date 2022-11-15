#pragma once

#ifndef RENDER_HPP
#define RENDER_HPP

#include <fstream>
#include "Scene.hpp"
#include "common.hpp"

inline double deg2rad(const float deg) { return deg * MY_PI / 180.0; }
class Render
{
public:
	void render(Scene& scene);
};

#endif