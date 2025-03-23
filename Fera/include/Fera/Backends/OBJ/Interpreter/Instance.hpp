#ifndef FeraBackendsOBJInterpreterInstance_hpp
#define FeraBackendsOBJInterpreterInstance_hpp

#include "Logica/Logica.hpp"
#include "Fera/Types.hpp"
#include "Fera/Meshing.hpp"

#include "Fera/Backends/OBJ/Interpreter/Properties.hpp"

/*
 * NOTE: for convenience, the <group>.<object> is all inside an simple object on the OBJ
 * parser, why? because we ONLY have this hierachical structure. That means we have an extra
 * work to do after the parsing that is mounting the MeshUnit system. 
 */

namespace Fera
{
    namespace Backends
    {
        namespace OBJ
        {
            namespace Interpreter
            {
                /// @brief The lists for the indexes that are required in OBJ.
                namespace InstanceLists
                {
                    typedef std::vector<Fera::Types::F32> AnyDimensionVector;
                    typedef std::vector<
                        Fera::Backends::OBJ::Interpreter::InstanceLists::AnyDimensionVector
                    > GenericAnyDimensionVectorList;
                    typedef std::vector<
                        Fera::Backends::OBJ::Interpreter::InstanceLists::AnyDimensionVector
                    > V;
                    typedef std::vector<
                        Fera::Backends::OBJ::Interpreter::InstanceLists::AnyDimensionVector
                    > VT;
                    typedef std::vector<
                        Fera::Backends::OBJ::Interpreter::InstanceLists::AnyDimensionVector
                    > VN;
                };

                /// @brief Contains all the states of the interpreter.
                namespace InstanceStates
                {
                    enum InstanceStates
                    {
                        Running = 0,
                        Finished,
                        Died
                    };
                };

                namespace InstanceErrors
                {
                    enum InstanceErrors
                    {
                        Ok = 0,

                        /// @brief For when you are drunk and you put the wrong opcode or the opcode
                        /// is not implemented (or even acknowledged by the Fera OBJ Backend).
                        InvalidOpcode,

                        /// @brief For when an opcode exists BUT it is not implemented.
                        UnimplementedOpcode,

                        /// @brief For when the tokenizer ended too early.
                        EarlyEnd,

                        /// @brief When a object was already defined, if the property is set to not
                        /// override objects, then this error will be done!
                        DuplicatedObject,

                        /// @brief Invalid face is when you have for example: f 10.2
                        InvalidFaceIndex,

                        /// @brief For when a index is not defined, like f 10 but there are only 9
                        /// vertices, so face 10 is not existant.
                        NotDefinedIndex,

                        /// @brief for errors that are impossible.
                        Unknown = UINT8_MAX
                    };
                };

                /// @brief The OBJ interpreter itself.
                struct Instance
                {
                    /* Logica Tokenizer: */
                    Logica::Texting::Tokenizer::Instance tokenizer;
                    Logica::Texting::Tokenizer::Rules tokenizer_rules;

                    /* Lists: */
                    Fera::Backends::OBJ::Interpreter::InstanceLists::V  current_V;
                    Fera::Backends::OBJ::Interpreter::InstanceLists::VT current_VT;
                    Fera::Backends::OBJ::Interpreter::InstanceLists::VN current_VN;

                    /* Group/Object */
                    Fera::Types::String current_group;
                    Fera::Types::String current_object;

                    /* Current Node, assuming everything has a root, then use this as root for
                     * our tree. The working unit will be the other point.
                     */
                    Fera::Meshing::Mesh* root;
                    Fera::Meshing::MeshUnitTypes::Object working_object;

                    /* Status: */
                    Logica::Control::Validator validator;
                    Fera::Types::U8 state;

                    /* Properties: */
                    Fera::Backends::OBJ::Interpreter::Properties properties;
                };
                Fera::Backends::OBJ::Interpreter::Instance InstanceNew();
                void InstanceDestroy(
                    Fera::Backends::OBJ::Interpreter::Instance* instance
                );
                void InstanceInit(
                    Fera::Backends::OBJ::Interpreter::Instance* instance,
                    Logica::Types::Buffer::Base* buffer
                );
                void InstanceStep(
                    Fera::Backends::OBJ::Interpreter::Instance* instance
                );
                void InstanceParse(
                    Fera::Backends::OBJ::Interpreter::Instance* instance
                );
                void InstanceGenerateObject(
                    Fera::Backends::OBJ::Interpreter::Instance* instance
                );
                void InstanceSetProperty(
                    Fera::Backends::OBJ::Interpreter::Instance* instance,
                    Fera::Backends::OBJ::Interpreter::Properties properties
                );
                Fera::Meshing::Mesh* InstanceGetMesh(
                    Fera::Backends::OBJ::Interpreter::Instance* instance
                );
            };
        };
    };
};

#endif