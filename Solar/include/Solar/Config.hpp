#ifndef SolarConfig_hpp
#define SolarConfig_hpp

// General Information
#define SOLAR_VERSION                   10000
#define SOLAR_VERSION_STR               "1.0.000"
#define SOLAR_VERSION_NAME              "Ghost"
#define SOLAR_VERSION_FULL              "Solar RPG Engine, v." SOLAR_VERSION_STR ", or: \"" SOLAR_VERSION_NAME "\"" 

// Solar/Modes/Scene/Components/Events.hpp:

// SOLAR_MODES_SCENE_COMPONENTS_EVENTS_SIZE: defines the size of the
// Solar::Modes::Scene::Components::Events vector, it holds an SDL_Event to the entire project.
#define SOLAR_MODES_SCENE_COMPONENTS_EVENTS_SIZE                        UINT8_MAX

// Solar/Core/Provider/Load/Mesh.hpp:

// SOLAR_CORE_PROVIDER_LOAD_MESH_FSIZE_DEFAULT: the default amount of faces expected on the OBJ
// file, (aka, the f opcode);
#define SOLAR_CORE_PROVIDER_LOAD_MESH_OBJ_FSIZE_DEFAULT     3

// SOLAR_CORE_PROVIDER_LOAD_MESH_VSIZE_DEFAULT: the default amount of vertices expected on the OBJ.
#define SOLAR_CORE_PROVIDER_LOAD_MESH_OBJ_VSIZE_DEFAULT     3

// SOLAR_CORE_PROVIDER_LOAD_MESH_VTSIZE_DEFAULT: the default amount of texture vertices expected
// on the OBJ.
#define SOLAR_CORE_PROVIDER_LOAD_MESH_OBJ_VTSIZE_DEFAULT    2

// SOLAR_CORE_PROVIDER_LOAD_MESH_VNSIZE_DEFAULT: the default amount of normals expected on the OBJ.
#define SOLAR_CORE_PROVIDER_LOAD_MESH_OBJ_VNSIZE_DEFAULT    3

#endif