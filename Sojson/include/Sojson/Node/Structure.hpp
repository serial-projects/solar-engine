#ifndef SojsonNodeStructure_hpp
#define SojsonNodeStructure_hpp

// Include the Logica Types here and all the Logica Infraestructure.
#include "Logica/Logica.hpp"
#include "Sojson/Types.hpp"
#include <vector>
#include <unordered_map>

namespace Sojson
{
    /// @brief All the types for the Node.
    namespace NodeTypes
    {
        enum NodeTypes
        {
            Null,
            Integer, 
            Decimal,
            String,
            Boolean,
            List,
            Table
        };
    };

    /// @brief Node is a container for the dynamic objects that an JSON has.
    struct Node
    {
        void* value;
        Sojson::Types::U8 type;
    };

    /// @brief Create an new node on heap.
    /// @return return the node pointer.
    Sojson::Node* NodeNew();

    /// @brief Destroy the node and all the possible values included.
    /// @param node the node to be destroyed.
    void NodeDestroy(Sojson::Node* node);

    /// @brief Initialize the node.
    /// @param node the node to be initialized.
    /// @param value the value (must be void* converted already).
    /// @param type the type of the node, see Sojson::NodeTypes::<ValueType>
    void NodeInit(Sojson::Node* node, void* value, const Logica::Types::Basic::U8 type);

    /// @brief Inside each Sojson::Node, an RepresentativeValue is there defined by the type,
    /// that is, on the json file, you have multiple types possible and since we are on a static
    /// typed language, we need to declare it here.
    namespace RepresentativeTypes
    {
        #ifdef  SOJSON_FORCE_64BITS_INTEGER
            typedef Logica::Types::Basic::I64   Integer;
        #else
            typedef Logica::Types::Basic::I32   Integer;
        #endif

        #ifdef  SOJSON_FORCE_64BITS_DECIMAL
            typedef Logica::Types::Basic::F64   Decimal;
        #else
            typedef Logica::Types::Basic::F32   Decimal;
        #endif

        typedef Logica::Types::Basic::U8        Boolean;
        typedef Logica::Types::Basic::String    String;
        typedef std::vector<Sojson::Node*>      List;
        typedef std::unordered_map<Logica::Types::Basic::String, Sojson::Node*> Table;
    };
};

#endif