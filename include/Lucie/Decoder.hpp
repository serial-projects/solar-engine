#ifndef LucieDecoder_hpp
#define LucieDecoder_hpp

#include "Lucie/Types.hpp"
#include "Lucie/Text.hpp"

namespace Lucie
{
    namespace Decoder
    {
        /* SINGLE TABLE SECTIONIZER: */
        
        /*
         * NOTE: An simple table sectionizer is fast and honestly enough for most of the Solar Engine
         * needs, there is no need for fancy recursion and that stuff since Solar doesn't write any
         * configuration back (it is written in binary on the save file, but that file is not Lucie
         * anymore).
         */

        typedef Lucie::String SingleTableSectionizerKey;
        typedef Lucie::PackedData8 SingleTableSectionizerValueHolderType;

        typedef struct SingleTableSectionizerValidator
        {
            Lucie::U8       state = 0;
            Lucie::U32      line;
            Lucie::String   report;
        } SingleTableSectionizerValidator;

        typedef struct SingleTableSectionizerValueHolder
        {
            void *value;
            Lucie::Decoder::SingleTableSectionizerValueHolderType type = 0;
        } SingleTableSectionizerValueHolder;

        typedef std::vector<Lucie::Decoder::SingleTableSectionizerValueHolder*> SingleTableSectionizerValueHolderList;

        void SingleTableSectionizerValueHolderDestroy(Lucie::Decoder::SingleTableSectionizerValueHolder* value_holder);
        Lucie::String SingleTableSectionizerValueHolderToString(Lucie::Decoder::SingleTableSectionizerValueHolder* value_holder);

        enum SingleTableSectionizerValueHolderTypes
        {
            Integer         = 0,
            Decimal,
            String,
            Boolean,
            List,
            Section
        };

        typedef std::unordered_map<
            Lucie::Decoder::SingleTableSectionizerKey,
            Lucie::Decoder::SingleTableSectionizerValueHolder*
        > SingleTableSectionizedContent;

        Lucie::Decoder::SingleTableSectionizedContent* SingleTableSectionizer(
            Lucie::Text::Tokens*                                tokens,
            Lucie::Decoder::SingleTableSectionizerValidator*    validator,
            const Lucie::Character                              separator
        );


        void SingleTableSectionizedContentDestroy(Lucie::Decoder::SingleTableSectionizedContent* content);

    };
};

#endif