#ifndef FeraBackendsOBJGlobals_hpp
#define FeraBackendsOBJGlobals_hpp

#include "Fera/Types.hpp"

namespace Fera
{
    namespace Backends
    {
        namespace OBJ
        {
            /**
             * \brief This contains all the globals on the OBJ file.
             */
            class Globals
            {
                public:
                    std::vector<Fera::Types::Vector::F32x3> vertices;
                    std::vector<Fera::Types::Vector::F32x3> uv;
                    std::vector<Fera::Types::Vector::F32x3> normals;
            };
        };
    };
};

#endif