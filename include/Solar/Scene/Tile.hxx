#ifndef solar_scene_tile_hxx
#define solar_scene_tile_hxx

#include "Solar/Math/Vector3.hxx"
#include "Solar/Types.hxx"
#include "Solar/GL.hxx"

namespace Solar
{
    namespace Scene
    {
        struct TileRecipe
        {
            Solar::Math::Vector3::D32 color = {0.0f, 0.0f, 0.0f};
        };
        struct Tile
        {
            public:
            // NOTE: some legends for the acronyms:
            // TTI: Tile Tag ID: this references an tile recipe;
            Solar::Types::U8            TTI = 0;

            // NOTE: position is set on the GRID.
            Solar::Math::Vector3::I16   position = {0, 0, 0};
        };
        typedef std::vector<Solar::Scene::TileRecipe> TileRecipes;
        typedef std::vector<Solar::Scene::Tile> Tiles;
    };
};

#endif
// Solar/Scene/Tile.hxx: