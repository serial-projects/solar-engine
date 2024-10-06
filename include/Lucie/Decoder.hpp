#ifndef LucieDecoder_hpp
#define LucieDecoder_hpp

#include "Lucie/Types.hpp"
#include "Lucie/Text.hpp"

namespace Lucie
{
    namespace Decoder
    {

        /* NOTE: this is an STACK object: */

        typedef struct SectionizerValidator
        {
            Lucie::String   log;
            Lucie::U8       error;
        } SectionizerValidator;

        Lucie::Decoder::SectionizerValidator SectionizerValidatorNew();
        void SectionizerValidatorReportError(Lucie::Decoder::SectionizerValidator* validator, const Lucie::String reason);

        typedef struct SectionizerState
        {
            Lucie::Decoder::SectionizerValidator validator;
            Lucie::Text::Tokens* tokens;
            Lucie::U64 token_index;
            Lucie::U64 token_amount;
            Lucie::U32 current_line;
        } SectionizerState;
        Lucie::Decoder::SectionizerState SectionizerStateNew();
        Lucie::String SectionizerStateGetToken(Lucie::Decoder::SectionizerState* sectionizer_state);
        Lucie::String SectionizerStatePretendGetToken(Lucie::Decoder::SectionizerState* sectionizer_state);

        /* Recursive Hell: */
        enum ValueHolderTypes
        {
            Integer     = 0,
            Decimal,
            String,
            Boolean,
            List,
            Branch
        };

        typedef struct ValueHolder
        {
            void            *value;
            Lucie::U8       type;
            Lucie::U16      order;
        } ValueHolder;

        /* section contains ValueHolder(s) and that value holders can hold more sections: */
        typedef std::unordered_map<Lucie::String, Lucie::Decoder::ValueHolder*> Section;
        typedef std::vector<Lucie::Decoder::ValueHolder*> ValueHolderList;

        Lucie::Decoder::ValueHolder* ValueHolderCreateNewFromSection(Lucie::Decoder::Section* section);
        Lucie::Decoder::ValueHolder* ValueHolderNew(Lucie::Integer value);
        Lucie::Decoder::ValueHolder* ValueHolderNew(Lucie::Decimal value);
        Lucie::Decoder::ValueHolder* ValueHolderNew(Lucie::String value);
        Lucie::Decoder::ValueHolder* ValueHolderNew(Lucie::Boolean value);
        Lucie::Decoder::ValueHolder* ValueHolderNew(Lucie::Decoder::ValueHolderList* value);

        Lucie::String ValueHolderPrint(Lucie::Decoder::ValueHolder* value_holder, const Lucie::U8 depth);
        Lucie::String ValueHolderBranchShow(Lucie::Decoder::ValueHolder* value_holder, const Lucie::U8 depth);
        void ValueHolderDestroy(Lucie::Decoder::ValueHolder* value_holder);

        /* begin parsing: */
        Lucie::Decoder::ValueHolder* RecursiveSectionizerParserGetValue(Lucie::Decoder::SectionizerState* sectionizer_state, const Lucie::U8 depth);
        Lucie::Decoder::ValueHolder* RecursiveSectionizerParser(Lucie::Decoder::SectionizerState* sectionizer_state, const Lucie::U8 depth);
        Lucie::Decoder::ValueHolder* RecursiveSectionizerParserBegin(Lucie::Decoder::SectionizerState* sectionizer_state);

        /* Load Files & Load From Buffer: */
        Lucie::Decoder::ValueHolder* RecursiveSectionizerLoadFromBuffer(const Lucie::String buffer, Lucie::Decoder::SectionizerState* sectionizer_state);
        Lucie::Decoder::ValueHolder* RecursiveSectionizerLoadFromFile(const Lucie::String path, Lucie::Decoder::SectionizerState* sectionizer_state);
        
        /* NOTE: get function: */
        Lucie::Decoder::ValueHolder* RecursiveSectionizerGet(Lucie::Decoder::ValueHolder* value_holder, const Lucie::String path);
        Lucie::Decoder::ValueHolder* RecursiveSectionizerGet(Lucie::Decoder::ValueHolder* value_holder, const std::vector<Lucie::String>* path);
    };
};

#endif