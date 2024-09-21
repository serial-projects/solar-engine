#ifndef SolarTypes_hpp
#define SolarTypes_hpp

#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

#include "Progator/Types.hpp"

namespace Solar
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

    /* PROGATOR - SOLAR TYPES: */
    typedef Progator::Matrix44 Matrix44;
    typedef Progator::Matrix33 Matrix33;
    typedef Progator::Matrix22 Matrix22;
    typedef Progator::Vector4 Vector4;
    typedef Progator::Vector3 Vector3;
    typedef Progator::Vector2 Vector2;
};

#endif