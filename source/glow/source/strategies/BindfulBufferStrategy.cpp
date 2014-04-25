#include "BindfulBufferStrategy.h"

#include <glow/Error.h>

namespace glow {

void * BindfulBufferStrategy::map(const Buffer * buffer, GLenum access) const
{
    buffer->bind();

    void * result = glMapBuffer(buffer->target(), access);
    CheckGLError();

    return result;
}

void * BindfulBufferStrategy::mapRange(const Buffer * buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) const
{
    buffer->bind();

    void * result = glMapBufferRange(buffer->target(), offset, length, access);
    CheckGLError();

    return result;
}

bool BindfulBufferStrategy::unmap(const Buffer * buffer) const
{
    buffer->bind();

    GLboolean success = glUnmapBuffer(buffer->target());
    CheckGLError();

    return success == GL_TRUE;
}

void BindfulBufferStrategy::setData(const Buffer * buffer, GLsizeiptr size, const GLvoid * data, GLenum usage) const
{
    buffer->bind();

    glBufferData(buffer->target(), size, data, usage);
    CheckGLError();
}

void BindfulBufferStrategy::setSubData(const Buffer * buffer, GLintptr offset, GLsizeiptr size, const GLvoid * data) const
{
    buffer->bind();

    glBufferSubData(buffer->target(), offset, size, data);
    CheckGLError();
}

void BindfulBufferStrategy::setStorage(const Buffer * buffer, GLsizeiptr size, const GLvoid * data, GLbitfield flags) const
{
    buffer->bind();

    glBufferStorage(buffer->target(), size, data, flags);
    CheckGLError();
}

void BindfulBufferStrategy::copySubData(const glow::Buffer * buffer, glow::Buffer * other, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) const
{
    GLenum readTarget = GL_COPY_READ_BUFFER;
    GLenum writeTarget = GL_COPY_WRITE_BUFFER;

    glBindBuffer(readTarget, buffer->id());
    CheckGLError();

    glBindBuffer(writeTarget, other->id());
    CheckGLError();

    glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
    CheckGLError();

    glBindBuffer(readTarget, 0);
    CheckGLError();

    glBindBuffer(writeTarget, 0);
    CheckGLError();
}

void BindfulBufferStrategy::getParameter(const Buffer * buffer, GLenum pname, GLint * data) const
{
    buffer->bind();

    glGetBufferParameteriv(buffer->target(), pname, data);
    CheckGLError();
}

void BindfulBufferStrategy::clearData(const Buffer * buffer, GLenum internalformat, GLenum format, GLenum type, const void * data) const
{
    buffer->bind();

    glClearBufferData(buffer->target(), internalformat, format, type, data);
    CheckGLError();
}

void BindfulBufferStrategy::clearSubData(const Buffer * buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data) const
{
    buffer->bind();

    glClearBufferSubData(buffer->target(), internalformat, offset, size, format, type, data);
    CheckGLError();
}

} // namespace glow
