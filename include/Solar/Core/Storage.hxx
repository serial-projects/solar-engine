#ifndef solar_core_storage_hxx
#define solar_core_storage_hxx

#include "Solar/Types.hxx"
#include "Solar/GL.hxx"

#include <glm/glm.hpp>
#include <unordered_map>

namespace Solar
{
    namespace Core
    {
        namespace Storage
        {
            inline Solar::Types::U8 GetCacheOperatingMode(Solar::Types::U8 should_delete);
            
            struct Shader
            {
                Solar::GL::ShaderProgram shader;
                Solar::Types::U64 lastuse   = 0;
                Solar::Types::U64 timestamp = 0;
                void LoadVertexAndFragmentShader(const Solar::Types::String path);
                void SetIntegerUniform(const Solar::Types::Character *key, Solar::Types::Integer value);
                void SetUnsignedIntegerUniform(const Solar::Types::Character *key, Solar::Types::U32 value);
                void SetDecimalUniform(const Solar::Types::Character *key, Solar::Types::D32 value);
                void SetVectorTwoUniform(const Solar::Types::Character *key, const glm::vec2 &value);
                void SetVectorThreeUniform(const Solar::Types::Character *key, const glm::vec3 &value);
                void SetVectorFourUniform(const Solar::Types::Character *key, const glm::vec4 &value);
                void SetMatrixTwoUniform(const Solar::Types::Character *key, const glm::mat2 &value);
                void SetMatrixThreeUniform(const Solar::Types::Character *key, const glm::mat3 &value);
                void SetMatrixFourUniform(const Solar::Types::Character *key, const glm::mat4 &value);
                void Use();
                void Clean();
            };

            // ContentProvider objects:
            typedef std::unordered_map<Solar::Types::String, Solar::Core::Storage::Shader> ShaderCacheTable;

            // ContentProvider will keep track of all cachable items and delete those that are not
            // used for an long time (usually 1 minute of non-usage)! This must be called periodically
            // from the Tick() side of the game since.
            struct ContentProvider
            {
                Solar::Core::Storage::ShaderCacheTable cached_shaders;
                Solar::Types::U8 mode = 0;
                Solar::Types::String resource_path;
                Solar::Core::Storage::Shader* GetShader(const Solar::Types::String key);
                void Clean();
            };
        };
    };
};


#endif
// Solar/Core/Storage.hxx:
