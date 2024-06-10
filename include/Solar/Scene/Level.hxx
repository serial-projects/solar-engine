#ifndef solar_scene_level_hxx
#define solar_scene_level_hxx

#include "Solar/GL.hxx"
#include "Solar/Math/Vector3.hxx"
#include "Solar/Scene/Tile.hxx"
#include "Solar/Shapes/Cube.hxx"
#include "Solar/Types.hxx"

namespace Solar
{
    namespace Scene
    {
        class Level
        {
            public:
            Solar::Scene::TileRecipes recipes;
            Solar::Scene::Tiles list;
            
            void Init();
            void Tick();
            void Draw();
        };
    };
};

#endif
// Solar/Scene/Level.hxx: