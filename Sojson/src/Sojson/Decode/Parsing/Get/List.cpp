#include "Sojson/Decode/Parsing/Get/List.hpp"

inline Sojson::Types::Result __SojsonDecodeParsingGetListValueAndPushBack(
    Sojson::Decode::Instance* instance,
    Sojson::RepresentativeTypes::List* working_list,
    Sojson::Types::U32 counter,
    Sojson::Types::U8 current_depth
)
{
    Sojson::Types::Result should_continue = true;
    Logica::Types::Basic::String value_entrypoint_closure_or_next_token = 
        instance->current_tokenizer.GetToken(false);
    if(value_entrypoint_closure_or_next_token == "]")
    {
        should_continue = false;
    }
    else
    {
        /* NOTE: check for ',' when counter != 0 since,
        * list is [0, 1, 2, 3 ...]
        *         ^ on the first iteration, there is no ',' token (counter == 0)
        *         but on later iterations, the ',' token is required! 
        * 
        * 1-) on the first case, if an ',' is set: [, 0, 0] -> invalid (value is expected);
        * 
        * 2-) on the second case, if an ',' is: [0, 0,] -> value is expected is here.
        *     but in this case, the GetValue is called BUT the token ']' is used as entry
        *     point and the GetValue will pipe this to GetBasicValueFromToken which
        *     will deal with the error.
        */
        if(value_entrypoint_closure_or_next_token == ",")
        {
            if(counter != 0)
                value_entrypoint_closure_or_next_token =
                    instance->current_tokenizer.GetToken(false);
            else
            {
                /* in this case, 0 started with an ',' (an intolerable mistake)! */
                instance->validator.SetError(
                    Sojson::Decode::InstanceErrors::ExpectedValue,
                    "on line %d, expected value, got = %s",
                    instance->current_tokenizer.GetCurrentLine(),
                    value_entrypoint_closure_or_next_token.c_str()
                );
                instance->state = Sojson::Decode::InstanceStates::Died;
                should_continue = false;
                goto error;
            }
        }
        else
        {
            /* in this case, then ',' is expected, like [0, 0 1] where is the ',' ? */
            if(counter != 0)
            {
                instance->validator.SetError(
                    Sojson::Decode::InstanceErrors::SyntaxError,
                    "on line %d, expected ',' or ']' token, got = %s",
                    instance->current_tokenizer.GetCurrentLine(),
                    value_entrypoint_closure_or_next_token.c_str()
                );
                instance->state = Sojson::Decode::InstanceStates::Died;
                should_continue = false;
                goto error;
            }
        }

        /* set the current value: */
        Sojson::Node* current_node = Sojson::Decode::Parsing::Get::Value(
            instance,
            value_entrypoint_closure_or_next_token,
            current_depth + 1
        );
        working_list->push_back(current_node);
    }
    error:
    return should_continue;
}

Sojson::Node* Sojson::Decode::Parsing::Get::List(
    Sojson::Decode::Instance* instance,
    const Sojson::Types::U8 current_depth
)
{
    Sojson::RepresentativeTypes::List* lv =
        new Sojson::RepresentativeTypes::List;
    const Sojson::Types::U32 list_started_at_line = 
        instance->current_tokenizer.GetCurrentLine();
    for(
        Sojson::Types::U32 counter = 0;
        (instance->state == Sojson::Decode::InstanceStates::Running);
        ++counter
    )
    {
        /* NOTE: did we reach the end of the tokenizer? */
        if(
            instance->current_tokenizer.GetState() != 
            Logica::Texting::Tokenizer::InstanceStatus::Running
        )
        {
            /* In this case, this is a non-wanted EOF! */
            instance->validator.SetError(
                Sojson::Decode::InstanceErrors::PrematureEnd,
                "on list that started on line %d, premature end at line %d",
                list_started_at_line,
                instance->current_tokenizer.GetCurrentLine()
            );
            instance->state = Sojson::Decode::InstanceStates::Died;
            break;
        }

        /* Here we check for ']' and the data entry point; */
        if(__SojsonDecodeParsingGetListValueAndPushBack(instance, lv, counter, current_depth))
            continue;
        else
            break;
    }
    Sojson::Node* current_node = Sojson::NodeNew();
    Sojson::NodeInit(current_node, (void*)lv, Sojson::NodeTypes::List);
    return current_node;
}