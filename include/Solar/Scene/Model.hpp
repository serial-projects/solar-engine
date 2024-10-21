#ifndef SolarSceneModel_hpp
#define SolarSceneModel_hpp

/* NOTE: brief explanation on what is a model:
 * Solar Engine's Model has:
 * -> A Loaded Mesh;
 * -> A Attached Shader for Rendering the Mesh;
 * -> A Texture (this can be changed during the sprite change).
 */

#include "Progator/Progator.hpp"
#include "Solar/Core.hpp"
#include "Solar/Types.hpp"
#include "Solar/Support/DotObj/Loader.hpp"

namespace Solar
{
    namespace Scene
    {
        /* ModelProperties: */
        typedef struct ModelProperties
        {
            Solar::U8 flags = 0;
        } ModelProperties;

        /* Model: */
        typedef struct Model
        {
            /* Basic Model Shared Elements: */
            Solar::Core*        linked_core;

            /* Mesh Rendering: */
            Progator::Mesh*                     current_mesh;
            Solar::Support::DotObj::MeshTable*  loaded_meshes;
            
            /* Model Properties: */
            Progator::Shader*   shader;
            Progator::Texture*  texture;

            /* Rendering Properties: */
            Solar::Vector3      position;
            Solar::Vector3      size;
            Solar::Vector3      rotation;

            /* Keep the Model matrix already here to prevent useless calculations: */
            Solar::Matrix44     model_matrix;
        } Model;

        Solar::Scene::Model* ModelNew();
        void ModelDestroy(Solar::Scene::Model* model);
        void ModelInit(Solar::Scene::Model* model, Solar::Core* core);

        /* Load Functions: */
        void ModelLoadShader(Solar::Scene::Model* model, const Solar::String tag_name);
        void ModelLoadTexture(Solar::Scene::Model* model, const Solar::String tag_name);
        void ModelLoadMesh(Solar::Scene::Model* model, const Solar::String tag_name);
        
        /* Drawing Functions: */
        void ModelDraw(Solar::Scene::Model* model);
        void ModelDraw(Solar::Scene::Model* model, Solar::Vector3 position);

        /* Drawing Everything Function: */
        void ModelDrawEverything(Solar::Scene::Model* model);
        void ModelDrawEverything(Solar::Scene::Model* model, Solar::Vector3 position);
    };
};

#endif