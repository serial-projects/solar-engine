#include "Logica/Texting/Tokenizer/Instance.hpp"

Logica::Texting::Tokenizer::Instance::Instance()
{
    this->state = Logica::Texting::Tokenizer::InstanceState::Running;
}

void Logica::Texting::Tokenizer::Instance::SetBuffer(
   Logica::Types::Stream::Buffer* buffer
)
{
    this->working_buffer = buffer;
}

void Logica::Texting::Tokenizer::Instance::SetRules(
   Logica::Texting::Tokenizer::Rules* rules
)
{
    this->current_rules = rules;
}

Logica::Types::Basic::U8 Logica::Texting::Tokenizer::Instance::GetState()
{
    return this->state;
}

Logica::Types::Basic::U32 Logica::Texting::Tokenizer::Instance::GetCurrentLine()
{
    return this->line_counter;
}