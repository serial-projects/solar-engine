#ifndef SolarSupportDotObjLoader_hpp
#define SolarSupportDotObjLoader_hpp

#include "Solar/Support/DotObj/Text.hpp"
#include "Progator/Progator.hpp"

namespace Solar
{
    namespace Support
    {
        namespace DotObj
        {
            Solar::Support::DotObj::Interpreter* InterpreterLoadFromBuffer(Solar::String* buffer);
            Solar::Support::DotObj::Interpreter* InterpreterLoadFromFile(const Solar::String file);
            
            /* DotObj::Interpreter -> MeshTable is T[Solar::String]=Progator::Mesh */
            typedef std::unordered_map<Solar::String, Progator::Mesh*> MeshTable;
            Solar::Support::DotObj::MeshTable* InterpreterBuildMeshTable(Solar::Support::DotObj::Interpreter* interpreter, Progator::Pointers* pointers, Progator::Validator* validator);
            void InterpreterDeleteBuiltMeshTable(Solar::Support::DotObj::MeshTable* mesh_table);
        };
    };
};

#endif