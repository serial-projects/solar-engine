#ifndef LogicaTypesFunctions_hpp
#define LogicaTypesFunctions_hpp

namespace Logica
{
    namespace Types
    {
        namespace Functions
        {
            template<typename RootStructure>
            void(*CallbackFunction)(RootStructure* base, void*userdata);
        };
    };
};

#endif