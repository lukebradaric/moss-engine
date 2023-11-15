#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	// Gen 1 buffer and assign id to rendererId
	GLCall(glGenBuffers(1, &_rendererId));
	// Bind rendererId buffer
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererId));
	// Set buffer size, data, and draw type (of previously bound buffer)
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &_rendererId));
}

void VertexBuffer::Bind() const
{
	// Bind this buffer (from rendererId)
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererId));
}


void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
