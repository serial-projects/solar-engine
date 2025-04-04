#include "Sojson/Decode/Instance.hpp"
#include <iostream>

static Logica::Types::Basic::Result __SojsonDecodeInstanceGetValueFromTableIsKeyValid(
    const Logica::Types::Basic::String& key
)
{
    Logica::Types::Basic::Result valid = false;
    if(key.size() >= 2)
    {
        const Sojson::Types::Basic::CH8 lv = key.at(0);
        const Sojson::Types::Basic::CH8 rv = key.at(key.size() - 1);
        valid = ((lv == '\"') && (lv == rv));
    }
    return valid;
}

inline
Sojson::Types::Basic::Result Sojson::Decode::Instance::GetValueFromTableOnTheFirstValue(
    Sojson::Node::Table* building_table,
    Sojson::Types::Basic::U8 depth
)
{
    Sojson::Types::Basic::Result should_continue = true;
    
    /* Adquire the token to start the processing: */
    Logica::Types::Basic::String key_or_early_closure;
    this->tokenizer_instance.GetToken(&key_or_early_closure);

    Logica::Types::Basic::String split_token;
    Logica::Types::Basic::String value_entrypoint;

    /* NOTE: here we want to search for the:
     * ->   When the {} is set, that is, the table is EMPTY, so in this case, we just
     *      ignore.
     * ->   When the {"A": 0, ...}, that is your usual table that will continue on the
     *      MiddleAndEndValue().
     */
    if(key_or_early_closure == "}")
    {
        should_continue = false;
    }
    else
    {
        /* Try to check if this is a key: */
        std::cout << __PRETTY_FUNCTION__ << ": Going for key? = " << key_or_early_closure << "\n";
        if(!__SojsonDecodeInstanceGetValueFromTableIsKeyValid(key_or_early_closure))
        {
            this->validator.ReportError(
                Sojson::Decode::Instance::TABLE_INVALID_KEY,
                "At line %d, got invalid key: %s",
                this->tokenizer_instance.GetCurrentLine(),
                key_or_early_closure.c_str()
            );
            this->state = Sojson::Decode::Instance::DIED;
            goto error;
        }
        key_or_early_closure = key_or_early_closure.substr(1, key_or_early_closure.size() - 2);

        /* Adquire the key and value splitter token, that is ':' one! */
        this->tokenizer_instance.GetToken(&split_token);
        if(split_token != ":")
        {
            this->validator.ReportError(
                Sojson::Decode::Instance::TABLE_LACKS_SPLIT,
                "At line %d, expected split, got: %s",
                this->tokenizer_instance.GetCurrentLine(),
                split_token.c_str()
            );
            this->state = Sojson::Decode::Instance::DIED;
            goto error;
        }

        /* Finally, get the value entry point: */
        this->tokenizer_instance.GetToken(&value_entrypoint);
        Sojson::Node* maybe_value = this->GetValue(value_entrypoint, depth + 1);
        
        /* Check if the possibly_new_token was sucessfully adquired, if not, DO NOT include
         * on the list and let the system crash itself: */
        if(this->state == Sojson::Decode::Instance::RUNNING)
            building_table->insert({key_or_early_closure, maybe_value});
    }

error:
    return should_continue;
}

inline
Sojson::Types::Basic::Result Sojson::Decode::Instance::GetValueFromTableOnTheMiddleAndEndValue(
    Sojson::Node::Table* building_table,
    Sojson::Types::Basic::U8 depth
)
{
    Sojson::Types::Basic::Result should_continue = true;

    /* NOTE: the next_indicator is the ',' token. */
    Logica::Types::Basic::String next_indicator_or_closure;
    this->tokenizer_instance.GetToken(&next_indicator_or_closure);

    Logica::Types::Basic::String key_token;
    Logica::Types::Basic::String split_token;
    Logica::Types::Basic::String value_entrypoint;

    if(next_indicator_or_closure == "}")
    {
        should_continue = false;
    }
    else if(next_indicator_or_closure == ",")
    {
        this->tokenizer_instance.GetToken(&key_token);
        if(!__SojsonDecodeInstanceGetValueFromTableIsKeyValid(key_token))
        {
            this->validator.ReportError(
                Sojson::Decode::Instance::TABLE_INVALID_KEY,
                "At line: %d, got invalid key: %s",
                this->tokenizer_instance.GetCurrentLine(),
                key_token.c_str()
            );
            this->state = Sojson::Decode::Instance::DIED;
            goto error;
        }
        key_token = key_token.substr(1, key_token.size() - 2);

        /* TODO: This is to be customized on the future, but the rule system is pretty simple: 
         * If the key is already defined on the table, we do a error, for example: {"A": 0, "A": 2},
         * this is a table redefinition. In the future, maybe allow it using an configuration.
         */
        if(building_table->find(key_token) != building_table->end())
        {
            this->validator.ReportError(
                Sojson::Decode::Instance::TABLE_KEY_REDEFINITION,
                "At line: %d, got an table redefinition, key: %s was already defined!",
                this->tokenizer_instance.GetCurrentLine(),
                key_token.c_str()
            );
            this->state = Sojson::Decode::Instance::DIED;
            goto error;
        }

        /* Keep going with the split now: */
        this->tokenizer_instance.GetToken(&split_token);
        if(split_token != ":")
        {
            this->validator.ReportError(
                Sojson::Decode::Instance::TABLE_LACKS_SPLIT,
                "At line %d, expected split, got: %s",
                this->tokenizer_instance.GetCurrentLine(),
                split_token.c_str()
            );
            this->state = Sojson::Decode::Instance::DIED;
            goto error;
        }

        /* Now, we get the value entry point: */
        this->tokenizer_instance.GetToken(&value_entrypoint);
        Sojson::Node* maybe_value = this->GetValue(value_entrypoint, depth + 1);
        if(this->state == Sojson::Decode::Instance::RUNNING)
            building_table->insert({key_token, maybe_value});
    }
error:
    return should_continue;
}

Sojson::Node* Sojson::Decode::Instance::GetTable(
    const Logica::Types::Basic::U8 depth
)
{
    Sojson::Node* building_node = new Sojson::Node;
    Sojson::Node::Table* building_table = building_node->CreateTable();
    Sojson::Types::Basic::String token;

    for(
        Sojson::Types::Basic::U8 counter = 0;
        (this->state == Sojson::Decode::Instance::RUNNING);
        counter++
    )
    {
        if(
            this->tokenizer_instance.state != Logica::Texting::Tokenizer::Instance::States::RUNNING
        )
        {
            this->validator.ReportError(
                Sojson::Decode::Instance::PREMATURE_END,
                "At line %d, table did not finish, got EOF!",
                this->tokenizer_instance.GetCurrentLine()
            );
            this->state = Sojson::Decode::Instance::DIED;
            break;
        }
        else
        {
            if(counter == 0)
            {
                if(this->GetValueFromTableOnTheFirstValue(building_table, depth))
                    continue;
                else
                    break;
            }
            else
            {
                if(this->GetValueFromTableOnTheMiddleAndEndValue(building_table, depth))
                    continue;
                else
                    break;
            }
        }
    }

    return building_node;
}