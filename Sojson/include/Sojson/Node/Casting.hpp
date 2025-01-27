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
        /// @brief Those types don't indicate an certain, they can only be POSSIBLY this, not that
        /// they are the types (all the types are std::optional<>)
        namespace Possibly
        {
            typedef std::optional<Sojson::RepresentativeTypes::Integer> Integer;
            typedef std::optional<Sojson::RepresentativeTypes::Decimal> Decimal;
            typedef std::optional<Sojson::RepresentativeTypes::String> String;
            typedef std::optional<Sojson::RepresentativeTypes::Boolean> Boolean;
        };

        Sojson::CastNode::Possibly::Integer Integer(Sojson::Node* node);
        Sojson::CastNode::Possibly::Decimal Decimal(Sojson::Node* node);
        Sojson::CastNode::Possibly::String String(Sojson::Node* node);
        Sojson::CastNode::Possibly::Boolean Boolean(Sojson::Node* node);
    };
};

#endif