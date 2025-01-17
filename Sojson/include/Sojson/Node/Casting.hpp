#ifndef SojsonNodeCasting_hpp
#define SojsonNodeCasting_hpp

#include "Sojson/Node/Structure.hpp"
#include <optional>

namespace Sojson
{
    /// @brief Due the nature of C++ being statically type, just: integer, decimal, string and
    /// boolean are cast(able) since List and Table are just containers for Sojson::Node*, the
    /// List and Table is Sojson::NodeGet() function! Also, all the CastNode are optional.
    namespace CastNode
    {
        std::optional<Sojson::RepresentativeTypes::Integer> Integer(Sojson::Node* node);
        std::optional<Sojson::RepresentativeTypes::Decimal> Decimal(Sojson::Node* node);
        std::optional<Sojson::RepresentativeTypes::String> String(Sojson::Node* node);
        std::optional<Sojson::RepresentativeTypes::Boolean> Boolean(Sojson::Node* node);
    };
};

#endif