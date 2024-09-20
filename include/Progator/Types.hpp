#ifndef ProgatorTypes_hpp
#define ProgatorTypes_hpp

#include <string>
#include <vector>
#include <cstdint>

#include "Progator/Support/Math.hpp"

namespace Progator
{
    /* BASIC TYPES: */
    typedef std::uint8_t    U8;
    typedef std::int8_t     I8;
    typedef std::uint16_t   U16;
    typedef std::int16_t    I16;
    typedef std::uint32_t   U32;
    typedef std::int32_t    I32;
    typedef std::uint64_t   U64;
    typedef std::int64_t    I64;
    typedef float           F32;
    typedef double          F64;
    typedef char            Character;
    typedef std::uint32_t   RGBA84;
    typedef std::string     String;

    /* GLM: */
    typedef glm::mat4       Matrix44;
    typedef glm::mat3       Matrix33;
    typedef glm::mat2       Matrix22;
    typedef glm::vec4       Vector4;
    typedef glm::vec3       Vector3;
    typedef glm::vec2       Vector2;
};

#endif