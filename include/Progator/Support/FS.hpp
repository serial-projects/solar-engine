#ifndef ProgatorSupportFS_hpp
#define ProgatorSupportFS_hpp

#include "Progator/Types.hpp"

namespace Progator
{
    namespace Support
    {
        typedef Progator::Character* FileBuffer;
        Progator::Support::FileBuffer FileBufferGet(const Progator::Character* path);
        void FileBufferDestroy(Progator::Support::FileBuffer buffer);
    };
};

#endif