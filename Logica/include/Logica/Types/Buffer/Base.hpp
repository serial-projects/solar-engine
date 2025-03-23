#ifndef LogicaTypesBufferBase_hpp
#define LogicaTypesBufferBase_hpp

#include "Logica/Types/Basic.hpp"
#include <functional>

namespace Logica
{
    namespace Types
    {
        namespace Buffer
        {
            class Base
            {
                public:
                    typedef std::function<void(void*)>                                              InitCallbackFunctionType;
                    typedef std::function<void(void*, const Logica::Types::Basic::Size)>            SetPositionCallbackFunctionType;
                    typedef std::function<Logica::Types::Basic::Size(void*)>                        GetPositionCallbackFunctionType;
                    typedef std::function<Logica::Types::Basic::I32(void*)>                         GetCharacterCallbackFunctionType;
                    typedef std::function<void(void*)>                                              CloseCallbackFunctionType;

                    /* initialize: */
                    Base();
                    ~Base();
            
                    /* Assignment Functions: */
                    void AssignInitCallback(InitCallbackFunctionType initf);
                    void AssignSetPositionCallback(SetPositionCallbackFunctionType setpf);
                    void AssignGetPositionCallback(GetPositionCallbackFunctionType getpf);
                    void AssignGetCharacterCallback(GetCharacterCallbackFunctionType getchf);
                    void AssignCloseCallback(CloseCallbackFunctionType closef);
                    void AssignUserData(void* userdata);
            
                    /* Buffer Functions: */
                    void Init();
                    void SetPosition(const Logica::Types::Basic::Size position);
                    Logica::Types::Basic::Size GetPosition();
                    Logica::Types::Basic::I32 GetCharacter();
                    void Close();
                private:
                    InitCallbackFunctionType            __init_f;
                    SetPositionCallbackFunctionType     __set_position_f;
                    GetPositionCallbackFunctionType     __get_position_f;
                    GetCharacterCallbackFunctionType    __get_character_f;
                    CloseCallbackFunctionType           __close_f;
                    void* userdata;
            };
        };
    };
};

#endif