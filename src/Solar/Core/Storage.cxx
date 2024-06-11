#include "Solar/Core/Storage.hxx"
#include "Solar/Utils.hxx"
#include "Solar/Config.hxx"

#include <fstream>
#include <sstream>

// Shader:
void Solar::Core::Storage::Shader::LoadVertexAndFragmentShader(const Solar::Types::String path)
{
    Solar::Types::String vertex_shader_buffer;
    Solar::Types::String fragment_shader_buffer;
    
    std::ifstream vertex_shader_file;   vertex_shader_file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    std::ifstream fragment_shader_file; fragment_shader_file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    // TODO: do something when error!
    try
    {
        // try to open the file;
        vertex_shader_file.open(path + ".vert");
        fragment_shader_file.open(path + ".frag");
        
        // from the stream, read the file:
        std::stringstream vertex_shader_stream; vertex_shader_stream << vertex_shader_file.rdbuf();
        std::stringstream fragment_shader_stream; fragment_shader_stream << fragment_shader_file.rdbuf();
        vertex_shader_file.close();
        fragment_shader_file.close();

        // convert to string:
        vertex_shader_buffer = vertex_shader_stream.str();
        fragment_shader_buffer = fragment_shader_stream.str();
    }
    catch(std::ifstream::failure *error)
    {
        GENERROR("failed to open shader file: " << error);
    }

    // begin to compile the shaders here:
    const char *vertex_shader_code = vertex_shader_buffer.c_str();
    const char *fragment_shader_code = fragment_shader_buffer.c_str();
    
    // error handler (during opengl compilations):
    int success; char log[SOLAR_CORE_STORAGE_SHADER_ERRLOGSIZE];

    // compile the vertex shader:
    Solar::GL::VertexShader vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    MAKESURE(success, {
        glGetShaderInfoLog(vertex_shader, SOLAR_CORE_STORAGE_SHADER_ERRLOGSIZE, NULL, log);
        GENERROR("failed to compile vertex shader: " << log);
    });

    // compile the fragment shader:
    Solar::GL::FragmentShader fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    std::cout << success << "\n";
    MAKESURE(success, {
        glGetShaderInfoLog(fragment_shader, SOLAR_CORE_STORAGE_SHADER_ERRLOGSIZE, NULL, log);
        GENERROR("failed to compile fragment shader: " << log);
    });

    // create the shader program:
    this->shader = glCreateProgram();
    glAttachShader(this->shader, vertex_shader);
    glAttachShader(this->shader, fragment_shader);
    glLinkProgram(this->shader);
    glGetProgramiv(this->shader, GL_LINK_STATUS, &success);
    MAKESURE(success, {
        glGetProgramInfoLog(this->shader, SOLAR_CORE_STORAGE_SHADER_ERRLOGSIZE, NULL, log);
        GENERROR("failed to link shader: " << log);
    });

    // delete all shaders that were create (since we have the program):
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // assign an timestamp and all:
    this->timestamp = SDL_GetTicks64();
}

#define ShaderGetAddressAndImplementFunction(call)                              \
    Solar::Types::Integer location = glGetUniformLocation(this->shader, key);   \
    WHEN(location != -1, call);/* if(location == -1) { GENDEBUG("failed to set shader location: " << key); } else call; */
void Solar::Core::Storage::Shader::SetIntegerUniform(const Solar::Types::Character *key, Solar::Types::Integer value)
{
    ShaderGetAddressAndImplementFunction(glUniform1i(location, value));
}

void Solar::Core::Storage::Shader::SetUnsignedIntegerUniform(const Solar::Types::Character *key, Solar::Types::U32 value)
{
    ShaderGetAddressAndImplementFunction(glUniform1ui(location, value));
}

void Solar::Core::Storage::Shader::SetDecimalUniform(const Solar::Types::Character *key, Solar::Types::D32 value)
{
    ShaderGetAddressAndImplementFunction(glUniform1f(location, value));
}

void Solar::Core::Storage::Shader::SetVectorTwoUniform(const Solar::Types::Character *key, const glm::vec2 &value)
{
    ShaderGetAddressAndImplementFunction(glUniform2fv(location, 1, &value[0]));
}

void Solar::Core::Storage::Shader::SetVectorThreeUniform(const Solar::Types::Character *key, const glm::vec3 &value)
{
    ShaderGetAddressAndImplementFunction(glUniform3fv(location, 1, &value[0]));
}

void Solar::Core::Storage::Shader::SetVectorFourUniform(const Solar::Types::Character *key, const glm::vec4 &value)
{
    ShaderGetAddressAndImplementFunction(glUniform4fv(location, 1, &value[0]));
}

void Solar::Core::Storage::Shader::SetMatrixTwoUniform(const Solar::Types::Character *key, const glm::mat2 &value)
{
    ShaderGetAddressAndImplementFunction(glUniformMatrix2fv(location, 1, GL_FALSE, &value[0][0]));
}

void Solar::Core::Storage::Shader::SetMatrixThreeUniform(const Solar::Types::Character *key, const glm::mat3 &value)
{
    ShaderGetAddressAndImplementFunction(glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]));
}

void Solar::Core::Storage::Shader::SetMatrixFourUniform(const Solar::Types::Character *key, const glm::mat4 &value)
{
    ShaderGetAddressAndImplementFunction(glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]));
}

void Solar::Core::Storage::Shader::Use()
{
    this->lastuse = SDL_GetTicks64();
    glUseProgram(this->shader);
}

void Solar::Core::Storage::Shader::Clean()
{
    glDeleteProgram(this->shader);
}

// Content Provider:
Solar::Core::Storage::Shader* Solar::Core::Storage::ContentProvider::GetShader(const Solar::Types::String key)
{
    if(this->cached_shaders.find(key) == this->cached_shaders.end())
    {
        // LOAD the shader into the memory:
        Solar::Core::Storage::Shader proto_shader_cache;
        proto_shader_cache.LoadVertexAndFragmentShader(this->resource_path + "Shaders/" + key);
        this->cached_shaders[key] = proto_shader_cache;
    }
    Solar::Core::Storage::Shader* shader = &this->cached_shaders[key];
    return shader;
}

void Solar::Core::Storage::ContentProvider::Clean()
{
    for(auto &content : this->cached_shaders)
        content.second.Clean();
    this->cached_shaders.clear();
}