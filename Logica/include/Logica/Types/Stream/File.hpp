#ifndef LogicaTypesStreamFile_hpp
#define LogicaTypesStreamFile_hpp

#include "Logica/Types/Basic.hpp"
#include "Logica/Types/Stream/Buffer.hpp"

namespace Logica
{
    namespace Types
    {
        namespace Stream
        {
            class FileUnit
            {
                private:
                std::FILE*                      file;
                Logica::Types::Basic::Size      position;
                public:
                
                FileUnit();

                void AssignFile(
                    std::FILE* file
                );
                
                void CloseFile();

                Logica::Types::Basic::Result IsOpen();
                
                Logica::Types::Basic::Size GetPosition();
                
                void SetPosition(
                    const Logica::Types::Basic::Size position
                );
                
                Logica::Types::Basic::I32 GetCharacter();
            };

            class File : public Logica::Types::Stream::Buffer
            {
                private:
                Logica::Types::Stream::FileUnit*    unit;
                
                void BuildInterfaceUsingFile(
                    std::FILE* file
                );

                public:
                File();
                
                ~File();

                Logica::Types::Basic::Result SetFile(
                    const Logica::Types::Basic::String& file
                );

                void UnsetFile();
            };
        };
    };
};

#endif