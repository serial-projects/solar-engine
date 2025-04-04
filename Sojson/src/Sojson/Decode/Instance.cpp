#include "Sojson/Decode/Instance.hpp"

Sojson::Decode::Instance::Instance()
{
    /* Set the type decider: */
    this->tokenizer_rules.get_character_type =
        [](Logica::Types::Basic::U32 ch)
        {
            Logica::Types::Basic::U8 type =
                Logica::Texting::Tokenizer::Rules::CharacterTypes::NOTHING;
            switch(ch)
            {
                case ' ': case '\t': case '\n':
                    type = Logica::Texting::Tokenizer::Rules::CharacterTypes::TOKEN_DELIMITER;
                    break;
                case '"': case '\'':
                    type = Logica::Texting::Tokenizer::Rules::CharacterTypes::STRING_DELIMITER;
                    break;
                case '[': case ']': case '{': case '}': case ',': case ':':
                    type = Logica::Texting::Tokenizer::Rules::CharacterTypes::HIGHLIGHT_TOKEN;
                    break;
            };
            return type;
        };
    /* Set the comments here: */
    this->tokenizer_rules.comment_token                     = '/';
    this->tokenizer_rules.line_comment_hint_token           = 0;
    this->tokenizer_rules.delimited_comment_hint_token      = '*';
    this->tokenizer_rules.delimited_comment_closure_token   = '*';
    
    /* Set to the tokenizer: */
    this->tokenizer_instance.SetRules(&this->tokenizer_rules);
}

void Sojson::Decode::Instance::SetBuffer(
    Logica::Types::Stream::Buffer* buffer
)
{
    this->tokenizer_instance.SetBuffer(buffer);
}

Sojson::Node* Sojson::Decode::Instance::Parse()
{
    return this->GetRootValue();
}

Sojson::Decode::Instance::States Sojson::Decode::Instance::GetState()
{
    return this->state;
}