#ifndef SojsonDecodeInstance_hpp
#define SojsonDecodeInstance_hpp

#include "Logica/Logica.hpp"
#include "Sojson/Types.hpp"
#include "Sojson/Node.hpp"

namespace Sojson
{
    namespace Decode
    {
        /// @brief Contains all the possible states the instance can be.
        namespace InstanceStates
        {
            enum InstanceStates
            {
                /// @brief The tokenizer is running.
                Running = 0,

                /// @brief The tokenizer had finished properly.
                Finished,

                /// @brief The tokenizer didn't finish and the validator should be considered.
                Died,

                /// @brief Impossible code reaches, something probably got very wrong here.
                Unknown = UINT8_MAX
            };
        };

        namespace InstanceErrors
        {
            enum InstanceErrors
            {
                /// @brief No errors.
                Ok = 0,

                /// @brief When the syntax is not alright :D
                SyntaxError,

                /// @brief Unexpected closures, like [0, 0,] <-- where is the next value? got
                /// closure instead of value, that applies for tables that {"value": 0, } <-- see,
                /// no value here.
                InvalidClosure,

                /// @brief When an key is bad like: 'hey' or hey (which out the quotes).
                BadKey,

                /// @brief For when the tokenizer ends before finishing an object (that is, closing
                /// the actual object), example: [0, 0, 1 ... <EOF> (at EOF, the tokenizer stops).
                PrematureEnd,

                /// @brief For when an object expects some value, like {, ...} <-- on the beginning
                /// it is expected an value, but got nothing!
                ExpectedValue,

                /// @brief When a key is already present on the node, for example: 
                /// {"A": 0, ..., "A": 10} <-- in this case the table already had the element A.
                DuplicatedKey,
            };
        };

        /// @brief The parser instance.
        struct Instance
        {
            Logica::Texting::Tokenizer::Instance current_tokenizer;
            Logica::Texting::Tokenizer::Rules current_tokenizer_rules;
            Logica::Control::Validator validator;
            Sojson::Types::U8 state;
        };

        /// @brief Returns an new instance (not on heap, this is just for the style).
        /// @return the new instance.
        Sojson::Decode::Instance InstanceNew();

        /// @brief Destroys an instance (doesn't do anything, you need to destroy the buffer yourself).
        /// @param instance the instance to be "destroyed"
        void InstanceDestroy(Sojson::Decode::Instance* instance);

        /// @brief Initializes the instance and prepares for tokenizer.
        /// @param instance the instance to initialize.
        /// @param buffer the buffer to be the source to the tokenizer.
        void InstanceInit(Sojson::Decode::Instance* instance, Logica::Types::Stream::Buffer* buffer);

        /// @brief Parses the whole inputed buffer (check for the validator for errors)
        /// @param instance the instance to do the parsing.
        /// @return the created node, use Sojson::NodeDestroy() to free it from memory.
        Sojson::Node* InstanceParse(Sojson::Decode::Instance* instance);
    };
};

#endif