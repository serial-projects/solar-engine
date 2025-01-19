#ifndef LogicaDataString_hpp 
#define LogicaDataString_hpp

#include "Logica/Types/Basic.hpp"

namespace Logica
{ 
    namespace Data
    {
        namespace String
        {
            /// @brief Result of SplitBase or Split functions.
            typedef std::vector<Logica::Types::Basic::String> SplitResult;

            /// @brief Split will read an string and split considering the delimiter.
            /// @tparam IndexVariableType   for customized index loop.
            /// @tparam IndexVariableLimit  the max the index can index.
            /// @param e                    string to be spliten;
            /// @param delimiter            the delimiter that will be considered;
            /// @return                     result of the split.
            template <typename IndexVariableType, IndexVariableType IndexVariableLimit>
            Logica::Data::String::SplitResult SplitBase(const Logica::Types::Basic::String& e, const Logica::Types::Basic::CH8 delimiter);

            /// @brief Split will use SplitBase<Solar::U16, UINT16_MAX> for indexing! 
            /// @param e            string to be spliten;
            /// @param delimiter    the delimiter that will be considered;
            /// @return             result of the split;
            Logica::Data::String::SplitResult Split(const Logica::Types::Basic::String& e, const Logica::Types::Basic::CH8 delimiter);
        };
    };
};

#endif