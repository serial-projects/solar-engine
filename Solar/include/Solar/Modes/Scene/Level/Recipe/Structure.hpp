#ifndef SolarModesSceneLevelRecipeStructure_hpp
#define SolarModesSceneLevelRecipeStructure_hpp

#include "Solar/Types.hpp"

namespace Solar
{
    namespace Modes
    {
        namespace Scene
        {
            namespace LevelRecipeTypes
            {
                /// @brief Contains everything necessary to the Load::Mesh() call, that is:
                /// the object site, object name (we are omitting the render unit).
                struct MeshUnit
                {
                    Solar::Types::Basic::String site;
                    Solar::Types::Basic::String name;
                };
                
                typedef std::vector<Solar::Modes::Scene::LevelRecipeTypes::MeshUnit>
                    MeshUnits;
                
                /// @brief Contains everything the Load::Shader() call needs.
                struct ShaderUnit
                {
                    Solar::Types::Basic::String site;
                };

                typedef std::vector<Solar::Modes::Scene::LevelRecipeTypes::ShaderUnit>
                    ShaderUnits;
            };

            /// @brief Contains all the information about drawing and more.
            struct LevelRecipe
            {
                Solar::Modes::Scene::LevelRecipeTypes::MeshUnits    Meshes;
                Solar::Modes::Scene::LevelRecipeTypes::ShaderUnits  Shaders;
            };
            
            Solar::Modes::Scene::LevelRecipe* LevelRecipeNew();
            void LevelRecipeDestroy(Solar::Modes::Scene::LevelRecipe* recipe);
            void LevelRecipeInit(Solar::Modes::Scene::LevelRecipe* recipe);
        };
    };
};

#endif