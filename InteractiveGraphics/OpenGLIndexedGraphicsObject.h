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
	OpenGLIndexedGraphicsObject(GLuint indexVbo) :
		OpenGLGraphicsObject(), _indexVbo(indexVbo)
	{}

	OpenGLIndexedGraphicsObject(AbstractGraphicsShader* abstractGraphicsShader, GLuint indexVbo) : 
		OpenGLGraphicsObject(abstractGraphicsShader), _indexVbo(indexVbo)
	{}

	void AddIdex(unsigned int index) { _indexes.push_back(index); }
	void Setup();
	void Render();
};

#endif

