#ifndef LogicaDataFile_hpp
#define LogicaDataFile_hpp

#include "Logica/Types.hpp"

namespace Logica
{
    namespace Data
    {
        namespace File
        {
            /// @brief Opens an file and put everything on the buffer (this function will not take
            /// case of any exception, make sure to have checked the file before hand).
            /// @param file the file path to be open.
            /// @return the buffer containing the file.
            Logica::Types::Basic::String Cat(const Logica::Types::Basic::String& file);

            /// @brief Checks if an file exists.
            /// @param file the file path to test.
            /// @return the result of the operation. 
            Logica::Types::Basic::Result Exists(const Logica::Types::Basic::String& file);
        };
    };
};

#endif