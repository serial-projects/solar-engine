#ifndef solar_shapes_mesh_hxx
#define solar_shapes_mesh_hxx

#include "Solar/Core/Storage.hxx"
#include "Solar/Math/Vector3.hxx"
#include "Solar/Math/Vector2.hxx"
#include "Solar/Math/Color.hxx"

#include "Solar/Types.hxx"
#include "Solar/GL.hxx"

#include <vector>

namespace Solar
{
    namespace Shapes
    {
        // GetMeshAttribute: Generate the mesh attributes:
        Solar::Types::U8 GetMeshAttribute(Solar::Types::Boolean Shape, Solar::Types::Boolean HasElementBuffer);

        // MeshTypes:
        typedef std::vector<Solar::Math::Vector3::D32>  MeshVertices;
        typedef std::vector<Solar::Math::Vector3::D32>  MeshColors;
        typedef std::vector<Solar::Math::Vector2::D32>  MeshTextureMap;
        typedef std::vector<Solar::Types::Integer>      MeshIndices;

        // MeshBasics:
        struct MeshAttributes
        {
            Solar::Math::Vector3::I64 position  { 0, 0, 0 };
            Solar::Math::Vector3::I32 size      { 1, 1, 1 };
            Solar::Math::Vector3::U16 rotation  { 0, 0, 0 };
            Solar::Math::Color4       color     { 0, 0, 0, 255 };
            glm::mat4 GetMeshMatrix();
            Solar::Types::U32 GetPackedColor4();
        };

        // Mesh:
        class Mesh : public Solar::Shapes::MeshAttributes
        {
            private:
            Solar::GL::VertexBufferObject   vbo;
            Solar::GL::VertexAttribObject   vao;
            Solar::GL::ElementBufferObject  ebo;
            Solar::Types::U64 buffer_size = 0;
            Solar::Types::U64 indices = 0;

            public:
            Solar::Types::U8 attributes = 0;

            // LoadMesh: this function will automatically decide the stride and other
            // OpenGL buffer operations. Keep in mind this defines an GL_STATIC_DRAW
            // and it is supposed to only be called ONCE!
            void LoadMesh(
                const Solar::Shapes::MeshVertices      vertices,
                const Solar::Shapes::MeshColors        colors,
                const Solar::Shapes::MeshTextureMap    texture_map,
                const Solar::Shapes::MeshIndices       indices
            );
            
            void Draw(Solar::Core::Storage::Shader *using_shader);
            void UnloadMesh();
        };
    };
};

#endif
// Solar/Shapes/RawMesh.hxx: