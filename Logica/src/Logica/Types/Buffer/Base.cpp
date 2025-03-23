#include "Logica/Types/Buffer/Base.hpp"

Logica::Types::Buffer::Base::Base()
{
    this->__init_f          = InitCallbackFunctionType();
    this->__set_position_f  = SetPositionCallbackFunctionType();
    this->__get_position_f  = GetPositionCallbackFunctionType();
    this->__get_character_f = GetCharacterCallbackFunctionType();
    this->__close_f         = CloseCallbackFunctionType();
    this->userdata          = nullptr;
}

Logica::Types::Buffer::Base::~Base()
{
    /* TODO: Don't do nothing here anyway: */
}

/* Assignment Functions: */
void Logica::Types::Buffer::Base::AssignInitCallback(InitCallbackFunctionType initf)                    { this->__init_f            = initf;}
void Logica::Types::Buffer::Base::AssignSetPositionCallback(SetPositionCallbackFunctionType setpf)      { this->__set_position_f    = setpf; }
void Logica::Types::Buffer::Base::AssignGetPositionCallback(GetPositionCallbackFunctionType getpf)      { this->__get_position_f    = getpf; }
void Logica::Types::Buffer::Base::AssignGetCharacterCallback(GetCharacterCallbackFunctionType getchf)   { this->__get_character_f   = getchf; }
void Logica::Types::Buffer::Base::AssignCloseCallback(CloseCallbackFunctionType closef)                 { this->__close_f           = closef; }
void Logica::Types::Buffer::Base::AssignUserData(void* userdata)                                        { this->userdata            = userdata; }

/* Buffer Functions: */
void Logica::Types::Buffer::Base::Init()
{
    if(this->__init_f)
        this->__init_f(this->userdata);
}

void Logica::Types::Buffer::Base::SetPosition(
    const Logica::Types::Basic::Size position
)
{
    if(this->__set_position_f)
        this->__set_position_f(this->userdata, position);
}

Logica::Types::Basic::Size Logica::Types::Buffer::Base::GetPosition()
{
    Logica::Types::Basic::Size value = -1;
    if(this->__get_position_f)
        value = this->__get_position_f(this->userdata);
    return value;
}

Logica::Types::Basic::I32 Logica::Types::Buffer::Base::GetCharacter()
{
    Logica::Types::Basic::I32 value = -1;
    if(this->__get_character_f)
        value = this->__get_character_f(this->userdata);
    return value;
}

void Logica::Types::Buffer::Base::Close()
{
    if(this->__close_f)
        this->__close_f(this->userdata);
}