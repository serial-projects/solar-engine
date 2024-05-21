#ifndef solar_scene_level_hxx
#define solar_scene_level_hxx

#include "Solar/Components/Cube.hxx"
#include "Solar/Types.hxx"
#include "Solar/GL.hxx"

namespace Solar
{
    namespace Scene
    {
        typedef std::vector<Solar::Types::U8> TileList;
        class Level
        {
            public:
            Solar::Scene::TileList tiles;
            void Init();
            void Tick();
            void Draw();
        };
    };
};

#endif
// Solar/Scene/Level.hxx: