#ifndef LogicaTextingTokenizerInstance_hpp
#define LogicaTextingTokenizerInstance_hpp

#include "Logica/Types.hpp"
#include "Logica/Control/Validator.hpp"
#include "Logica/Texting/Tokenizer/Rules.hpp"

namespace Logica
{
    namespace Texting
    {
        namespace Tokenizer
        {
            /// @brief All the status of the tokenizer.
            namespace InstanceStatus
            {
                enum InstanceStatus
                {
                    /// @brief Tokenizer has not finished (EOF not reached);
                    Running = 0,

                    /// @brief EOF was reached;
                    Finished,

                    /// @brief Something bad happened.
                    Died
                };
            };

            /// @brief All the instance error codes.
            namespace InstanceErrorCodes
            {
                enum InstanceErrorCodes
                {
                    /// @brief No errors.
                    Ok = 0,
                    
                    /// @brief When consider_eof is false and a EOF is found.
                    EarlyEndOfLine,

                    /// @brief When a string ends early by EOF.
                    BadString,

                    /// @brief When a comment is bad formed.
                    BadComment,

                    /// @brief Impossible errors.
                    Unknown = UINT8_MAX
                };
            };

            /// @brief This is actually an machine that has states and will tokenize until the      \a
            /// end of the buffer is reached. That means the tokenizer CAN'T go back which is       \a
            /// quite a bummer BUT it is simpler that way.
            class Instance
            {
                private:
                    Logica::Texting::Tokenizer::Rules* rules;
                    Logica::Types::Buffer::Base* buffer;
                    Logica::Types::Basic::U8 state;

                    /* GetDelimited Token/String */
                    inline Logica::Types::Basic::String __GetDelimitedToken(const Logica::Types::Basic::I32 starter);
                    inline Logica::Types::Basic::String __GetDelimitedString(const Logica::Types::Basic::I32 starter);
                    inline Logica::Types::Basic::CH8 __GetEscapeCharacter();

                    /* Determine/Proceed/Waste Comment Functions: */
                    inline void __DetermineCommentTypeAndWasteComment(const Logica::Types::Basic::I32 comment_type_hint);
                    inline void __DetermineLineCommentTypeAndWasteComment(const Logica::Types::Basic::I32 comment_type_hint);
                    inline void __ProceedLineCommentUsingRuleSingleLineCommentHint(const Logica::Types::Basic::I32 comment_type_hint);
                    inline void __WasteLineComment();
                    inline void __WasteDelimitedComment();

                    /* MISC. EOF and Buffer Rewind: */
                    inline void __TreatEOF(Logica::Types::Basic::Boolean consider_eof);
                    inline void __RewindBuffer(const Logica::Types::Basic::U8 amount);

                    /// @brief Get the character and consider '\n' already to be counted on the line_counter.
                    /// @return return an character from the buffer.
                    inline Logica::Types::Basic::I32 __GetCharacter();
                    
                    /// @brief max_position_ever as the name implies is the maximum position the
                    /// buffer has ever reached, this is useful to avoid '\n' repeating or some
                    /// other character we MIGHT want to count.
                    Logica::Types::Basic::U32 max_position_ever;

                    /// @brief Counter for the lines.
                    Logica::Types::Basic::U32 line_counter;
                public:
                    /// @brief Holds the errors that might arrive when tokenizing!
                    Logica::Control::Validator validator;
                    
                    /// @brief Builds the tokenizer:
                    Instance();

                    /// @brief Get the current line the tokenizer is.
                    /// @return the line from 1 to UINT32_MAX.
                    Logica::Types::Basic::U32 GetCurrentLine();

                    /// @brief Set the rules.
                    /// @param rules the rules pointer.
                    void SetRules(Logica::Texting::Tokenizer::Rules* rules);

                    /// @brief Set the buffer (can be FileBuffer, StringBuffer, etc);
                    /// @param buffer the buffer pointer.
                    void SetBuffer(Logica::Types::Buffer::Base* buffer);

                    /// @brief Returns the state the instance is
                    /// @return the state (an Logica::Texting::Tokenizer::InstanceStatus value).
                    Logica::Types::Basic::U8 GetState();

                    /// @brief Returns a single token.
                    /// @param consider_eof if EOF is to be considered or not expected.
                    /// @return the token that was adquired (empty when Died or Finished).
                    Logica::Types::Basic::String GetToken(Logica::Types::Basic::Boolean consider_eof);
            };
        };
    };
};

#endif