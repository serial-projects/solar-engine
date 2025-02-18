#ifndef SolarTypesGLM_hpp
#define SolarTypesGLM_hpp

#include "Progator/Progator.hpp"

// Just some code to redirect Progator's GLM types to Solar's GLM:

namespace Solar
{
    namespace Types
    {
        namespace GLM
        {
            typedef Progator::Types::GLM::Vector4   Vector4;
            typedef Progator::Types::GLM::Vector3   Vector3;
            typedef Progator::Types::GLM::Vector2   Vector2;
            typedef Progator::Types::GLM::Matrix44  Matrix44;
            typedef Progator::Types::GLM::Matrix33  Matrix33;
            typedef Progator::Types::GLM::Matrix22  Matrix22;
        };
    };
};

#endif