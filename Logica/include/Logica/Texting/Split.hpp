#ifndef LogicaTextingSplit_hpp
#define LogicaTextingSplit_hpp

#include "Logica/Types.hpp"

namespace Logica
{
    namespace Texting
    {
        /**
         * \brief The return of the Split() function.
         */
        typedef std::vector<Logica::Types::Basic::String> SplitResult;

        /**
         * \brief This function takes a string and a separator to generate
         * a list containing the split result.
         */
        Logica::Texting::SplitResult Split(
            Logica::Types::Basic::String& source,
            Logica::Types::Basic::CH8 separator
        );
    };
};

#endif