#ifndef SojsonNodeGet_hpp
#define SojsonNodeGet_hpp

#include "Sojson/Node/Structure.hpp"
#include "Sojson/Types.hpp"

namespace Sojson
{
    typedef std::vector<Sojson::Types::String> NodePath;
    Sojson::Node* NodeGet(Sojson::Node* node, const Sojson::NodePath& node_path);
    Sojson::Node* NodeGet(Sojson::Node* node, const Sojson::Types::String& key);
    Sojson::Node* NodeGet(Sojson::Node* node, const Sojson::Types::CH8* key);
};

#endif