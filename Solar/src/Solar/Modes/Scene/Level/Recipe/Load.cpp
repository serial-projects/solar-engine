#include "Solar/Modes/Scene/Level/Recipe/Load.hpp"
#include <iostream>

/*
 * Meshes
 */

inline static void __SolarModesSceneLevelRecipesLoadActualRecipeExtractMeshesPushPair(
    Solar::Modes::Scene::LevelRecipe* recipe,
    Solar::Modes::Scene::Mode* mode,
    Sojson::RepresentativeTypes::List* pair
)
{
    Sojson::Node* site_node     = pair->at(0);
    auto maybe_site             = Sojson::CastNode::String(site_node);
    Sojson::Node* object_node   = pair->at(1);
    auto maybe_object           = Sojson::CastNode::String(object_node);

    /* Begin to form this: */
    Solar::Modes::Scene::LevelRecipeTypes::MeshUnit mesh_unit;
    if(maybe_site.has_value())
        mesh_unit.site          = maybe_site.value();
    else
    {
        /* TODO: use more information and report on the mode validator! */
        std::cout
            << __PRETTY_FUNCTION__
            << ": Failed to load recipe due bad formed pair!\n";
        std::abort();
    }
    
    /* TODO: on the future, enforce an error here: */
    mesh_unit.name              = maybe_object.value_or("*");
}

inline static void __SolarModesSceneLevelRecipesLoadActualRecipeExtractMeshesIterateList(
    Solar::Modes::Scene::LevelRecipe* recipe,
    Solar::Modes::Scene::Mode* mode,
    Sojson::RepresentativeTypes::List* list
)
{
    for(
        Solar::Types::Basic::U16 index = 0;
        index < list->size() && index < UINT16_MAX;
        index++
    )
    {
        Sojson::Node* in_list_node = list->at(index);
        auto maybe_in_list = Sojson::CastNode::List(in_list_node);
        if(maybe_in_list.has_value())
        {
            __SolarModesSceneLevelRecipesLoadActualRecipeExtractMeshesPushPair(
                recipe,
                mode,
                maybe_in_list.value()
            );
        }
        else
        {
            /* TODO: use more information and report on the mode validator! */
            std::cout
                << __PRETTY_FUNCTION__
                << ": Failed to load recipe due bad formed pair!\n";
            std::abort();
        }
    }
}

static void __SolarModesSceneLevelRecipeLoadActualRecipeExtractMeshes(
    Solar::Modes::Scene::LevelRecipe* recipe,
    Solar::Modes::Scene::Mode* mode,
    Sojson::Node* input
)
{
    Sojson::Node* meshes    = Sojson::NodeGet(input, "Meshes");
    auto maybe_meshes       = Sojson::CastNode::List(meshes);
    if(maybe_meshes.has_value())
    {
        /* Expected format:
         * <site>, <object>
         */
        __SolarModesSceneLevelRecipesLoadActualRecipeExtractMeshesIterateList(
            recipe,
            mode,
            maybe_meshes.value()
        );
    }
}

/*
 * Shader:
 */

static void __SolarModesSceneLevelRecipeLoadActualRecipeExtractShaders(
    Solar::Modes::Scene::LevelRecipe* recipe,
    Solar::Modes::Scene::Mode* mode,
    Sojson::Node* input    
)
{
    
}

static void __SolarModesSceneLevelRecipeLoadActualRecipe(
    Solar::Modes::Scene::LevelRecipe* recipe,
    Solar::Modes::Scene::Mode* mode,
    Sojson::Node* input
)
{
    __SolarModesSceneLevelRecipeLoadActualRecipeExtractMeshes(
        recipe,
        mode,
        input
    );
}

void Solar::Modes::Scene::LevelRecipeLoad(
    Solar::Modes::Scene::LevelRecipe* recipe,
    Solar::Modes::Scene::Mode* mode,
    const Solar::Types::Basic::String& site,
    const Solar::Types::Basic::String& name
)
{
    Sojson::Node* recipe_file = 
        Solar::Core::Provider::Load::DataFile(
            &mode->shared->warehouse,
            site
        );
    /* check inside the file: */
    Sojson::Node* actual_recipe =
        Sojson::NodeGet(recipe_file, name);
}