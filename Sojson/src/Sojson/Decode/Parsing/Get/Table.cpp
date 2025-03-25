#include "Sojson/Decode/Parsing/Get/Table.hpp"
#include "Sojson/Decode/Parsing/IsToken.hpp"
#include <iostream>

inline Sojson::Types::Result __SojsonDecodeParsingGetTableValueFirstValue(
    Sojson::Decode::Instance* instance,
    Sojson::RepresentativeTypes::Table* working_table,
    const Sojson::Types::U8 current_depth
)
{
    /* TODO: account for EOF. */
    /* TODO: set errors when invalid token! */
    Sojson::Types::Result should_continue = true;
    Logica::Types::Basic::String key_or_closure = instance->current_tokenizer.GetToken(false);
    if(key_or_closure != "}")
    {
        /* get the closure or the key: */
        if(!Sojson::Decode::Parsing::IsToken::ValidKey(key_or_closure))
        {
            instance->validator.SetError(
                Sojson::Decode::InstanceErrors::BadKey,
                "on line %d, bad key = %s",
                instance->current_tokenizer.GetCurrentLine(),
                key_or_closure.c_str()
            );
            instance->state = Sojson::Decode::InstanceStates::Died;
            should_continue = false;
            goto error;
        }
        key_or_closure = key_or_closure.substr(1, key_or_closure.size() - 2);
                
        /* adquire the split: */
        Sojson::Types::String split = instance->current_tokenizer.GetToken(false);
        if(split != ":")
        {
            instance->validator.SetError(
                Sojson::Decode::InstanceErrors::SyntaxError,
                "on line %d, expected split ':' token, got = %s",
                instance->current_tokenizer.GetCurrentLine(),
                split.c_str()
            );
            instance->state = Sojson::Decode::InstanceStates::Died;
            should_continue = false;
            goto error;
        }

        /* get the data: */
        Logica::Types::Basic::String value_entrypoint =
            instance->current_tokenizer.GetToken(false);
        Sojson::Node* current_node = 
            Sojson::Decode::Parsing::Get::Value(instance, value_entrypoint, current_depth + 1);
        working_table->insert({ key_or_closure, current_node });
    }
    else
    {
        should_continue = false;
    }
    error:
    return should_continue;
}

