#include "Solar/Support/DotObj/Loader.hpp"
#include "Solar/Support/FS.hpp"

#include <iostream>

Solar::Support::DotObj::Interpreter* Solar::Support::DotObj::InterpreterLoadFromBuffer(
    Solar::String* buffer
)
{
    Solar::Support::DotObj::Interpreter* interpreter_instance =
        Solar::Support::DotObj::InterpreterNew();
    Solar::Support::DotObj::Validator* validator =
        Solar::Support::DotObj::ValidatorNew();
    Solar::Support::DotObj::InterpreterInit(interpreter_instance, validator, buffer);
    
    /* begin parsing: */
    while(interpreter_instance->state == Running)
        Solar::Support::DotObj::InterpreterStep(interpreter_instance);
    
    /* if failure then std::abort(), this is just for debug: */
    if(validator->state == Failed)
    {
        std::cerr
            << __PRETTY_FUNCTION__
            << ": failed to load object file due: "
            << validator->log
            << "\n";
        std::abort();
    }

    return interpreter_instance;
}

Solar::Support::DotObj::Interpreter* Solar::Support::DotObj::InterpreterLoadFromFile(
    const Solar::String file
)
{
    Solar::String buffer = Solar::Support::LoadFile(file.c_str());
    return Solar::Support::DotObj::InterpreterLoadFromBuffer(&buffer);
}

/* DotObj::Interpreter -> MeshTable is T[Solar::String]=Progator::Mesh */
static Progator::Mesh* BuildProgatorMesh(
    std::vector<Solar::F32>* constructed_buffer,
    Progator::Pointers* pointers,
    Progator::Validator* validator
)
{
    Progator::Mesh* working_mesh =
        Progator::MeshNew();
    Progator::MeshInit(working_mesh, pointers, validator);

    /* build vertex, texture map and normals: */
    std::cout
        << __PRETTY_FUNCTION__
        << ": loading to buffer: "
        << constructed_buffer->size()
        << " floats.\n";

    Progator::MeshLoadVerTexNor(
        working_mesh,
        constructed_buffer->data(),
        constructed_buffer->size() / (3 + 2 + 3)
    );

    /* done: */
    return working_mesh;
}

Solar::Support::DotObj::MeshTable* Solar::Support::DotObj::InterpreterBuildMeshTable(
    Solar::Support::DotObj::Interpreter* interpreter,
    Progator::Pointers* pointers,
    Progator::Validator* validator
)
{
    Solar::Support::DotObj::MeshTable* mesh_table = new
        Solar::Support::DotObj::MeshTable;
    for(auto &value : interpreter->objects)
        mesh_table->insert(
            {
                value.first,
                BuildProgatorMesh(&value.second->constructed_buffer, pointers, validator)
            }
        );
    return mesh_table;
}

void Solar::Support::DotObj::InterpreterDeleteBuiltMeshTable(
    Solar::Support::DotObj::MeshTable* mesh_table
)
{
    for(auto &value : *mesh_table)
        Progator::MeshDestroy(value.second);
    delete mesh_table;
}