#ifndef FeraBackendsOBJDecode_hpp
#define FeraBackendsOBJDecode_hpp

#include "Fera/Types.hpp"

namespace Fera
{
    namespace Backends
    {
        namespace OBJ
        {
            class Decode
            {
                public:
                    Decode();
                    ~Decode();

                    /**
                     * \brief The decoder needs an buffer to decode the OBJ raw file, this is done
                     * by setting using this function.
                     */
                    void SetBuffer(Logica::Types::Stream::Buffer* buffer);
                private:
                    
            };
        };
    };
};

#endif