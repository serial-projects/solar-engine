#ifndef SolarSceneLevel_hpp
#define SolarSceneLevel_hpp

#include "Solar/Scene/Model.hpp"
#include "Solar/Types.hpp"
#include "Solar/Core.hpp"
#include "Solar/Scene/Camera.hpp"
#include "Solar/Scene/Level.hpp"

#include "Progator/Progator.hpp"

namespace Solar
{
    namespace Scene
    {
        namespace LevelProperties
        {
            /* TODO: implement this: */
        };

        enum LevelDebugStates
        {
            WireframeMode   = 0b10000000,
            Version         = 0b01000000
        };

        typedef struct Level
        {
            Solar::Core*                linked_core;
            Solar::Scene::FreeCamera    camera;
            Solar::U8                   debug_states = 0;
            Solar::Scene::Model*        root_model;

            /* NOTE: keep in mind that the Solar Engine is an voxel based
             * engine without many voxels optimizations ;-)
             */
            Progator::Shader*   basic_voxel_shader;
            Progator::Mesh*     basic_voxel_mesh;
            Progator::Texture*  basic_voxel_texture;

            Solar::Vector3      basic_sun;
        } Level;

        Solar::Scene::Level* LevelNew();
        void LevelDestroy(Solar::Scene::Level* level);
        void LevelInit(Solar::Scene::Level* level, Solar::Core *core);
        void LevelTick(Solar::Scene::Level* level);
        void LevelDraw(Solar::Scene::Level* level);
        void LevelQuit(Solar::Scene::Level* level);
    };
};

#endif