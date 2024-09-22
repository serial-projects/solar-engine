#include "Progator/Backends/OpenGL/Shader.hpp"
#include "Progator/Support/FS.hpp"

#include <iostream>

Progator::Backends::OpenGL::Shader* Progator::Backends::OpenGL::ShaderNew()
{
    Progator::Backends::OpenGL::Shader* proto = new Progator::Backends::OpenGL::Shader;
    return proto;
}

void Progator::Backends::OpenGL::ShaderDestroy(Progator::Backends::OpenGL::Shader* shader)
{
    glDeleteShader(shader->vertex_shader);
    glDeleteShader(shader->fragment_shader);
    glDeleteProgram(shader->program);
    delete shader;
}

void Progator::Backends::OpenGL::ShaderInit(Progator::Backends::OpenGL::Shader* shader, Progator::Validator* validator)
{
    shader->validator = validator;
}

void Progator::Backends::OpenGL::ShaderLoadVertexCodeFromFile(Progator::Backends::OpenGL::Shader* shader, const Progator::Character* path)
{
    Progator::Support::FileBuffer buffer = Progator::Support::FileBufferGet(path);
    if(buffer != nullptr)
    {
        shader->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shader->vertex_shader, 1, (const GLchar **)&buffer, NULL);
        glCompileShader(shader->vertex_shader);

        Progator::I32 success; Progator::Character build_log[256];
        glGetShaderiv(shader->vertex_shader, GL_COMPILE_STATUS, &success);
        if(! success )
        {
            glGetShaderInfoLog(shader->vertex_shader, 256, NULL, (GLchar*)&build_log);
            
            /* TODO: use validator now: */
            std::cout << build_log << "\n";
            abort();
        }
        Progator::Support::FileBufferDestroy(buffer);
    }
    else
    {
        /* TODO: use validator now: */
        abort();
    }
}

void Progator::Backends::OpenGL::ShaderLoadFragmentCodeFromFile(Progator::Backends::OpenGL::Shader* shader, const Progator::Character* path)
{
    Progator::Support::FileBuffer buffer = Progator::Support::FileBufferGet(path);
    if(buffer != nullptr)
    {
        shader->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(shader->fragment_shader, 1, (const GLchar **)&buffer, NULL);
        glCompileShader(shader->fragment_shader);

        Progator::I32 success; Progator::Character build_log[256];
        glGetShaderiv(shader->vertex_shader, GL_COMPILE_STATUS, &success);
        if(! success )
        {
            glGetShaderInfoLog(shader->vertex_shader, 256, NULL, (GLchar*)&build_log);
            
            /* TODO: use validator now: */
            std::cout << build_log << "\n";
            abort();
        }
        Progator::Support::FileBufferDestroy(buffer);
    }
    else
    {
        /* TODO: use validator now: */
        abort();
    }
}

void Progator::Backends::OpenGL::ShaderCompile(Progator::Backends::OpenGL::Shader* shader)
{
    shader->program = glCreateProgram();
    glAttachShader(shader->program, shader->vertex_shader);
    glAttachShader(shader->program, shader->fragment_shader);
    glLinkProgram(shader->program);

    Progator::I32 success; Progator::Character build_log[256];
    glGetProgramiv(shader->program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shader->program, 256, NULL, (GLchar*)&build_log);
        
        /* TODO: use validator now: */
        std::cout << build_log << "\n";
        abort();
    }
}

void Progator::Backends::OpenGL::ShaderUse(Progator::Backends::OpenGL::Shader* shader)
{
    glUseProgram(shader->program);
}

#define PROGATOR_PROGRAMSHADER_NOLOCATION   -1

void Progator::Backends::OpenGL::ShaderSUMatrix44(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::Matrix44 value)
{
    const Progator::I32 keylocation = glGetUniformLocation(shader->program, key);
    if(keylocation != PROGATOR_PROGRAMSHADER_NOLOCATION)
        glUniformMatrix4fv(keylocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Progator::Backends::OpenGL::ShaderSUMatrix33(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::Matrix33 value)
{
    const Progator::I32 keylocation = glGetUniformLocation(shader->program, key); 
    if(keylocation != PROGATOR_PROGRAMSHADER_NOLOCATION)
        glUniformMatrix3fv(keylocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Progator::Backends::OpenGL::ShaderSUMatrix22(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::Matrix22 value)
{
    const Progator::I32 keylocation = glGetUniformLocation(shader->program, key);
    if(keylocation != PROGATOR_PROGRAMSHADER_NOLOCATION)
        glUniformMatrix2fv(keylocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Progator::Backends::OpenGL::ShaderSUVector4(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::Vector4 value)
{
    const Progator::I32 keylocation = glGetUniformLocation(shader->program, key);
    if(keylocation != PROGATOR_PROGRAMSHADER_NOLOCATION)
        glUniform4fv(keylocation, 1, glm::value_ptr(value));
}

void Progator::Backends::OpenGL::ShaderSUVector3(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::Vector3 value)
{
    const Progator::I32 keylocation = glGetUniformLocation(shader->program, key);
    if(keylocation != PROGATOR_PROGRAMSHADER_NOLOCATION)
        glUniform3fv(keylocation, 1, glm::value_ptr(value));
}

void Progator::Backends::OpenGL::ShaderSUVector2(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::Vector2 value)
{
    const Progator::I32 keylocation = glGetUniformLocation(shader->program, key);
    if(keylocation != PROGATOR_PROGRAMSHADER_NOLOCATION)
        glUniform2fv(keylocation, 1, glm::value_ptr(value));
}

void Progator::Backends::OpenGL::ShaderSUInteger(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::I32 value)
{
    const Progator::I32 keylocation = glGetUniformLocation(shader->program, key);
    if(keylocation != PROGATOR_PROGRAMSHADER_NOLOCATION)
        glUniform1i(keylocation, value);
}

void Progator::Backends::OpenGL::ShaderSUUInteger(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::U32 value)
{
    const Progator::I32 keylocation = glGetUniformLocation(shader->program, key);
    if(keylocation != PROGATOR_PROGRAMSHADER_NOLOCATION)
        glUniform1ui(keylocation, value);
}

void Progator::Backends::OpenGL::ShaderSURGBA84(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::RGBA84 value)
{
    const Progator::I32 keylocation = glGetUniformLocation(shader->program, key);
    if(keylocation != PROGATOR_PROGRAMSHADER_NOLOCATION)
        glUniform1ui(keylocation, value);
}

void Progator::Backends::OpenGL::ShaderSUDecimal(Progator::Backends::OpenGL::Shader* shader, const Progator::Character *key, const Progator::F32 value)
{
    const Progator::I32 keylocation = glGetUniformLocation(shader->program, key);
    if(keylocation != PROGATOR_PROGRAMSHADER_NOLOCATION)
        glUniform1f(keylocation, value);
}