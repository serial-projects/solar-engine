#ifndef SojsonDecodeInstance_hpp
#define SojsonDecodeInstance_hpp

#include "Sojson/Types.hpp"
#include "Logica/Logica.hpp"
#include "Sojson/Decorators.hpp"

namespace Sojson
{
    namespace Decode
    {
        
        class Instance
        {
            private:
            Logica::Texting::Tokenizer::Instance    tokenizer_instance;
            Logica::Texting::Tokenizer::Rules       tokenizer_rules;

            /* GetRootValue() */
            SOJSON_NODISCARD
            Sojson::Node* GetRootValue();
            
            /* GetValue(): */
            SOJSON_NODISCARD
            Sojson::Node* GetValue(
                Logica::Types::Basic::String& key,
                const Logica::Types::Basic::U8 depth
            );

            /* GetBasicValue() */
            SOJSON_NODISCARD
            Sojson::Node* GetBasicValue(Logica::Types::Basic::String& key);
            
            /* GetList() */
            SOJSON_NODISCARD
            Sojson::Types::Basic::Result GetValueAndPushBackToList(
                Sojson::Node::List* building_list,
                Sojson::Types::Basic::U8 depth
            );
            
            SOJSON_NODISCARD
            Sojson::Node* GetList(
                const Logica::Types::Basic::U8 depth
            );

            /* GetTable() */
            SOJSON_NODISCARD
            Sojson::Types::Basic::Result GetValueFromTableOnTheFirstValue(
                Sojson::Node::Table* building_table,
                Sojson::Types::Basic::U8 depth
            );

            SOJSON_NODISCARD
            Sojson::Types::Basic::Result GetValueFromTableOnTheMiddleAndEndValue(
                Sojson::Node::Table* building_table,
                Sojson::Types::Basic::U8 depth
            );

            SOJSON_NODISCARD
            Sojson::Node* GetTable(const Logica::Types::Basic::U8 depth);

            public:
            Instance();

            /**
             * \brief Contains all the possible states for the instance.
             */
            enum States
            {
                RUNNING         = 0,
                FINISHED,
                DIED
            };
            Sojson::Decode::Instance::States state;

            /**
             * \brief Contains all the error to the validator:
             */
            enum Errors
            {
                NO                      = 0,
                INVALID_TOKEN,
                INVALID_SYNTAX,
                TABLE_INVALID_KEY,
                TABLE_LACKS_SPLIT,
                TABLE_KEY_REDEFINITION,
                PREMATURE_END
            };

            /**
             * \brief Validator to hold any errors that might arrive with:
             */
            Logica::Control::Validator validator;
            
            /**
             * \brief The buffer is the common source to where the code will be pumped
             * you must specify one.
             */
            void SetBuffer(Logica::Types::Stream::Buffer* buffer);

            /**
             * \brief Parse the buffer you specified.
             */
            SOJSON_NODISCARD
            Sojson::Node* Parse();

            /**
             * \brief Get the state of the tokenizer.
             * \returns The state of the tokenizer.
             */
            Sojson::Decode::Instance::States GetState();
        };
    }
};

#endif