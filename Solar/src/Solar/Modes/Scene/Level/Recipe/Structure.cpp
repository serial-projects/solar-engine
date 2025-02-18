#include "Solar/Modes/Scene/Level/Recipe/Structure.hpp"

Solar::Modes::Scene::LevelRecipe* Solar::Modes::Scene::LevelRecipeNew()
{
    Solar::Modes::Scene::LevelRecipe* recipe =
        new Solar::Modes::Scene::LevelRecipe;
    return recipe;
}

void Solar::Modes::Scene::LevelRecipeDestroy(
    Solar::Modes::Scene::LevelRecipe* recipe
)
{
    delete recipe;
}

void Solar::Modes::Scene::LevelRecipeInit(
    Solar::Modes::Scene::LevelRecipe* recipe
)
{
    /* TODO: don't do anything here, this is just to initialize something. */
    recipe->Meshes  = Solar::Modes::Scene::LevelRecipeTypes::MeshUnits();
    recipe->Shaders = Solar::Modes::Scene::LevelRecipeTypes::ShaderUnits();
}