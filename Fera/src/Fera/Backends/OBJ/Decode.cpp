#include "Fera/Backends/OBJ/Decode.hpp"

Fera::Backends::OBJ::Decode::Decode()
{
    this->state             = Fera::Backends::OBJ::Decode::NOTHING;
    this->building_mesh     = nullptr;
    
    /** INIT THE TOKENIZER RULES: */
    this->tokenizer_rules.comment_token                     = '#';
    this->tokenizer_rules.line_comment_hint_token           = 0;
    this->tokenizer_rules.delimited_comment_hint_token      = 0;
    this->tokenizer_rules.delimited_comment_closure_token   = 0; 
    this->tokenizer_rules.get_character_type = 
        [](Logica::Types::Basic::I32 value)
        {
            Logica::Types::Basic::U8 type =
                Logica::Texting::Tokenizer::Rules::CharacterTypes::NOTHING;
            switch(value)
            {
                case ' ': case '\t': case '\n':
                    type = Logica::Texting::Tokenizer::Rules::CharacterTypes::TOKEN_DELIMITER;
                    break;
                case '"': case '\'':
                    type = Logica::Texting::Tokenizer::Rules::CharacterTypes::STRING_DELIMITER;
                    break;
                default:
                    break;
            };
            return type;
        };
    this->tokenizer.SetRules(&this->tokenizer_rules);
}

Fera::Backends::OBJ::Decode::~Decode()
{
    /* NOTE: Don't do anything. */
}

void Fera::Backends::OBJ::Decode::SetBuffer(
    Logica::Types::Stream::Buffer* buffer
)
{
    this->tokenizer.SetBuffer(buffer);
    this->state = Fera::Backends::OBJ::Decode::States::RUNNING;
}