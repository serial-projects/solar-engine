#include "Sojson/Decode/Parsing/Get/Basic.hpp"
#include "Sojson/Decode/Parsing/IsToken.hpp"

Sojson::Node* Sojson::Decode::Parsing::Get::BasicValueFromToken(
    Sojson::Decode::Instance* instance,
    const Logica::Types::Basic::String& token
)
{
    Logica::Types::Basic::U8 number_or_decimal_result =
        Sojson::Decode::Parsing::IsToken::Type(token);
    Sojson::Node* value_node = Sojson::NodeNew();
    switch(number_or_decimal_result)
    {
        case Sojson::Decode::Parsing::IsToken::TypeResult::Number:
            {
                Sojson::RepresentativeTypes::Integer* iv =
                    new Sojson::RepresentativeTypes::Integer;
                *iv = std::stoi(token);
                Sojson::NodeInit(value_node, (void*)iv, Sojson::NodeTypes::Integer);
            };
            break;
        case Sojson::Decode::Parsing::IsToken::TypeResult::Decimal:
            {
                Sojson::RepresentativeTypes::Decimal* dv = 
                    new Sojson::RepresentativeTypes::Decimal;
                *dv = std::stof(token);
                Sojson::NodeInit(value_node, (void*)dv, Sojson::NodeTypes::Decimal);
            };
            break;
        case Sojson::Decode::Parsing::IsToken::TypeResult::String:
            {
                Sojson::RepresentativeTypes::String* sv =
                    new Sojson::RepresentativeTypes::String;
                *sv = token.substr(1, token.size() - 2);
                Sojson::NodeInit(value_node, (void*)sv, Sojson::NodeTypes::String);
            };
            break;
        case Sojson::Decode::Parsing::IsToken::TypeResult::Boolean:
            {
                Sojson::RepresentativeTypes::Boolean* bv =
                    new Sojson::RepresentativeTypes::Boolean;
                *bv = (token == "yes" || token == "true") ? 1 : 0;
                Sojson::NodeInit(value_node, (void*)bv, Sojson::NodeTypes::Boolean);
            };
            break;
        case Sojson::Decode::Parsing::IsToken::TypeResult::Null:
            {
                Sojson::NodeInit(value_node, nullptr, Sojson::NodeTypes::Null);
            };
            break;
        case Sojson::Decode::Parsing::IsToken::TypeResult::Neither:
        default:
            /* There are a possible things that can fall here:
             * 1-) } ] closure tokens;
             * 2-) invalid tokens.
             */
            {
                if(token == "]" || token == "}")
                {
                    instance->validator.SetError(
                        Sojson::Decode::InstanceErrors::InvalidClosure,
                        "on line %d, expected value got closure = %s",
                        instance->current_tokenizer.GetCurrentLine(),
                        token.c_str()
                    );
                    instance->state = Sojson::Decode::InstanceStates::Died;
                }
                else
                {
                    instance->validator.SetError(
                        Sojson::Decode::InstanceErrors::SyntaxError,
                        "on line %d, got invalid token = %s",
                        instance->current_tokenizer.GetCurrentLine(),
                        token.c_str()
                    );
                    instance->state = Sojson::Decode::InstanceStates::Died;
                }
            }
            break;
    }
    return value_node;
}