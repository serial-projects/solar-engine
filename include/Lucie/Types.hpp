#ifndef LucieTypes_hpp
#define LucieTypes_hpp

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

namespace Lucie
{
    /* FOR LUCIE DATA: */
    typedef     std::int32_t    Integer;
    typedef     float           Decimal;
    typedef     std::string     String;
    typedef     std::uint8_t    Boolean;

    /* FOR LUCIE: */
    typedef     std::uint8_t    PackedData8;
    typedef     std::uint8_t    U8;
    typedef     std::uint32_t   U32;

    typedef     char            Character;
    typedef     std::uint32_t   Indexer;
};

#endif