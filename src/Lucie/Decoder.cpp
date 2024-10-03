#include "Lucie/Decoder.hpp"
#include <iostream>

/*
 * SingleTableSectionizerValueHolder:
 */

void Lucie::Decoder::SingleTableSectionizerValueHolderDestroy(Lucie::Decoder::SingleTableSectionizerValueHolder* value_holder)
{
    switch(value_holder->type)
    {
        case Lucie::Decoder::SingleTableSectionizerValueHolderTypes::Integer:
            delete (Lucie::Integer*)(value_holder->value);
            break;
        case Lucie::Decoder::SingleTableSectionizerValueHolderTypes::Decimal:
            delete (Lucie::Decimal*)(value_holder->value);
            break;
        case Lucie::Decoder::SingleTableSectionizerValueHolderTypes::String:
            delete (Lucie::String*)(value_holder->value);
            break;
        case Lucie::Decoder::SingleTableSectionizerValueHolderTypes::Boolean:
            delete (Lucie::Boolean*)(value_holder->value);
            break;
        case Lucie::Decoder::SingleTableSectionizerValueHolderTypes::List:
            /* TODO: recursively remove it: */
            {
                Lucie::Decoder::SingleTableSectionizerValueHolderList* list = (Lucie::Decoder::SingleTableSectionizerValueHolderList*)(value_holder->value);
                for(Lucie::Indexer index = 0; index < list->size(); index++)
                    Lucie::Decoder::SingleTableSectionizerValueHolderDestroy(list->at(index));
                delete (Lucie::Decoder::SingleTableSectionizerValueHolderList*)value_holder->value;
            }
            break;
        case Lucie::Decoder::SingleTableSectionizerValueHolderTypes::Section:
            /* NOTE: this is just a mark so no need to delete: */
            break;
        default:
            /* anything ? */
            break;   
    }

    /* finally deletes the value holder itself. */
    delete value_holder;
}

Lucie::String Lucie::Decoder::SingleTableSectionizerValueHolderToString(Lucie::Decoder::SingleTableSectionizerValueHolder* value_holder)
{
    Lucie::String value_to_string;
    switch(value_holder->type)
    {
        case Lucie::Decoder::SingleTableSectionizerValueHolderTypes::Integer:
            value_to_string = std::to_string( *(Lucie::Integer*)(value_holder->value) );
            break;
        case Lucie::Decoder::SingleTableSectionizerValueHolderTypes::Decimal:
            value_to_string = std::to_string( *(Lucie::Decimal*)(value_holder->value) );
            break;
        case Lucie::Decoder::SingleTableSectionizerValueHolderTypes::String:
            value_to_string = "\"" + *(Lucie::String*)(value_holder->value) + "\"";
            break;
        case Lucie::Decoder::SingleTableSectionizerValueHolderTypes::Boolean:
            value_to_string = *(Lucie::Boolean*)(value_holder->value) ? "yes" : "no";
            break;
        case Lucie::Decoder::SingleTableSectionizerValueHolderTypes::List:
            {
                Lucie::Decoder::SingleTableSectionizerValueHolderList* list = (Lucie::Decoder::SingleTableSectionizerValueHolderList*)(value_holder->value);
                value_to_string = "[";
                for(Lucie::Indexer index = 0; index < list->size(); index++)
                    value_to_string += Lucie::Decoder::SingleTableSectionizerValueHolderToString(list->at(index)) + (index >= list->size() - 1 ? "" : ", ");
                value_to_string += "]";
            }
            break;
        case Lucie::Decoder::SingleTableSectionizerValueHolderTypes::Section:
            value_to_string = "section";
            break;
        default:
            /* anything ? */
            break;
    }
    return value_to_string;
}

/*
 * SingleTableSectionizer:
 */

static bool IsTokenInteger(const Lucie::String *token)
{
    /* NOTE: is the token an integer? */
    bool result = true;
    for(Lucie::Indexer index = 0; index < token->size(); index++)
    {
        const Lucie::Character character = token->at(index);
        if((character >= '0' && character <= '9') || (character == '-' && index == 0))
        {
            /* valid character: */
            continue;
        }
        else
        {
            result = false;
            break;
        }
    }
    return result;
}

static bool IsTokenDecimal(const Lucie::String *token)
{
    Lucie::U8 result = 0;
    for(Lucie::Indexer index = 0; index < token->at(index); index++)
    {
        const Lucie::Character character = token->at(index);
        if((character >= '0' && character <= '9'))  { continue;                 }
        else if((character == '.' && result == 0))  { result = 1;   continue;   }
        else                                        { result = 2; break;        }
    }
    return result == 1;
}

static Lucie::Decoder::SingleTableSectionizerValueHolder* SingleTableSectionizerBuildValue(
    Lucie::Text::Tokens*                                tokens,
    Lucie::Decoder::SingleTableSectionizerValidator*    validator,
    Lucie::Indexer*                                     indexer,
    Lucie::Indexer*                                     linec,
    Lucie::U8                                           depth
)
{
find_another_token:
    
    /* NOTE: Take care of the new line situation, there are two things that can happen:
     * 1-) BuildValue outside an list, then consider the new line and just get another token;
     * 2-) inside a list, do not consider and leave it to the list controller.
     */
    Lucie::String token = tokens->at(*indexer);
    if(token == "\n" && depth <= 0)
    {
        *indexer += 1, *linec += 1;
        goto find_another_token;
    }

    Lucie::Character lefthint     = token.at(0);
    Lucie::Character righthint    = token.at(token.size() - 1);
    Lucie::Decoder::SingleTableSectionizerValueHolder* value = new Lucie::Decoder::SingleTableSectionizerValueHolder;
    
    /* FOR integers: */
    if(IsTokenInteger(&token))
    {
        /* NOTE: this requires C++11 to be present due: std::atoi() & std::stof(). */
        value->value = new Lucie::Integer;
        value->type  = Lucie::Decoder::SingleTableSectionizerValueHolderTypes::Integer;
        *(Lucie::Integer*)value->value = std::atoi(token.c_str());
    }
    /* FOR decimals: */
    else if(IsTokenDecimal(&token))
    {
        value->value = new Lucie::Decimal;
        value->type  = Lucie::Decoder::SingleTableSectionizerValueHolderTypes::Decimal;
        *(Lucie::Decimal*)value->value = std::stof(token.c_str());
    }
    /* FOR strings: */
    else if((lefthint == '"' || lefthint == '\'') && (righthint == lefthint))
    {
        value->value = new Lucie::String;
        value->type  = Lucie::Decoder::SingleTableSectionizerValueHolderTypes::String;
        *(Lucie::String*)value->value = token.substr(1, token.size() - 2);
    }
    /* FOR booleans: */
    else if((token == "yes" || token == "true") || (token == "false" || token == "no"))
    {
        value->value    = new Lucie::Boolean;
        value->type     = Lucie::Decoder::SingleTableSectionizerValueHolderTypes::Boolean;
        *(Lucie::Boolean*)value->value = (token == "yes" || token == "true");
    }
    /* FOR lists: */
    else if(token == "[")
    {
        /* NOTE: begin recursion here: */
        value->value    = new Lucie::Decoder::SingleTableSectionizerValueHolderList;
        value->type     = Lucie::Decoder::SingleTableSectionizerValueHolderTypes::List;
        Lucie::Decoder::SingleTableSectionizerValueHolderList* list = (Lucie::Decoder::SingleTableSectionizerValueHolderList*)(value->value);

        *indexer += 1;     /* set to the first token on the list: */
        while(*indexer < tokens->size())
        {
            const Lucie::String subtoken = tokens->at(*indexer);
            if(subtoken == "]")                 { break; }
            else if(subtoken == "\n")           { *indexer += 1, *linec += 1; continue; }
            else
            {                
                Lucie::Decoder::SingleTableSectionizerValueHolder* list_value = SingleTableSectionizerBuildValue(tokens, validator, indexer, linec, depth + 1);
                list->push_back(list_value);
            }
        }
    }
    else
    {
        validator->report   = Lucie::String("in data definition, invalid token: ") + token;
        validator->state    = 1;

        /* NOTE: delete the allocated value since it is not required due failure: */
        delete value;
    }

    *indexer += 1;
    return value;
}

static Lucie::String SingleTableSectionizerFlatLocation(
    std::vector<Lucie::String>* location,
    const Lucie::Character      separator
)
{
    Lucie::String location_flatten;
    for(Lucie::Indexer index = 0; index < location->size(); index++)
        location_flatten += (location->at(index) + separator);
    return location_flatten;
}

Lucie::Decoder::SingleTableSectionizedContent* Lucie::Decoder::SingleTableSectionizer(
    Lucie::Text::Tokens*                                tokens,
    Lucie::Decoder::SingleTableSectionizerValidator*    validator,
    const Lucie::Character                              separator
)
{
    /* Sectionizing: */
    Lucie::Decoder::SingleTableSectionizedContent* content = new Lucie::Decoder::SingleTableSectionizedContent;
    
    /* Location and indexing: */
    Lucie::Indexer  index           = 0;
    Lucie::Indexer  length          = tokens->size();
    Lucie::Indexer  line_counter    = 1;
    
    std::vector<Lucie::String> location;
    
    /* DO THIS: */
    while(index < length)
    {
        /* TODO: ugly but it works: */
        if(validator->state != 0) break;

        Lucie::String token = tokens->at(index);

        if (token == "section")
        {
            const Lucie::String name    = tokens->at(index + 1);
            location.push_back(name);            
            index += 2;
        }
        else if (token == "end")
        {
            /* NOTE: find the last separator: */
            location.pop_back();
            index++;
        }
        else if (token == "set")
        {
            /* Calculate the name: */
            const Lucie::String name = tokens->at(index + 1); 
            index += 2;

            /* NOTE: set the adquired_value: */
            Lucie::Decoder::SingleTableSectionizerValueHolder* adquired_value = SingleTableSectionizerBuildValue(tokens, validator, &index, &line_counter, 0);
            const Lucie::String actual_name = SingleTableSectionizerFlatLocation(&location, separator) + name;
            content->insert({actual_name, adquired_value});
        }
        else if (token == "\n")
        {
            line_counter    ++;
            index           ++;
        }
        else
        {
            validator->state        = 1;
            validator->line         = line_counter;
            validator->report       = Lucie::String("Invalid token: ") + token;
            break;
        }
    }

    /* DONE: */
    return content;
}

void Lucie::Decoder::SingleTableSectionizedContentDestroy(Lucie::Decoder::SingleTableSectionizedContent* content)
{
    /* Begin to clean all the unidimensional list here: */
    for(auto &p : *content)
        Lucie::Decoder::SingleTableSectionizerValueHolderDestroy(p.second);
    delete content;
}