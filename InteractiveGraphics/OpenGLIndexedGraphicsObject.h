#pragma once
#ifndef OPEN_GL_INDEXED_GRAPHICS_OBJECT
#define OPEN_GL_INDEXED_GRAPHICS_OBJECT

#include "OpenGLGraphicsObject.h"
class OpenGLIndexedGraphicsObject :
	public OpenGLGraphicsObject
{
protected:
	GLuint _indexVbo;
	vector<unsigned int> _indexes;

public:
	OpenGLIndexedGraphicsObject() :
		OpenGLGraphicsObject(), _indexVbo(0)
	{}

	OpenGLIndexedGraphicsObject(AbstractGraphicsShader* shader) : 
		OpenGLGraphicsObject(shader), _indexVbo(0)
	{}

	void AddIndex(unsigned int index) { _indexes.push_back(index); }
	void Setup();
	void Render();
};

#endif

