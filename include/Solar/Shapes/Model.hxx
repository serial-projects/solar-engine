#ifndef solar_shapes_rawmodel_hxx
#define solar_shapes_rawmodel_hxx

#include "Solar/Shapes/World.hxx"
#include "Solar/Core/Storage.hxx"
#include "Solar/GL.hxx"
#include "Solar/Math/Vector3.hxx"
#include "Solar/Math/Vector2.hxx"
#include "Solar/Types.hxx"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace Solar
{
    namespace Shapes
    {
        // GetModelAttribute:
        Solar::Types::U8 GetModelAttribute(Solar::Types::Boolean Shape, Solar::Types::Boolean HasElementBuffer);

        // Model:
        typedef std::vector<Solar::Math::Vector3::D32> ModelVertices;
        typedef std::vector<Solar::Math::Vector3::D32> ModelColors;
        typedef std::vector<Solar::Math::Vector2::D32> ModelTextureMap;

        typedef std::vector<Solar::Types::Integer> ModelIndices;
        class Model
        {
            private:
            Solar::GL::VertexBufferObject   vbo;
            Solar::GL::VertexAttribObject   vao;
            Solar::GL::ElementBufferObject  ebo;
            Solar::Types::U64 buffer_size = 0;
            Solar::Types::U64 indices = 0;

            public:
            Solar::Shapes::PositionVector   position    = { 0, 0, 0 };
            Solar::Shapes::SizeVector       size        = { 1, 1, 1 };
            Solar::Shapes::RotationVector   rotation    = { 0, 0, 0 };
            Solar::Types::U8 attributes = 0;

            // LoadModel: this function will automatically decide the stride and other
            // OpenGL buffer operations. Keep in mind this defines an GL_STATIC_DRAW
            // and it is supposed to only be called ONCE!
            void LoadModel(
                const Solar::Shapes::ModelVertices      vertices,
                const Solar::Shapes::ModelColors        colors,
                const Solar::Shapes::ModelTextureMap    texture_map,
                const Solar::Shapes::ModelIndices       indices
            );
            void Draw(Solar::Core::Storage::Shader *using_shader);
            void UnloadModel();
        };
    };
};

#endif
// Solar/Shapes/RawModel.hxx: