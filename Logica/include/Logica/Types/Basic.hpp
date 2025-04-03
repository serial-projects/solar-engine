#ifndef LogicaTypesBasic_hpp
#define LogicaTypesBasic_hpp

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

namespace Logica
{
    namespace Types
    {
        namespace Basic
        {
            /* Basic Integers: */
            typedef std::uint8_t        U8;
            typedef std::int8_t         I8;
            typedef std::uint16_t       U16;
            typedef std::int16_t        I16;
            typedef std::uint32_t       U32;
            typedef std::int32_t        I32;
            typedef std::uint64_t       U64;
            typedef std::int64_t        I64;
            
            /* Character Types: */
            typedef char                CH8;
            typedef char16_t            CH16;
            typedef char32_t            CH32;

            /* Customizable Types: */
            typedef std::size_t         Size;

            /* Basic Decimals: */
            typedef float               F32;
            typedef double              F64;

            /* Booleans: */
            typedef bool                Result;
            typedef bool                Boolean;
            
            /* More Advanced Types: */
            typedef std::string         String;
        };
    };
};

#endif