inline Sojson::Types::Result __SojsonDecodeParsingGetTableMiddleEndValue(
    Sojson::Decode::Instance* instance,
    Sojson::RepresentativeTypes::Table* working_table,
    const Sojson::Types::U8 current_depth
)
{
    /* Set the should_continue to true, since most of the time, the user will do the 
     * correct thing and no syntax error should arrive, right?
     */
    Sojson::Types::Result should_continue = true;

    /* For the Middle and End Value, we need to check for the ',' and the '}' */
    Logica::Types::Basic::String next_key_or_closure = instance->current_tokenizer.GetToken(false);
    if(next_key_or_closure == ",")
    {    
        /* if we have ',' then we have the next token that MUST be a key: */
        /* NOTE: in case the user have set the {... ,} <- where is the next key? */
        Logica::Types::Basic::String key = instance->current_tokenizer.GetToken(false);
        if(!Sojson::Decode::Parsing::IsToken::ValidKey(key))
        {
            instance->validator.SetError(
                (key == "}" || key == "]")
                    ? Sojson::Decode::InstanceErrors::InvalidClosure
                    : Sojson::Decode::InstanceErrors::BadKey,
                /* set the hint for the user: */
                (key == "}" || key == "]") 
                    ? "on line %d, expected key, got closure = %s"
                    : "on line %d, bad key = %s",
                /* keep going ... */
                instance->current_tokenizer.GetCurrentLine(),
                key.c_str()
            );
            instance->state = Sojson::Decode::InstanceStates::Died;
            should_continue = false;
            goto error;
        }
        key = key.substr(1, key.size() - 2);

        /* TODO: customize whether the application requires to enforce single key on table
         * policy or not. If not, then just free the node and keep going forward. This check 
         * is done only on the middle and end value since the first value doesn't duplicate
         * anything.
         */
        if(working_table->find(key) != working_table->end())
        {
            instance->validator.SetError(
                Sojson::Decode::InstanceErrors::DuplicatedKey,
                "on line %d, the key \"%s\" is already used",
                instance->current_tokenizer.GetCurrentLine(),
                key.c_str()
            );
            instance->state = Sojson::Decode::InstanceStates::Died;
            should_continue = false;
            goto error;
        }

        /* adquire the split: */
        Logica::Types::Basic::String split = instance->current_tokenizer.GetToken(false);
        if(split != ":")
        {
            instance->validator.SetError(
                Sojson::Decode::InstanceErrors::SyntaxError,
                "on line %d, expected split ':' token, got = %s",
                instance->current_tokenizer.GetCurrentLine(),
                split.c_str()
            );
            instance->state = Sojson::Decode::InstanceStates::Died;
            should_continue = false;
            goto error;
        }
        
        /* adquire the node: */
        Logica::Types::Basic::String value_entrypoint = 
            instance->current_tokenizer.GetToken(false);
        Sojson::Node* current_node =
            Sojson::Decode::Parsing::Get::Value(instance, value_entrypoint, current_depth + 1);
        working_table->insert({key, current_node});
    }
    else if(next_key_or_closure == "}")
    {
        /* Close the loop: */
        should_continue = false;
        goto error;
    }
    else
    {
        /* SyntaxError: unexpected token? */
        instance->validator.SetError(
            Sojson::Decode::InstanceErrors::SyntaxError,
            "on line %d, expected ',' or '}' but got = %s",
            instance->current_tokenizer.GetCurrentLine(),
            (next_key_or_closure == "") 
                ? "<EOF>?"
                : next_key_or_closure.c_str()
        );
        instance->state = Sojson::Decode::InstanceStates::Died;
        should_continue = false;
        goto error;
    }

    error:
    return should_continue;
}

Sojson::Node* Sojson::Decode::Parsing::Get::Table(
    Sojson::Decode::Instance* instance,
    const Sojson::Types::U8 current_depth
)
{
    /* NOTE: begin the very unsafe loop here :^) */
    /* TODO: be procedural when loading the first element to avoid function repeating! */
    Sojson::Types::U32 table_started_at_line =
        instance->current_tokenizer.GetCurrentLine();

    Sojson::RepresentativeTypes::Table* tv = 
        new Sojson::RepresentativeTypes::Table;
    for(
        Sojson::Types::U32 counter = 0;
        (instance->state == Sojson::Decode::InstanceStates::Running);
        ++counter
    )
    {
        if(
            instance->current_tokenizer.GetState() != 
            Logica::Texting::Tokenizer::Instance::States::RUNNING
        )
        {
            /* In this case, this is a non-wanted EOF! */
            instance->validator.SetError(
                Sojson::Decode::InstanceErrors::PrematureEnd,
                "on table that started on line %d, premature end at line %d",
                table_started_at_line,
                instance->current_tokenizer.GetCurrentLine()
            );
            instance->state = Sojson::Decode::InstanceStates::Died;
            break;
        }

        /* NOTE: 
         * There are two states we can possibly have here:
         * 1-) when we are on the start of the list, in that case, we are looking for the
         * key already, not the ',' token.
         * 2-) when we are not in the start anymore, then we have to look for '}' and ','
         * token we have to check that step.
         */
        if(counter == 0)
        {
            if(__SojsonDecodeParsingGetTableValueFirstValue(instance, tv, current_depth))
                continue;
            else
                break;
        }
        else
        {
            if(__SojsonDecodeParsingGetTableMiddleEndValue(instance, tv, current_depth))
                continue;
            else
                break;
        }
    }
    Sojson::Node* current_node = Sojson::NodeNew();
    Sojson::NodeInit(current_node, (void*)tv, Sojson::NodeTypes::Table);
    return current_node;
}