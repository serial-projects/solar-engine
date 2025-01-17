#include "Logica/Texting/Tokenizer/Rules.hpp"

Logica::Texting::Tokenizer::Rules::Rules()
{
    /* Initialize some functions: */
    this->is_token_delimiter 
        = Logica::Texting::Tokenizer::RulesFunctions::IsTokenDelimiter();
    this->is_token_string_delimiter
        = Logica::Texting::Tokenizer::RulesFunctions::IsTokenStringDelimiter();
    this->is_token_highlight
        = Logica::Texting::Tokenizer::RulesFunctions::IsTokenToHighlight();
    
    /* NEXT: set the token hints: */
    this->comment_starter =
        '#';
    this->comment_single_line_hint =
        0;
    this->comment_delimited_hint =
        '*';
}
