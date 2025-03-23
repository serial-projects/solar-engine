#ifndef LogicaTypesBufferFile_hpp
#define LogicaTypesBufferFile_hpp

#include "Logica/Types/Buffer/Base.hpp"
#include "Logica/Types/Basic.hpp"

namespace Logica
{
    namespace Types
    {
        namespace Buffer
        {
            /**
             * \brief This is a type of buffer that gets its DATA from files.
             */
            class File : public Logica::Types::Buffer::Base
            {
                private:
                    struct Handler
                    {
                        std::FILE*                      os_connector    = nullptr;
                        Logica::Types::Basic::Size      position        = 0;
                        Logica::Types::Basic::String    path;
                    };
                    Logica::Types::Buffer::File::Handler current_handler;
                public:
                    File();
                    ~File();

                    /**
                     * \brief This function will set an new file on the Handler for the
                     * Init buffer callback to initialize it, THIS FUNCTION WON'T init
                     * the new file access for you and MIGHT trigger some error if you
                     * DON'T run the Init(), also, run Close() to close the file.
                     * 
                     * \return If the file exists.
                     */
                    Logica::Types::Basic::Result SetFile(const Logica::Types::Basic::String& path);
            };
        };
    };
};

#endif