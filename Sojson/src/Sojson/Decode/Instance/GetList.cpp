#include "Sojson/Decode/Instance.hpp"
#include <iostream>

Sojson::Types::Basic::Result Sojson::Decode::Instance::GetValueAndPushBackToList(
    Sojson::Node::List* building_list,
    Sojson::Types::Basic::U8 depth
)
{
    Sojson::Types::Basic::Result should_continue = true;
    Sojson::Node* list_node_entry = nullptr;

    /* NOTE: next indicator is the ',' token, which here determines whether the object should
     * close or not, using ']' will close the list, independent of the size the list is in. */
    Logica::Types::Basic::String value_entrypoint_or_next_indicator_or_closure;
    this->tokenizer_instance.GetToken(&value_entrypoint_or_next_indicator_or_closure);

    std::cout
        << __PRETTY_FUNCTION__
        << ": "
        << building_list->size()
        << "\n";
    std::cout
        << __PRETTY_FUNCTION__
        << ": "
        << value_entrypoint_or_next_indicator_or_closure
        << "\n";

    if(value_entrypoint_or_next_indicator_or_closure == "]")
    {
        should_continue = false;
        goto skip_due_closure;
    }
    else
    {
        /* NOTE: in this case, we have two scenarios:
         * [',', '0']    -> which is invalid;
         * ['0', ',', '0'] -> which is valid;
         */
        if(value_entrypoint_or_next_indicator_or_closure == ",")
        {
            /* For this case, the list has started with next indicator token, so we put a failure
             * here since this is a invalid construct: */
            if(building_list->size() == 0)
            {
                this->validator.ReportError(
                    Sojson::Decode::Instance::INVALID_SYNTAX,
                    "At line %d, expected value on beginning of the list, got = ',' token!",
                    this->tokenizer_instance.GetCurrentLine()
                );
                this->state = Sojson::Decode::Instance::DIED;
                goto skip_due_error;
            }
            else
            {
                this->tokenizer_instance.GetToken(&value_entrypoint_or_next_indicator_or_closure);
            }
        }
        else
        {
            if(building_list->size() != 0)
            {
                this->validator.ReportError(
                    Sojson::Decode::Instance::INVALID_SYNTAX,
                    "At line %d, list expected ',' got: %s",
                    this->tokenizer_instance.GetCurrentLine(),
                    value_entrypoint_or_next_indicator_or_closure.c_str()
                );
                this->state = Sojson::Decode::Instance::DIED;
                goto skip_due_error;
            }
        }
    }
    /* If the code reaches here, every syntax is valid and we can proceed: */
    list_node_entry = this->GetValue(value_entrypoint_or_next_indicator_or_closure, depth + 1);
    building_list->push_back(list_node_entry);
skip_due_error:
skip_due_closure:
    return should_continue;
}

Sojson::Node* Sojson::Decode::Instance::GetList(
    const Logica::Types::Basic::U8 depth
)
{
    /* NOTE: create an list and start to parse the code: */
    Sojson::Node* current_node = new Sojson::Node;
    Sojson::Node::List* building_list = current_node->CreateList();
    Logica::Types::Basic::String token;
    for( 
        ;
        (this->state == Sojson::Decode::Instance::RUNNING);

    )
    {
        if(
            this->tokenizer_instance.GetState() !=
                Logica::Texting::Tokenizer::InstanceState::Running
        )
        { 
            this->validator.ReportError(
                Sojson::Decode::Instance::PREMATURE_END,
                "Premature end for list constructor at the line: %d",
                this->tokenizer_instance.GetCurrentLine()
            );
            this->state = Sojson::Decode::Instance::DIED;
        }
        else
        {
            /* Use this function to determine to whether break out the loop: */
            if(this->GetValueAndPushBackToList(building_list, depth))
                continue;
            else
                break;
        }
    }
    return current_node;
}