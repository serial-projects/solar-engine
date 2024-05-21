#ifndef solar_types_hxx
#define solar_types_hxx

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>

namespace Solar
{
    // The primitive/dynamic types that are going to be used/derived to other types
    // on the entire engine! This is important to keep in mind future portability to
    // other platforms.
    namespace Types
    {
        typedef std::uint8_t    U8;     typedef std::int8_t     I8;
        typedef std::uint16_t   U16;    typedef std::int16_t    I16;
        typedef std::uint32_t   U32;    typedef std::int32_t    I32;
        typedef std::uint64_t   U64;    typedef std::int64_t    I64;
        typedef char            Character;
        typedef int             Integer;
        typedef double          D64;
        typedef float           D32;
        typedef std::string     String;
        typedef bool            Result;
        typedef bool            Boolean;
    };
};

#endif
// Solar/Types.hxx: