#include "Lucie/Decoder.hpp"
#include <iostream>

Lucie::Decoder::SectionizerValidator Lucie::Decoder::SectionizerValidatorNew()
{
    Lucie::Decoder::SectionizerValidator validator;
    validator.log       = Lucie::String();
    validator.error     = 0;
    return validator;
}

void Lucie::Decoder::SectionizerValidatorReportError(
    Lucie::Decoder::SectionizerValidator* validator,
    const Lucie::String reason
)
{
    validator->log      = reason;
    validator->error    = 1;
}

Lucie::Decoder::SectionizerState Lucie::Decoder::SectionizerStateNew()
{
    Lucie::Decoder::SectionizerState state;
    state.validator     = Lucie::Decoder::SectionizerValidatorNew();
    state.tokens        = nullptr;
    state.token_index   = 0;
    state.token_amount  = 0;
    state.current_line  = 1;
    return state;
}

Lucie::String Lucie::Decoder::SectionizerStateGetToken(
    Lucie::Decoder::SectionizerState* sectionizer_state
)
{
    Lucie::String token;
return_point_after_newline:
    if(sectionizer_state->token_index > sectionizer_state->token_amount)
    {
        Lucie::Decoder::SectionizerValidatorReportError(
            &sectionizer_state->validator,
            "Expected token, got EOF."
        );
    }
    else
    {
        token = sectionizer_state->tokens->at(sectionizer_state->token_index);
        sectionizer_state->token_index++;
        if(token == "\n")
        {
            sectionizer_state->current_line++;
            goto return_point_after_newline;
        }
    }
    return token;
}

Lucie::String Lucie::Decoder::SectionizerStatePretendGetToken(
    Lucie::Decoder::SectionizerState* sectionizer_state
)
{
    Lucie::U32 index = sectionizer_state->token_index;
    Lucie::String token;
return_point_after_newline:
    if(index > sectionizer_state->token_amount)
    {
        Lucie::Decoder::SectionizerValidatorReportError(
            &sectionizer_state->validator,
            "Expected token, got EOF."
        );
    }
    else
    {
        token = sectionizer_state->tokens->at(index);
        index ++;
        if(token == "\n")
        {
            goto return_point_after_newline;
        }
    }
    return token;
}

Lucie::Decoder::ValueHolder* Lucie::Decoder::ValueHolderCreateNewFromSection(
    Lucie::Decoder::Section* section
)
{
    Lucie::Decoder::ValueHolder* value_holder = new Lucie::Decoder::ValueHolder;
    value_holder->type = Lucie::Decoder::ValueHolderTypes::Branch;
    value_holder->value= section;
    return value_holder;
}

Lucie::Decoder::ValueHolder* Lucie::Decoder::ValueHolderNew(Lucie::Integer value)
{
    Lucie::Decoder::ValueHolder* value_holder = new Lucie::Decoder::ValueHolder;
    value_holder->type = Lucie::Decoder::ValueHolderTypes::Integer;
    value_holder->value = new Lucie::Integer(value);
    return value_holder;
}

Lucie::Decoder::ValueHolder* Lucie::Decoder::ValueHolderNew(Lucie::Decimal value)
{
    Lucie::Decoder::ValueHolder* value_holder = new Lucie::Decoder::ValueHolder;
    value_holder->type = Lucie::Decoder::ValueHolderTypes::Decimal;
    value_holder->value= new Lucie::Decimal(value);
    return value_holder;
}

Lucie::Decoder::ValueHolder* Lucie::Decoder::ValueHolderNew(Lucie::String value)
{
    Lucie::Decoder::ValueHolder* value_holder = new Lucie::Decoder::ValueHolder;
    value_holder->type = Lucie::Decoder::ValueHolderTypes::String;
    value_holder->value= new Lucie::String(value);
    return value_holder;
}

Lucie::Decoder::ValueHolder* Lucie::Decoder::ValueHolderNew(Lucie::Boolean value)
{
    Lucie::Decoder::ValueHolder* value_holder = new Lucie::Decoder::ValueHolder;
    value_holder->type = Lucie::Decoder::ValueHolderTypes::Boolean;
    value_holder->value= new Lucie::Boolean(value);
    return value_holder;
}

Lucie::Decoder::ValueHolder* Lucie::Decoder::ValueHolderNew(Lucie::Decoder::ValueHolderList* value)
{
    Lucie::Decoder::ValueHolder* value_holder = new Lucie::Decoder::ValueHolder;
    value_holder->type = Lucie::Decoder::ValueHolderTypes::List;
    value_holder->value= value;
    return value_holder;
}
Lucie::String Lucie::Decoder::ValueHolderPrint(
    Lucie::Decoder::ValueHolder* value_holder,
    const Lucie::U8 depth
)
{
    Lucie::String printed_value;
    switch(value_holder->type)
    {
        case Lucie::Decoder::ValueHolderTypes::Integer:
            printed_value = std::to_string(*(Lucie::Integer*)(value_holder->value));
            break;
        case Lucie::Decoder::ValueHolderTypes::Decimal:
            printed_value = std::to_string(*(Lucie::Decimal*)(value_holder->value));
            break;
        case Lucie::Decoder::ValueHolderTypes::String:
            printed_value = ("\"" + Lucie::String(*(Lucie::String*)(value_holder->value)) + "\"");
            break;
        case Lucie::Decoder::ValueHolderTypes::Boolean:
            {
                Lucie::Boolean value    = *(Lucie::Boolean*)(value_holder->value);
                printed_value           = value ? "yes" : "no";
            };
            break;
        case Lucie::Decoder::ValueHolderTypes::List:
            {
                Lucie::Decoder::ValueHolderList* list=
                    (Lucie::Decoder::ValueHolderList*)(value_holder->value);
                printed_value = "[";
                for(Lucie::U32 index=0; index<list->size(); index++)
                    printed_value += (
                        Lucie::Decoder::ValueHolderPrint(list->at(index), depth + 1) + 
                        (index >= (list->size() - 1) ? "" : ", ")
                    );
                printed_value += "]";
            };
            break;
        case Lucie::Decoder::ValueHolderTypes::Branch:
            printed_value = "branch";
            break;
        default:
            break;
    }
    return printed_value;
}

Lucie::String Lucie::Decoder::ValueHolderBranchShow(
    Lucie::Decoder::ValueHolder* value_holder,
    const Lucie::U8 depth
)
{
    Lucie::String printed_value;

    /* NOTE: assume the value_holder: */
    Lucie::Decoder::Section* section = (Lucie::Decoder::Section*)(value_holder->value);
    for(auto &branch_values : *section)
    {
        for(Lucie::U16 index=0; index<(depth * 2); index++) printed_value += " ";
        printed_value += (
            branch_values.first
            + ": "
            + ( 
                branch_values.second->type == Lucie::Decoder::ValueHolderTypes::Branch
                ? ("branch\n" + Lucie::Decoder::ValueHolderBranchShow(branch_values.second, depth + 1))
                : Lucie::Decoder::ValueHolderPrint(branch_values.second, 0)
            )
        );
        printed_value += "\n";
    }
    return printed_value;
}

void Lucie::Decoder::ValueHolderDestroy(Lucie::Decoder::ValueHolder* value_holder)
{
    switch(value_holder->type)
    {
        case Lucie::Decoder::ValueHolderTypes::Integer:
            delete (Lucie::Integer*)(value_holder->value);
            break;
        case Lucie::Decoder::ValueHolderTypes::Decimal:
            delete (Lucie::Decimal*)(value_holder->value);
            break;
        case Lucie::Decoder::ValueHolderTypes::String:
            delete (Lucie::String*)(value_holder->value);
            break;
        case Lucie::Decoder::ValueHolderTypes::Boolean:
            delete (Lucie::String*)(value_holder->value);
            break;
        case Lucie::Decoder::ValueHolderTypes::List:
            {
                Lucie::Decoder::ValueHolderList* list =
                    (Lucie::Decoder::ValueHolderList*)(value_holder->value);
                for(Lucie::U32 index=0; index < list->size(); index++)
                    Lucie::Decoder::ValueHolderDestroy(list->at(index));
            };
            delete (Lucie::Decoder::ValueHolderList*)(value_holder->value);
            break;
        case Lucie::Decoder::ValueHolderTypes::Branch:
            {
                Lucie::Decoder::Section* section = 
                    (Lucie::Decoder::Section*)(value_holder->value);
                for(auto &section_data : *section) 
                    Lucie::Decoder::ValueHolderDestroy(section_data.second);
            };
            delete (Lucie::Decoder::Section*)(value_holder->value);
            break;
        default:
            break;
    };
    delete value_holder;
}

static bool IsTokenInteger(const Lucie::String *token)
{
    /* NOTE: is the token an integer? */
    bool result = true;
    for(Lucie::Indexer index = 0; index < token->size(); index++)
    {
        const Lucie::Character character = token->at(index);
        if((character >= '0' && character <= '9') || (character == '-' && index == 0))
            continue;
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
    for(Lucie::Indexer index = 0; index < token->size(); index++)
    {
        const Lucie::Character character = token->at(index);
        if((character >= '0' && character <= '9'))  { continue;                 }
        else if((character == '.' && result == 0))  { result = 1;   continue;   }
        else                                        { result = 2; break;        }
    }
    return result == 1;
}

#define LDRSGV_ISBOOL(x)(x=="yes"||x=="true"||x=="no"||x=="false")

Lucie::Decoder::ValueHolder* Lucie::Decoder::RecursiveSectionizerParserGetValue(
    Lucie::Decoder::SectionizerState* sectionizer_state,
    const Lucie::U8 depth
)
{
    const Lucie::String entrypoint_token = 
        Lucie::Decoder::SectionizerStateGetToken(sectionizer_state);
    
    const Lucie::Character lhc           = entrypoint_token.at(0);
    const Lucie::Character rhc           = entrypoint_token.at(entrypoint_token.size() - 1);
    Lucie::Decoder::ValueHolder* value   = nullptr;
    
    /* NOTE: take advantage of C++ overload feature here: */

    if(IsTokenInteger(&entrypoint_token))
        value = 
            Lucie::Decoder::ValueHolderNew(std::atoi(entrypoint_token.c_str()));
    else if(IsTokenDecimal(&entrypoint_token))
        value =
            Lucie::Decoder::ValueHolderNew(std::stof(entrypoint_token.c_str()));
    else if((lhc=='\''||lhc=='"')&&(lhc==rhc))
        value = 
            Lucie::Decoder::ValueHolderNew(entrypoint_token.substr(1, entrypoint_token.size() - 2));
    else if(LDRSGV_ISBOOL(entrypoint_token))
        value = 
            Lucie::Decoder::ValueHolderNew((entrypoint_token=="yes" || entrypoint_token=="true"));
    else if(entrypoint_token=="[")
    {
        /* NOTE: begin subindex: */
        Lucie::Decoder::ValueHolderList* list = new Lucie::Decoder::ValueHolderList;
        while(sectionizer_state->token_index <= sectionizer_state->token_amount)
        {
            const Lucie::String token = 
                Lucie::Decoder::SectionizerStatePretendGetToken(sectionizer_state);
            if(token == "]")
            {
                /* NOTE: if we pretend to get the value, then get the value now and set the index to
                 * the next valid position: 
                 */
                Lucie::Decoder::SectionizerStateGetToken(sectionizer_state);
                break;
            }
            else
            {
                list->push_back(
                    Lucie::Decoder::RecursiveSectionizerParserGetValue(sectionizer_state, depth + 1)
                );
            }
        }
        value = Lucie::Decoder::ValueHolderNew(list);
    }
    else
    {
        Lucie::Decoder::SectionizerValidatorReportError(
            &sectionizer_state->validator,
            "During Get Value, got invalid token = \"" + entrypoint_token + "\""
        );

        /* NOTE: to prevent segmentation fault, allocate an 0 value here: 
         * to disable this behavior, just define the macro: LUCIE_ACCEPT_DANGER:
         */
        #ifndef LUCIE_ACCEPT_DANGER
            value = Lucie::Decoder::ValueHolderNew(0);
        #endif
    }

    return value;
}

#undef LDRSGV_ISBOOL

/*
 * BUG: consider the depth = 0, there is no section to close, so the program will just keep running
 * until the last token, but that is MOSTLY fine since files don't contain thousand of empty lines
 * after its actual end, right?
 */

Lucie::Decoder::ValueHolder* Lucie::Decoder::RecursiveSectionizerParser(
    Lucie::Decoder::SectionizerState* sectionizer_state,
    const Lucie::U8 depth
)
{
    Lucie::Decoder::Section* branch = new Lucie::Decoder::Section;
    Lucie::U16 order = 0;
    
    while(sectionizer_state->token_index < sectionizer_state->token_amount)
    {
        /* NOTE: before adquiring the token, check for the validator, if the state still 
         * consistent, then keep parsing, if not, then give up:
         */
        if(sectionizer_state->validator.error != 0)
            break;

        /* If everything is fine, then keep parsing: */
        const Lucie::String token = Lucie::Decoder::SectionizerStateGetToken(sectionizer_state);
        if(token == "section")
        {
            const Lucie::String name = Lucie::Decoder::SectionizerStateGetToken(sectionizer_state);
            Lucie::Decoder::ValueHolder* branched_section = 
                Lucie::Decoder::RecursiveSectionizerParser(sectionizer_state, depth + 1);
            branch->insert({name, branched_section});
            order++;
        }
        else if(token == "end")
        {
            /* DONE, quit the loop: */
            break;
        }
        else if(token == "set")
        {
            const Lucie::String name = Lucie::Decoder::SectionizerStateGetToken(sectionizer_state);
            Lucie::Decoder::ValueHolder* value = 
                Lucie::Decoder::RecursiveSectionizerParserGetValue(sectionizer_state, 0);
            branch->insert({name, value});
            order++;
        }
        else
        {
            Lucie::Decoder::SectionizerValidatorReportError(
                &sectionizer_state->validator,
                "Invalid Token = \"" + token + "\""
            );
            break;
        }
    }

    /* DONE: */
    Lucie::Decoder::ValueHolder* branch_value_holder =
        Lucie::Decoder::ValueHolderCreateNewFromSection(branch);
    branch_value_holder->order = order;
    return branch_value_holder;
}

Lucie::Decoder::ValueHolder* Lucie::Decoder::RecursiveSectionizerParserBegin(
    Lucie::Decoder::SectionizerState* sectionizer_state
)
{
    /* According the the Lucie Specifications; You can't define any data outside an initial section
     * so, everything must be inside an section.
     */
    return Lucie::Decoder::RecursiveSectionizerParser(sectionizer_state, 0);
}

/*
 * LOAD FILE & LOAD BUFFER:
 */

Lucie::Decoder::ValueHolder* Lucie::Decoder::RecursiveSectionizerLoadFromBuffer(
    const Lucie::String                 buffer,
    Lucie::Decoder::SectionizerState*   sectionizer_state
)
{
    /* tokenize the buffer: */
    Lucie::Text::Tokenizer* tokenizer = Lucie::Text::TokenizerNew();
    Lucie::Text::TokenizerInit(tokenizer);
    Lucie::Text::TokenizerFeed(tokenizer, buffer);
    
    /* begin the construction of the tree: */
    sectionizer_state->tokens = &tokenizer->tokens;
    sectionizer_state->token_amount = tokenizer->tokens.size();

    Lucie::Decoder::ValueHolder* built_section =
        Lucie::Decoder::RecursiveSectionizerParserBegin(sectionizer_state);

    Lucie::Text::TokenizerDestroy(tokenizer);
    return built_section;
}

#include <fstream>
#include <sstream>

Lucie::Decoder::ValueHolder* Lucie::Decoder::RecursiveSectionizerLoadFromFile(
    const Lucie::String path,
    Lucie::Decoder::SectionizerState* sectionizer_state
)
{
    std::ostringstream  buffer;
    std::ifstream       input(path);
    buffer              << input.rdbuf();

    /* with the buffer, proceed to read: */
    return Lucie::Decoder::RecursiveSectionizerLoadFromBuffer( buffer.str(), sectionizer_state);
}

Lucie::Decoder::ValueHolder* Lucie::Decoder::RecursiveSectionizerGet(
    Lucie::Decoder::ValueHolder* value_holder,
    const Lucie::String path
)
{
    std::vector<Lucie::String> split_path;
    Lucie::String accumulator;
    for(Lucie::U32 index=0; index<path.size(); index++)
    { 
        const Lucie::Character ch = path.at(index);
        if(ch == '.')   { split_path.push_back(accumulator); accumulator.clear();   }
        else            { accumulator.push_back(ch);                                }
    }
    if(accumulator.size() > 0) split_path.push_back(accumulator);
    return Lucie::Decoder::RecursiveSectionizerGet( value_holder, &split_path );
}

static Lucie::Decoder::ValueHolder* __RecursiveSectionGet(
    Lucie::Decoder::ValueHolder*        current_value,
    const std::vector<Lucie::String>*   path,
    const Lucie::U8                     depth
)
{
    Lucie::Decoder::ValueHolder* value = nullptr;
    if(current_value->type == Lucie::Decoder::ValueHolderTypes::Branch)
    {
        Lucie::Decoder::Section* current_section =
            (Lucie::Decoder::Section*)(current_value->value);
        const Lucie::String desired_branch = path->at(depth);
        if(current_section->find(desired_branch) != current_section->end())
        {
            /* when depth < path->size() - 1 is true, then: the end of the list. */
            if(depth >= path->size() - 1)
                value = current_section->at(desired_branch);
            else
                value = __RecursiveSectionGet(
                    current_section->at(desired_branch),
                    path,
                    depth + 1
                );
        }
    }
    return value;
}

Lucie::Decoder::ValueHolder* Lucie::Decoder::RecursiveSectionizerGet(
    Lucie::Decoder::ValueHolder* value_holder,
    const std::vector<Lucie::String>* path
)
{
    /* NOTE: expect the first to be at least an section. */
    return __RecursiveSectionGet(
        value_holder,
        path,
        0
    );
}