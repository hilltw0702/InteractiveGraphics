#pragma once
#include "GraphicsStructures.h"
#include "OpenGLGraphicsObject.h"

#ifndef GENERATE

class Generate
{
public:
	static OpenGLGraphicsObject* FlatSurface(float width, float depth, RGBA color);
	static OpenGLGraphicsObject* Cuboid(float width, float height, float depth, RGBA color);
};

#endif

