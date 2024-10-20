#include "Solar/Scene/Model.hpp"

Solar::Scene::Model* Solar::Scene::ModelNew()
{
    Solar::Scene::Model* proto = new
        Solar::Scene::Model;
    return proto;
}

void Solar::Scene::ModelDestroy(Solar::Scene::Model* model)
{
    delete model;
}

static void ModelCalculateModelMatrix(Solar::Scene::Model* model)
{
    /* TODO: implement rotation: */
    model->model_matrix = Solar::Matrix44(1.0f);
    model->model_matrix = glm::translate(model->model_matrix, model->position);
    model->model_matrix = glm::scale(model->model_matrix, Progator::Vector3(1.0f, 1.0f, 1.0f));
}

void Solar::Scene::ModelInit(Solar::Scene::Model* model, Solar::Core* core)
{
    /* set the model to render: */
    model->linked_core = core;
    
    /* set the model transformations: */
    model->position = Solar::Vector3(0.0f);
    model->size     = Solar::Vector3(1.0f);
    model->rotation = Solar::Vector3(0.0f);
    ModelCalculateModelMatrix(model);

    /* set the current mesh, shader and texture to NULL: */
    model->current_mesh     = nullptr;
    model->shader           = nullptr;
    model->texture          = nullptr;
}

void Solar::Scene::ModelLoadShader(Solar::Scene::Model* model, const Solar::String tag_name)
{
    model->shader = Solar::Engine::ProviderLoadShader(model->linked_core->provider, tag_name);
}

void Solar::Scene::ModelLoadTexture(Solar::Scene::Model* model, const Solar::String tag_name)
{
    model->texture = Solar::Engine::ProviderLoadTexture(model->linked_core->provider, tag_name);
}

void Solar::Scene::ModelLoadMesh(Solar::Scene::Model* model, const Solar::String path)
{
    /* DO IT HERE: */
    Solar::Support::DotObj::Interpreter* interpreter =
        Solar::Support::DotObj::InterpreterLoadFromFile(path);
    Solar::Support::DotObj::MeshTable* mesh_table = 
        Solar::Support::DotObj::InterpreterBuildMeshTable(
            interpreter, 
            model->linked_core->pointers,
            model->linked_core->validator
        );
    
    model->loaded_meshes = mesh_table;
    model->current_mesh  = model->loaded_meshes->at("main");
}

void Solar::Scene::ModelDraw(Solar::Scene::Model* model)
{
    if(model->current_mesh != nullptr)
    {
        if(model->shader != nullptr)
        {
            Progator::ShaderSUMatrix44(model->shader, "SolarModelMatrix", model->model_matrix);
            Progator::ShaderUse(model->shader);
        }
        if(model->texture != nullptr)
        {
            Progator::TextureUse(model->texture);
        }
        Progator::MeshDraw(model->current_mesh);
    }
}

void Solar::Scene::ModelDrawEverything(Solar::Scene::Model* model)
{
    if(model->shader != nullptr)
    {
        Progator::ShaderSUMatrix44(model->shader, "SolarModelMatrix", model->model_matrix);
        Progator::ShaderUse(model->shader);
    }
    if(model->texture != nullptr)
    {
        Progator::TextureUse(model->texture);
    }
    for(auto &value : *model->loaded_meshes)
    {
        Progator::MeshDraw(value.second);
    }
}