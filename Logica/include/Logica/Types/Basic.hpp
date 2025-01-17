#ifndef LogicaTypesBasic_hpp
#define LogicaTypesBasic_hpp

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace Logica
{
    namespace Types
    {
        namespace Basic
        {
            typedef std::uint8_t                U8;
            typedef std::uint16_t               U16;
            typedef std::uint32_t               U32;
            typedef std::uint64_t               U64;
            typedef std::int8_t                 I8;
            typedef std::int16_t                I16;
            typedef std::int32_t                I32;
            typedef std::int64_t                I64;
            typedef float                       F32;
            typedef double                      F64;
            typedef char                        CH8;
            typedef std::string                 String;
            typedef bool                        Boolean;
            typedef bool                        Result;

            /* CUSTOMIZABLE: */
            typedef Logica::Types::Basic::U32   Size;
        };
    };
};

#endif