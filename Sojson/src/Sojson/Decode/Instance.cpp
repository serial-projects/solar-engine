#include "Sojson/Decode/Instance.hpp"
#include "Sojson/Decode/Parsing.hpp"
#include <iostream>

Sojson::Decode::Instance Sojson::Decode::InstanceNew()
{
    Sojson::Decode::Instance instance;
    return instance;
}

void Sojson::Decode::InstanceDestroy(
    Sojson::Decode::Instance* instance
)
{
    // DO NOTHING
    return;
}

void Sojson::Decode::InstanceInit(
    Sojson::Decode::Instance* instance,
    Logica::Types::Buffer::Base* buffer
)
{
    /*
     * On JSON (with comments), we must consider the following:
     * "" -> strings;
     * ' ', '\n', '\t' -> token delimiters;
     * '[]', '{}' ... -> important tokens;
     * 
     * Sojson supports comments by default.
     */
    instance->current_tokenizer_rules = Logica::Texting::Tokenizer::Rules();
    instance->current_tokenizer_rules.is_token_delimiter = [](
        Logica::Types::Basic::U32 ch
    )
    {
        return (
            ch == ' '   ||
            ch == '\n'  ||
            ch == '\t'
        );
    };
    instance->current_tokenizer_rules.is_token_string_delimiter = [](
        Logica::Types::Basic::U32 ch
    )
    {
        return (
            ch == '\'' ||
            ch == '"'
        );
    };
    instance->current_tokenizer_rules.is_token_highlight = [](
        Logica::Types::Basic::U32 ch
    )
    {
        return (
            ch == ':' ||    /* json requires ':', so on GetTableValue(), this will be required! */
            ch == ',' ||    /* json requires ',' so on GetTableValue() or on GetListValue() we can determine whether to continue or not. */
            ch == '[' ||
            ch == ']' ||
            ch == '{' ||
            ch == '}'
        );
    };
    instance->current_tokenizer_rules.comment_starter           = '/';
    instance->current_tokenizer_rules.comment_single_line_hint  = '/';
    instance->current_tokenizer_rules.comment_delimited_hint    = '*';

    /*
     * Set the tokenizer to prepare for the json tokenization and
     * parsing!
     */
    instance->current_tokenizer = Logica::Texting::Tokenizer::Instance();
    instance->current_tokenizer.SetRules(&instance->current_tokenizer_rules);
    instance->current_tokenizer.SetBuffer(buffer);
    instance->state = Sojson::Decode::InstanceStates::Running;
}

Sojson::Node* Sojson::Decode::InstanceParse(
    Sojson::Decode::Instance* instance
)
{
    /* NOTE: GetValue() is the first thing we need on a JsonC file, right ? */
    Sojson::Node* root_value =
        Sojson::Decode::Parsing::Get::ValueRoot(instance);

    /* did we keep running flag? if yes, then set to finish, if not, keep it. */
    if(instance->state == Sojson::Decode::InstanceStates::Running)
        instance->state = Sojson::Decode::InstanceStates::Finished;
    return root_value;
}