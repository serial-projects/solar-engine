#ifndef LucieTypes_hpp
#define LucieTypes_hpp

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

namespace Lucie
{
    /* FOR LUCIE DATA: */
    typedef     std::int32_t    Integer;
    typedef     float           Decimal;
    typedef     std::string     String;
    typedef     std::uint8_t    Boolean;

    /* FOR LUCIE: */
    typedef     std::uint8_t    U8;
    typedef     std::uint16_t   U16;
    typedef     std::uint32_t   U32;
    typedef     std::uint64_t   U64;

    typedef     std::int8_t     I8;
    typedef     std::int16_t    I16;
    typedef     std::int32_t    I32;
    typedef     std::int64_t    I64;

    typedef     char            Character;
    typedef     std::uint32_t   Indexer;
};

#endif